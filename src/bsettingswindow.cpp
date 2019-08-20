#include "bdatabaseloader.h"
#include "bdeviceinfo.h"
#include "bdevicemanager.h"
#include "bsettingswindow.h"

#include <QApplication>
#include <QFileDialog>
#include <QQmlContext>

#include "version.h"

BSettingsWindow::BSettingsWindow(QWidget *parent) :
    QQuickWidget(parent)
{
    setWindowTitle(QString("%1 v%2").arg(VER_FILEDESCRIPTION_STR).arg(VER_FILEVERSION_STR));
    setWindowModality(Qt::ApplicationModal);
    setAttribute(Qt::WA_DeleteOnClose, true);
    setResizeMode(SizeRootObjectToView);
    qmlRegisterType<BSettingsWindow>();
    qmlRegisterType<BDeviceInfo>();
    qmlRegisterType<BDeviceManager>();
    qmlRegisterType<BFontData>();
    qmlRegisterType<BDatabaseLoader>();

    mFontDatabase = new BDatabaseLoader;
    mFontDatabase->load();

    QDir tDir;
    setAppliationDir(tDir.absolutePath());

    rootContext()->setContextProperty("settings", this);
    rootContext()->setContextProperty("deviceManager", BDeviceManager::instance());
    rootContext()->setContextProperty("fontDatabase", mFontDatabase);
    setSource(QUrl(QStringLiteral("qrc:/ui/qml/main.qml")));
}

QString BSettingsWindow::appliationDir() const
{
    return mAppliationDir;
}


void BSettingsWindow::setAppliationDir(QString appliationDir)
{
    if (mAppliationDir == appliationDir)
        return;

    mAppliationDir = appliationDir;
    emit appliationDirChanged(appliationDir);
}
