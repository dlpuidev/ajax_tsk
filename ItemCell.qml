import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Window 2.13
import QtQml.Models 2.13

Rectangle {
    id: root
    required property Item dragParent
    signal signalClicked
    signal signalPressed
    signal signalReleased

    property int visualIndex: 0

    anchors {
        horizontalCenter: parent.horizontalCenter
        verticalCenter: parent.verticalCenter
    }
    radius: 10

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        drag.target: root
        onClicked: root.signalClicked()
        onPressed: root.signalPressed()
        onReleased: {
            parent.Drag.drop()
            root.signalReleased()
        }
    }

    Drag.active: mouseArea.drag.active
    Drag.source: root
    Drag.hotSpot.x: root.width / 2
    Drag.hotSpot.y: root.height / 2

    states: [
        State {
            when: mouseArea.drag.active
            ParentChange {
                target: root
                parent: root.dragParent
            }

            AnchorChanges {
                target: root
                anchors.horizontalCenter: undefined
                anchors.verticalCenter: undefined
            }
        }
    ]
}
