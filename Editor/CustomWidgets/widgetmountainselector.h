/*
    RPG Paper Maker Copyright (C) 2017-2019 Wano

    RPG Paper Maker engine is under proprietary license.
    This source code is also copyrighted.

    Use Commercial edition for commercial use of your games.
    See RPG Paper Maker EULA here:
        http://rpg-paper-maker.com/index.php/eula.
*/

#ifndef WIDGETMOUNTAINSELECTOR_H
#define WIDGETMOUNTAINSELECTOR_H

#include <QWidget>
#include "systempicture.h"

// -------------------------------------------------------
//
//  CLASS WidgetMountainSelector
//
//  Widget used for panel textures for mountains.
//
// -------------------------------------------------------

namespace Ui {
class WidgetMountainSelector;
}

class WidgetMountainSelector : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetMountainSelector(QWidget *parent = nullptr);
    ~WidgetMountainSelector();

    void initializeTilesetPictureID(int pictureID);
    void updateAngle();

private:
    Ui::WidgetMountainSelector *ui;

public slots:
    void on_spinBoxSquareWidth_valueChanged(int);
    void on_spinBoxPixelWidth_valueChanged(int);
    void on_spinBoxSquareHeight_valueChanged(int);
    void on_spinBoxPixelHeight_valueChanged(int);
};

#endif // WIDGETMOUNTAINSELECTOR_H