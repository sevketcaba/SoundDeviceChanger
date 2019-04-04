#include "bcontroller.h"
#include "bdeviceinfo.h"
#include "bdevicemanager.h"
#include "bsettings.h"

#include <QApplication>
#include <QDir>
#include <QDebug>

#include "awesome/qtawesome.h"
#include "bdefinitions.h"

BController::BController(QObject *parent)
    : QObject(parent)
{
    mTray = new QSystemTrayIcon;

    mMenu = new QMenu;
    createMenu();

    connect(BDeviceManager::instance(), &BDeviceManager::defaultChanged, this, &BController::defaultChanged);
    connect(BDeviceManager::instance(), &BDeviceManager::defaultIconChanged, this, &BController::defaultChanged);

    mFont = new QtAwesome(qApp);
    mFont->initFontAwesome();

    defaultChanged();

    mTray->setContextMenu(mMenu);
    mTray->show();

    connect(mTray, &QSystemTrayIcon::activated, this, [](QSystemTrayIcon::ActivationReason pReason){
        if(pReason == QSystemTrayIcon::DoubleClick)
        {
            BDeviceManager::instance()->setNextAsDefault();
        }
    });
}

BController::~BController()
{

}

void BController::createMenu()
{
    clearMenu();
    BDeviceManager *tDeviceMan = BDeviceManager::instance();

    for(int i=0;i<tDeviceMan->deviceCount();++i)
    {
        BDeviceInfo *tInfo = tDeviceMan->device(i);
        connect(tInfo, &BDeviceInfo::iconChanged, this, &BController::createMenu);
        connect(tInfo, &BDeviceInfo::isHiddenChanged, this, &BController::createMenu);

        if(tInfo->isHidden())
            continue;

        QAction *tAction = mMenu->addAction(tInfo->name(), this, SLOT(menuClicked()));
        tAction->setObjectName(tInfo->id());
        tAction->setCheckable(true);
        tAction->setChecked(tInfo->isActive());

        connect(tInfo, &BDeviceInfo::isActiveChanged, tAction, &QAction::setChecked);
    }

    mMenu->addSeparator();

    {
        QAction *tAction = mMenu->addAction("Settings", this, SLOT(menuClicked()));
        tAction->setObjectName("[settings]");
    }
    {
        QAction *tAction = mMenu->addAction("Exit", this, SLOT(menuClicked()));
        tAction->setObjectName("[exit]");
    }
}

void BController::clearMenu()
{
    QList<QAction*> tActions = mMenu->actions();
    while(tActions.size())
    {
        QAction *tAction = tActions.takeFirst();
        mMenu->removeAction(tAction);
        tAction->deleteLater();
    }
}

void BController::menuClicked()
{
    QAction *tAction = dynamic_cast<QAction*>(sender());
    if(!tAction)
        return;
    if(!tAction->objectName().compare("[exit]"))
        qApp->quit();
    else if(!tAction->objectName().compare("[settings]"))
    {
        BSettings *tSettings = new BSettings;
        tSettings->show();
    }
    else
    {
        BDeviceManager::instance()->setDeviceActive(tAction->objectName());
    }
}

void BController::defaultChanged()
{
    QVariantMap tOptions;
    tOptions.insert( "color" , QColor(0,255,0) );

    BDeviceInfo *tInfo = BDeviceManager::instance()->defaultDevice();
    QIcon tIcon = mFont->icon(fa::question, tOptions);

    if(tInfo)
    {
        tInfo->setIsHidden(false);
        if(!tInfo->icon().isEmpty())
        {
            QString tIconName = tInfo->icon();
            if(tIconName.size() == 1)
            {
                int tCh = tIconName.at(0).unicode();
                tIcon = mFont->icon(tCh, tOptions);
            }
            else
            {
                QString tTmp = QString("%1").arg(tIconName);
                bool tOk;
                int tCh = tTmp.toInt(&tOk, 16);
                tIcon = mFont->icon(tCh, tOptions);
            }
        }
    }


    mTray->setIcon(tIcon);
}

//void BController::defaultIconChanged()
//{

//}

