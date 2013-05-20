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

#ifndef SUNMENUREPRESENTATION_H_
#define SUNMENUREPRESENTATION_H_

#include <QObject>
#include <QMap>
#include <QPair>
#include <QBrush>

class QGraphicsItem;
class QGraphicsItemGroup;
class AbstractMenuBehavior;
class SunMenuItemView;
class SunMenuLayer;
class MenuItemModel;

class SunMenuRepresentation: public QObject
{
    Q_OBJECT
    friend class SunMenuLayer;
public:
    explicit SunMenuRepresentation(AbstractMenuBehavior *behavior = 0);
    virtual ~SunMenuRepresentation();

    void addRepresentedMenu(MenuItemModel* newMenu);
    QList<SunMenuItemView*> representedMenus() const;

    QGraphicsItem* menuItem();

    SunMenuLayer* parentLayer() const;

    qint32 treeHeight(bool onlyVisible = true) const;
    QList<SunMenuLayer*> layers(bool onlyVisible = true) const;

    void setBehavior(AbstractMenuBehavior* behavior);
    AbstractMenuBehavior* behavior() const;

    QBrush brush() const;
    void setBrush(const QBrush& brush);

    /*!
     * Inner radius for root menu. If root menu consists of a single item - means nothing.
     */
    qreal innerRadius() const;
    void setInnerRadius(qreal radius);

    bool menuContainsPoint(const QPointF &scenePoint);

    QPointF scenePos();

    void assoiciateWith(QObject* object);
    QObject* associatedObject() const;

    //! Collapses submenu and restores the original dimensions
    void resetMenu();
signals:
    void brushChanged(const QBrush& brush);

private:
    void recalculateMenuAngles();

    AbstractMenuBehavior* mBehavior;
    SunMenuLayer* mParentLayer;
    qreal mInnerRadius;

    QBrush mDefaultMenuBrush;
    QGraphicsItemGroup* mResultGroup;

    QObject* mAssociatedObject;
};

#endif /* SUNMENUREPRESENTATION_H_ */
