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

#ifndef SUITASKPARAMS_H
#define SUITASKPARAMS_H

#include <QObject>
#include <QMap>

class SuiTaskParams
{
public:
    explicit SuiTaskParams();
    virtual ~SuiTaskParams();

    /*! Operator, that return reference to specified parameter value
      * @param key Parameter name
      */
    QVariant& operator [] (const QString &key);

    /*! Append new parameter with value.
      * If value with a specified \p namealready exist, then it value will be raplaced with \p value
      * @param name Parameter name
      * @param value Parameter value
      */
    void appendParam(const QString &name, const QVariant &value);

    /*! Remove specified parameter by name
      * @param name Name of parameter, that need to be removed
      */
    void removeParam(const QString &name);

private:
    //! Type for map that contains parameter values
    typedef QMap<QString, QVariant> ParamValuesMap;
    //! Parameter values map
    ParamValuesMap mParamValues;

signals:

public slots:

};

#endif // SUITASKPARAMS_H
