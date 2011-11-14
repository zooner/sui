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

#include "scgprecompiled.h"
#include "scgwaitwidget.h"

#include <QTimer>
#include <QPainter>
#include <QFontMetrics>

SCgWaitWidget::SCgWaitWidget(QGraphicsItem *parent) :
    QGraphicsWidget(parent),
    mProgress(0.f)
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateAnimationProgress()));
    timer->start(50); // 20 frames per second
}


SCgWaitWidget::~SCgWaitWidget()
{
}

void SCgWaitWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF boundRect = boundingRect();

    // draw background
    painter->setBrush(QBrush(QColor(128, 128, 128, 128)));
    painter->setPen(Qt::NoPen);
    painter->drawRoundedRect(boundRect, 10, 10);

    // draw circles
    qreal r = qMin(boundRect.width(), boundRect.height());
    r /= 2.f;
    qreal gr = r * 0.7f;
    qreal dr = r * 0.2f;
    quint32 num = 10;
    QPointF offset(boundRect.width() / 2.f, boundRect.height() / 2.f);
    qreal da = mProgress * M_PI * 2;

    painter->setBrush(QBrush(QColor(255, 255, 255, 196)));
    for (quint32 i = 0; i < num; i++)
    {
        qreal radius = dr * ((i + 1) / (qreal)num);
        painter->drawEllipse(QPointF(gr * cos(i * M_PI * 2 / (qreal)num + da) + offset.x(),
                                     gr * sin(i * M_PI * 2 / (qreal)num + da) + offset.y()),
                             radius, radius);
    }

    if (!mTextValue.isEmpty())
    {
        QFont font("Arial", 8, 8);
        painter->setPen(QPen(QColor(255, 255, 255, 196)));
        painter->setFont(font);
        QRectF font_bounds = QFontMetrics(font).boundingRect(mTextValue);
        font_bounds.moveCenter(boundRect.center());
        painter->drawText(font_bounds, mTextValue);
    }
}

void SCgWaitWidget::updateAnimationProgress()
{
    mProgress += 0.06;
    if (mProgress > 1.f) mProgress -= 1.f;

    update();
}

void SCgWaitWidget::setText(const QString &text)
{
    mTextValue = text;
}

void SCgWaitWidget::setPercentText(qreal percent)
{
    mTextValue = QString("%1\%").arg((quint32)(percent * 100));
}

const QString& SCgWaitWidget::text() const
{
    return mTextValue;
}
