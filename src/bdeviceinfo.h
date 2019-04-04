#ifndef BDEVICEINFO_H
#define BDEVICEINFO_H

#include <QObject>

class BDeviceInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isActive READ isActive WRITE setIsActive NOTIFY isActiveChanged)
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY iconChanged)
    Q_PROPERTY(bool isHidden READ isHidden WRITE setIsHidden NOTIFY isHiddenChanged)

public:
    explicit BDeviceInfo(QObject *parent = nullptr);

    bool isActive() const;
    QString id() const;
    QString name() const;
    QString icon() const;
    bool isHidden() const;

signals:
    void isActiveChanged(bool);
    void idChanged();
    void nameChanged();
    void iconChanged();
    void isHiddenChanged();

public slots:
    void setIsActive(bool pIsActive);
    void setId(QString pId);
    void setName(QString pName);
    void setIcon(QString icon);
    void setIsHidden(bool isHidden);

    void loadSettings();
    void saveSettings();
protected:
    bool mIsActive;
    QString mId;
    QString mName;
    QString mIcon;
    bool mIsHidden;
};


#endif // BDEVICEINFO_H
