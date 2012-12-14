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

#ifndef SCGMAINWINDOWINPUTHANDLER_H
#define SCGMAINWINDOWINPUTHANDLER_H

#include "scgprerequest.h"

#include "interfaces/SCgInputHandlerInterface.h"

#include <QObject>
#include <QPointF>
#include <QVector>
#include <QPair>

class QGraphicsPathItem;
class SCgModeInterface;
class SCgMainWindowScene;

class SCgMainWindowInputHandler : public QObject,
                                  public SCgInputHandlerInterface
{
    Q_OBJECT
    Q_INTERFACES(SCgInputHandlerInterface)
public:
    explicit SCgMainWindowInputHandler(QObject* parent = 0);
    virtual ~SCgMainWindowInputHandler();

    typedef enum
    {
        ModeSelect = 0, // selection mode
        ModePair,        // arc/edge creation mode
        ModeBus,        // bus creation mode
        ModeContour,     // contour creation mode

        ModeCount
    } Mode;

protected:

    /*! Change current mode to new. If new mode is equivalent to current, then do nothing.
      * @param newMode New mode.
      */
    void changeMode(Mode newMode);

    //! @copydoc SCgInputHandlerInterface::contextMenuEvent
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *contextMenuEvent);
    //! @copydoc SCgInputHandlerInterface::dragEnterEvent
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    //! @copydoc SCgInputHandlerInterface::dragLeaveEvent
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    //! @copydoc SCgInputHandlerInterface::dragMoveEvent
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    //! @copydoc SCgInputHandlerInterface::drawBackground
    void drawBackground(QPainter *painter, const QRectF &rect);
    //! @copydoc SCgInputHandlerInterface::drawForeground
    void drawForeground(QPainter *painter, const QRectF &rect);
    //! @copydoc SCgInputHandlerInterface::dropEvent
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    //! @copydoc SCgInputHandlerInterface::focusInEvent
    void focusInEvent(QFocusEvent *focusEvent);
    //! @copydoc SCgInputHandlerInterface::focusOutEvent
    void focusOutEvent(QFocusEvent *focusEvent);
    //! @copydoc SCgInputHandlerInterface::helpEvent
    void helpEvent(QGraphicsSceneHelpEvent *helpEvent);
    //! @copydoc SCgInputHandlerInterface::inputMethodEvent
    void inputMethodEvent(QInputMethodEvent *event);
    //! @copydoc SCgInputHandlerInterface::keyPressEvent
    void keyPressEvent(QKeyEvent *keyEvent);
    //! @copydoc SCgInputHandlerInterface::keyReleaseEvent
    void keyReleaseEvent(QKeyEvent *keyEvent);
    //! @copydoc SCgInputHandlerInterface::mouseDoubleClickEvent
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);
    //! @copydoc SCgInputHandlerInterface::mouseMoveEvent
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent, bool afterSceneEvent);
    //! @copydoc SCgInputHandlerInterface::mousePressEvent
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent, bool afterSceneEvent);
    //! @copydoc SCgInputHandlerInterface::mouseReleaseEvent
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent, bool afterSceneEvent);
    //! @copydoc SCgInputHandlerInterface::wheelEvent
    void wheelEvent(QGraphicsSceneWheelEvent *wheelEvent);

private:
    //! Vector with all available modes. (Pattern State)
    QVector<SCgModeInterface* > mAvailableModes;

    //! Current mode
    SCgModeInterface* mMode;
signals:

public slots:

    //! Deletes all selected objects on scene.
    void deleteSelected();

    //! Deletes only selected contour keeping it's content unchanged.
    void deleteJustContour();

};

#endif // SCGMAINWINDOWINPUTHANDLER_H
