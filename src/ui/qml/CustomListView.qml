import QtQuick 2.0

ListView {
    id: listView

    Item {
        x: 0
        y: 0
        width: listView.orientation == Qt.Vertical ? listView.width : 10
        height: listView.orientation == Qt.Vertical ? 10 : listView.height
        visible: !listView.atYBeginning
        clip: true

        Text {
            anchors.fill: parent
            text: "\uf0d8"
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            font.pointSize: 14
            color: "white"
            style: Text.Outline
            font.family: "FontAwesome"
        }
    }

    Item {
        x: listView.orientation == Qt.Vertical ? 0 : listView.width - 10
        y: listView.orientation == Qt.Vertical ? listView.height - 10 : 0
        width: listView.orientation == Qt.Vertical ? listView.width : 10
        height: listView.orientation == Qt.Vertical ? 10 : listView.height
        visible: !listView.atYEnd
        clip: true

        Text {
            anchors.fill: parent
            text: "\uf0d7"
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            font.pointSize: 14
            color: "white"
            style: Text.Outline
            font.family: "FontAwesome"
        }
    }
}
