#include <QApplication>
#include <QQuickView>
#include <QQmlEngine>

#include "babyphonedefines.h"
#include "settings.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow;

#ifdef BABYPHONE_DESKTOP_BUILD
    mainWindow.show();
#else
    mainWindow.showFullScreen();
    QObject::connect(&mainWindow, SIGNAL(requestExit()), &app, SLOT(closeAllWindows()));
#endif

    return app.exec();
}
