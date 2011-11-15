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
#include "suitask.h"

#include <QMutex>

SuiTask::SuiTask(const QString &name, QObject *parent) :
    QObject(parent),
    mIsRunning(false),
    mParentTask(0),
    mIsFinished(false),
    mMutex(0)
{
    setAutoDelete(false);
    setObjectName(name);

    mMutex = new QMutex(QMutex::Recursive);
}

SuiTask::~SuiTask()
{
    delete mMutex;
}


void SuiTask::run()
{
    Q_ASSERT(mIsRunning == false);

    mMutex->lock();
    mIsRunning = true;
    mMutex->unlock();

    started(this);

    Result result = runImpl();

    mMutex->lock();
    if (result != Restart)
        mIsFinished = true;
    mMutex->unlock();

    complete(this, result);
}

void SuiTask::setParentTask(SuiTask *parentTask)
{
    QMutexLocker locker(mMutex);

    if (mParentTask == parentTask) return; // do nothing

    if (mParentTask != 0) mParentTask->_removeChildTask(this);

    mParentTask = parentTask;

    mParentTask->_appendChildTask(this);
}

SuiTask* SuiTask::parentTask() const
{
    QMutexLocker locker(mMutex);
    return mParentTask;
}

bool SuiTask::isFinished() const
{
    QMutexLocker locker(mMutex);
    return mIsFinished;
}

SuiTask::SuiTaskList SuiTask::childTasks(bool subChilds)
{
    QMutexLocker locker(mMutex);

    if (!subChilds) return mChildTasks;

    SuiTaskList list;
    SuiTask *task;
    foreach(task, mChildTasks)
        list.append(task->childTasks(true));
    return list;
}

QVariant SuiTask::operator [](const QString &key)
{
    QMutexLocker locker(mMutex);
    return mParams[key];
}

void SuiTask::setPriority(int priority)
{
    QMutexLocker locker(mMutex);
    mPriority = priority;
}

int SuiTask::priority() const
{
    QMutexLocker locker(mMutex);
    return mPriority;
}

void SuiTask::_appendChildTask(SuiTask *task)
{
    if (mChildTasks.contains(task))
        SuiExcept(SuiExceptionDuplicateItem,
                  QString("Task '%1' is already in a childs list for task '%2'").arg(task->objectName()).arg(objectName()),
                  "void SuiTask::_appendChildTask(SuiTask *task)");

    mChildTasks.append(task);
}

void SuiTask::_removeChildTask(SuiTask *task)
{
    if (!mChildTasks.contains(task))
        SuiExcept(SuiExceptionItemNotFound,
                  QString("Task '%1' isn't in a childs list for task '%2'").arg(task->objectName()).arg(objectName()),
                  "void SuiTask::_removeChildTask(SuiTask *task)");

    mChildTasks.removeOne(task);
}
