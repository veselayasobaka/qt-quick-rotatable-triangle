import QtQuick 2.12
import QtQuick.Controls 2.12
import RotTriangle 1.0

Item {
    visible: true
    width: 640
    height: 480

    // Our QuickItem
    RotatableTriangle {
        id: rotTriangle
        anchors.fill: parent
        focus: true
    }

    Rectangle {
        id: rect
        color: Qt.rgba(1, 1, 1, 0.7)
        radius: 10
        border.width: 1
        border.color: "white"
        anchors.fill: label
        anchors.margins: -10
    }

    Text {
        id: label
        color: "black"
        wrapMode: Text.WordWrap
        text: "Simple example: rotatable triangle. Use buttons to change rotation velocity."
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.margins: 20
    }

    // Simple buttons for speed changing
    Button {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        text: "+"
        onPressed: {
            rotTriangle.rotate = 1;
        }
    }
    Button {
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        text: "-"
        onPressed: {
            rotTriangle.rotate = -1;
        }
    }
}
