#ifndef POINTCLOUDGEOMETRY_H
#define POINTCLOUDGEOMETRY_H

#include <QObject>
#include <QtQuick3D/QQuick3DGeometry>
#include <QVector3D>
#include <QVariant>
#include <QColor>
#include <QFile>
#include <QTextStream>

class PointCloudGeometry : public QQuick3DGeometry
{
    Q_OBJECT
    QML_NAMED_ELEMENT(PointCloudGeometry)
public:
    explicit PointCloudGeometry();
    Q_INVOKABLE void loadFromFile(const QUrl &fileUrl);

public slots:
    void setPoints(const QVariantList &points, const QVariantList &intensities);

private:
    void updateData();
    QVector<QVector3D> m_points;
    QVector<float> m_intensities;
};

#endif // POINTCLOUDGEOMETRY_H
