/*
    RPG Paper Maker Copyright (C) 2017-2019 Marie Laporte

    RPG Paper Maker engine is under LGPL-3 license.

    Commercial license for commercial use of your games:
        https://creativecommons.org/licenses/by-nc/4.0/.

    See more information here: http://rpg-paper-maker.com/index.php/downloads.
*/

#include "troopsdatas.h"
#include "rpm.h"
#include "common.h"
#include "systemtroop.h"
#include "systemmonstertroop.h"

// -------------------------------------------------------
//
//  CONSTRUCTOR / DESTRUCTOR / GET / SET
//
// -------------------------------------------------------

TroopsDatas::TroopsDatas()
{
    m_model = new QStandardItemModel;
}

TroopsDatas::~TroopsDatas()
{
    SuperListItem::deleteModel(m_model);
}

void TroopsDatas::read(QString path){
    RPM::readJSON(Common::pathCombine(path, RPM::pathTroops), *this);
}

QStandardItemModel* TroopsDatas::model() const { return m_model; }

// -------------------------------------------------------
//
//  INTERMEDIARY FUNCTIONS
//
// -------------------------------------------------------

void TroopsDatas::setDefault(QStandardItem *modelMonsters){
    SystemTroop* sysTroop;
    SystemMonsterTroop* sysMonsterTroop;
    QStandardItem* itemMonster;
    QStandardItem* itemLevel;
    QStandardItem* item;
    SuperListItem* monster;
    int id;
    int level;
    QList<QStandardItem *> row;
    QStandardItemModel* monsters;
    QString names[] = {"Wooly[1]", "Wooly[1][1]", "Wooly[5]"};
    QVector<int> idsMonsters[] = {QVector<int>({1}), QVector<int>({1, 1}),
        QVector<int>({1})};
    QVector<int> levels[] = {QVector<int>({1}), QVector<int>({1, 1}),
        QVector<int>({5})};

    int length = (sizeof(names)/sizeof(*names));

    for (int i = 0; i < length; i++){

        // Monsters list
        monsters = new QStandardItemModel;
        for (int j = 0; j < idsMonsters[i].size(); j++){
            row = QList<QStandardItem*>();
            id = idsMonsters[i][j];
            monster = SuperListItem::getById(modelMonsters, id);
            level = levels[i][j];
            sysMonsterTroop = new SystemMonsterTroop(id, monster->name(),
                                                     level);
            itemMonster = new QStandardItem;
            itemMonster->setData(
                        QVariant::fromValue(
                            reinterpret_cast<quintptr>(sysMonsterTroop)));
            itemMonster->setText(sysMonsterTroop->toString());
            itemLevel = new QStandardItem;
            itemLevel->setData(QVariant::fromValue(level));
            itemLevel->setText(QString::number(level));
            row.append(itemMonster);
            row.append(itemLevel);
            monsters->appendRow(row);
        }
        item = new QStandardItem();
        item->setText(SuperListItem::beginningText);
        monsters->appendRow(item);

        // System troop
        sysTroop = new SystemTroop(i+1, names[i], monsters);
        item = new QStandardItem;
        item->setData(QVariant::fromValue(
                          reinterpret_cast<quintptr>(sysTroop)));
        item->setText(sysTroop->toString());
        m_model->appendRow(item);
    }
}

// -------------------------------------------------------
//
//  READ / WRITE
//
// -------------------------------------------------------

void TroopsDatas::read(const QJsonObject &json){

    // Clear
    SuperListItem::deleteModel(m_model, false);

    // Read
    QJsonArray jsonList = json["troops"].toArray();
    for (int i = 0; i < jsonList.size(); i++){
        QStandardItem* item = new QStandardItem;
        SystemTroop* sysTroop = new SystemTroop;
        sysTroop->read(jsonList[i].toObject());
        item->setData(QVariant::fromValue(
                          reinterpret_cast<quintptr>(sysTroop)));
        item->setFlags(item->flags() ^ (Qt::ItemIsDropEnabled));
        item->setText(sysTroop->toString());
        m_model->appendRow(item);
    }
}

// -------------------------------------------------------

void TroopsDatas::write(QJsonObject &json) const{
    QJsonArray jsonArray;
    for (int i = 0; i < m_model->invisibleRootItem()->rowCount(); i++){
        QJsonObject jsonCommon;
        SystemTroop* sysTroop = ((SystemTroop*)m_model->item(i)->data()
                                 .value<quintptr>());
        sysTroop->write(jsonCommon);
        jsonArray.append(jsonCommon);
    }
    json["troops"] = jsonArray;
}