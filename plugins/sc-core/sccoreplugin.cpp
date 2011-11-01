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

#include "sccoreplugin.h"
#include "sccorememory.h"

Q_EXPORT_PLUGIN2(sc-core, ScCorePlugin)

ScCorePlugin::ScCorePlugin(QObject *parent) :
    QObject(parent),
    mName("sc-core"),
    mVersion("0.2.5")
{
}

ScCorePlugin::~ScCorePlugin()
{
    QObject *obj;
    foreach(obj, mInterfaces)
        delete obj;
    mInterfaces.clear();
}

const QString& ScCorePlugin::name() const
{
    return mName;
}

const QString& ScCorePlugin::version() const
{
    return mVersion;
}

const QList<QObject*>& ScCorePlugin::interfaces() const
{
    return mInterfaces;
}

void ScCorePlugin::initialize(UiRootInterface *root)
{
    Q_ASSERT(root != 0);
    mInterfaces.push_back(new ScCoreMemoryFactory(this));
}

void ScCorePlugin::shutdown()
{

}
