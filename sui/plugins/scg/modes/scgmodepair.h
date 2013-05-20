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

#ifndef SCGMODEPAIR_H_
#define SCGMODEPAIR_H_


#include "scgmodeinterface.h"

#include <QObject>
#include <QPointer>

class SCgPathItem;

class SCgModePair: public QObject, public SCgModeInterface
{
    Q_OBJECT
public:
    explicit SCgModePair(SCgInputHandlerInterface* inputHandler, SCgModeInterface *childMode = 0);

    virtual ~SCgModePair();

    //! @copydoc QGraphicsScene::keyPressEvent
    void keyPressEvent ( QKeyEvent * keyEvent ) ;
    //! @copydoc QGraphicsScene::keyReleaseEvent
    void keyReleaseEvent ( QKeyEvent * keyEvent );
    //! @copydoc QGraphicsScene::mouseDoubleClickEvent
    void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    //! @copydoc QGraphicsScene::mouseMoveEvent
    void mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent, bool afterSceneEvent );
    //! @copydoc QGraphicsScene::mousePressEvent
    void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent, bool afterSceneEvent );
    //! @copydoc QGraphicsScene::mouseReleaseEvent
    void mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent, bool afterSceneEvent );


    /*! Called then this mode is become active.
     * Here you should provide some initial code you'll need.
     */
    void activate();

    /*! Called when handler state is become to change
     *  to clear unfinished operations or whole state of current mode.
     */
    void deactivate();

    void startPairCreation(SCgVisualObject *obj, const QPointF &scenePoint);
signals:
    void operationCompleted(bool success);

private:
    void endPairCreation(bool success);
    QPointer<SCgPathItem> mPathItem;
    QPointer<SCgVisualObject> mObjectAtFirstPoint;

    bool mPassMouseReleaseEvent;
};

#endif /* SCGMODEPAIR_H_ */
