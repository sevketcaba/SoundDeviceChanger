#include "bsettings.h"

BSettings::BSettings() :
    QSettings("settings.ini", IniFormat)
{

}
