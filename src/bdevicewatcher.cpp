#include "bdevicewatcher.h"

#include <QDebug>


BDeviceWatcher::BDeviceWatcher(QObject *parent) :
     QObject(parent)
    , _cRef(1)
{

}

BDeviceWatcher::~BDeviceWatcher()
{
    SafeRelease(&_pEnumerator);
}

ULONG STDMETHODCALLTYPE BDeviceWatcher::AddRef()
{
    return InterlockedIncrement(&_cRef);
}

ULONG STDMETHODCALLTYPE BDeviceWatcher::Release()
{
    ULONG ulRef = InterlockedDecrement(&_cRef);
    if (0 == ulRef)
    {
        delete this;
    }
    return ulRef;
}

HRESULT STDMETHODCALLTYPE BDeviceWatcher::QueryInterface(
        REFIID riid, VOID **ppvInterface)
{
    if (IID_IUnknown == riid)
    {
        AddRef();
        *ppvInterface = (IUnknown*)this;
    }
    else if (__uuidof(IMMNotificationClient) == riid)
    {
        AddRef();
        *ppvInterface = (IMMNotificationClient*)this;
    }
    else
    {
        *ppvInterface = NULL;
        return E_NOINTERFACE;
    }
    return S_OK;
}

HRESULT STDMETHODCALLTYPE BDeviceWatcher::OnDefaultDeviceChanged(
        EDataFlow flow, ERole role,
        LPCWSTR pwstrDeviceId)
{
    if(flow != eRender)
        return S_OK;

    if(role == eCommunications)
        return S_OK;

    QString tDeviceId = QString::fromWCharArray(pwstrDeviceId);
    emit defaultDeviceChanged(tDeviceId);

    return S_OK;
}


HRESULT STDMETHODCALLTYPE BDeviceWatcher::OnDeviceAdded(LPCWSTR pwstrDeviceId)
{
    Q_UNUSED(pwstrDeviceId)
    return S_OK;
}

HRESULT STDMETHODCALLTYPE BDeviceWatcher::OnDeviceRemoved(LPCWSTR pwstrDeviceId)
{
    Q_UNUSED(pwstrDeviceId)
    return S_OK;
}

HRESULT STDMETHODCALLTYPE BDeviceWatcher::OnDeviceStateChanged(
        LPCWSTR pwstrDeviceId,
        DWORD dwNewState)
{
    Q_UNUSED(pwstrDeviceId)
    Q_UNUSED(dwNewState)
    return S_OK;
}

HRESULT STDMETHODCALLTYPE BDeviceWatcher::OnPropertyValueChanged(
        LPCWSTR pwstrDeviceId,
        const PROPERTYKEY key)
{
    Q_UNUSED(pwstrDeviceId)
    Q_UNUSED(key)
    return S_OK;
}
