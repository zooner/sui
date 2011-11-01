/*
 * scgmodeselect.h
 *
 *  Created on: 14.07.2011
 *      Author: ZooNer
 */

#ifndef SCGMODESELECT_H_
#define SCGMODESELECT_H_


#include "scgmodeinterface.h"

class SCgModeSelect: public SCgModeInterface
{
public:

    explicit SCgModeSelect(SCgInputHandlerInterface* inputHandler);

    virtual ~SCgModeSelect();

    void keyPressEvent ( QKeyEvent * keyEvent ) ;
    //! @copydoc QGraphicsScene::keyReleaseEvent
    void keyReleaseEvent ( QKeyEvent * keyEvent );
    //! @copydoc QGraphicsScene::mouseDoubleClickEvent
    void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    //! @copydoc QGraphicsScene::mouseMoveEvent
    void mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    //! @copydoc QGraphicsScene::mousePressEvent
    void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    //! @copydoc QGraphicsScene::mouseReleaseEvent
    void mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent );

    /*! Called then this mode is become active.
     * Here you should provide some initial code you'll need.
     */
    void activate();

    /*! Called when handler state is become to change
     *  to clear unfinished operations or whole state of current mode.
     */
    void deactivate();
private:

    //! True if items positions have changed.
    bool mIsItemsMoved;
    //! Currently controlled pointObject.
    SCgVisualPointObject* mCurrentPointObject;
};

#endif /* SCGMODESELECT_H_ */
