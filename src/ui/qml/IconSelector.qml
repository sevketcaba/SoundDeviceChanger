import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "../js/fontawesome.js" as FontA
Rectangle {
    id: iconSelector
    border.width: 1
    border.color: "gray"
    color: "black"

    signal iconSelected(string icon)
    signal iconSelectionCanceled()

    property string customText: txtEdit.text

    function show()  {
        txtEdit.text = ""
        opacity = 1
    }

    Rectangle {
        id: rectCustom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: 15*Screen.pixelDensity
        clip: true
        anchors.margins: 1
        color: "black"
        opacity: busyRect.visible ? .4 : 1
        enabled: !busyRect.visible

        Rectangle {
            id: btnBack
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            width: height
            clip: true
            anchors.margins: 1
            color: "black"
            TextEdit {
                text: "\uf0a8"
                anchors.fill: parent
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                color: maBack.containsMouse ? "white" : "silver"
                font.family: "FontAwesome"
                font.pointSize: 18
            }
            MouseArea {
                id: maBack
                hoverEnabled: true
                anchors.fill: parent
                onClicked: iconSelector.iconSelectionCanceled()
            }
        }
        Rectangle {
            id: searchRect
            anchors.top: parent.top
            anchors.right: btnDownload.left
            anchors.bottom: parent.bottom
            anchors.left: btnBack.right
            clip: true
            anchors.margins: 5
            color: "black"
            border.color: "silver"
            border.width: 1
            radius: 5
            TextEdit {
                id: txtEdit
                text: ""
                anchors.fill: parent
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                color: "white"
                font.family: "FontAwesome"
                font.pointSize: 14
            }
        }
        Rectangle {
            id: btnDownload
            anchors.top: parent.top
            anchors.right: btnSend.left
            anchors.bottom: parent.bottom
            width: height
            clip: true
            anchors.margins: 1
            color: "black"
            TextEdit {
                text: "\uf0ed"
                anchors.fill: parent
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                color: maDownload.containsMouse ? "white" : "silver"
                font.family: "FontAwesome"
                font.pointSize: 18
            }
            MouseArea {
                id: maDownload
                hoverEnabled: true
                anchors.fill: parent
                onClicked: {
                    fontDatabase.reload()
                }
            }
        }
        Rectangle {
            id: btnSend
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            width: height
            clip: true
            anchors.margins: 1
            color: "black"
            enabled: txtEdit.text.length == 0 || txtEdit.text.length == 4
            TextEdit {
                text: "\uf058"
                anchors.fill: parent
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                color: btnSend.enabled
                       ? maSend.containsMouse ? "white" : "silver" : "gray"
                font.family: "FontAwesome"
                font.pointSize: 18
            }
            MouseArea {
                id: maSend
                hoverEnabled: true
                anchors.fill: parent
                onClicked: {
                    iconSelector.iconSelected(txtEdit.text)
                }
            }
        }
    }

    Rectangle {
        id: rectTable
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: rectCustom.bottom
        anchors.bottom: parent.bottom
        clip: true
        anchors.margins: 1
        color: "black"
        opacity: busyRect.visible ? .4 : 1
        enabled: !busyRect.visible

        ListView {
            anchors.fill: parent
            delegate: Rectangle {
                anchors.left: parent.left
                anchors.right: parent.right
                height: model.modelData.name.indexOf(txtEdit.text) >= 0 || model.modelData.code.indexOf(txtEdit.text) >= 0 ? 40 : 0
                visible: height > 0
                clip: true
                Behavior on height {
                    NumberAnimation { duration: 200 }
                }

                color: "black"

                Rectangle {
                    id: bg
                    anchors.fill: parent
                    anchors.margins: 5
                    color: maItem.containsMouse ? "gray" : "black"
                }

                Item {
                    id: icon
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    width: 40
                    anchors.margins: 5

                    Text {
                        anchors.fill: parent
                        text: model.modelData.icon
                        horizontalAlignment: Qt.AlignHCenter
                        verticalAlignment: Qt.AlignVCenter
                        color: "white"
                        font.family: "FontAwesome"
                        font.pointSize: 18
                    }
                }
                Item {
                    id: code
                    anchors.left: icon.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    width: 80
                    anchors.margins: 5

                    Text {
                        anchors.fill: parent
                        text: model.modelData.code
                        horizontalAlignment: Qt.AlignHCenter
                        verticalAlignment: Qt.AlignVCenter
                        color: "white"
                        font.family: "FontAwesome"
                        font.pointSize: 14
                    }
                }
                Item {
                    id: name
                    anchors.left: code.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    anchors.margins: 5

                    Text {
                        anchors.fill: parent
                        text: model.modelData.name
                        horizontalAlignment: Qt.AlignLeft
                        verticalAlignment: Qt.AlignVCenter
                        color: "white"
                        font.family: "FontAwesome"
                        font.pointSize: 14
                        elide: Text.ElideLeft
                    }
                }

                Rectangle {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    height: 1
                    color: "silver"
                    anchors.leftMargin: 10
                    anchors.rightMargin: 10
                }

                ToolTip.text: model.modelData.name
                ToolTip.visible: maItem.containsMouse

                MouseArea {
                    id: maItem
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: iconSelector.iconSelected(model.modelData.code)
                }
            }
            model: fontDatabase.fontData
        }

//        GridLayout {
//            columns: 5
//            id: gridView
//            clip: true
//            anchors.fill: parent
//            anchors.margins: 1

//            Repeater {
//            Rectangle {
//                id: iconCell
//                property string icon: model.modelData.icon //FontA.CharUTF8[model.index]
//                property string name: model.modelData.name //Object.keys(FontA.Icon).filter(function(key) {return FontA.Icon[key] === icon})[0];  //(_.invert(FontA.Icon))[icon] //Object.entries(FontA.Icon)[model.index]//[0]
//                property bool filtered: customText == ""
//                                        ? true
//                                        : name.indexOf(customText) >= 0 || icon.indexOf(customText) >= 0
//                                          ? true
//                                          : false

//                width: filtered ? 80 : 0
//                height: filtered ? width : 0
//                color: "black"
//                border.width: 1
//                border.color: "gray"
//                clip: true
//                visible: width > 0

//                Behavior on width  {
//                    NumberAnimation { duration: 200 }
//                }
//                Behavior on height {
//                    NumberAnimation { duration: 200 }
//                }

//                Text {
//                    id: iconText
//                    anchors.fill: parent
//                    text: iconCell.icon
//                    horizontalAlignment: Qt.AlignHCenter
//                    verticalAlignment: Qt.AlignVCenter
//                    color: "white"
//                    font.family: "FontAwesome"
//                    font.pointSize: 18
//                }

//                MouseArea {
//                    id: rectMouse
//                    anchors.fill: parent
//                    hoverEnabled: true
//                    onClicked: iconSelector.iconSelected(iconText.text)
//                }

//                ToolTip {
//                    text: iconCell.name
//                    visible: rectMouse.containsMouse
//                }
//            }
//            model: fontDatabase.fontData //FontA.CharUTF8.length
//            }
//        }
    }

    Rectangle {
        id: busyRect
        anchors.centerIn: parent
        width: 400
        height: 80
        visible: fontDatabase.busyMessage.length > 0
        color: "black"
        border.width: 1
        border.color: "white"

        BusyIndicator {
            id: busyInd
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: height
            anchors.margins: 10
        }

        Text {
            anchors.left: busyInd.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            font.pointSize: 18
            font.family: "FontAwesome"
            color: "white"
            text: fontDatabase.busyMessage
        }
    }
}
