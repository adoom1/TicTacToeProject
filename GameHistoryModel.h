// GameHistoryModel.h
#ifndef GAMEHISTORYMODEL_H
#define GAMEHISTORYMODEL_H

#include <QAbstractTableModel>
#include <vector>
#include "Game.h"

using namespace std; // Added: using namespace std

class GameHistoryModel : public QAbstractTableModel {
    Q_OBJECT

public:
    explicit GameHistoryModel(QObject *parent = nullptr);

    // Required overrides for QAbstractTableModel
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Custom methods for managing game history
    void loadHistory(const QString &username);
    void addGameRecord(const QString &username, const QString &result, const QString &opponent);

private:
    vector<GameRecord> historyData;
    QStringList headers;
};

#endif // GAMEHISTORYMODEL_H
