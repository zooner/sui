/*
 * scgmodeselect.h
 *
 *  Created on: 14.07.2011
 *      Author: ZooNer
 */

#ifndef SCGMODEPAIR_H_
#define SCGMODEPAIR_H_


#include "scgmodeinterface.h"
#include <QPointer>

class SCgPathItem;

class SCgModePair: public SCgModeInterface
{
public:
    explicit SCgModePair(SCgInputHandlerInterface* inputHandler);

    virtual ~SCgModePair();

    //! @copydoc QGraphicsScene::keyPressEvent
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

    QPointer<SCgPathItem> mPathItem;

    QPointer<SCgVisualObject> mObjectAtFirstPoint;
};

#endif /* SCGMODEPAIR_H_ */
