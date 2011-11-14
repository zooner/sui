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

#ifndef SCGWAITWIDGET_H
#define SCGWAITWIDGET_H

#include <QGraphicsWidget>

class SCgWaitWidget : public QGraphicsWidget
{
    Q_OBJECT
public:
    explicit SCgWaitWidget(QGraphicsItem *parent = 0);
    virtual ~SCgWaitWidget();

    //! Return wait text value
    const QString& text() const;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


private:
    //! Animation progress
    qreal mProgress;
    //! Wait action text
    QString mTextValue;

signals:

public slots:
    /*! Set new text value into wait text
      * @param text New wait text value
      */
    void setText(const QString &text);

    /*! Set wait text value to percentage
      * @param percent Percent value in range [0..1]
      */
    void setPercentText(qreal percent);

protected slots:
    //! Update animation progress
    void updateAnimationProgress();

};

#endif // SCGWAITWIDGET_H
