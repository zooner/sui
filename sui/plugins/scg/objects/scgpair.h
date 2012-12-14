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

#ifndef SCGPAIR_H
#define SCGPAIR_H

#include "scgpointcontainer.h"

/*! Sc.g-pair object is a sign of sc-pair. That type of object connect
  * other sc.g-objects. You can change begin and end sc.g-objects any time.
  * Also it has information about line points, that information used to visualize
  * sc.g-pair.
  * You can see an example of sc.g-pair object on image:
  * \image html scg/scg_pair_example.png
  * Sc.g-object \b 1 is an begin object for sc.g-pair, and sc.g-object \b 2 is
  * end object. Also you can see red and green points. They also can be
  * modified.
  * Green point - is a point where sc.g-pair connect to begin or end object.
  * Red point - is a point, where sc.g-pair can change direction. That useful
  * for layout.
  * You can get list of points by function SCgPair::points.
  *
  * Begin or end object of sc.g-pair can be any of sc.g-object types. So position
  * of connection point (green points) depend on that type. There is a dot position
  * data for a begin and end objects. It used to place connection point. There are
  * rules that used to calculate connector point coordinates for different type of
  * sc.g-objects:
  * \li sc.g-node
  * - dot position doens't affect to connection point for sc.g-nodes. Another words
  * if sc.g-pair calculate connection point for a sc.g-node object, then dot position
  * doesn't use. Connection point position will be at intersection of bound circle of
  * sc.g-node object and line segment, that start at N-1 line point (where N - is a number of
  * points) and end at sc.g-node center. See, example image:
  * \image html scg/scg_node_dot_example.png
  * \li sc.g-pair
  * - each sc.g-pair consist of line segments, so dot position point information about
  * line segment number and position in it. Float numbers used to store dot position.
  * Number before dot is an line segment number, where connection point need to be placed.
  * Number after dot is an proportional position in line segment. See image:
  * \image html scg/scg_pair_dot_example.png
  * \li sc.g-contour
  * - each sc.g-contour consist of line segments, so it works like sc.g-pair. See image:
  * \image html scg/scg_contour_dot_example.png
  * \li sc.g-bus
  * - use the same mechanism, like sc.g-pair. See image:
  * \image html scg/scg_bus_dot_example.png
  * \li sc.g-border
  * \li sc.g-control
  */
class SCgPair : public SCgPointContainer,
                public SCgObjectObserver
{
    friend class SCgConstruction;
    Q_OBJECT

protected:
    explicit SCgPair(QObject *parentObject = 0);
    virtual ~SCgPair();

public:

    //! @copydoc SCgObject::type
    int type() const { return Pair; }

    /*! Set begin sc.g-object for sc.g-pair
      * @param object Pointer to begin sc.g-object
      */
    void setBeginObject(SCgObject *object);

    //! Return pointer to begin sc.g-object
    SCgObject* beginObject() const { return mBeginObject; }

    /*! Set end sc.g-object for sc.g-pair
      * @param object Pointer to end sc.g-object
      */
    void setEndObject(SCgObject *object);

    //! Return pointer to end sc.g-object
    SCgObject* endObject() const { return mEndObject; }

    /*! Set new width for pair
      * @param width New pair width
      */
    void setLineWidth(qreal width);

    //! Return line width
    qreal lineWidth() const { return mLineWidth; }

    //! Set begin dot position
    void setBeginDotPosition(qreal dotPosition);
    //! Return begin dot position
    qreal beginDotPosition() const { return mBeginDotPos; }

    //! Set end dot position
    void setEndDotPosition(qreal dotPosition);
    //! Return end dot position
    qreal endDotPosition() const { return mEndDotPos; }

protected:
    //! @copydoc SCgObject::calculateDotCoordinates
    QPointF calculateDotCoordinates(qreal dotPosition, const QPointF &point) const;

    //! @copydoc SCgObject::calculateDotPosition
    qreal calculateDotPosition(const QPointF &point) const;

    //! @copydoc SCgObjectObserver::_update
    void _update(UpdateEventType eventType, SCgObject *object);

    void _notifyUpdate(SCgObjectObserver::UpdateEventType eventType);

public:
    //! Recalculate dot point coordinates
    void updateDotCoordinates();

private:
    //! Pointer to begin object
    SCgObject *mBeginObject;
    //! Pointer to end object
    SCgObject *mEndObject;
    //! Pair width
    qreal mLineWidth;
    //! Begin dot position
    qreal mBeginDotPos;
    //! End dot postion
    qreal mEndDotPos;
};

#endif // SCGPAIR_H
