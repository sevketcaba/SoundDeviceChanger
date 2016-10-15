import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import "../js/fontawesome.js" as FontA
Rectangle {
    id: iconSelector
    border.width: 1
    border.color: "gray"
    color: "black"

    signal iconSelected(string icon)
    signal iconSelectionCanceled()


    Rectangle {
        id: rectCustom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: 15*Screen.pixelDensity
        clip: true
        anchors.margins: 1
        color: "black"
        Rectangle {
            anchors.top: parent.top
            anchors.right: btnSend.left
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            clip: true
            anchors.margins: 1
            color: "black"
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
            id: btnSend
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            width: height
            clip: true
            anchors.margins: 1
            color: "black"
            TextEdit {
                text: "\uf058"
                anchors.fill: parent
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                color: "white"
                font.family: "FontAwesome"
                font.pointSize: 14
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    iconSelector.iconSelected(txtEdit.text)
                }
            }
        }
    }

    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: rectCustom.bottom
        anchors.bottom: btnBack.top
        clip: true
        anchors.margins: 1
        color: "black"

        GridView {
            id: gridView
            clip: true
            anchors.fill: parent
            anchors.margins: 1
            cellWidth: 80
            cellHeight: cellWidth
            delegate: Column {
                Rectangle {
                    width: 80
                    height: width
                    color: "black"
                    border.width: 1
                    border.color: "gray"

                    Text {
                        id: iconText
                        anchors.fill: parent
                        text: FontA.CharUTF8[model.index]
                        horizontalAlignment: Qt.AlignHCenter
                        verticalAlignment: Qt.AlignVCenter
                        color: "white"
                        font.family: "FontAwesome"
                        font.pointSize: 18
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: iconSelector.iconSelected(iconText.text)
                    }
                }
            }
            model: FontA.CharUTF8.length
        }
    }

    Rectangle {
        id: btnBack
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: 15*Screen.pixelDensity
        clip: true
        anchors.margins: 1
        color: "black"
        Text {
            text: "\uf0e2"
            anchors.fill: parent
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            color: "white"
            font.family: "FontAwesome"
            font.pointSize: 14
        }
        MouseArea {
            anchors.fill: parent
            onClicked: iconSelector.iconSelectionCanceled()
        }
    }
}
