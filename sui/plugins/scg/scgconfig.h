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

#ifndef SCGCONFIG_H
#define SCGCONFIG_H

#include "scgbuildconfig.h"

#include <QObject>
#include <QMap>
#include <QVariant>
#include <QColor>
#include <QDir>

// Defines to make work with values more simple
#define scg_config  SCgConfig::getInstance()
#define scg_cfg_get_value(key)          scg_config->value(key)
#define scg_cfg_set_value(key, value)   scg_config->setValue(key, QVariant(value))

#define scg_cfg_set_value_color(key, value) scg_cfg_set_value(key, scg_config->color2string(value))

#define scg_cfg_get_value_string(key)       scg_cfg_get_value(key).toString()
#define scg_cfg_get_value_float(key)        scg_cfg_get_value(key).toFloat()
#define scg_cfg_get_value_uint(key)         scg_cfg_get_value(key).toUInt()
#define scg_cfg_get_value_color(key)        scg_config->string2color(scg_cfg_get_value_string(key))

// --- default values ---
#define scg_cfg_get_default_value(key)          scg_config->defaultValue(key)
#define scg_cfg_set_default_value(key, value)   scg_config->setDefaultValue(key, QVariant(value))

#define scg_cfg_set_default_value_color(key, value) scg_cfg_set_default_value(key, scg_config->color2string(value))

#define scg_cfg_get_default_string(key)         scg_cfg_get_default_value(key).toString()
#define scg_cfg_get_default_color(key)          scg_config->string2color(scg_cfg_get_default_string(key))
#define scg_cfg_get_default_float(key)          scg_cfg_get_default_value(key).toFloat()
#define scg_cfg_get_default_uint(key)           scg_cfg_get_default_value(key).toUInt()


// predefined keys
#define scg_key_element_color_normal QString("element/color/normal")
#define scg_key_element_color_selected QString("element/color/selected")
#define scg_key_element_color_highlight QString("element/color/highlight")
#define scg_key_element_font_name   QString("element/font/name")
#define scg_key_element_font_size   QString("element/font/size")
#define scg_key_element_font_color_normal QString("element/font/color/normal")
#define scg_key_element_font_color_selected QString("element/font/color/selected")
#define scg_key_element_font_color_highlight QString("element/font/colot/highlight")

#define scg_key_control_backcolor_normal QString("control/backcolor/normal")
#define scg_key_control_backcolor_selected QString("control/backcolor/selected")
#define scg_key_control_backcolor_highlight QString("control/backcolor/highlight")
#define scg_key_control_color_normal QString("control/color/normal")
#define scg_key_control_color_selected QString("control/color/selected")
#define scg_key_control_color_highlight QString("control/color/highlight")
#define scg_key_control_font_name QString("control/font/name")
#define scg_key_control_font_size QString("control/font/size")
#define scg_key_control_font_color QString("control/font/color")

#if ENABLE_VISUAL_EFFECTS_SUPPORT
#define scg_key_effects_enabled QString("effects/enabled")
#endif

class SCgConfig : public QObject
{
    Q_OBJECT
public:
    explicit SCgConfig(QObject *parent = 0);
    virtual ~SCgConfig();

    static SCgConfig* getInstance();
    static void Destroy();

    static QDir pathIcons;
    static QDir pathMedia;

    /*! Set option value
      * @param option Option name. Use '/' to make hiararchy storage. Example 'color/element/normal'.
      * @param value Option value.
      */
    void setValue(const QString &option, const QVariant &value);

    /*! Get option value
      * @param option Option name.
      *
      * @return return specified option value.
      */
    QVariant value(const QString &option) const;

    /*! Check if option exists
      * @param option Option name.
      *
      * @return If option with specified name exists, then return true, else - return false.
      */
    bool haveValue(const QString &option) const;


    /*! Set default option value
      * @param option Option name.
      * @param value Option value.

      * @see SCgConfig::setValue
      */
    void setDefaultValue(const QString &option, const QVariant &value);

    /*! Get default option value
      * @param option Option name.
      *
      * @return return default value for specified option
      */
    QVariant defaultValue(const QString &option) const;

    /*! Check if default value for  option exists
      * @param option Option name.
      *
      * @return If default value for option exists, then return true, else - return false.
      */
    bool haveDefaultValue(const QString &option) const;

    /*! Represent QColor to QString
      * @param color Color to represent as string
      * @return return color represented as string
      */
    QString color2string(const QColor &color) const;
    /*! Build QColor from string representation
      * @param str String that contatins color.
      * @return Color made from string representation.
      */
    QColor string2color(const QString &str) const;

private:
    static SCgConfig *mInstance;

    //! Options value map
    QMap<QString, QVariant> mValues;
    //! Default values
    QMap<QString, QVariant> mDefaultValues;

protected:
    //! Initialize configuration
    void initialize();
    //! Initialize default values
    void initializeDefault();

    //! Read values from configuration storage
    void readConfiguration();
    //! Save configuration to storage
    void saveConfiguration();

signals:

public slots:

};

#endif // SCGCONFIG_H
