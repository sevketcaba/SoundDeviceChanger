#ifndef BDEFINITIONS_H
#define BDEFINITIONS_H


#include <QDebug>
#ifndef BREAK
#define BREAK(hr) { if(FAILED(hr)) { qWarning() << "ERROR" << __LINE__ << QString::number((hr), 16).right(8); break; } }
#endif
#ifndef DONTBREAK
#define DONTBREAK(hr) { if(FAILED(hr)) { qWarning() << "ERROR" << __LINE__ << QString::number((hr), 16).right(8); } }
#endif
template <class T>
inline void SafeRelease(T **ppT)
{
    if(*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}

#endif // BDEFINITIONS_H
