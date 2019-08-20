#include "bsettings.h"

#include <QStandardPaths>

BSettings::BSettings() :
    QSettings(QString("%1/settings.ini").arg(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation)), IniFormat)
{
}
