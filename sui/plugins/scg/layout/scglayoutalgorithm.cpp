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

#include "scgprecompiled.h"
#include "scglayoutalgorithm.h"

SCgLayoutAlgorithm::SCgLayoutAlgorithm(QObject *parent) :
    QObject(parent),
    mConstruction(0)
{
}

SCgLayoutAlgorithm::~SCgLayoutAlgorithm()
{
}

void SCgLayoutAlgorithm::setConstruction(SCgConstruction *construction)
{
    mConstruction = construction;
}



SCgLayoutAlgorithmFactory::SCgLayoutAlgorithmFactory(QObject *parent) :
    QObject(parent),
    mRatingInstance(0)
{
    //! \todo: Refactor this
    //DO NOT CALL VIRTUAL FUNCTIONS FROM CONSTRUCTORS AND DESTRUCTORS!
    //REALY! NEVER! In the best case it won't work as you expect.
    //mRatingInstance = createAlgorithm();
}

SCgLayoutAlgorithmFactory::~SCgLayoutAlgorithmFactory()
{
    delete mRatingInstance;
}

float SCgLayoutAlgorithmFactory::calculateRating(SCgConstruction *construction)
{
    Q_ASSERT(mRatingInstance != 0);
    return mRatingInstance->calculateRating(construction);
}
