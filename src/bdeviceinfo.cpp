#include "bdeviceinfo.h"

#include <QFileInfo>
#include <QSettings>

BDeviceInfo::BDeviceInfo(QObject *parent) :
    QObject(parent)
  , mIsActive(false)
  , mIsHidden(false)
{
    connect(this, &BDeviceInfo::iconChanged, this, &BDeviceInfo::saveSettings);
    connect(this, &BDeviceInfo::isHiddenChanged, this, &BDeviceInfo::saveSettings);
    connect(this, &BDeviceInfo::idChanged, this, &BDeviceInfo::loadSettings);
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
    QSettings tSettings;
    bool tIsHidden = tSettings.value(QString("%1/is_hidden").arg(mId)).toBool();
    setIsHidden(tIsHidden);
    QString tIcon = tSettings.value(QString("%1/icon").arg(mId)).toString();
    setIcon(tIcon);

}

void BDeviceInfo::saveSettings()
{
    if(mId.isEmpty())
        return;

    QSettings tSettings;
    tSettings.setValue(QString("%1/is_hidden").arg(mId), mIsHidden);
    tSettings.setValue(QString("%1/icon").arg(mId), mIcon);
    tSettings.sync();
}
