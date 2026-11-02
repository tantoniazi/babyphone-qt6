import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    id: aboutPage
    objectName: "aboutPage"

    property string version: "2.0"

    Column {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        Text {
            id: heading
            text: qsTr("About Babyphone")
            font.pixelSize: 30
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            id: versionText
            text: qsTr("Version: ") + parent.version
            font.pixelSize: 18
        }

        Text {
            id: info
            text: qsTr("Babyphone is a baby monitoring application that measures the audio noise level.\n"
                       "If the volume exceeds a configurable threshold the phone initiates a call to a predefined phone number (the parents).")
            wrapMode: Text.Wrap
            font.pixelSize: 14
        }

        Text {
            id: copyright
            text: "(c) 2011, Roman Morawek"
            font.pixelSize: 14
        }

        Text {
            id: url
            text: "http://babyphone.garage.maemo.org"
            color: "blue"
            font.pixelSize: 14
            MouseArea {
                anchors.fill: parent
                onClicked: Qt.openUrlExternally(url.text)
            }
        }
    }
}
