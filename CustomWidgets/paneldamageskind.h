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

#ifndef PANELDAMAGESKIND_H
#define PANELDAMAGESKIND_H

#include <QWidget>
#include "primitivevalue.h"

// -------------------------------------------------------
//
//  CLASS PanelDamagesKind
//
//  The panel for damages and costs.
//
// -------------------------------------------------------

namespace Ui {
class PanelDamagesKind;
}

class PanelDamagesKind : public QWidget
{
    Q_OBJECT

public:
    explicit PanelDamagesKind(QWidget *parent = nullptr);
    ~PanelDamagesKind();

    void initialize(PrimitiveValue *statisticID, PrimitiveValue *currencyID,
        SuperListItem *variableID, SuperListItem *kind);
    void hideAll();
    void showElement();

private:
    Ui::PanelDamagesKind *ui;
    PrimitiveValue *m_statisticID;
    PrimitiveValue *m_currencyID;
    SuperListItem *m_variableID;
    SuperListItem *m_kind;

public slots:
    void on_comboBoxChoice_currentIndexChanged(int index);
};

#endif // PANELDAMAGESKIND_H
