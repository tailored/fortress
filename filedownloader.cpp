#include "filedownloader.h"

/**
 * @brief FileDownloader::FileDownloader
 * @param imageUrl
 * @param parent
 */
FileDownloader::FileDownloader(QUrl imageUrl, QObject *parent) :
    QObject(parent)
{
    connect(&m_WebCtrl, SIGNAL(finished(QNetworkReply*)),
                SLOT(fileDownloaded(QNetworkReply*)));

    QNetworkRequest request(imageUrl);
    m_WebCtrl.get(request);
}

/**
 * @brief FileDownloader::~FileDownloader
 */
FileDownloader::~FileDownloader()
{

}

/**
 * @brief FileDownloader::fileDownloaded
 * @param pReply
 */
void FileDownloader::fileDownloaded(QNetworkReply* pReply)
{
    m_DownloadedData = pReply->readAll();
    //emit a signal
    pReply->deleteLater();
    emit downloaded();
}

/**
 * @brief FileDownloader::downloadedData
 * @return
 */
QByteArray FileDownloader::downloadedData() const
{
    return m_DownloadedData;
}
