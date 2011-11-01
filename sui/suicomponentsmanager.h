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

#ifndef SUICOMPONENTSMANAGER_H
#define SUICOMPONENTSMANAGER_H

#include <QObject>
#include "interfaces/UiCompManager.h"

class suiComponentsManager : public QObject,
                             public UiComponentManagerInterface
{
    Q_OBJECT
    Q_INTERFACES(UiComponentManagerInterface)
public:
    explicit suiComponentsManager(QObject *parent = 0);

    //! @copydoc UiComponentManagerInterface::factoriesList
    bool factoriesList(const UiComponentType &type, UiComponentFactoryInterfaceList &result) const;
    //! @copydoc UiComponentManagerInterface::registerFactory
    void registerFactory(UiComponentFactoryInterface *factory);
    //! @copydoc UiComponentManagerInterface::unregisterFactory
    void unregisterFactory(UiComponentFactoryInterface *factory);

private:
    typedef QSet<UiComponentFactoryInterface*> FactoriesSet;
    //! List of registered editor components
    FactoriesSet mFactories;

signals:

public slots:

};

#endif // SUICOMPONENTSMANAGER_H
