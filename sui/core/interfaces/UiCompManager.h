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

#ifndef COMP_MANAGER_H
#define COMP_MANAGER_H

#include <QtPlugin>
#include "UiComponents.h"

// ----- Interfaces ------
/*! Interface for components manager
  */
class UiComponentManagerInterface
{
public:
    virtual ~UiComponentManagerInterface() {}

    /*! Returns list of registered component factories with specified type
      * @param type Component type
      * @param result List of registered component factories with specified \p type
      * @return Return true, if any component founded; otherwise return false.
      */
    virtual bool factoriesList(const UiComponentType &type, UiComponentFactoryInterfaceList &result) const = 0;

    /*! Register new factory
      * @param factory Pointer to new factory
      */
    virtual void registerFactory(UiComponentFactoryInterface *factory) = 0;

    /*! Unregister specified factory
      * @param factory Pointer to factory, that need to be unregistered
      */
    virtual void unregisterFactory(UiComponentFactoryInterface *factory) = 0;

};

Q_DECLARE_INTERFACE(UiComponentManagerInterface,
                    "com.OSTIS.ui.UiComponentManagerInterface/1.0")

#endif // COMP_MANAGER_H
