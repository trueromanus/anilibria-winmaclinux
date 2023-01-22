/*
    AniLibria - desktop client for the website anilibria.tv
    Copyright (C) 2021 Roman Vladimirov

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "torrentnotifierviewmodel.h"

TorrentNotifierViewModel::TorrentNotifierViewModel(QObject *parent)
    : QObject{parent}
{
    m_timer->setInterval(4000);
    m_webSocket = new QWebSocket("localhost", QWebSocketProtocol::VersionLatest, this);

    connect(m_timer,&QTimer::timeout, this, &TorrentNotifierViewModel::triggerNotifier);
    connect(m_webSocket,&QWebSocket::textMessageReceived, this, &TorrentNotifierViewModel::triggerNotifier);
}

void TorrentNotifierViewModel::startGetNotifiers(int port)
{
    if (m_timer->isActive()) return;

    m_webSocket->open(QUrl("ws://localhost:" + QString::number(port) + "/ws"));

    m_timer->start();

}

void TorrentNotifierViewModel::stopNotifiers()
{
    if (!m_timer->isActive()) return;

    m_webSocket->close(QWebSocketProtocol::CloseCode::CloseCodeNormal, "not need");
    m_timer->stop();
}

void TorrentNotifierViewModel::triggerNotifier()
{
    if (m_webSocket->state() != QAbstractSocket::ConnectedState) return;

    m_webSocket->sendTextMessage("ds:");
}

void TorrentNotifierViewModel::messageReceived(const QString &message)
{
    if (message.isEmpty()) return;

    auto document = QJsonDocument::fromJson(message.toUtf8());
    auto items = document.array();
    foreach (auto item, items) {
        auto object = item.toObject();
        auto isAll = false;
        QString path = "";
        int identifier = 0;
        if (object.contains("all")) isAll = object.value("all").toBool();
        if (object.contains("path")) path = object.value("path").toString();
        if (object.contains("identifier")) identifier = object.value("identifier").toInt();
        if (identifier > 0 && !path.isEmpty()) {
            auto key = QString::number(identifier) + path;
            if (!m_downloadedStatuses.contains(key) && isAll) {
                m_downloadedStatuses.insert(key, true);
                return;
            }
            if (m_downloadedStatuses.contains(key)) {
                auto value = m_downloadedStatuses.value(key);
                if (!value && isAll) {
                    emit torrentFullyDownloaded(identifier);
                    return;
                }
            }

            m_downloadedStatuses.insert(key, isAll);
        }
    }
}
