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

#ifndef SUITASK_H
#define SUITASK_H

#include <QObject>
#include <QRunnable>

class QMutex;

/*! Base class for interface tasks.
  *
  * You can create task tree by using functions SuiTask::setParentTask, SuiTask::parentTask.
  * Any task in that tree runs, when all child tasks finished.
  *
  * Like in QRunnable class you can use autoDelete flag, but in that case it
  * has a false value by default.
  */
class SuiTask : public QObject, public QRunnable
{
    Q_OBJECT

    friend class SuiTaskManager;

public:
    /*! Enumeration of possible results, that return by task
      */
    typedef enum
    {
        NoError = 0,    // task finished without any errors
        Error,          // task finished with some errors
        Restart         // task need to be restarted
    } Result;

public:
    /*! Constructor
      * @param name Task instanc name
      * @param parent Pointer to parent QObject
      */
    explicit SuiTask(const QString &name, QObject *parent = 0);
    virtual ~SuiTask();

    //! @copydoc QRunnable::run
    void run();

    /*! Set parent task for this. Setting null parent,
      * makes this as a root in task tree. If current parent
      * is equivalent to \p parentTask, then this function do nothing.
      * @param parentTask Pointer to parent task
      */
    void setParentTask(SuiTask *parentTask);

    /*! Get pointer to parent task
      * @return Return pointer to parent task
      */
    SuiTask* parentTask() const;

    //! Check if task is finished
    bool isFinished() const;

protected:
    /*! Task impelementation
      * @return Return result code
      */
    virtual Result runImpl() = 0;

protected:
    /*! Append new task into child tasks list
      * @param task Pointer to new task
      */
    void _appendChildTask(SuiTask *task);

    /*! Remove task from a child task list
      * @param task Pointer to removing task
      */
    void _removeChildTask(SuiTask *task);

protected:
    //! Type for a list of tasks
    typedef QList<SuiTask*> SuiTaskList;
    //! List of "child" tasks
    SuiTaskList mChildTasks;

    //! Pointer to a parent task
    SuiTask *mParentTask;
    //! Task execution finish flag
    bool mIsFinished;
    //! Pointer to mutex, tath used to make this class thread-safe
    QMutex *mMutex;

signals:

public slots:

};

#endif // SUITASK_H
