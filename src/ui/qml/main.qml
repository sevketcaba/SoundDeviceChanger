import QtQuick 2.0
import QtQuick.Window 2.0
import "../js/fontawesome.js" as FontAw
import "../js/fontawesomearray.js" as FontA

Rectangle {
    id: root
    width: 540
    height: 960
    color: "black"

    property bool showHidden: false
    property string iconId: ""

    Rectangle {
        id: topBar
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 15*Screen.pixelDensity
        border.width: 1
        border.color: "gray"
        color: "black"

        Item {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: 40 * Screen.pixelDensity
            anchors.margins: 2

            Rectangle {
                id: chkRect
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: height
                anchors.margins: 4*Screen.pixelDensity
                color: "black"
                border.width: 1
                border.color: "gray"
            }
            Rectangle {
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: height
                radius: width
                anchors.margins: 6*Screen.pixelDensity
                color: "white"
                opacity: showHidden ? 1 : 0
                visible: opacity > 0
                Behavior on opacity {
                    NumberAnimation { duration: 200 }
                }
            }

            Text {
                text: "Show Hidden"
                anchors.left: chkRect.right
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                color: showHidden ? "white" : "gray"
                style: Text.Sunken
                font.pointSize: 10
                font.bold: true
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }

            MouseArea {
                anchors.fill: parent
                onClicked: showHidden = !showHidden
            }

        }
    }

    ListView {
        id: deviceList
        enabled: !iconSelector.visible
        anchors.top: topBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: Screen.pixelDensity
        model: deviceManager.devices
        clip: true
        spacing: 1
        delegate : Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            height: model.modelData.isHidden
                        ? showHidden
                            ? 15*Screen.pixelDensity
                            : 0
                        : 15*Screen.pixelDensity
            anchors.margins: 1
            visible: height > 0
            border.width: 1
            border.color: "gray"
            color: "black"
            clip: true

            Behavior on height {
                NumberAnimation { duration: 200 }
            }

            Rectangle {
                id: iconRect
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.margins: 1
                width: height
                color: "black"
                border.width: 1
                border.color: "gray"

                Text {
                    id: iconText
                    anchors.fill: parent
                    text: model.modelData.icon.length == 1
                          ? model.modelData.icon
                          : model.modelData.icon.length == 0
                            ? ""
                            : (FontA.IconArray[model.modelData.icon] == undefined)
                                ? "undefined : " + model.modelData.icon
                                : FontA.IconArray[model.modelData.icon]
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    color: model.modelData.isActive ? "white" : "gray"
                    font.family: "FontAwesome"
                    font.pointSize: 18
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        root.iconId = model.modelData.id
                        iconSelector.opacity = 1
                    }
                }
            }
            Rectangle {
                id: iconHidden
                anchors.left: iconRect.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.margins: 1
                width: showHidden ? height : 0
                color: "black"
                border.width: 1
                border.color: "gray"
                clip: true


                Text {
                    id: iconVisible
                    anchors.fill: parent
                    //                    anchors.left: parent.left
                    //                    anchors.top: parent.top
                    //                    anchors.bottom: parent.bottom
                    //                    width: height
                    text: model.modelData.isHidden ? "\uf070" : "\uf06e"
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    color: model.modelData.isActive ? "white" : "gray"
                    font.family: "FontAwesome"
                    font.pointSize: 18
                }

//                Rectangle {
//                    anchors.left: parent.left
//                    anchors.top: parent.top
//                    anchors.bottom: parent.bottom
//                    width: height
//                    radius: width
//                    anchors.margins: 6*Screen.pixelDensity
//                    color: "white"
//                    opacity: model.modelData.isHidden ? 0 : 1
//                    visible: opacity > 0
//                    Behavior on opacity {
//                        NumberAnimation { duration: 200 }
//                    }
//                }

                MouseArea {
                    anchors.fill: parent
                    enabled: !model.modelData.isActive
                    onClicked: deviceManager.setDeviceHidden(model.modelData.id, !model.modelData.isHidden)
                }

                Behavior on width {
                    NumberAnimation { duration: 200 }
                }
            }

            Text {
                id: name
                text: model.modelData.name
                anchors.left: showHidden ? iconHidden.right : iconRect.right
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                color: model.modelData.isActive ? "white" : "gray"
                style: Text.Sunken
                font.pointSize: 14
                font.bold: true
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere

                MouseArea {
                    anchors.fill: parent
                    enabled: !model.modelData.isHidden
                    onDoubleClicked: {
                        deviceManager.setDeviceActive(model.modelData.id)
                    }
                }
            }
        }
    }

    IconSelector {
        id: iconSelector
        anchors.centerIn: parent
        width: 440
        height: 860
        opacity: 0
        visible: opacity > 0
        Behavior on opacity {
            NumberAnimation { duration: 200 }
        }
        onIconSelected: {
            deviceManager.setDeviceIcon(root.iconId, icon)
            iconSelector.opacity = 0
        }
        onIconSelectionCanceled: {
            root.iconId = ""
            iconSelector.opacity = 0
        }
    }

    FontLoader {
        name: "FontAwesome"
        source: "qrc:/ui/font/fontawesome-webfont.ttf"
    }

}
