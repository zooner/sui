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

#ifndef SCGMOVINGHELPER_H
#define SCGMOVINGHELPER_H

#include "commands/scgcommandobjectmove.h"
#include "commands/scgcommandchangepairbeginenddots.h"
#include <QMap>
#include <QPointF>

class QUndoCommand;
class SCgSceneBase;


class SCgMovingHelper
{
public:
    SCgMovingHelper();

    /*!
     * \brief Use to initialize moving helper. Give a chance to store initial objects' configurations.
     * \param objList List of objects to be moved
     * \param startPoint Point, from which moving process is started. (Usualy it's left mouse down scene coordinate)
     */
    virtual void initializeWithObjects(const QList<QGraphicsItem*>& itemList, const QPointF& startPoint);

    /*!
     * \brief Use to move objects from their initial positions (\ref initializeWithObjects()) to new /
     * positions, specifiet by \p toPoint. It calculates the offset between start point and the point given.
     */
    virtual void moveTo(const QPointF& toPoint);

    /*!
     * \brief Creates an undo/redo command based on information, obtained from \ref initializeWithObjects() and \ref moveTo() calls
     */
    virtual QUndoCommand* createCommand(SCgSceneBase* scene) const;

    /*! Use it to reset state of moving helper.
     * \brief clearState
     */
    virtual void resetState();

    /*!
     * \return true if current helper is properly initialized and contain objects to be moved on next \ref moveTo() call
     */
    virtual bool isInitialized() const;
private:

    /*!
     * \brief movePair moves pair from its initial position to another.
     * \param pair
     * \param toPoint
     */
    void setAndStoreDotPositions(SCgPair *pair);

    /*! Stores initial object position including all child objects of given object in the \ref mInitialObjectPositions.
     * It takes in count pairs which dot positions stored in \ref mInitialPairsDotPositions.
     * \param object
     */
    void storeInitialObjectPosition(SCgObject *object);
    void storeInitialObjectPosition(SCgPair *pair);

    SCgCommandObjectMove::MoveInfo mMoveInfo;

    SCgCommandChangePairBeginEndDots::ChangeDotsInfo mChangedPairsDotPositions;
    //SCgPair => QPaiir<first segment Angle, last segment angle>
    QMap<SCgPair*, QPair<qreal,qreal> > mInitialPairsAngles;
    QPointF mStartPoint;
};

#endif // SCGMOVINGHELPER_H
