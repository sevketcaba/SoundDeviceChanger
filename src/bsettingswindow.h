#ifndef BSETTINGSWINDOW_H
#define BSETTINGSWINDOW_H

#include <QQuickWidget>

class BDatabaseLoader;

class BSettingsWindow : public QQuickWidget
{
    Q_OBJECT
    Q_PROPERTY(QString appliationDir READ appliationDir WRITE setAppliationDir NOTIFY appliationDirChanged)
    QString mAppliationDir;

public:
    explicit BSettingsWindow(QWidget *parent = nullptr);

    QString appliationDir() const;

signals:
    void appliationDirChanged(QString appliationDir);

public slots:
    void setAppliationDir(QString appliationDir);

protected:
    BDatabaseLoader *mFontDatabase;
};

#endif // BSETTINGSWINDOW_H
