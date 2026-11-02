#ifndef PROFILESWITCHER_H
#define PROFILESWITCHER_H

#include <QObject>
#include "settings.h"

class ProfileSwitcher : public QObject
{
    Q_OBJECT
public:
    explicit ProfileSwitcher(const Settings *settings, QObject *parent = nullptr);
    void switchToSilent();
    void switchToGeneral();

private:
    const Settings * const itsSettings;
};

#endif // PROFILESWITCHER_H
