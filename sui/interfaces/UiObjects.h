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

#ifndef OBJECTS_H
#define OBJECTS_H

#include <QtPlugin>
#include "ScMemory.h"

/*! Interface to work with objects that linked to any sc-element
  */
class ScObjectInterface
{
public:
    virtual ~ScObjectInterface() {}

    //! Return uri of associated sc-element
    virtual const ScUri& uri() const { return mUri; }

    /*! Set new uri of associated sc-element
      * @param uri New sc-element uri
      */
    virtual void setUri(const ScUri &uri) { mUri = uri; }

protected:
    //! Uri of associated sc-element
    ScUri mUri;
};

class ScWindowInterface : public ScObjectInterface
{
public:
    virtual ~ScWindowInterface() {}

    /*! Check if sc-window is opened
      * @return Retursn true, if sc-window is opened; otherwise return false.
      */
    virtual bool isOpened() const = 0;

    /*! Get widget
      * @return Returns pointer to QWidget, that implement sc-window
      */
    virtual QWidget* widget() const = 0;
};

Q_DECLARE_INTERFACE(ScObjectInterface,
                    "com.OSTIS.ui.ScObjectInterface/1.0")
Q_DECLARE_INTERFACE(ScWindowInterface,
                    "com.OSTIS.ui.ScWindowInterface/1.0")

#endif // OBJECTS_H
