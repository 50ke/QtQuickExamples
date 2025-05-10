import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick3D
import QtQuick3D.Helpers
import PointCloud 1.0
import QtQuick.Dialogs

ApplicationWindow {
    width: 800
    height: 600
    visible: true

    menuBar: MenuBar {
        Menu {
            title: qsTr("文件")
            Action {
                text: qsTr("打开")
                onTriggered: fileDialog.open()
            }
        }
    }

    FileDialog {
            id: fileDialog
            title: qsTr("选择点云文件")
            nameFilters: ["TXT 文件 (*.txt)", "所有文件 (*)"]
            onAccepted: {
                pointCloud.loadFromFile(selectedFile) // 调用点云加载方法
            }
        }

    View3D {
        anchors.fill: parent

        environment: SceneEnvironment {
            clearColor: "#1a1a1a"
            backgroundMode: SceneEnvironment.Color
        }

        PerspectiveCamera {
            id: camera
            position: Qt.vector3d(0, 50, 100)
            eulerRotation.x: -30
        }

        Model {
            geometry: PointCloudGeometry {
                id: pointCloud
            }
            materials: [
                PrincipledMaterial {
                    vertexColorsEnabled: true
                    lighting: PrincipledMaterial.NoLighting
                }
            ]
        }

        OrbitCameraController {
            origin: camera
            camera: camera
            anchors.fill: parent
        }
    }
}
