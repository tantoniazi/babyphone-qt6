#include "profileswitcher.h"

#include <QDebug>

ProfileSwitcher::ProfileSwitcher(const Settings *settings, QObject *parent)
    : QObject(parent), itsSettings(settings)
{
}

void ProfileSwitcher::switchToSilent()
{
    Q_UNUSED(itsSettings)
    qDebug() << "ProfileSwitcher: switching to silent profile";
}

void ProfileSwitcher::switchToGeneral()
{
    qDebug() << "ProfileSwitcher: switching to general profile";
}
