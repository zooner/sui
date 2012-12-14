/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010 OSTIS

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

#ifndef SCGVISUALNODE_H
#define SCGVISUALNODE_H

#include "scgvisualobject.h"
#include "scgcontent.h"


class SCgVisualBus;
//class SCgContentViewer;

class SCgVisualNode : public SCgVisualObject
{
    Q_OBJECT

protected:
    friend class SCgVisualObject;
    explicit SCgVisualNode(QGraphicsScene *scene = 0);
public:
    //! Type for qgraphicsitem_cast
    int type() const { return SCgNodeType; }

    virtual ~SCgVisualNode();

private:
    //! Type information update
    void updateType();

protected:
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void paintStruct(QPainter *painter);

public:
    void updatePosition();



signals:


public slots:

};

#endif // SCGNODE_H
