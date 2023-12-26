import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Window 2.13
import QtQml.Models 2.13

ApplicationWindow {
    id: application

    width: 720
    height: 480

    title: "Client App"
    visible: true

    Rectangle {
        color: "#242424"
        anchors.fill: parent
    }

    Dialog {
        id: errorDialog
        title: "Error..."
        modal: true

        standardButtons: Dialog.Ok
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2


        contentItem: Rectangle {
            implicitWidth: 100
            implicitHeight: 50
            anchors.centerIn: parent
            Text {
                id: errorText
                anchors.centerIn: parent
            }
        }

        onAccepted: {
            console.log("And of course you could only agree.")
            Qt.quit()
        }

        function error(t) {
            errorText.text = t;
            errorDialog.open()
        }

        Component.onCompleted:{
            client.errorSignal.connect(error)
            client.run();
        }
    }

    Dialog {
        id: downloadDialog
        modal: true
        standardButtons: Dialog.Cancel
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        title: "Downloading..."

        contentItem: ProgressBar {
            id: progressBar
            value: 0
            from: 0
            to: 0
        }

        onRejected:{
            client.stop()
        }

        function startDownload(num) {
            progressBar.to = num;
            downloadDialog.open()
        }

        function finishDownload() {
            downloadDialog.close()
        }

        function newElement(el) {
            progressBar.value = el;
        }

        Component.onCompleted:{
            client.startDownload.connect(startDownload)
            client.finishDownload.connect(finishDownload)
            client.elementDownloaded.connect(newElement)
        }
    }

    Dialog {
        id: colorDialog
        title: "Enter new color"
        modal: true
        standardButtons: Dialog.Cancel | Dialog.Ok

        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        focus: true

        TextInput {
            id: inputText
            text: "color"
            cursorVisible: true
            focus: true
            anchors.fill: parent
            Keys.onReturnPressed: colorDialog.accept()
        }

        onAccepted:{
            client.mainModel.setColor(grid.currentIndex, inputText.text);
        }
    }

    Item {
        id: content
        anchors.fill: parent
        CustomGrid {
            id: grid
            anchors.fill: parent
        }
    }
}
