#include "myanilibrialistmodel.h"
#include "../../globalconstants.h"

MyAnilibriaListModel::MyAnilibriaListModel(QObject *parent)
    : QAbstractListModel{parent}
{
    m_fullSections.insert(StatisticsSectionId);
    m_fullSections.insert(NewInFavoritesSectionId);
    m_fullSections.insert(NewFromStartSectionId);
    m_fullSections.insert(LastTwoDaysSectionId);
    m_fullSections.insert(AbandonedSeensSectionId);

    m_sections.append(StatisticsSectionId);
    m_sections.append(NewInFavoritesSectionId);
    m_sections.append(NewFromStartSectionId);
    m_sections.append(LastTwoDaysSectionId);
    m_sections.append(AbandonedSeensSectionId);

    m_sectionTitles.insert(StatisticsSectionId, "Статистика");
    m_sectionTitles.insert(NewInFavoritesSectionId, "Обновления по избранному");
    m_sectionTitles.insert(NewFromStartSectionId, "Обновления с последнего посещения");
    m_sectionTitles.insert(LastTwoDaysSectionId, "Последние обновления");
    m_sectionTitles.insert(AbandonedSeensSectionId, "Брошенный просмотр");
}

int MyAnilibriaListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return m_sections.size();
}

QVariant MyAnilibriaListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();

    auto section = m_sections.at(index.row());
    auto title = m_sectionTitles.value(section);

    switch (role) {
        case SectionIdRole: {
            return QVariant(section);
        }
        case SectionTitleRole: {
            return QVariant(title);
        }
        case ComponentIdRole: {
            if (section == StatisticsSectionId) {
                return QVariant(StatisticsSectionComponent);
            } else {
                return QVariant(SimpleListSectionComponent);
            }
        }
        case HeaderVisibleRole: {
            return QVariant(getHideSection(section));
        }
    }

    return QVariant();
}

QHash<int, QByteArray> MyAnilibriaListModel::roleNames() const
{
    return {
        {
            SectionIdRole,
            "sectionId"
        },
        {
            SectionTitleRole,
            "title"
        },
        {
            ComponentIdRole,
            "componentId"
        },
        {
            HeaderVisibleRole,
            "needHideSection"
        }
    };
}

void MyAnilibriaListModel::setUserConfiguration(const UserConfigurationViewModel *userConfiguration) noexcept
{
    if (m_userConfiguration == userConfiguration) return;

    m_userConfiguration = const_cast<UserConfigurationViewModel *>(userConfiguration);
    emit userConfigurationChanged();
}

void MyAnilibriaListModel::fillSections(const QSet<QString> &sections) noexcept
{
    m_sections.clear();

    foreach (auto section, sections) {
        if (!m_fullSections.contains(section)) continue;

        m_sections.append(section);
    }
}

QStringList MyAnilibriaListModel::getSections() const noexcept
{
    return m_sections;
}

void MyAnilibriaListModel::setSectionHideMark(const QString &section, const bool notVisible) noexcept
{
    if (section == StatisticsSectionId) m_userConfiguration->setHideStatistics(notVisible);
    if (section == NewInFavoritesSectionId) m_userConfiguration->setHideUpdatesByFavorites(notVisible);
    if (section == NewFromStartSectionId) m_userConfiguration->setHideUpdatesFromStart(notVisible);
    if (section == LastTwoDaysSectionId) m_userConfiguration->setHideUpdatesLastTwoDays(notVisible);
    if (section == AbandonedSeensSectionId) m_userConfiguration->setHideAbandonedSeens(notVisible);
}

void MyAnilibriaListModel::toggleSectionHideMark(const QString &section)
{
    if (section == StatisticsSectionId) {
        auto current = m_userConfiguration->hideStatistics();
        m_userConfiguration->setHideStatistics(!current);
    }
    if (section == NewInFavoritesSectionId) {
        auto current = m_userConfiguration->hideUpdatesByFavorites();
        m_userConfiguration->setHideUpdatesByFavorites(!current);
    }
    if (section == NewFromStartSectionId) {
        auto current = m_userConfiguration->hideUpdatesFromStart();
        m_userConfiguration->setHideUpdatesFromStart(!current);
    }
    if (section == LastTwoDaysSectionId) {
        auto current = m_userConfiguration->hideUpdatesLastTwoDays();
        m_userConfiguration->setHideUpdatesLastTwoDays(!current);
    }
    if (section == AbandonedSeensSectionId) {
        auto current = m_userConfiguration->hideAbandonedSeens();
        m_userConfiguration->setHideAbandonedSeens(!current);
    }

    auto itemIndex = m_sections.indexOf(section);
    if (itemIndex == -1) return;

    emit dataChanged(index(itemIndex,0), index(itemIndex,0));
}

void MyAnilibriaListModel::setNotVisibleAllMarks(const bool visible)
{
    beginResetModel();

    foreach (auto section, m_sections) {
        setSectionHideMark(section, visible);
    }

    endResetModel();
}

bool MyAnilibriaListModel::getHideSection(const QString &section) const noexcept
{
    if (section == StatisticsSectionId) {
        return m_userConfiguration->hideStatistics();
    }
    if (section == NewInFavoritesSectionId) {
        return m_userConfiguration->hideUpdatesByFavorites();
    }
    if (section == NewFromStartSectionId) {
        return m_userConfiguration->hideUpdatesFromStart();
    }
    if (section == LastTwoDaysSectionId) {
        return m_userConfiguration->hideUpdatesLastTwoDays();
    }
    if (section == AbandonedSeensSectionId) {
        return m_userConfiguration->hideAbandonedSeens();
    }

    return false;
}