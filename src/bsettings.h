#ifndef BSETTINGS_H
#define BSETTINGS_H

#include <QSettings>

class BSettings : public QSettings
{
    Q_OBJECT
public:
    BSettings();
};

#endif // BSETTINGS_H
