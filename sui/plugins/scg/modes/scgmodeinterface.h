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

#ifndef SCGMODEINTERFACE_H_
#define SCGMODEINTERFACE_H_


#include "interfaces/SCgInputHandlerInterface.h"
#include "scgscenebase.h"

#include <QGraphicsSceneMouseEvent>

/*! Interface for managing different handler states.
 * You receive each event twice: before scene processin and after.
 * \attention All events are real-time. Handlers shuld be as fast as possible.
 * Use \b afterSceneEvent flag.
 * You could suppress further event processing by accepting event then \b afterSceneEvent is false.
 */
class SCgModeInterface
{
public:

    explicit SCgModeInterface(SCgInputHandlerInterface* inputHandler, SCgModeInterface* childMode)
        :mInputHandler(inputHandler), mDecoratedMode(childMode) {}

    virtual ~SCgModeInterface() {}


    virtual void keyPressEvent ( QKeyEvent * keyEvent ) = 0;
    //! @copydoc QGraphicsScene::keyReleaseEvent
    virtual void keyReleaseEvent ( QKeyEvent * keyEvent) = 0;
    //! @copydoc QGraphicsScene::mouseDoubleClickEvent
    virtual void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent) = 0;
    //! @copydoc QGraphicsScene::mouseMoveEvent
    virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent, bool afterSceneEvent ) = 0;
    //! @copydoc QGraphicsScene::mousePressEvent
    virtual void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent, bool afterSceneEvent ) = 0;
    //! @copydoc QGraphicsScene::mouseReleaseEvent
    virtual void mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent, bool afterSceneEvent ) = 0;

    /*! Called then this mode is become active.
     * Here you should provide some initial code you'll need.
     */
    virtual void activate() = 0;

    /*! Called when handler state is become to change
     *  to clear unfinished operations or whole state of current mode.
     */
    virtual void deactivate() = 0;

protected:
    SCgSceneBase* scene() const { return mInputHandler->scene(); }
    SCgInputHandlerInterface* mInputHandler;

    SCgModeInterface* mDecoratedMode;
};


#endif /* SCGMODEINTERFACE_H_ */
