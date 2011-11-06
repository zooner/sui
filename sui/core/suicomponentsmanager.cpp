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

#include "suiprecompiled.h"
#include "suicomponentsmanager.h"

suiComponentsManager::suiComponentsManager(QObject *parent) :
    QObject(parent)
{
}

bool suiComponentsManager::factoriesList(const UiComponentType &type, UiComponentFactoryInterfaceList &result) const
{
    result.clear();
    UiComponentFactoryInterface *factory;
    foreach(factory, mFactories)
    {
        if (factory->type() == type)
            result.append(factory);
    }

    return !result.empty();
}

void suiComponentsManager::registerFactory(UiComponentFactoryInterface *factory)
{
    if (mFactories.find(factory) != mFactories.end())
        SuiExcept(SuiExceptionDuplicateItem,
                  QString("Factory %1 already registered. Component type = %2").arg((quintptr)factory).arg(factory->type()),
                  "void suiComponentsManager::registerFactory(UiComponentFactoryInterface *factory)");

    mFactories.insert(factory);
}

void suiComponentsManager::unregisterFactory(UiComponentFactoryInterface *factory)
{
    if (mFactories.find(factory) == mFactories.end())
        SuiExcept(SuiExceptionItemNotFound,
                  QString("Factory %1 doesn't exist").arg((quintptr)factory),
                  "void suiComponentsManager::unregisterFactory(UiComponentFactoryInterface *factory)");

    mFactories.remove(factory);
}
