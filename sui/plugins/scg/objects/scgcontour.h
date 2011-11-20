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

#ifndef SCGCONTOUR_H
#define SCGCONTOUR_H

#include "scgpointcontainer.h"

/*! Class represents sc.g-contour object.
  * \chapter Coordinate system.
  * All coordinate sof contour points must to bee relative to it position.
  */
class SCgContour : public SCgPointContainer
{
    Q_OBJECT
public:
    explicit SCgContour(QObject *parent = 0);
    virtual ~SCgContour();

    //! @see SCgObject::calculateDotCoordinates
    QPointF calculateDotCoordinates(qreal dotPosition, const QPointF &point) const;

    //! @see SCgObject::calculateDotPosition
    qreal calculateDotPosition(const QPointF &point) const;

    /*! Set new border accuracy
      * @param value New border accuracy
      */
    void setBorderAccuracy(qreal value);

    //! Return border accuracy
    qreal borderAccuracy() const;

    //! @copydoc SCgObject::type
    int type() const { return Contour; }

private:
    //! Bodred accuracy value
    qreal mBorderAccuracy;

signals:

public slots:

};

#endif // SCGCONTOUR_H
