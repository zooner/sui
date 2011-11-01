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

#ifndef SCGMAINWINDOWSCENE_H
#define SCGMAINWINDOWSCENE_H

#include "scgscenebase.h"

class SCgInputHandlerInterface;

class SCgMainWindowScene : public SCgSceneBase
{
    Q_OBJECT
public:
    explicit SCgMainWindowScene(SCgInputHandlerInterface *inputHandler, QObject *parent = 0);
    virtual ~SCgMainWindowScene();

    //! @copydoc SCgConstructionObserver::_update
    void _update(SCgConstructionObserver::UpdateEventType eventType, QObject *object);

    /*! Get sc.g-object at specified point with maximum Z-value
      * @param point Point coordinates
      * @return Return pointer to any founded sc.g-object, if there are no
      * any sc.g-object in that point, then return \b null pointer
      */
    SCgObject* scgObjectAt(const QPointF& point) const;

    /*! Get visual sc.g-object at specified point.
      * This function does the same as SCgSceneBase::scgObjectAt, but
      * return pointer to SCgVisualObject
      */
    SCgVisualObject* scgVisualObjectAt(const QPointF& point) const;

private:
    //! Process object created event
    void _processEventObjectCreated(QObject *object);
    //! Process object deleted event
    void _processEventObjectDeleted(QObject *object);

signals:

public slots:

};

#endif // SCGMAINWINDOWSCENE_H
