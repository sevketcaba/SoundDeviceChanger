#ifndef BDATABASELOADER_H
#define BDATABASELOADER_H

#include <QObject>
#include <QMap>
#include <QQmlListProperty>

class BFontData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY iconChanged)
    Q_PROPERTY(QString code READ code WRITE setCode NOTIFY codeChanged)

public:
    QString name() const { return mName; }
    QString icon() const { return mIcon; }
    QString code() const { return mCode; }

signals:
    void nameChanged();
    void iconChanged();
    void codeChanged();
public slots:
    void setName(const QString &pName) {
        if(mName == pName)
            return;
        mName = pName;
        emit nameChanged();
    }
    void setIcon(const QString &pIcon) {
        if(mIcon == pIcon)
            return;
        mIcon = pIcon;
        emit iconChanged();
    }
    void setCode(const QString &pCode) {
        if(mCode == pCode)
            return;
        mCode = pCode;
        emit codeChanged();
    }
protected:
    QString mName;
    QString mIcon;
    QString mCode;
};

class BDatabaseLoader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<BFontData> fontData READ fontData NOTIFY fontDataChanged)
    Q_PROPERTY(QString busyMessage READ busyMessage WRITE setBusyMessage NOTIFY busyMessageChanged)
public:
    explicit BDatabaseLoader(QObject *parent = nullptr);

    QQmlListProperty<BFontData> fontData();
    QString busyMessage();
signals:
    void fontDataChanged();
    void busyMessageChanged();
public slots:
    void reload();
    void load();

protected slots:
    void download();
    void save(const QString &pHtml);

    void setBusyMessage(QString pBusyMessage);
protected:
    struct Data
    {
        QString name;
        QString code;
        QString icon;
    };

    bool mDownload;
    QList<BFontData*> mFontData;
    QString mBusyMessage;
};

#endif // BDATABASELOADER_H
