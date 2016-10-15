#include "bdeviceinfo.h"
#include "bdevicemanager.h"
#include "bsettings.h"

#include <QApplication>
#include <QFileDialog>
#include <QQmlContext>

BSettings::BSettings(QWidget *parent) :
    QQuickWidget(parent)
{
    setWindowModality(Qt::ApplicationModal);
    setAttribute(Qt::WA_DeleteOnClose, true);
    setResizeMode(SizeRootObjectToView);
    qmlRegisterType<BSettings>("tr.gen.caba.android.qt.qmltypes", 1, 0, "Settings");
    qmlRegisterType<BDeviceInfo>(); //"tr.gen.caba.android.qt.qmltypes", 1, 0, "DeviceManager");
    qmlRegisterType<BDeviceManager>(); //"tr.gen.caba.android.qt.qmltypes", 1, 0, "DeviceManager");

    QDir tDir;
    setAppliationDir(tDir.absolutePath());

    rootContext()->setContextProperty("settings", this);
    rootContext()->setContextProperty("deviceManager", BDeviceManager::instance());
    setSource(QUrl(QStringLiteral("qrc:/ui/qml/main.qml")));
}

QString BSettings::appliationDir() const
{
    return mAppliationDir;
}


void BSettings::setAppliationDir(QString appliationDir)
{
    if (mAppliationDir == appliationDir)
        return;

    mAppliationDir = appliationDir;
    emit appliationDirChanged(appliationDir);
}
