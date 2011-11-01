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

#include "scgprecompiled.h"
#include "scgplugin.h"
#include "scgmainwindow.h"

#include "components/scgtranslategwftosc.h"

Q_EXPORT_PLUGIN2(scg, SCgPlugin)

UiRootInterface* SCgPlugin::mRootInterface = 0;

SCgPlugin::SCgPlugin()
{

}

SCgPlugin::~SCgPlugin()
{

}

UiRootInterface* SCgPlugin::rootInterface()
{
    return mRootInterface;
}

void SCgPlugin::initialize(UiRootInterface *root)
{
    mRootInterface = root;

    mInterfaces.append(new SCgMainWindowFactory(this));
    mInterfaces.append(new SCgTranslateGWFToScFactory(this));

}

void SCgPlugin::shutdown()
{

}

const QString& SCgPlugin::name() const
{
    static QString _name("SCg");
    return _name;
}

const QString& SCgPlugin::version() const
{
    static QString _version("0.2.0");
    return _version;
}

const QList<QObject*>& SCgPlugin::interfaces() const
{
    return mInterfaces;
}
