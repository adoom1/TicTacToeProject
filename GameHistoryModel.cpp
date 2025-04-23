// GameHistoryModel.cpp
#include "GameHistoryModel.h"
#include "DBManager.h"

GameHistoryModel::GameHistoryModel(QObject *parent)
    : QAbstractTableModel(parent) {
    headers << "Date" << "Result" << "Opponent" << "Board State";
}

int GameHistoryModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;
    return historyData.size();
}

int GameHistoryModel::columnCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;
    return headers.size();
}

QVariant GameHistoryModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (index.row() >= (int)historyData.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        const GameRecord &record = historyData[index.row()];

        switch (index.column()) {
        case 0: return QString::fromStdString(record.date);
        case 1: return QString::fromStdString(record.result);
        case 2: return QString::fromStdString(record.opponent);
        case 3: return QString::fromStdString(record.boardState);
        default: return QVariant();
        }
    }
    return QVariant();
}

QVariant GameHistoryModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal && section < headers.size()) {
        return headers.at(section);
    }
    return QVariant();
}

void GameHistoryModel::loadHistory(const QString &username) {
    // Load game history from database
    historyData = DBManager::getInstance().getGameRecords(username.toStdString());

    // Notify views that data has changed
    beginResetModel();
    endResetModel();
}

void GameHistoryModel::addGameRecord(const QString &username, const QString &result, const QString &opponent) {
    GameRecord record(username.toStdString(), result.toStdString(), opponent.toStdString());

    // Save to database using DBManager
    DBManager::getInstance().saveGameRecord(record);

    // Refresh history from database
    loadHistory(username);
}
