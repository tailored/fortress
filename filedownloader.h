#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

/**
 * @brief The FileDownloader class
 */
class FileDownloader : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief FileDownloader
     * @param imageUrl
     * @param parent
     */
    explicit FileDownloader(QUrl imageUrl, QObject *parent = 0);

    /**
     * @brief ~FileDownloader
     */
    virtual ~FileDownloader();

    /**
     * @brief downloadedData
     * @return
     */
    QByteArray downloadedData() const;

signals:
    /**
     * @brief downloaded
     */
    void downloaded();

private slots:
    /**
     * @brief fileDownloaded
     * @param pReply
     */
    void fileDownloaded(QNetworkReply* pReply);

private:

    /**
     * @brief m_WebCtrl
     */
    QNetworkAccessManager m_WebCtrl;

    /**
     * @brief m_DownloadedData
     */
    QByteArray m_DownloadedData;

};

#endif // FILEDOWNLOADER_H
