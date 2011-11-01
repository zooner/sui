/*
 * scgmodeselect.h
 *
 *  Created on: 14.07.2011
 *      Author: ZooNer
 */

#ifndef SCGMODEINTERFACE_H_
#define SCGMODEINTERFACE_H_


#include "interfaces/SCgInputHandlerInterface.h"
#include "scgscenebase.h"

#include <QGraphicsSceneMouseEvent>

/*! Interface for managing different handler states.
 *
 */
class SCgModeInterface
{
public:

    explicit SCgModeInterface(SCgInputHandlerInterface* inputHandler):mInputHandler(inputHandler) {}

    virtual ~SCgModeInterface() {}


    virtual void keyPressEvent ( QKeyEvent * keyEvent ) = 0;
    //! @copydoc QGraphicsScene::keyReleaseEvent
    virtual void keyReleaseEvent ( QKeyEvent * keyEvent ) = 0;
    //! @copydoc QGraphicsScene::mouseDoubleClickEvent
    virtual void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent ) = 0;
    //! @copydoc QGraphicsScene::mouseMoveEvent
    virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent ) = 0;
    //! @copydoc QGraphicsScene::mousePressEvent
    virtual void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent ) = 0;
    //! @copydoc QGraphicsScene::mouseReleaseEvent
    virtual void mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent ) = 0;

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
};


#endif /* SCGMODEINTERFACE_H_ */
