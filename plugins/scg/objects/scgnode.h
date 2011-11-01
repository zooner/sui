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

#ifndef SCGNODE_H
#define SCGNODE_H

#include "scgobject.h"

class SCgNode : public SCgObject
{
    friend class SCgConstruction;

    Q_OBJECT

protected:
    explicit SCgNode(QObject *parentObject = 0);
    virtual ~SCgNode();

    //! @see SCgObject::calculateDotCoordinates
    QPointF calculateDotCoordinates(qreal dotPosition, const QPointF &point) const;

    //! @see SCgObject::calculateDotPosition
    qreal calculateDotPosition(const QPointF &point) const;

public:

private:

};

#endif // SCGNODE_H
