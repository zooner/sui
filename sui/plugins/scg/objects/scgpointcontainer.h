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

#ifndef SCGPOINTCONTAINER_H
#define SCGPOINTCONTAINER_H

#include "scgobject.h"

/*! Base class for all sc.g-objects, that contains points.
  * It provides unified interfaces to work with points.
  */
class SCgPointContainer : public SCgObject
{
    Q_OBJECT
public:
    explicit SCgPointContainer(QObject *parent = 0);
    virtual ~SCgPointContainer();

    //! Append point to the end of list
    void appendPoint(const QPointF &point);
    //! Insert point in specified index
    void insertPoint(quint32 idx, const QPointF &point);
    //! Remove points with specified index
    void removePoint(quint32 idx);

    //! Return point with specified index
    const QPointF& point(quint32 idx) const;
    //! Return number of points
    quint32 pointsCount() const;
    //! Return points
    const QVector<QPointF>& points() const;


protected:
    //! List of points
    QVector<QPointF> mPoints;
};

#endif // SCGPOINTCONTAINER_H
