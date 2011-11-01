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

#ifndef SCGSCENEBASE_H
#define SCGSCENEBASE_H

#include "scgprerequest.h"
#include "objects/scgconstructionobserver.h"
#include <QGraphicsScene>
#include <QMap>

class SCgInputHandlerInterface;
class QUndoCommand;
class QUndoStack;

/*! Base graphics scene for all scg realizations.
  * It contains functionality, that can be used in each type of scene
  */
class SCgSceneBase : public QGraphicsScene,
                        public SCgConstructionObserver
{
    Q_OBJECT
public:
    explicit SCgSceneBase(SCgInputHandlerInterface *inputHandler, QObject *parent = 0);
    virtual ~SCgSceneBase();

public:

    /*! Return pointer to associated sc.g-construction
      */
    SCgConstruction* construction() const { return mConstruction; }

    /*! Append new undo command
      * @param command Pointer to undo command
      */
    void appendUndoCommand(QUndoCommand *command);

    /*! You can specify your event handler by using this method.
     * @note Scene doesn't take ownership of the input handler, so won't be destroyed after setting new handler or on destroying scene.
     *
     * @param handler new input handler.
     */
    void setInputHandler(SCgInputHandlerInterface* handler);

    QUndoStack* undoStack() const
    {
        return mUndoStack;
    }

    /*! Get sc.g-object at specified point with maximum Z-value
      * @param point Point coordinates
      * @return Return pointer to any founded sc.g-object, if there are no
      * any sc.g-object in that point, then return \b null pointer
      */
    virtual SCgObject* scgObjectAt(const QPointF& point) const = 0;

    /*! Get visual sc.g-object at specified point.
      * This function does the same as SCgSceneBase::scgObjectAt, but
      * return pointer to SCgVisualObject
      */
    virtual SCgVisualObject* scgVisualObjectAt(const QPointF& point) const = 0;

protected:
    //! @copydoc QGraphicsScene::contextMenuEvent
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    //! @copydoc QGraphicsScene::dragEnterEvent
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    //! @copydoc QGraphicsScene::dragLeaveEvent
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    //! @copydoc QGraphicsScene::dragMoveEvent
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    //! @copydoc QGraphicsScene::drawBackground
    void drawBackground(QPainter *painter, const QRectF &rect);
    //! @copydoc QGraphicsScene::drawForeground
    void drawForeground(QPainter *painter, const QRectF &rect);
    //! @copydoc QGraphicsScene::dropEvent
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    //! @copydoc QGraphicsScene::focusInEvent
    void focusInEvent(QFocusEvent *event);
    //! @copydoc QGraphicsScene::focusOutEvent
    void focusOutEvent(QFocusEvent *event);
    //! @copydoc QGraphicsScene::helpEvent
    void helpEvent(QGraphicsSceneHelpEvent *event);
    //! @copydoc QGraphicsScene::inputMethodEvent
    void inputMethodEvent(QInputMethodEvent *event);
    //! @copydoc QGraphicsScene::keyPressEvent
    void keyPressEvent(QKeyEvent *event);
    //! @copydoc QGraphicsScene::keyReleaseEvent
    void keyReleaseEvent(QKeyEvent *event);
    //! @copydoc QGraphicsScene::mouseDoubleClickEvent
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    //! @copydoc QGraphicsScene::mouseMoveEvent
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    //! @copydoc QGraphicsScene::mousePressEvent
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    //! @copydoc QGraphicsScene::mouseReleaseEvent
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    //! @copydoc QGraphicsScene::wheelEvent
    void wheelEvent(QGraphicsSceneWheelEvent *event);

protected:
    //! Pointer to used mode
    SCgInputHandlerInterface *mInputHandler;
    //! Undo commands stack
    QUndoStack *mUndoStack;
    //! Pointer to sc.g-construction, that controlled by scene
    SCgConstruction *mConstruction;
    //! Mapping sc.g-object to visual object
    QMap<SCgObject*, SCgVisualObject*> mObjectToVisual;


signals:

};

#endif // SCGSCENEBASE_H
