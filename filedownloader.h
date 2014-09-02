/**************************************************************************
 * Copyright (C) 2014  - Christian Richter                                *
 *                     - Daniel Niedermeyer                               *
 *                     - Benjamin Hiefner                                 *
 *                                                                        *
 * This program is free software: you can redistribute it and/or modify   *
 * it under the terms of the GNU General Public License as published by   *
 * the Free Software Foundation, either version 3 of the License, or      *
 * (at your option) any later version.                                    *
 *                                                                        *
 * This program is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 * GNU General Public License for more details.                           *
 *                                                                        *
 * You should have received a copy of the GNU General Public License      *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>   *
 **************************************************************************
 * File: filedownloader.h                                                 *
 **************************************************************************/

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
