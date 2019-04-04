#include "bdeviceinfo.h"
#include "bsettings.h"

#include <QFileInfo>

BDeviceInfo::BDeviceInfo(QObject *parent) :
    QObject(parent)
  , mIsActive(false)
  , mIsHidden(false)
{
    connect(this, &BDeviceInfo::iconChanged, this, &BDeviceInfo::saveSettings);
    connect(this, &BDeviceInfo::isHiddenChanged, this, &BDeviceInfo::saveSettings);
    connect(this, &BDeviceInfo::idChanged, this, &BDeviceInfo::loadSettings);
    connect(this, &BDeviceInfo::nameChanged, this, &BDeviceInfo::loadSettings);
}

bool BDeviceInfo::isActive() const
{
    return mIsActive;
}

QString BDeviceInfo::id() const
{
    return mId;
}

QString BDeviceInfo::name() const
{
    return mName;
}

QString BDeviceInfo::icon() const
{
    return mIcon;
}

bool BDeviceInfo::isHidden() const
{
    return mIsHidden;
}

void BDeviceInfo::setIsActive(bool pIsActive)
{
    if(mIsActive == pIsActive)
        return;
    mIsActive = pIsActive;
    emit isActiveChanged(pIsActive);
}

void BDeviceInfo::setId(QString pId)
{
    if(mId == pId)
        return;
    mId = pId;

    emit idChanged();
}

void BDeviceInfo::setName(QString pName)
{
    if(mName == pName)
        return;
    mName = pName;
    emit nameChanged();
}

void BDeviceInfo::setIcon(QString icon)
{
    if (mIcon == icon)
        return;

    mIcon = icon;
    emit iconChanged();
}

void BDeviceInfo::setIsHidden(bool isHidden)
{
    if (mIsHidden == isHidden)
        return;

    mIsHidden = isHidden;
    emit isHiddenChanged();
}

void BDeviceInfo::loadSettings()
{
    if(mId.isEmpty())
        return;
    BSettings tSettings;
    bool tIsHidden = tSettings.value(QString("%1/is_hidden").arg(escStr(mName))).toBool();
    setIsHidden(tIsHidden);
    QString tIcon = tSettings.value(QString("%1/icon").arg(escStr(mName))).toString();
    setIcon(tIcon);

}

void BDeviceInfo::saveSettings()
{
    if(mId.isEmpty())
        return;

    BSettings tSettings;
    tSettings.setValue(QString("%1/is_hidden").arg(escStr(mName)), mIsHidden);
    tSettings.setValue(QString("%1/icon").arg(escStr(mName)), mIcon);
    tSettings.sync();
}

QString BDeviceInfo::escStr(QString pStr)
{
    return pStr.replace('/', '_').replace(' ', '_').replace('(', '_').replace(')', '_').replace('-', '_');
}
