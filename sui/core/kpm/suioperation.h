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

#ifndef SUIOPERATION_H
#define SUIOPERATION_H

#include "../suiCore_global.h"
#include "../interfaces/ScMemory.h"
#include <QObject>

/*! Base class for user interface operation.
  *
  * @note You need to call suiOperation::init function to initialize operation and
  * suiOperation::shutdown to shut it down.
  */
class SUICORESHARED_EXPORT suiOperation : public QObject,
                                            public ScEventCallbackInterface
{
    Q_OBJECT
    Q_INTERFACES(ScEventCallbackInterface)
    Q_PROPERTY(QString mName READ name);

public:
    explicit suiOperation(const QString &_name, QObject *parent = 0);
    virtual ~suiOperation();

    /*! Initialize operation. When you call that function, it register sc-event callback and
      * automaticaly add operation into knowledge processing machine.
      * @param eventType Event type @see ScEventType
      * @param uri sc-element uri that we want to listen
      * @param memory Pointer to sc-memory interface that will be used to register
      * sc-event callback. If it have null value, then default interface will be used.
      * By default it have null value.
      * @see suiOperation::shutdown
      */
    void init(ScEventType eventType, const ScUri &uri, ScMemoryInterface *memory = 0);

    /*! Shutdown operation. Disconnect callback for sc-event and remove operation
      * from knowledge processing machine.
      * @see suiOperation::init
      */
    void shutdown();

    //! Return operation name
    const QString& name() const;

protected:
    //! @copydoc ScEventCallbackInterface::
    bool eventCallBack(const ScEvent &event);

    /*! Check operation run condition. That function calls when
      * sc-event callback called. It check if operation need to be started.
      * It must be reimplemented in a subclass.
      *
      * @param event event information
      * @return Return true, if operation need to be started; otherwise return false
      */
    virtual bool checkCondition(const ScEvent &event) = 0;

    /*! Implementation of operation. In that function you need to implement
      * main functionality of operation.
      * It must be reimplemented in subclass.
      * @param event event information
      * @return Retrun true, if operation finished witout any errors; otherwise return false.
      */
    virtual bool run_impl(const ScEvent &event) = 0;

private:
    //! operation name
    QString mName;
    //! Pointer to used sc-memory interface
    ScMemoryInterface *mScMemory;
    //! Event type
    ScEventType mEventType;
    //! Listened uri
    ScUri mUri;

signals:

public slots:

};

#endif // SUIOPERATION_H
