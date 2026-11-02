import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: mainPage
    objectName: "mainPage"

    property bool inPortrait: true
    property alias volume: volume_settings.value
    property alias duration: duration_settings.value

    signal dataChanged()
    signal changeState()

    property string state: "OFF"

    Column {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        Text {
            id: heading
            text: inPortrait ? "Babyphone" : ""
            font.pixelSize: 30
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            text: qsTr("Parent's Phone:")
            font.pixelSize: 16
        }
        TextField {
            id: contact
            objectName: "contact"
            text: ""
            onTextChanged: mainPage.dataChanged()
            enabled: mainPage.state === "OFF"
        }

        Row {
            spacing: 20
            Text { text: qsTr("Volume:"); font.pixelSize: 16 }
            Slider {
                id: volume_settings
                objectName: "volume_settings"
                from: 1
                to: 40
                value: 16
                onValueChanged: mainPage.dataChanged()
            }
        }

        Row {
            spacing: 20
            Text { text: qsTr("Duration:"); font.pixelSize: 16 }
            Slider {
                id: duration_settings
                objectName: "duration_settings"
                from: 1
                to: 40
                value: 10
                onValueChanged: mainPage.dataChanged()
            }
        }

        Rectangle {
            id: volume_graph
            objectName: "volume_graph"
            height: 150
            color: "#2c3e50"
            border.color: "#ecf0f1"
        }

        Rectangle {
            id: duration_graph
            objectName: "duration_graph"
            height: 150
            color: "#2c3e50"
            border.color: "#ecf0f1"
        }

        Button {
            id: button
            objectName: "button"
            text: state === "ON" ? qsTr("Active - Click to stop")
                   : state === "WAITING" ? qsTr("Waiting for activation delay")
                   : qsTr("Inactive - Click to start")
            onClicked: changeState()
            width: parent.width
            height: 60
            background: Rectangle {
                color: state === "OFF" ? "#27ae60" : "#c0392b"
                radius: 4
            }
        }
    }
}
