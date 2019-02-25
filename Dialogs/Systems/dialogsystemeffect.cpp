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

#include <QGridLayout>
#include "dialogsystemeffect.h"
#include "ui_dialogsystemeffect.h"

// -------------------------------------------------------
//
//  CONSTRUCTOR / DESTRUCTOR / GET / SET
//
// -------------------------------------------------------

DialogSystemEffect::DialogSystemEffect(SystemEffect &effect, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSystemEffect),
    m_effect(effect)
{
    ui->setupUi(this);

    initialize();
}

DialogSystemEffect::~DialogSystemEffect() {
    delete ui;
}

SystemEffect & DialogSystemEffect::effect() const {
    return m_effect;
}

// -------------------------------------------------------
//
//  INTERMEDIARY FUNCTIONS
//
// -------------------------------------------------------

void DialogSystemEffect::initialize() {
    ui->panelDamagesKind->initialize(m_effect.damagesStatisticID(), m_effect
        .damagesCurrencyID(), m_effect.damagesVariableID(), m_effect
        .damagesKind());
}
