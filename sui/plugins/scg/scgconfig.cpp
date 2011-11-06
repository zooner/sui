/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010 OSTIS

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
#include "scgconfig.h"

SCgConfig* SCgConfig::mInstance = 0;
QDir SCgConfig::pathIcons = QDir();
QDir SCgConfig::pathMedia = QDir();

SCgConfig* SCgConfig::getInstance()
{
    if (mInstance == 0)
    {
        mInstance = new SCgConfig();
        mInstance->initialize();
    }

    return mInstance;
}

void SCgConfig::Destroy()
{
    if(mInstance)
    {
        mInstance->saveConfiguration();
        delete mInstance;
    }
    mInstance = 0;
}

SCgConfig::SCgConfig(QObject *parent) :
    QObject(parent)
{
}

SCgConfig::~SCgConfig()
{

}

void SCgConfig::initialize()
{
    initializeDefault();

    // read values from configuration storage
    readConfiguration();
}

void SCgConfig::initializeDefault()
{
    // --- elements ---
    scg_cfg_set_default_value_color(scg_key_element_color_normal, QColor(0, 0, 0));
    scg_cfg_set_default_value_color(scg_key_element_color_selected, QColor(0, 193, 43));
    scg_cfg_set_default_value_color(scg_key_element_color_highlight, QColor(255, 124, 0));
    scg_cfg_set_default_value(scg_key_element_font_name, QString("Arial [Times New Roman"));
    scg_cfg_set_default_value(scg_key_element_font_size, 10);
    scg_cfg_set_default_value_color(scg_key_element_font_color_normal, QColor(0, 0, 128));
    scg_cfg_set_default_value_color(scg_key_element_font_color_selected, QColor(0, 128, 0));
    scg_cfg_set_default_value_color(scg_key_element_font_color_highlight, QColor(128, 64, 0));

    // --- controls ---
    scg_cfg_set_default_value_color(scg_key_control_backcolor_normal, QColor(99, 186, 35));
    scg_cfg_set_default_value_color(scg_key_control_backcolor_selected, QColor(99, 215, 35));
    scg_cfg_set_default_value_color(scg_key_control_backcolor_highlight, QColor(99, 215, 35));
    scg_cfg_set_default_value_color(scg_key_control_color_normal, QColor(255, 255, 255));
    scg_cfg_set_default_value_color(scg_key_control_color_selected, QColor(99, 215, 35));
    scg_cfg_set_default_value_color(scg_key_control_color_highlight, QColor(99, 186, 35));
    scg_cfg_set_default_value(scg_key_control_font_name, QString("Times New Roman [Arial]"));
    scg_cfg_set_default_value(scg_key_control_font_size, 12);
    scg_cfg_set_default_value_color(scg_key_control_font_color, QColor(255, 255, 255));

#if ENABLE_VISUAL_EFFECTS_SUPPORT
    // --- effects ---
    scg_cfg_set_default_value(scg_key_effects_enabled, 1);
#endif


    // copy default values to current
    mValues = mDefaultValues;
}

void SCgConfig::readConfiguration()
{

}

void SCgConfig::saveConfiguration()
{

}

void SCgConfig::setValue(const QString &option, const QVariant &value)
{
    mValues[option] = value;
}

QVariant SCgConfig::value(const QString &option) const
{
    Q_ASSERT_X(mValues.find(option) != mValues.end(),
               "const QVariant& SCgConfig::optionValue(const QString &option) const",
               "Option value for option doesn't exist");
    return mValues[option];
}

bool SCgConfig::haveValue(const QString &option) const
{
    return mValues.find(option) != mValues.end();
}

void SCgConfig::setDefaultValue(const QString &option, const QVariant &value)
{
    mDefaultValues[option] = value;
}

QVariant SCgConfig::defaultValue(const QString &option) const
{
    Q_ASSERT_X(mDefaultValues.find(option) != mDefaultValues.end(),
               "QVariant SCgConfig::defaultValue(const QString &option) const",
               "Default value for option doesn't exist");
    return mDefaultValues[option];
}

bool SCgConfig::haveDefaultValue(const QString &option) const
{
    return mDefaultValues.find(option) != mDefaultValues.end();
}


QString SCgConfig::color2string(const QColor &color) const
{
    return QString("%1 %2 %3 %4").arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha());
}

QColor SCgConfig::string2color(const QString &str) const
{
    QStringList strs = str.split(" ");
    Q_ASSERT_X(strs.size() == 4,
               "QColor SCgConfig::string2color(const QString &str) const",
               "Invalid string that represents color");
    return QColor(strs[0].toInt(), strs[1].toInt(), strs[2].toInt(), strs[3].toInt());
}
