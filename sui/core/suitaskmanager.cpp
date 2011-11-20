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
#include "suitaskmanager.h"

#include <QMutex>
#include <QThreadPool>

SuiTaskManager* SuiTaskManager::mInstance = 0;

SuiTaskManager* SuiTaskManager::getInstance()
{
    Q_ASSERT(mInstance != 0);
    return mInstance;
}

SuiTaskManager::SuiTaskManager(QObject *parent) :
    QObject(parent)
{
    mMutex = new QMutex(QMutex::Recursive);
    mThreadPool = new QThreadPool(this);
}

SuiTaskManager::~SuiTaskManager()
{
    delete mMutex;
    //delete mThreadPool;
}

void SuiTaskManager::runTask(SuiTask *task)
{
    QMutexLocker locker(mMutex);

    if (mRunningTasks.contains(task))
        SuiExcept(SuiExceptionDuplicateItem,
                  QString("Task '%1' already running").arg(task->objectName()),
                  "void SuiTaskManager::runTask(SuiTask *task)");

    mThreadPool->start(task, task->priority());
}

void SuiTaskManager::taskStarted(SuiTask *task)
{
    QMutexLocker locker(mMutex);

    Q_ASSERT(task != 0);

    if (mRunningTasks.contains(task))
        SuiExcept(SuiExceptionDuplicateItem,
                  QString("Task '%1' already running").arg(task->objectName()),
                  "void SuiTaskManager::taskStarted(SuiTask *task)");

    mRunningTasks.append(task);
}

void SuiTaskManager::taskCompleted(SuiTask *task, SuiTask::Result result)
{
    QMutexLocker locker(mMutex);

    Q_ASSERT(task != 0);

    if (result == SuiTask::Restart)
        runTask(task);
}
