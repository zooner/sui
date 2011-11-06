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

#ifndef SCCOREPLUGIN_H
#define SCCOREPLUGIN_H

#include <QObject>
#include "interfaces/UiPlugins.h"

class ScCorePlugin : public QObject,
                     public UiPluginInterface
{
    Q_OBJECT
    Q_INTERFACES(UiPluginInterface)
public:
    explicit ScCorePlugin(QObject *parent = 0);
    virtual ~ScCorePlugin();

    //! @see UiPluginInterface::name
    const QString& name() const;
    //! @see UiPluginInterface::version
    const QString& version() const;
    //! @see UiPluginInterface::interfaces
    const QList<QObject*>& interfaces() const;
    //! @see UiPluginInterface::initialize
    void initialize(UiRootInterface *root);
    //! @see UiPluginInterface::shutdown
    void shutdown();

private:
    //! Plugin name
    QString mName;
    //! PLugin version
    QString mVersion;
    //! Plugin interfaces list
    QList<QObject*> mInterfaces;

signals:

public slots:

};


#endif // SCCOREPLUGIN_H
