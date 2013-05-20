/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2011 OSTIS

OSTIS is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OSTIS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OSTIS.  If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------------
*/

#ifndef SUNMENULAYER_H_
#define SUNMENULAYER_H_

#include <QGraphicsItem>
#include <QBrush>
#include <QPen>

class SunMenuItemView;
class SunMenuRepresentation;
class MenuItemModel;
class AbstractMenuBehavior;

class SunMenuLayer: public QObject
{
    Q_OBJECT

    Q_PROPERTY(qint32 innerRadius READ innerRadius WRITE setInnerRadius /*NOTIFY innerRadiusChanged*/)
    Q_PROPERTY(qint32 width READ width WRITE setWidth/* NOTIFY widthChanged*/)

public:
    // Specifies parameter, which isn't changed while inner radius is changing.
    enum ConstantParameterEnum
    {
        ConstantWidth,
        ConstantOuterRadius
    };

    explicit SunMenuLayer(SunMenuRepresentation* representation, SunMenuItemView* parentMenu = 0);

    virtual ~SunMenuLayer();

    qreal startAngle() const;
    qreal sweepLength() const;

    SunMenuItemView* parentMenu() const;
    SunMenuLayer* parentLayer() const;

    SunMenuRepresentation* representation() const;

    QList<SunMenuItemView*> childMenuItems() const;

    void setInnerRadius(qint32 value);
    void setWidth(qint32 value);
    qint32 innerRadius() const;
    qint32 width() const;

    void addMenuItem(MenuItemModel* item);

    void hide();
    void show();
    bool isVisible() const;
    bool isFolding() const;
    void setFolding(bool value);

    void setConstantParameter(ConstantParameterEnum constantParameter);
    ConstantParameterEnum constantParameter() const;

private:

    void initialize();

    SunMenuRepresentation* mRepresentation;
    SunMenuItemView* mParentItem;

    QList<SunMenuItemView*> mMenuItems;

    bool mIsVisible;
    bool mIsFolding;

    qint32 mInnerRadius;
    qint32 mWidth;

    ConstantParameterEnum mConstantParameter;
};

#endif /* SUNMENULAYER_H_ */
