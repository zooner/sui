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

#ifndef SUIKPM_H
#define SUIKPM_H

#include <QObject>

class suiOperation;

/*! Class realize knowledge processing machine for interface.
  * It control all operations that need for user interface working.
  * When you create new operation it automaticaly register in suiKpm. It will be destroyed automaticaly,
  * when knowledge process machine will be shutted down.
  */
class suiKpm : public QObject
{
    friend class suiOperation;

    Q_OBJECT
public:
    explicit suiKpm(QObject *parent = 0);
    virtual ~suiKpm();

    /*! Initialize knowldege processing machine
      */
    void initialize();
    /*! Shutdown
      */
    void shutdown();

protected:
    /*! Register new operation.
      * @param operation Pointer to operation that need to be registered.
      */
    void registerOperation(suiOperation *operation);

    /*! Unregister operation.
      * @param operation Pointer to operation that need to be unregistered.
      */
    void unregisterOperation(suiOperation *operation);

private:
    typedef QList<suiOperation*> suiOperationList;
    //! List of registered operations
    suiOperationList mOperations;

signals:

public slots:

};

#endif // SUIKPM_H
