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

#ifndef SCGCONTROL_H
#define SCGCONTROL_H

#include "scgobject.h"

class QGraphicsSceneMouseEvent;

/*! Class define any sc.g-control, that can be used in sc.g-window.
  * It allow to work with control types. Also it store whole information
  * that need to define control.
  * Control can be one of types:
  * \li noatom user commands. They can be opened by mouse click. After opening
  * child commands (relation decomposition*) will showed
  * \li class of user commands. They can be initiated by mouse click. Depending on command
  * type they start edit or view command, or initiade question.
  * \li controls that already associated with object, that they affect.
  * \li objects, that doesn't initiate anything, but can be used as arguments
  * to any command
  */
class SCgControl : public SCgObject
{
    friend class SCgConstruction;
    Q_OBJECT

public:
    explicit SCgControl(QObject *parent = 0);
    virtual ~SCgControl();

    //! Contol type
    typedef enum
    {
        Unlnown = 0,
        NoAtom,
        Class,
        Instance,
        Object
    } ControlType;

    //! @copydoc SCgObject::calculateDotCoordinates
    QPointF calculateDotCoordinates(qreal dotPosition, const QPointF &point) const;
    //! @copydoc SCgObject::calculateDotPosition
    qreal calculateDotPosition(const QPointF &point) const;

    //! @copydoc SCgObject::type
    int type() const { return Control; }

    /*! Return control type. This function gets control type by
      * using sc-memory. So it's no so fast.
      */
    ControlType controlType() const;

    /*! Get all child commands for noatom command
      * @param childs Result vector, where child commands ScUri's will be placed
      * @return Return true, if command have any childs; otherwise return false
      */
    bool childCommands(ScUriVector &childs);

private:
    //! Process initiation of noatom control
    void initiatedNoAtom();


signals:

public slots:
    /*! Initiate command. This function just change sc-memory state (to initiate agents)
      */
    void initiated();

};

#endif // SCGCONTROL_H
