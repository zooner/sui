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

#include "sunmenulayer.h"
#include "sunmenuIiemview.h"

#include <QtCore/QtCore>

SunMenuLayer::SunMenuLayer(SunMenuRepresentation* representation,
                           SunMenuItemView* parentMenu) :
    mRepresentation(representation), mParentItem(parentMenu),
    mIsVisible(true), mConstantParameter(ConstantWidth)
{
    initialize();
}

SunMenuLayer::~SunMenuLayer()
{

}

SunMenuLayer::ConstantParameterEnum SunMenuLayer::constantParameter() const
{
    return mConstantParameter;
}

void SunMenuLayer::setConstantParameter(ConstantParameterEnum constantParameter)
{
    mConstantParameter = constantParameter;
}

void SunMenuLayer::initialize()
{
    setParent(mParentItem);
    mInnerRadius = 0;
    mWidth = 0;
}

SunMenuItemView* SunMenuLayer::parentMenu() const
{
    return mParentItem;
}

SunMenuLayer* SunMenuLayer::parentLayer() const
{
    if (!mParentItem)
        return 0;

    return mParentItem->parentLayer();
}

QList<SunMenuItemView*> SunMenuLayer::childMenuItems() const
{
    return mMenuItems;
}

qreal SunMenuLayer::startAngle() const
{
    if (mParentItem)
        return mParentItem->startAngle();
    else
        return 0;
}

qreal SunMenuLayer::sweepLength() const
{
    if (mParentItem)
        return mParentItem->sweepLength();
    else
        return 360;
}

void SunMenuLayer::hide()
{
    mIsVisible = false;
    foreach(SunMenuItemView* mc, mMenuItems)
        mc->hide();
}

void SunMenuLayer::show()
{
    mIsVisible = true;
    foreach(SunMenuItemView* mc, mMenuItems)
        mc->show();
}

bool SunMenuLayer::isVisible() const
{
    return mIsVisible;
}

bool SunMenuLayer::isFolding() const
{
    return mIsFolding;
}

void SunMenuLayer::setFolding(bool value)
{
    mIsFolding = value;
}

SunMenuRepresentation* SunMenuLayer::representation() const
{
    return mRepresentation;
}

void SunMenuLayer::addMenuItem(MenuItemModel* item)
{
    foreach(SunMenuItemView* mc, mMenuItems)
        if (mc->mItemModel == item)
            return;

    SunMenuItemView* newItem = new SunMenuItemView(this, item, mParentItem);

    newItem->setWidth(mWidth);
    if (mParentItem)
        newItem->setInnerRadius(
                    mParentItem->innerRadius() + mParentItem->width());
    else
        newItem->setInnerRadius(mInnerRadius);

    newItem->setVisible(mIsVisible);
    mMenuItems.append(newItem);
}

void SunMenuLayer::setInnerRadius(qint32 value)
{
    if(mConstantParameter == ConstantOuterRadius)
        mWidth += (mInnerRadius - value);
    mInnerRadius = value;
    foreach(SunMenuItemView* mc, mMenuItems)
        mc->setInnerRadius(mInnerRadius);
}

void SunMenuLayer::setWidth(qint32 value)
{
    mWidth = value;
    foreach(SunMenuItemView* mc, mMenuItems)
        mc->setWidth(mWidth);
}

qint32 SunMenuLayer::innerRadius() const
{
    return mInnerRadius;
}

qint32 SunMenuLayer::width() const
{
    return mWidth;
}
