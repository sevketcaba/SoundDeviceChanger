#include "bdatabaseloader.h"

#include <QDebug>
#include <QDomDocument>
#include <QFile>

#include <QWebEnginePage>
#include <QWebEngineSettings>

BDatabaseLoader::BDatabaseLoader(QObject *parent) :
    QObject(parent)
  , mDownload(true)
{

}

QQmlListProperty<BFontData> BDatabaseLoader::fontData()
{
    return QQmlListProperty<BFontData>(this, mFontData);
}

void BDatabaseLoader::reload()
{
    qDebug() << "Reload";
    mDownload = true;
    download();
}

void BDatabaseLoader::save(const QString &pHtml)
{
    qDebug() << "Save";
    int tIndex = pHtml.indexOf("<div class=\"row\">");
    int tIndex2 = pHtml.indexOf("<footer");
    QString tHtml = pHtml.mid(tIndex, tIndex2-tIndex).trimmed();
    tHtml = tHtml.left(tHtml.size()-6).trimmed();
    tHtml = tHtml.left(tHtml.size()-6).trimmed();
    QFile tFile("font-db.xml");
    tFile.open(QIODevice::WriteOnly);
    tFile.write(tHtml.toUtf8());
    tFile.close();
}

void BDatabaseLoader::load()
{
    qDebug() << "Load";
    while(mFontData.size())
    {
        BFontData *tData = mFontData.takeFirst();
        emit fontDataChanged();
        tData->deleteLater();
    }

    QDomDocument tDoc;
    QString tErrorString;
    int tCol;
    int tLine;

    QFile tFile("font-db.xml");
    if(!tFile.exists())
    {
        if(mDownload)
        {
            mDownload = false; // prevent recursion
            download();
        }
        return;
    }
    tFile.open(QIODevice::ReadOnly);

    if(!tDoc.setContent(&tFile, &tErrorString, &tLine, &tCol))
    {
        qCritical() << "XML ERROR" << tErrorString << tLine << tCol;
        tFile.close();
        return;
    }
    tFile.close();

    QDomNode tDiv = tDoc.documentElement().firstChild();
    while(!tDiv.isNull())
    {
        QDomNode tSub = tDiv.firstChild();
        BFontData *tData = new BFontData;
        while(!tSub.isNull())
        {
            QDomElement tEle = tSub.toElement();
            do
            {
                if(tEle.tagName() == "small")
                    continue;

                if(tEle.tagName().isEmpty())
                    tData->setName( tSub.nodeValue().trimmed() );
                else if(tEle.tagName() == "span")
                    tData->setCode( tEle.firstChild().toText().data().mid(4,4) );
                else if(tEle.tagName() == "i")
                    tData->setIcon(tEle.firstChild().toText().data());
            }
            while(false);
            tSub = tSub.nextSibling();
        }

        mFontData.push_back(tData);
        tDiv = tDiv.nextSibling();
    }

    emit fontDataChanged();
}

void BDatabaseLoader::download()
{
    qDebug() << "Download";
    QWebEnginePage *tPage = new QWebEnginePage;
    tPage->settings()->setAttribute(QWebEngineSettings::AutoLoadImages, false);
    tPage->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, false);
    connect(tPage, &QWebEnginePage::loadFinished, this, [=](bool){
        tPage->toHtml([this](const QString &pPageSource)  {
            save(pPageSource);
            load();
        });
    });
    tPage->load(QUrl("https://fontawesome.com/v4.7.0/cheatsheet/"));
}
