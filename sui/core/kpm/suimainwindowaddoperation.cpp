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

#include "../suiprecompiled.h"
#include "suimainwindowaddoperation.h"
#include "../suiroot.h"

suiMainWindowAddOperation::suiMainWindowAddOperation(const QString &_name, QObject *parent) :
    suiOperation(_name, parent)
{
}

suiMainWindowAddOperation::~suiMainWindowAddOperation()
{
}

bool suiMainWindowAddOperation::checkCondition(const ScEvent &event)
{
    return true;
}

bool suiMainWindowAddOperation::run_impl(const ScEvent &event)
{
    // check param
    Q_ASSERT(event.scTemplate().param(2).is_uri());
    // we use output arc event, so end element in template is added into window sc-element
    suiRoot::getInstance()->mainScWindow()->showObjects(ScUriList() << event.scTemplate().param(2).uri());
    return true;
}
