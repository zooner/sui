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

#ifndef SUIMAINWINDOWADDOPERATION_H
#define SUIMAINWINDOWADDOPERATION_H

#include "suioperation.h"

/*! Operation that show added to main window object on screen.\n
  * <b>Initial condition:</b>
  * \image html operations/op_main_window_add_cond.png
  * <b>Result:</b>
  * Show \e $obj on screen.
  */
class suiMainWindowAddOperation : public suiOperation
{
    Q_OBJECT
public:
    explicit suiMainWindowAddOperation(const QString &_name, QObject *parent = 0);
    virtual ~suiMainWindowAddOperation();

protected:
    //! @copydoc suiOperation::checkCondition
    bool checkCondition(const ScEvent &event);
    //! @copydoc suiOperation::run_impl
    bool run_impl(const ScEvent &event);
};

#endif // SUIMAINWINDOWADDOPERATION_H
