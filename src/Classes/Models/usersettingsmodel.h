/*
    AniLibria - desktop client for the website anilibria.tv
    Copyright (C) 2020 Roman Vladimirov

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

#ifndef USERSETTINGSMODEL_H
#define USERSETTINGSMODEL_H

#include <QString>
#include <QJsonDocument>
#include <QJsonObject>

class UserSettingsModel
{

private:
    int m_Quality;
    double m_Volume;
    bool m_AutoNextVideo;
    bool m_AutoTopMost;
    int m_TorrentDownloadMode;
    bool m_NotificationForFavorites;
    int m_JumpMinute;
    int m_JumpSecond;
    bool m_ShowReleaseInfo;
    bool m_ClearFiltersAfterChangeSection;
    bool m_CompactMode;

public:
    UserSettingsModel();

    int quality() const { return m_Quality; }
    double volume() const { return m_Volume; }
    bool autoNextVideo() const { return m_AutoNextVideo; }
    bool autoTopMost() const { return  m_AutoTopMost; }
    int torrentDownloadMode() const { return  m_TorrentDownloadMode; }
    bool notificationForFavorites() const { return m_NotificationForFavorites; }
    int jumpMinute() const { return m_JumpMinute; }
    int jumpSecond() const { return m_JumpSecond; }
    bool showReleaseInfo() const { return m_ShowReleaseInfo; }
    bool clearFiltersAfterChangeSection() const { return m_ClearFiltersAfterChangeSection; }
    bool compactMode() const { return m_CompactMode; }

    void setQuality(const int quality) noexcept;
    void setVolume(const double volume) noexcept;
    void setAutoNextVideos(const bool autoNextVideo) noexcept;
    void setAutoTopMost(const bool autoTopMost) noexcept;
    void setTorrentDownloadMode(const int torrentDownloadMode) noexcept;
    void setNotificationForFavorites(const bool notificationForFavorites) noexcept;
    void setJumpMinute(const int jumpMinute) noexcept;
    void setJumpSecond(const int jumpSecond) noexcept;
    void setShowReleaseInfo(const bool showReleaseInfo) noexcept;
    void setClearFiltersAfterChangeSection(const bool clearFiltersAfterChangeSection) noexcept;
    void setCompactMode(const bool compactMode) noexcept;

    void fromJson(QString json);
    QString toJson() noexcept;

};

#endif // USERSETTINGSMODEL_H
