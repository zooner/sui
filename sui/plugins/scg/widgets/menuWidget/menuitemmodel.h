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

#ifndef MENUITEMMODEL_H_
#define MENUITEMMODEL_H_

#include "sizableItems/abstractsizableitem.h"
#include <QObject>

class QAction;

class MenuItemModel: public QObject
{
    Q_OBJECT
public:
    /*! The class takes control over an action item (i.e. it becomes action's parent)
     */
    MenuItemModel(QAction* action, AbstractSizableItem* item,
                  MenuItemModel* parent = 0);

    MenuItemModel(QAction* action, const QString& text, MenuItemModel* parent =
            0);

    MenuItemModel(QAction* action, MenuItemModel* parent = 0);

    virtual ~MenuItemModel();

    QAction* action();
    AbstractSizableItem* displayedItem();

    void addChildItem(MenuItemModel* childItem);
    MenuItemModel* parentMenu() const
    {
        return mParentItem;
    }

    QList<MenuItemModel*> childMenus() const
    {
        return mChildMenus;
    }

    qint32 leafCount() const
    {
        return mLeafCount;
    }

signals:
    void childAdded(MenuItemModel* newChild);

private:
    void initialize();
    void recalcLeafCount();

    qint32 mLeafCount;

    MenuItemModel* mParentItem;

    QAction* mAction;
    AbstractSizableItem* mDisplayedItem;

    QList<MenuItemModel*> mChildMenus;
};
#endif //MENUITEMMODEL_H_
