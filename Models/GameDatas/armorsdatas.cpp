/*
    RPG Paper Maker Copyright (C) 2017-2019 Marie Laporte

    This file is part of RPG Paper Maker.

    RPG Paper Maker is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    RPG Paper Maker is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "armorsdatas.h"
#include "systemarmor.h"
#include "rpm.h"
#include "common.h"
#include "systemcaracteristic.h"

// -------------------------------------------------------
//
//  CONSTRUCTOR / DESTRUCTOR / GET / SET
//
// -------------------------------------------------------

ArmorsDatas::ArmorsDatas() {
    m_model = new QStandardItemModel;
}

ArmorsDatas::~ArmorsDatas()
{
    SuperListItem::deleteModel(m_model);
}

void ArmorsDatas::read(QString path){
    RPM::readJSON(Common::pathCombine(path, RPM::pathArmors), *this);
}

QStandardItemModel* ArmorsDatas::model() const { return m_model; }

// -------------------------------------------------------
//
//  INTERMEDIARY FUNCTIONS
//
// -------------------------------------------------------

void ArmorsDatas::setDefault() {
    int i, j, length, l;
    QStandardItemModel * modelCaracteristics;
    SystemArmor *armor;

    QString names[] = {
        "Dress"
    };
    int iconsID[] = {
        1
    };
    int types[] = {
        4
    };
    QString descriptions[] = {
        "A thin dress."
    };
    int prices[] = {
        30
    };
    QVector<SystemCaracteristic *> caracteristics[] = {
        {SystemCaracteristic::createBuff(10, 5, false, false)}
    };
    length = (sizeof(names)/sizeof(*names));

    for (i = 0; i < length; i++) {
        modelCaracteristics = new QStandardItemModel;
        for (j = 0, l = caracteristics[i].length(); j < l; j++) {
            modelCaracteristics->appendRow(caracteristics[i][j]->getModelRow());
        }
        modelCaracteristics->appendRow(new QStandardItem);
        armor = new SystemArmor(i + 1, new LangsTranslation(names[i]), iconsID
            [i], types[i], new LangsTranslation(descriptions[i]), new
            PrimitiveValue(PrimitiveValueKind::None), new PrimitiveValue(prices
            [i]), modelCaracteristics);
        m_model->appendRow(armor->getModelRow());
    }
}

// -------------------------------------------------------
//
//  READ / WRITE
//
// -------------------------------------------------------

void ArmorsDatas::read(const QJsonObject &json){

    // Clear
    SuperListItem::deleteModel(m_model, false);

    // Read
    QJsonArray jsonList = json["armors"].toArray();
    for (int i = 0; i < jsonList.size(); i++){
        QStandardItem* item = new QStandardItem;
        SystemArmor* sysArmor = new SystemArmor;
        sysArmor->read(jsonList[i].toObject());
        item->setData(
                    QVariant::fromValue(reinterpret_cast<quintptr>(sysArmor)));
        item->setFlags(item->flags() ^ (Qt::ItemIsDropEnabled));
        item->setText(sysArmor->toString());
        m_model->appendRow(item);
    }
}

// -------------------------------------------------------

void ArmorsDatas::write(QJsonObject &json) const{
    QJsonArray jsonArray;
    for (int i = 0; i < m_model->invisibleRootItem()->rowCount(); i++){
        QJsonObject jsonCommon;
        SystemArmor* sysArmor =
                ((SystemArmor*)m_model->item(i)->data().value<quintptr>());
        sysArmor->write(jsonCommon);
        jsonArray.append(jsonCommon);
    }
    json["armors"] = jsonArray;
}
