/*
 * scgmodeselect.h
 *
 *  Created on: 14.07.2011
 *      Author: ZooNer
 */

#ifndef SCGMODECONTOUR_H_
#define SCGMODECONTOUR_H_


#include "scgmodeinterface.h"

#include <QPointer>
class SCgPathItem;

class SCgModeContour: public SCgModeInterface
{
public:
    explicit SCgModeContour(SCgInputHandlerInterface* inputHandler);

    virtual ~SCgModeContour();

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
protected:
    QList<QGraphicsItem* > selectItemsForContour() const;

    QPointer<SCgPathItem> mPathItem;

    QPointer<SCgVisualContour> mParentContour;
};

#endif /* SCGMODECONTOUR_H_ */
