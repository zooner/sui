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

#ifndef SUITASKMANAGER_H
#define SUITASKMANAGER_H

#include <QObject>

/*! This class used to control all tasks, that processed in user interface core.
 * It implements task oriented system, when developer just create any type of task
 * and run it with task manager. Task manager control running of tasks depending on
 * available system resources.
 * Task mechanism allow to create tasks, that depend on another tasks, so you can
 * create big tree of tasks, and run them. Task manager decide when they can work
 * in parallel, when no and run them.
 */
class SuiTaskManager : public QObject
{
    Q_OBJECT
public:
    explicit SuiTaskManager(QObject *parent = 0);
    virtual ~SuiTaskManager();

signals:

public slots:

};

#endif // SUITASKMANAGER_H
