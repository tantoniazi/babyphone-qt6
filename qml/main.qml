import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: appWindow
    visible: true
    width: 480
    height: 800
    title: qsTr("Babyphone")

    signal requestExit()

    MainPage {
        id: mainPage
        onVolumeChanged: settingsPage.volume = volume
        onDurationChanged: settingsPage.duration = duration
    }
    SettingsPage {
        id: settingsPage
        onVolumeChanged: mainPage.volume = volume
        onDurationChanged: mainPage.duration = duration
    }
    AboutPage { id: aboutPage }

    initialPage: mainPage

    footer: ToolBar {
        ToolButton {
            text: qsTr("About")
            onClicked: pageStack.push(aboutPage)
        }
        ToolButton {
            text: qsTr("Settings")
            onClicked: pageStack.push(settingsPage)
        }
    }

    Banner {
        id: banner
        objectName: "banner"
        topMargin: 50
        timerShowTime: 6000
    }
}
