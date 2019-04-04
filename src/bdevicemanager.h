#ifndef BDEVICEMANAGER_H
#define BDEVICEMANAGER_H

#include <QObject>
#include <QQmlListProperty>


class BDeviceInfo;
class BDeviceWatcher;

class BDeviceManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<BDeviceInfo> devices READ devices NOTIFY devicesChanged)
    BDeviceManager(QObject *parent = nullptr);
public:
    static BDeviceManager *instance();

    QQmlListProperty<BDeviceInfo> devices();
    int deviceCount();
    BDeviceInfo *device(int pIndex);
    BDeviceInfo *defaultDevice();
signals:
    void devicesChanged();
    void defaultChanged();
    void defaultIconChanged();
public slots:
    void setDeviceHidden(QString pDeviceId,bool pIsHidden);
    void setDeviceIcon(QString pDeviceId, QString pIcon);
    void setDeviceActive(QString pDeviceId);
    void setNextAsDefault();
protected:
    QList<BDeviceInfo*> mDevices;
    BDeviceWatcher *mDeviceWatcher;

    int getVisibleDeviceCount();

    BDeviceInfo *deviceById(QString pId);
private:
    void enumerateDevices();
};

#endif // BDEVICEMANAGER_H
