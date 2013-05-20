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

#include "menuitemmodel.h"
#include "sizableItems/textsizableitem.h"

#include <QAction>

MenuItemModel::MenuItemModel(QAction* action, AbstractSizableItem* item,
                             MenuItemModel* parent) :
    mLeafCount(0), mParentItem(parent), mAction(action),
    mDisplayedItem(item)
{
    initialize();
}

MenuItemModel::MenuItemModel(QAction* action, const QString& text,
                             MenuItemModel* parent) :
    mLeafCount(0), mParentItem(parent), mAction(action)
{
    mDisplayedItem = new TextSizableItem(text);
    initialize();
}

MenuItemModel::MenuItemModel(QAction* action, MenuItemModel* parent) :
    mLeafCount(0), mParentItem(parent), mAction(action)
{
    mDisplayedItem = new TextSizableItem(action->text());
    initialize();
}

void MenuItemModel::initialize()
{
    if (mParentItem)
        mParentItem->addChildItem(this);
    setParent(mParentItem);
//    if(mAction)
//        mAction->setParent(this);
    Q_ASSERT(mDisplayedItem->graphicsItem());
}

MenuItemModel::~MenuItemModel()
{

}

QAction* MenuItemModel::action()
{
    return mAction;
}

AbstractSizableItem* MenuItemModel::displayedItem()
{
    return mDisplayedItem;
}

void MenuItemModel::addChildItem(MenuItemModel* childItem)
{
    if (childItem == 0)
        return;

    mChildMenus.append(childItem);
    childItem->mParentItem = this;
    childItem->setParent(this);

    recalcLeafCount();

    emit(childAdded(childItem));
}

void MenuItemModel::recalcLeafCount()
{
    mLeafCount = 0;
    if (mChildMenus.isEmpty())
        return;

    foreach(MenuItemModel* m, mChildMenus)
    {
        if (m->mLeafCount == 0)
            ++mLeafCount;
        else
            mLeafCount += m->mLeafCount;
    }
    if (mParentItem)
        mParentItem->recalcLeafCount();
}
