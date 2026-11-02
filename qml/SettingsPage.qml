import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: settingsPage
    objectName: "settingsPage"

    property bool inPortrait: true
    property alias volume: volume_settings.value
    property alias duration: duration_settings.value

    signal dataChanged()
    signal helpRequested()

    ScrollView {
        anchors.fill: parent

        Column {
            spacing: 20
            anchors.fill: parent
            anchors.margins: 20

            Text {
                text: qsTr("Settings")
                font.pixelSize: 30
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
            }

            Text { text: qsTr("Audio Volume:"); font.pixelSize: 16 }
            Slider {
                id: volume_settings
                objectName: "volume_settings"
                from: 1
                to: 40
                value: 16
                onValueChanged: settingsPage.dataChanged()
            }

            Text { text: qsTr("Audio Duration:"); font.pixelSize: 16 }
            Slider {
                id: duration_settings
                objectName: "duration_settings"
                from: 1
                to: 40
                value: 10
                onValueChanged: settingsPage.dataChanged()
            }

            Text {
                text: qsTr("Advanced Settings")
                font.pixelSize: 25
                font.bold: true
            }

            Text { text: qsTr("Activation delay [s]:"); font.pixelSize: 16 }
            Slider {
                id: activationdelay_settings
                objectName: "activationdelay_settings"
                from: 0
                to: 300
                value: 0
                onValueChanged: settingsPage.dataChanged()
            }

            Text { text: qsTr("Recall timeout [s]:"); font.pixelSize: 16 }
            Slider {
                id: recalldelay_settings
                objectName: "recalldelay_settings"
                from: 0
                to: 300
                value: 180
                onValueChanged: settingsPage.dataChanged()
            }

            Text { text: qsTr("Call setup limit [s]:"); font.pixelSize: 16 }
            Slider {
                id: callsetupdelay_settings
                objectName: "callsetupdelay_settings"
                from: 0
                to: 100
                value: 30
                onValueChanged: settingsPage.dataChanged()
            }

            Row {
                spacing: 10
                CheckBox {
                    id: incomingcalls_settings
                    objectName: "incomingcalls_settings"
                    text: qsTr("Handle incom. calls")
                    checked: true
                    onCheckedChanged: settingsPage.dataChanged()
                }
                CheckBox {
                    id: sms_settings
                    objectName: "sms_settings"
                    text: qsTr("Missed calls SMS")
                    onCheckedChanged: settingsPage.dataChanged()
                }
                CheckBox {
                    id: profile_settings
                    objectName: "profile_settings"
                    text: qsTr("Switch profile")
                    checked: true
                    onCheckedChanged: settingsPage.dataChanged()
                }
            }

            Button {
                id: help
                objectName: "help"
                text: qsTr("Help")
                onClicked: helpRequested()
                width: parent.width
            }
        }
    }
}
