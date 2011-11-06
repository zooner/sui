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

#ifndef SCGLAYOUTALGORITHM_H
#define SCGLAYOUTALGORITHM_H

#include "scgprerequest.h"
#include <QObject>
#include "interfaces/SCgLayoutAlgorithmInterface.h"

class SCgLayoutAlgorithm : public QObject,
                            public SCgLayoutAlgorithmInterface
{
    Q_OBJECT
    Q_INTERFACES(SCgLayoutAlgorithmInterface)
public:
    explicit SCgLayoutAlgorithm(QObject *parent = 0);
    virtual ~SCgLayoutAlgorithm();

    //! @copydoc SCgLayoutAlgorithmInterface::setLayoutGroup
    void setConstruction(SCgConstruction *construction);

    //! @copydoc SCgLayoutAlgorithmInterface::algorithmType
    AlgorithmType algorithmType() const { return mType; }

protected:
    //! Pointer to layout group
    SCgConstruction *mConstruction;
    //! Layout algorithm type
    AlgorithmType mType;

signals:

public slots:

};

class SCgLayoutAlgorithmFactory : public QObject,
                                    public SCgLayoutAlgorithmFactoryInterface
{
    Q_OBJECT
    Q_INTERFACES(SCgLayoutAlgorithmFactoryInterface)
public:
    explicit SCgLayoutAlgorithmFactory(QObject *parent = 0);
    virtual ~SCgLayoutAlgorithmFactory();

    //! @copydoc SCgLayoutAlgorithmFactoryInterface::calculateRating
    float calculateRating(SCgConstruction *construction);

protected:
    //! Pointer to layout algorithm instance that used to calculate ratings
    SCgLayoutAlgorithmInterface *mRatingInstance;
};

#endif // SCGLAYOUTALGORITHM_H
