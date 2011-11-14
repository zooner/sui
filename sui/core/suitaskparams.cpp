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
#include "suitaskparams.h"

SuiTaskParams::SuiTaskParams()
{
}

SuiTaskParams::~SuiTaskParams()
{
}

void SuiTaskParams::appendParam(const QString &name, const QVariant &value)
{
    mParamValues[name] = value;
}

void SuiTaskParams::removeParam(const QString &name)
{
    ParamValuesMap::iterator it = mParamValues.find(name);
    if (it == mParamValues.end())
        SuiExcept(SuiExceptionItemNotFound,
                  QString("There are no parameter with name '%1'").arg(name),
                  "void SuiTaskParams::removeParam(const QString &name)");

    mParamValues.erase(it);
}

QVariant& SuiTaskParams::operator [](const QString &key)
{
    Q_ASSERT(mParamValues.contains(key));
    return mParamValues[key];
}
