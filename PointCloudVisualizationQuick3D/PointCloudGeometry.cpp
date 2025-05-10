#include "PointCloudGeometry.h"

PointCloudGeometry::PointCloudGeometry()
{
    setStride(6 * sizeof(float)); // 3 position + 3 color
    setPrimitiveType(QQuick3DGeometry::PrimitiveType::Points);

    addAttribute(Attribute::PositionSemantic, 0, Attribute::F32Type);
    addAttribute(Attribute::ColorSemantic, 3 * sizeof(float), Attribute::F32Type);
}

void PointCloudGeometry::loadFromFile(const QUrl &fileUrl){
    QString filePath = fileUrl.toLocalFile();
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "无法打开文件:" << filePath;
        return;
    }

    m_points.clear();
    m_intensities.clear();

    QTextStream in(&file);
    while(!in.atEnd()){
        QString line = in.readLine().trimmed();
        QStringList parts = line.split(" ", Qt::SkipEmptyParts);

        bool ok[4] = {false};
        float x = parts[0].toFloat(&ok[0]);
        float y = parts[1].toFloat(&ok[1]);
        float z = parts[2].toFloat(&ok[2]);
        float intensity = parts[3].toFloat(&ok[3]);
        m_points.append(QVector3D(x, y, z));
        m_intensities.append(intensity);
    }
    updateData();
}

void PointCloudGeometry::setPoints(const QVariantList &points, const QVariantList &intensities)
{
    // if (points.size() != intensities.size()) {
    //     qWarning("Points and intensities size mismatch!");
    //     return;
    // }

    // m_points.clear();
    // m_intensities.clear();

    // for (int i = 0; i < points.size(); ++i) {
    //     QVariant pointVar = points[i];
    //     if (pointVar.canConvert<QVector3D>()) {
    //         m_points.append(pointVar.value<QVector3D>());
    //     }

    //     QVariant intensityVar = intensities[i];
    //     bool ok;
    //     float intensity = intensityVar.toFloat(&ok);
    //     if (ok) m_intensities.append(intensity);
    // }

    // updateData();
}

void PointCloudGeometry::updateData()
{
    QByteArray vertexData;
    vertexData.resize(m_points.size() * 6 * sizeof(float));

    float *dataPtr = reinterpret_cast<float*>(vertexData.data());

    for (int i = 0; i < m_points.size(); ++i) {
        const QVector3D &point = m_points[i];
        float intensity = m_intensities[i];

        // 根据强度计算HSV颜色
        float hue = (1.0f - intensity) * 240.0f / 360.0f;
        QColor color;
        color.setHsvF(hue, 1.0, 1.0);

        // 填充位置数据
        *dataPtr++ = point.x();
        *dataPtr++ = point.y();
        *dataPtr++ = point.z();

        // 填充颜色数据
        *dataPtr++ = color.redF();
        *dataPtr++ = color.greenF();
        *dataPtr++ = color.blueF();
    }

    setVertexData(vertexData);
    update();
}
