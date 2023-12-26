import QtQuick 2.14
import QtQml.Models 2.15

GridView {
    id: root
    anchors.fill: parent

    property int currentIndex: 0

    cellWidth: 100
    cellHeight: 100

    displaced: Transition {
        NumberAnimation {
            properties: "x,y"
            easing.type: Easing.OutQuad
            duration: 400
        }
    }

    clip: true
    interactive: true
    model: DelegateModel {
        id: visualModel
        model: client.mainModel

        delegate: DropArea {
            id: delegateRoot
            required property color color

            property int index

            width: root.cellWidth
            height: root.cellHeight

            onEntered: function (drag) {
                var from = (drag.source as ItemCell).visualIndex
                var to = itemCell.visualIndex
                visualModel.items.move(from, to)
            }

            onDropped: function (drag) {
                var from = index
                var to = (drag.source as ItemCell).visualIndex
                client.mainModel.moveItem(from, to)
            }

            property int visualIndex: DelegateModel.itemsIndex

            ItemCell {
                id: itemCell
                width: root.cellWidth * 0.95
                height: root.cellHeight * 0.95
                dragParent: root
                visualIndex: delegateRoot.visualIndex
                color: delegateRoot.color
                onSignalPressed: delegateRoot.index = visualIndex
                onSignalClicked:
                {
                    root.currentIndex = index
                    colorDialog.open()
                }
            }
        }
    }
}
