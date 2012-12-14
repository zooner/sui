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

#ifndef SCGINPUTHANDLERINTERFACE_H
#define SCGINPUTHANDLERINTERFACE_H

#include <QtPlugin>
#include <QRectF>

class SCgSceneBase;

class QGraphicsSceneContextMenuEvent;
class QGraphicsSceneDragDropEvent;
class QPainter;
class QFocusEvent;
class QGraphicsSceneHelpEvent;
class QInputMethodEvent;
class QKeyEvent;
class QGraphicsSceneMouseEvent;
class QGraphicsSceneWheelEvent;

/*! Interface for scg view(edit) input handler. It realize whole logic of view(edit)
  */
class SCgInputHandlerInterface
{
public:
    /*! Constructor
      * @param scene Pointer to viewed(edited) scene
      */
    explicit SCgInputHandlerInterface() :
        mScene(0)
    {
    }

    virtual ~SCgInputHandlerInterface() {}

    /*! Set controlled scene into input handler
      * @param scene Pointer to controlled scene
      */
    void setScene(SCgSceneBase *scene) { Q_ASSERT(scene != 0); mScene = scene; }

    /*! Get pointer to controlled scene
      * @return Return pointer to controlled scene.
      */
    SCgSceneBase* scene() const { return mScene; }

    //! @copydoc QGraphicsScene::contextMenuEvent
    virtual void contextMenuEvent ( QGraphicsSceneContextMenuEvent * contextMenuEvent ) = 0;
    //! @copydoc QGraphicsScene::dragEnterEvent
    virtual void dragEnterEvent ( QGraphicsSceneDragDropEvent * event ) = 0;
    //! @copydoc QGraphicsScene::dragLeaveEvent
    virtual void dragLeaveEvent ( QGraphicsSceneDragDropEvent * event ) = 0;
    //! @copydoc QGraphicsScene::dragMoveEvent
    virtual void dragMoveEvent ( QGraphicsSceneDragDropEvent * event ) = 0;
    //! @copydoc QGraphicsScene::drawBackground
    virtual void drawBackground ( QPainter * painter, const QRectF & rect ) = 0;
    //! @copydoc QGraphicsScene::drawForeground
    virtual void drawForeground ( QPainter * painter, const QRectF & rect ) = 0;
    //! @copydoc QGraphicsScene::dropEvent
    virtual void dropEvent ( QGraphicsSceneDragDropEvent * event ) = 0;
    //! @copydoc QGraphicsScene::focusInEvent
    virtual void focusInEvent ( QFocusEvent * focusEvent ) = 0;
    //! @copydoc QGraphicsScene::focusOutEvent
    virtual void focusOutEvent ( QFocusEvent * focusEvent ) = 0;
    //! @copydoc QGraphicsScene::helpEvent
    virtual void helpEvent ( QGraphicsSceneHelpEvent * helpEvent ) = 0;
    //! @copydoc QGraphicsScene::inputMethodEvent
    virtual void inputMethodEvent ( QInputMethodEvent * event ) = 0;
    //! @copydoc QGraphicsScene::keyPressEvent
    virtual void keyPressEvent ( QKeyEvent * keyEvent ) = 0;
    //! @copydoc QGraphicsScene::keyReleaseEvent
    virtual void keyReleaseEvent ( QKeyEvent * keyEvent ) = 0;
    //! @copydoc QGraphicsScene::mouseDoubleClickEvent
    virtual void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent ) = 0;
    //! @copydoc QGraphicsScene::mouseMoveEvent
    virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent, bool afterSceneEvent ) = 0;
    //! @copydoc QGraphicsScene::mousePressEvent
    virtual void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent, bool afterSceneEvent ) = 0;
    //! @copydoc QGraphicsScene::mouseReleaseEvent
    virtual void mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent, bool afterSceneEvent ) = 0;
    //! @copydoc QGraphicsScene::wheelEvent
    virtual void wheelEvent ( QGraphicsSceneWheelEvent * wheelEvent ) = 0;


protected:
    //! Pointer to viewed(edited) scg scene
    SCgSceneBase *mScene;
};

Q_DECLARE_INTERFACE(SCgInputHandlerInterface,
                    "com.OSTIS.scg.SCgInputHandlerInterface/1.0");

#endif // SCGMODEINTERFACE_H
