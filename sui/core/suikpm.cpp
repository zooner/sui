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
#include "suikpm.h"
#include "suiroot.h"
#include "kpm/suioperation.h"
#include "kpm/suimainwindowaddoperation.h"


suiKpm::suiKpm(QObject *parent) :
    QObject(parent)
{
}

suiKpm::~suiKpm()
{

}

void suiKpm::initialize()
{
    qDebug() << "Initialize knowledge process machine";
    suiOperation *op = new suiMainWindowAddOperation("Main window add object", this);
    op->init(ScEventOutputEdgeAdded, suiRoot::getInstance()->scHelper()->keynode("/ui/main_window"));
}

void suiKpm::shutdown()
{
    qDebug() << "Shutdown knowledge processing machine";
    suiOperationList::iterator it;
    // make list copy, because when we will delete operations, then they will
    // be unregister and change mOperations list
    suiOperationList list = mOperations;
    for (it = list.begin(); it != list.end(); ++it)
        (*it)->shutdown();
    mOperations.clear();
}

void suiKpm::registerOperation(suiOperation *operation)
{
    Q_ASSERT(operation != 0);

    if (mOperations.contains(operation))
        SuiExcept(SuiExceptionDuplicateItem,
                  QString("Operation already registered: %1").arg(operation->name()),
                  "void suiKpm::registerOperation(suiOperation *operation)");

    mOperations.append(operation);
    qDebug() << QString("Operation '%1' registered").arg(operation->name());

}

void suiKpm::unregisterOperation(suiOperation *operation)
{
    Q_ASSERT(operation != 0);

    suiOperationList::iterator it;
    for (it = mOperations.begin(); it != mOperations.end(); ++it)
        if (*it == operation)
        {
            qDebug() << QString("Operation '%1' unregistered").arg(operation->name());
            mOperations.erase(it);
            return;
        }

    SuiExcept(SuiExceptionItemNotFound,
              QString("Operation doesn't registered: %1").arg(operation->name()),
              "void suiKpm::unregisterOperation(suiOperation *operation)");
}
