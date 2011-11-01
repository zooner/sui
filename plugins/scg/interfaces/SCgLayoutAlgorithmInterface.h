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

#ifndef SCGLAYOUTALGORITHMINTERFACE_H
#define SCGLAYOUTALGORITHMINTERFACE_H

#include <QtPlugin>
#include "scgprerequest.h"

class SCgGroupLayoutData;

/*! Interface for layout algorithms. Layout algorithms used to
  * visualize scg-constructions on screen. They can change object
  * position, size, color and other.
  *
  * Layout system based on layout ratings. Each algorithm have a function that
  * calculates layout rating for a specified construction. Layout rating is a float number
  * in range from 0 to 1. Zero value means that construction couldn't be layouted with specified algorithm,
  * 1 - constructinon will be good layouted with algorithm. Each rating calculates depending on construction
  * and that is the hard part of layout algorithm, that need to be realized very carefuly.
  */
class SCgLayoutAlgorithmInterface
{
public:
    typedef enum
    {
        AT_Unknown = 0,
        AT_Hierarhical,
        AT_Network,
        AT_Universal
    } AlgorithmType;


    virtual ~SCgLayoutAlgorithmInterface() {}

    /*! Rate algorithm layout possibilities for specified construction.
      * @param construction Pointer to scg-construction, that used to calculate layout rating
      * @return Return float number in range from 0 to 1. Where 0 - is the worth rate (do not recomend to
      * use algorithms with bad rates for construction layout), 1 - best rate (construction will be have best layout,
      * with using that algorithm)
      */
    virtual float calculateRating(SCgConstruction *construction) = 0;

    /*! Setup data for layout
      * @param construction Pointer to scg-construction that will be layouted with algorithm
      */
    virtual void setConstruction(SCgConstruction *construction) = 0;

    /*! Execute layout algorithm
      */
    virtual void execute() = 0;

    /*! Get algorithm type
      * @return Return algorithm type
      */
    virtual AlgorithmType algorithmType() const = 0;
};

Q_DECLARE_INTERFACE(SCgLayoutAlgorithmInterface,
                    "com.OSTIS.scg.SCgLayoutAlgorithmInterface/1.0");

/*! Interface for layout algorithm factory. It used by layout manager
  * to search and create algorithm that will be used for layout scg-construction.
  * It contains functions to get layout rating for specified scg-construction.
  */
class SCgLayoutAlgorithmFactoryInterface
{
public:
    virtual ~SCgLayoutAlgorithmFactoryInterface() {}

    /*! Create layout algorithm instance
      * @return Return pointer to interface of created layout algorithm
      */
    virtual SCgLayoutAlgorithmInterface* createAlgorithm() = 0;

    //! @copydoc SCgLayoutAlgorithmInterface::calculateRating
    virtual float calculateRating(SCgConstruction *construction) = 0;
};

Q_DECLARE_INTERFACE(SCgLayoutAlgorithmFactoryInterface,
                    "com.OSTIS.scg.SCgLayoutAlgorithmFactoryInterface/1.0");


#endif // SCGLAYOUTALGORITHM_H
