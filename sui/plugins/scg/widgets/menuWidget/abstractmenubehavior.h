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

#ifndef ABSTRACTMENUBEHAVIOR_H_
#define ABSTRACTMENUBEHAVIOR_H_

#include <QFocusEvent>
#include <QtGui>

class SunMenuItemView;

class AbstractMenuBehavior
{
public:
    virtual ~AbstractMenuBehavior();
    AbstractMenuBehavior();

    virtual void focusInEvent(SunMenuItemView* eventReciever,
                              QFocusEvent* event) = 0;
    virtual void focusOutEvent(SunMenuItemView* eventReciever,
                               QFocusEvent* event) = 0;

    virtual void hoverEnterEvent(SunMenuItemView* eventReciever,
                                 QGraphicsSceneHoverEvent* event) = 0;
    virtual void hoverLeaveEvent(SunMenuItemView* eventReciever,
                                 QGraphicsSceneHoverEvent* event) = 0;
    virtual void hoverMoveEvent(SunMenuItemView* eventReciever,
                                QGraphicsSceneHoverEvent* event) = 0;

    virtual void keyPressEvent(SunMenuItemView* eventReciever,
                               QKeyEvent* event) = 0;
    virtual void keyReleaseEvent(SunMenuItemView* eventReciever,
                                 QKeyEvent* event) = 0;

    virtual void mouseDoubleClickEvent(SunMenuItemView* eventReciever,
                                       QGraphicsSceneMouseEvent* event) = 0;
    virtual void mouseMoveEvent(SunMenuItemView* eventReciever,
                                QGraphicsSceneMouseEvent* event) = 0;
    virtual void mousePressEvent(SunMenuItemView* eventReciever,
                                 QGraphicsSceneMouseEvent* event) = 0;
    virtual void mouseReleaseEvent(SunMenuItemView* eventReciever,
                                   QGraphicsSceneMouseEvent* event) = 0;

    virtual int maxMenuRadius() const = 0;

    virtual void reset() = 0;
};

#endif /* ABSTRACTMENUBEHAVIOR_H_ */
