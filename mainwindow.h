#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QQuickView>
#include <QTimer>

#include "settings.h"
#include "babyphone.h"

class MainWindow : public QQuickView
{
    Q_OBJECT
public:
    explicit MainWindow();
    ~MainWindow();

private:
    void setupGui();
    void setupSettingsGui();
    void showFirstRunInfo();
    void activateMonitor();
    void deactivateMonitor();
    void onStatusChanged(QQuickView::Status status);

signals:
    void requestExit();

private slots:
    void newAudioData(int counter, int value);
    void newCallStatus(bool finish, bool selfInitiated);
    void showNotificationError();
    void activationTimerExpired();
    void bringWindowToFront();
    void dataChanged();
    void storeGuiSettings();
    void changeState();
    void showHelp();

private:
    Settings *itsSettings = nullptr;
    bool itsIsScreenOff = false;
    QTimer itsActivationDelayTimer;
    Babyphone *itsBabyphone = nullptr;
    bool guiInitialized = false;
};

#endif // MAINWINDOW_H
