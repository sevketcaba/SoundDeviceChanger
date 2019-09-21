#ifndef BDEVICEWATCHER_H
#define BDEVICEWATCHER_H

#include <QObject>

#include <Mmdeviceapi.h>
#include "bdefinitions.h"

class BDeviceWatcher : public QObject, public IMMNotificationClient
{
    Q_OBJECT
public:
    explicit BDeviceWatcher(QObject *parent = 0);
    ~BDeviceWatcher();
signals:
    void defaultDeviceChanged(QString);
    void devicesChanged();
protected:
    LONG _cRef;
    IMMDeviceEnumerator *_pEnumerator;
    HRESULT QueryInterface(const IID &riid, void **ppvInterface);
    ULONG AddRef();
    ULONG Release();

    HRESULT STDMETHODCALLTYPE OnDeviceStateChanged(LPCWSTR pwstrDeviceId, DWORD dwNewState);
    HRESULT STDMETHODCALLTYPE OnDeviceAdded(LPCWSTR pwstrDeviceId);
    HRESULT STDMETHODCALLTYPE OnDeviceRemoved(LPCWSTR pwstrDeviceId);
    HRESULT STDMETHODCALLTYPE OnDefaultDeviceChanged(EDataFlow flow, ERole role, LPCWSTR pwstrDeviceId);
    HRESULT STDMETHODCALLTYPE OnPropertyValueChanged(LPCWSTR pwstrDeviceId, const PROPERTYKEY key);

};

#endif // BDEVICEWATCHER_H
