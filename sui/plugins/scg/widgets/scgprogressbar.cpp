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
#include "scgprogressbar.h"

#include <QTimer>
#include <QPainter>
#include <QFontMetrics>

const qreal FrameRateInit = 20; // 20 frames per second.
const qreal WidthInit = 200;
const qreal HeightInit = 15;
const qreal StepWidthInit = 0.01;
const QBrush BrushInit = QBrush(QColor(128, 128, 128, 128));
const QBrush ProgressBrushInit = QBrush(QColor(255, 255, 255, 196));
const QPen PenInit = QPen(QBrush(Qt::black), 2);
const qreal RoundedRectXRadiusInit = 5;
const qreal RoundedRectYRadiusInit = 5;
const QFont TextFontInit = QFont("Arial", 8, 8);
const QPen TextPenInit = QPen(QColor(0, 0, 0, 196));
const bool ProgressTextVisibleInit = true;
//------------------------------------------------------------------------------
SCgProgressBar::SCgProgressBar(QGraphicsItem *parent) : QGraphicsWidget(parent)
{
    mText = "";

    mCurProgress = 0.f;
    mProgressQueue.clear();

    mTimer = new QTimer(this);
    connect(mTimer, SIGNAL(timeout()), this, SLOT(updateAnimationProgress()));
    mFrameRate = FrameRateInit;

    mWidth = WidthInit;
    mHeight = HeightInit;
    mStepWidth = StepWidthInit;
    mBrush = BrushInit;
    mProgressBrush = ProgressBrushInit;
    mPen = PenInit;
    mRoundedRectXRadius = RoundedRectXRadiusInit;
    mRoundedRectYRadius = RoundedRectYRadiusInit;
    mTextFont = TextFontInit;
    mTextPen = TextPenInit;
    mProgressTextVisible = ProgressTextVisibleInit;
}
//------------------------------------------------------------------------------
SCgProgressBar::~SCgProgressBar()
{
}
//------------------------------------------------------------------------------
QRectF SCgProgressBar::boundingRect() const
{
    return QRectF(0, 0, mWidth + 1.5 * (qreal)mPen.width(),
                  mHeight + 1.5 * (qreal)mPen.width());
}
//------------------------------------------------------------------------------
QPainterPath SCgProgressBar::shape() const
{
    QPainterPath path;
    path.addRoundedRect(boundingRect(), mRoundedRectXRadius + (qreal)mPen.width() / 2.,
                        mRoundedRectYRadius + (qreal)mPen.width() / 2.);
    return path;
}
//------------------------------------------------------------------------------
const QString & SCgProgressBar::text() const
{
    return mText;
}
//------------------------------------------------------------------------------
qreal SCgProgressBar::curProgress() const
{
    return mCurProgress;
}
//------------------------------------------------------------------------------
const QQueue<qreal> & SCgProgressBar::progressQueue() const
{
    return mProgressQueue;
}
//------------------------------------------------------------------------------
void SCgProgressBar::setFrameRate(qreal frameRate)
{
    mFrameRate = frameRate;
    mTimer->setInterval(1000 / frameRate);
    if (mTimer->isActive()) {
        mTimer->start();
    }
}
//------------------------------------------------------------------------------
qreal SCgProgressBar::frameRate() const
{
    return mFrameRate;
}
//------------------------------------------------------------------------------
void SCgProgressBar::setWidth(qreal width)
{
    if (mWidth != width) {
        prepareGeometryChange();
        mWidth = width;
    }
}
//------------------------------------------------------------------------------
qreal SCgProgressBar::width() const
{
    return mWidth;
}
//------------------------------------------------------------------------------
void SCgProgressBar::setHeight(qreal height)
{
    if (mHeight != height) {
        prepareGeometryChange();
        mHeight = height;
    }
}
//------------------------------------------------------------------------------
qreal SCgProgressBar::height() const
{
    return mHeight;
}
//------------------------------------------------------------------------------
void SCgProgressBar::setStepWidth(qreal stepWidth)
{
    if (mStepWidth != stepWidth) {
        prepareGeometryChange();
        mStepWidth = stepWidth;
    }
}
//------------------------------------------------------------------------------
qreal SCgProgressBar::stepWidth() const
{
    return mStepWidth;
}
//------------------------------------------------------------------------------
void SCgProgressBar::setBrush(QBrush brush)
{
    if (mBrush != brush) {
        prepareGeometryChange();
        mBrush = brush;
    }
}
//------------------------------------------------------------------------------
QBrush SCgProgressBar::brush() const
{
    return mBrush;
}
//------------------------------------------------------------------------------
void SCgProgressBar::setProgressBrush(QBrush progressBrush)
{
    if (mProgressBrush != progressBrush) {
        prepareGeometryChange();
        mProgressBrush = progressBrush;
    }
}
//------------------------------------------------------------------------------
QBrush SCgProgressBar::progressBrush() const
{
    return mProgressBrush;
}
//------------------------------------------------------------------------------
void SCgProgressBar::setPen(QPen pen)
{
    if (mPen != pen) {
        prepareGeometryChange();
        mPen = pen;
    }
}
//------------------------------------------------------------------------------
QPen SCgProgressBar::pen() const
{
    return mPen;
}
//------------------------------------------------------------------------------
void SCgProgressBar::setRoundedRectXRadius(qreal roundedRectXRadius)
{
    if (mRoundedRectXRadius != roundedRectXRadius) {
        prepareGeometryChange();
        mRoundedRectXRadius = roundedRectXRadius;
    }
}
//------------------------------------------------------------------------------
qreal SCgProgressBar::roundedRectXRadius() const
{
    return mRoundedRectXRadius;
}
//------------------------------------------------------------------------------
void SCgProgressBar::setRoundedRectYRadius(qreal roundedRectYRadius)
{
    if (mRoundedRectYRadius != roundedRectYRadius) {
        prepareGeometryChange();
        mRoundedRectYRadius = RoundedRectYRadiusInit;
    }
}
//------------------------------------------------------------------------------
qreal SCgProgressBar::roundedRectYRadius() const
{
    return mRoundedRectYRadius;
}
//------------------------------------------------------------------------------
void SCgProgressBar::setTextFont(QFont font)
{
    if (mTextFont != font) {
        prepareGeometryChange();
        mTextFont = font;
    }
}
//------------------------------------------------------------------------------
QFont SCgProgressBar::textFont() const
{
    return mTextFont;
}
//------------------------------------------------------------------------------
void SCgProgressBar::setTextPen(QPen pen)
{
    if (mTextPen != pen) {
        prepareGeometryChange();
        mTextPen = pen;
    }
}
//------------------------------------------------------------------------------
QPen SCgProgressBar::textPen() const
{
    return mTextPen;
}
//------------------------------------------------------------------------------
void SCgProgressBar::setProgressTextVisible(bool visible)
{
    if (mProgressTextVisible != visible) {
        prepareGeometryChange();
        mProgressTextVisible = visible;
    }
}
//------------------------------------------------------------------------------
bool SCgProgressBar::isProgressTextVisible() const
{
    return mProgressTextVisible;
}
//------------------------------------------------------------------------------
void SCgProgressBar::setText(const QString &text)
{
    mText = text;
}
//------------------------------------------------------------------------------
void SCgProgressBar::setPercentText(qreal percent)
{
    mText = QString("%1\%").arg((quint32)(percent * 100));
}
//------------------------------------------------------------------------------
bool SCgProgressBar::setProgressSmoothly(qreal progress)
{
    if (progress >= 0 && progress <= 1) {
        mProgressQueue.enqueue(progress);
        mTimer->start(1000 / mFrameRate);

        return true;
    }
    else {
        return false;
    }
}
//------------------------------------------------------------------------------
bool SCgProgressBar::setProgressAbruptly(qreal progress)
{
    if (progress >= 0 && progress <= 1) {
        if (mTimer->isActive()) {
            mTimer->stop();
            mProgressQueue.clear();
        }

        mCurProgress = progress;
        emit progressChanged(mCurProgress);
        update();

        return true;
    }
    else {
        return false;
    }
}
//------------------------------------------------------------------------------
void SCgProgressBar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF boundRect = boundingRect();

    // draw background
    painter->setBrush(mBrush);
    painter->setPen(mPen);
    painter->drawRoundedRect(QRectF((qreal)mPen.width() / 2., (qreal)mPen.width() / 2.,
                                    mWidth + (qreal)mPen.width() / 2., mHeight + (qreal)mPen.width() / 2.),
                             mRoundedRectXRadius, mRoundedRectYRadius);

    painter->setBrush(mProgressBrush);
    painter->setPen(Qt::NoPen);

    qreal curWidth = mCurProgress * mWidth;
    qreal width = curWidth - (qreal)mPen.width() / 2.;
    qreal height = mHeight - (qreal)mPen.width() / 2.;
    if (width < 0) {
        width = 0;
    }
    if (height < 0) {
        height = 0;
    }
    painter->drawRoundedRect(QRectF((qreal)mPen.width(), (qreal)mPen.width(), width, height),
                             mRoundedRectXRadius - (qreal)mPen.width() / 2., mRoundedRectYRadius - (qreal)mPen.width() / 2.);

    // Draw text:
    if (!mText.isEmpty() || mProgressTextVisible) {
        painter->setPen(mTextPen);
        painter->setFont(mTextFont);

        // Draw progress text:
        if (mProgressTextVisible) {
            QString progressText = QString("%1\%").arg((quint32)(mCurProgress * 100));
            QRectF progressTextBoundingRect = QFontMetrics(mTextFont).boundingRect(progressText);
            progressTextBoundingRect.moveCenter(boundRect.center());
            painter->drawText(progressTextBoundingRect, progressText);
        }

        // Draw user text:
        if (!mText.isEmpty()) {
            QRectF textBoundingRect = QFontMetrics(mTextFont).boundingRect(mText);
            textBoundingRect.moveCenter(boundRect.center());
            painter->drawText(textBoundingRect, mText);
        }
    }
}
//------------------------------------------------------------------------------
void SCgProgressBar::updateAnimationProgress()
{
    // Check progress value in range:
    if (mCurProgress > mProgressQueue.head() - mStepWidth
            && mCurProgress < mProgressQueue.head() + mStepWidth) {
        mCurProgress = mProgressQueue.dequeue();
        emit progressChanged(mCurProgress);
        if (mProgressQueue.isEmpty()) {
            mTimer->stop();
            emit smoothlyChangingFinished(mCurProgress);
        }
    }
    else if (mCurProgress < mProgressQueue.head()) {
        mCurProgress += mStepWidth;
        emit progressChanged(mCurProgress);
    }
    else if (mCurProgress > mProgressQueue.head()) {
        mCurProgress -= mStepWidth;
        emit progressChanged(mCurProgress);
    }

    update();
}
//------------------------------------------------------------------------------
