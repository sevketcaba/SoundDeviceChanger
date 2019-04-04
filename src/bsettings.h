#ifndef BSETTINGS_H
#define BSETTINGS_H

#include <QQuickWidget>

class BDatabaseLoader;

class BSettings : public QQuickWidget
{
    Q_OBJECT
    Q_PROPERTY(QString appliationDir READ appliationDir WRITE setAppliationDir NOTIFY appliationDirChanged)
    QString mAppliationDir;

public:
    explicit BSettings(QWidget *parent = nullptr);

    QString appliationDir() const;

signals:
    void appliationDirChanged(QString appliationDir);

public slots:
    void setAppliationDir(QString appliationDir);

protected:
    BDatabaseLoader *mFontDatabase;
};

#endif // BSETTINGS_H
