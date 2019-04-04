#include "bdevicemanager.h"

#include <QDebug>

#include <Windows.h>
#include <mmdeviceapi.h>
#include <functiondiscoverykeys_devpkey.h>

#include "bdefinitions.h"
#include "bdeviceinfo.h"
#include "bdevicewatcher.h"
#include "ipolicyconfig.h"

BDeviceManager::BDeviceManager(QObject *parent) :
    QObject(parent)
  , mDeviceWatcher(nullptr)
{
    enumerateDevices();
}

BDeviceManager *BDeviceManager::instance()
{
    static BDeviceManager tInstance;
    return &tInstance;
}


QQmlListProperty<BDeviceInfo> BDeviceManager::devices()
{
    return QQmlListProperty<BDeviceInfo>(this, mDevices);
}

int BDeviceManager::deviceCount()
{
    return mDevices.size();
}

BDeviceInfo *BDeviceManager::device(int pIndex)
{
    return mDevices[pIndex];
}

BDeviceInfo *BDeviceManager::defaultDevice()
{
    for(int i=0;i<mDevices.size();++i)
    {
        BDeviceInfo *tInfo = mDevices[i];
        if(tInfo->isActive())
            return tInfo;
    }
    return nullptr;
}

void BDeviceManager::setDeviceHidden(QString pDeviceId, bool pIsHidden)
{
    BDeviceInfo *tInfo = deviceById(pDeviceId);
    if(!tInfo)
        return;
    tInfo->setIsHidden(pIsHidden);
}

void BDeviceManager::setDeviceIcon(QString pDeviceId, QString pIcon)
{
    BDeviceInfo *tInfo = deviceById(pDeviceId);
    if(!tInfo)
        return;
    tInfo->setIcon(pIcon);
    if(tInfo->isActive())
        emit defaultIconChanged();
}

void BDeviceManager::setDeviceActive(QString pDeviceId)
{
    BDeviceInfo *tInfo = deviceById(pDeviceId);
    if(!tInfo)
        return;
    BDeviceInfo *tActiveDevice = defaultDevice();
    if(tActiveDevice)
    {
        if(tInfo == tActiveDevice)
            return;
        if(tInfo->id() == tActiveDevice->id())
            return;

        // do the trick here
        PCWSTR tDevID = reinterpret_cast<const wchar_t*>(pDeviceId.utf16());
        IPolicyConfigVista *tPolicyConfig = nullptr;
        do
        {
            HRESULT hr = CoCreateInstance(__uuidof(CPolicyConfigVistaClient), nullptr, CLSCTX_ALL, __uuidof(IPolicyConfigVista), reinterpret_cast<LPVOID *>(&tPolicyConfig));
            BREAK(hr);
            hr = tPolicyConfig->SetDefaultEndpoint(tDevID, eConsole);
        } while(false);
        SafeRelease(&tPolicyConfig);

        tActiveDevice->setIsActive(false);
    }
    tInfo->setIsActive(true);
    emit defaultChanged();
}

void BDeviceManager::setNextAsDefault()
{
    int tDc = getVisibleDeviceCount();
    if(tDc < 2)
        return;

    int tIndex = -1;
    for(int i=0;i<mDevices.size();++i)
    {
        BDeviceInfo *tInfo = mDevices[i];
        if(tInfo->isActive())
        {
            tIndex = i;
            break;
        }
    }
    do
    {
        ++tIndex;
        if(tIndex==mDevices.size())
            tIndex = 0;
        if(mDevices[tIndex]->isHidden())
            continue;
        if(mDevices[tIndex]->isActive())
            continue;
        break;
    }
    while(true);
    setDeviceActive(mDevices[tIndex]->id());
}

void BDeviceManager::enumerateDevices()
{
    IMMDeviceEnumerator *tEnumerator = nullptr;
    IMMDeviceCollection *tDevices = nullptr;
    do
    {
        HRESULT hr = S_OK;
        Q_UNUSED(hr)

        const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
        const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);
        hr = CoCreateInstance(
                    CLSID_MMDeviceEnumerator, nullptr,
                    CLSCTX_ALL, IID_IMMDeviceEnumerator,
                    reinterpret_cast<void**>(&tEnumerator));
        BREAK(hr);

        mDeviceWatcher = new BDeviceWatcher;
        connect(mDeviceWatcher, &BDeviceWatcher::defaultDeviceChanged, this, [=](QString pDeviceId){
            BDeviceInfo *tOld = defaultDevice();
            if(tOld)
                tOld->setIsActive(false);
            BDeviceInfo *tNew = deviceById(pDeviceId);
            if(tNew)
            {
                tNew->setIsHidden(false);
                tNew->setIsActive(true);
            }
            emit defaultChanged();
        });
        tEnumerator->RegisterEndpointNotificationCallback(mDeviceWatcher);

        hr = tEnumerator->EnumAudioEndpoints(eRender, DEVICE_STATE_ACTIVE, &tDevices);
        BREAK(hr);

        QString tDefaultDeviceId;
        IMMDevice *tDefDevice = nullptr;
        LPWSTR tDefDeviceId = nullptr;
        do
        {
            hr = tEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &tDefDevice);
            BREAK(hr);
            hr = tDefDevice->GetId(&tDefDeviceId);
            BREAK(hr);
            tDefaultDeviceId = QString::fromWCharArray(tDefDeviceId);
        }
        while(false);
        CoTaskMemFree(tDefDeviceId);
        tDefDeviceId = nullptr;
        SafeRelease(&tDefDevice);

        quint32 tDeviceCount = 0;
        hr = tDevices->GetCount(&tDeviceCount);
        BREAK(hr);
        for(quint32 i =0; i < tDeviceCount;++i)
        {
            IMMDevice *tDevice = nullptr;
            LPWSTR tDeviceId = nullptr;
            IPropertyStore *tProps = nullptr;
            PROPVARIANT tDeviceName;
            PropVariantInit(&tDeviceName);
            do
            {
                hr = tDevices->Item(i, &tDevice);
                BREAK(hr);

                hr = tDevice->GetId(&tDeviceId);
                BREAK(hr);

                hr = tDevice->OpenPropertyStore(STGM_READ, &tProps);
                BREAK(hr);

                hr = tProps->GetValue(PKEY_Device_FriendlyName, &tDeviceName);
                BREAK(hr);

                BDeviceInfo *tDeviceInfo = new BDeviceInfo(this);
                tDeviceInfo->setId(QString::fromWCharArray(tDeviceId));
                tDeviceInfo->setName(QString::fromWCharArray(tDeviceName.pwszVal));
                tDeviceInfo->setIsActive(!tDeviceInfo->id().compare(tDefaultDeviceId));
                mDevices.push_back(tDeviceInfo);
                emit devicesChanged();

            }
            while(false);
            CoTaskMemFree(tDeviceId);
            tDeviceId = nullptr;
            PropVariantClear(&tDeviceName);
            SafeRelease(&tProps);
            SafeRelease(&tDevice);
        }
    }
    while(false);

    SafeRelease(&tDevices);
    SafeRelease(&tEnumerator);
}

int BDeviceManager::getVisibleDeviceCount()
{
    int tCount = 0;
    foreach(BDeviceInfo *tInfo, mDevices)
    {
        if(!tInfo->isHidden())
            ++tCount;
    }
    return tCount;
}

BDeviceInfo *BDeviceManager::deviceById(QString pDeviceId)
{
    for(int i=0;i<mDevices.size();++i)
    {
        BDeviceInfo *tInfo = mDevices[i];
        if(!tInfo->id().compare(pDeviceId))
            return tInfo;
    }
    return nullptr;
}
