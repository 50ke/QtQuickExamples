import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick3D
import QtQuick3D.Helpers
import PointCloud 1.0

Window {
    width: 800
    height: 600
    visible: true

    View3D {
        anchors.fill: parent

        environment: SceneEnvironment {
            clearColor: "#1a1a1a"
            backgroundMode: SceneEnvironment.Color
        }

        PerspectiveCamera {
            id: camera
            position: Qt.vector3d(0, 0, 50)
            eulerRotation.x: 30
        }

        Model {
            geometry: PointCloudGeometry {
                id: pointCloud
            }
            materials: [ PrincipledMaterial {
                vertexColorsEnabled: true
                lighting: PrincipledMaterial.NoLighting
            } ]
        }

        OrbitCameraController {
            origin: camera
            camera: camera
            anchors.fill: parent
        }

        Component.onCompleted: {
            // 生成测试数据（球面点云）
            let points = [];
            let intensities = [];
            const pointCount = 50000;

            for (let i = 0; i < pointCount; ++i) {
                // 球坐标系参数
                let radius = Math.random() * 15;
                let theta = Math.random() * Math.PI * 2;
                let phi = Math.random() * Math.PI;

                // 转换为笛卡尔坐标
                let x = radius * Math.sin(phi) * Math.cos(theta);
                let y = radius * Math.sin(phi) * Math.sin(theta);
                let z = radius * Math.cos(phi);

                points.push(Qt.vector3d(x, y, z));
                intensities.push(Math.random());
            }

            pointCloud.setPoints(points, intensities);
        }
    }
}
