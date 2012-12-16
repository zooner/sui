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

#ifndef SCGPROGRESSBAR_H
#define SCGPROGRESSBAR_H

#include <QGraphicsWidget>

#include <QQueue>
#include <QPen>
//------------------------------------------------------------------------------
class SCgProgressBar : public QGraphicsWidget
{
    Q_OBJECT
public:
    explicit SCgProgressBar(QGraphicsItem *parent = 0);
    virtual ~SCgProgressBar();

    virtual QRectF boundingRect() const;
    virtual QPainterPath shape() const;

    //! Return text
    const QString & text() const;

    //! Return current progress
    qreal curProgress() const;

    //! Return progress queue
    const QQueue<qreal> & progressQueue() const;

    /*! Set new frame rate value
      * @param frameRate New frame rate value
      */
    void setFrameRate(qreal frameRate);
    //! Return frame rate value
    qreal frameRate() const;

    /*! Set new width value
      * @param width New width value
      */
    void setWidth(qreal width);
    //! Return width value
    qreal width() const;

    /*! Set new height value
      * @param height New height value
      */
    void setHeight(qreal height);
    //! Return height value
    qreal height() const;

    /*! Set new step width value
      * @param stepWidth New step width value
      */
    void setStepWidth(qreal stepWidth);
    //! Return step width value
    qreal stepWidth() const;

    /*! Set new brush
      * @param brush New brush
      */
    void setBrush(QBrush brush);
    //! Return brush
    QBrush brush() const;

    /*! Set new progress brush
      * @param progressBrush New progress brush
      */
    void setProgressBrush(QBrush progressBrush);
    //! Return progressBrush
    QBrush progressBrush() const;

    /*! Set new pen
      * @param pen New pen
      */
    void setPen(QPen pen);
    //! Return pen
    QPen pen() const;

    /*! Set new radius of rounded rectangle on the X axis
      * @param roundedRectXRadius
      */
    void setRoundedRectXRadius(qreal roundedRectXRadius);
    //! Return roundedRectXRadius
    qreal roundedRectXRadius() const;

    /*! Set new radius of rounded rectangle on the Y axis
      * @param roundedRectYRadius
      */
    void setRoundedRectYRadius(qreal roundedRectYRadius);
    //! Return roundedRectYRadius
    qreal roundedRectYRadius() const;

    /*! Set new text font
      * @param font New text font
      */
    void setTextFont(QFont font);
    //! Return text font
    QFont textFont() const;

    /*! Set new text pen
      * @param pen New text pen
      */
    void setTextPen(QPen pen);
    //! Return text pen
    QPen textPen() const;

    /*! Set progress text visibility property value
      * @param visible New progress text visibility property value
      */
    void setProgressTextVisible(bool visible);
    //! Return text visibility property value
    bool isProgressTextVisible() const;

public slots:
    /*! Set new text
      * @param text New text
      */
    void setText(const QString &text);

    /*! Set text value to percentage
      * @param percent Percent value in range [0..1]
      */
    void setPercentText(qreal percent);

    /*! Set new progress value smoothly
      * @param progress New progress value
      */
    bool setProgressSmoothly(qreal progress);

    /*! Set new progress value abruptly
      * @param progress New progress value
      */
    bool setProgressAbruptly(qreal progress);

signals:
    /*! This signal is emitted when progress bar reaches the setting of progress value
      * @param progress The reached progress value
      */
    void smoothlyChangingFinished(qreal progress);

    /*! This signal is emitted when progress bar value changes
      * @param progress New progress value
      */
    void progressChanged(qreal progress);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected slots:
    //! Update animation progress
    void updateAnimationProgress();

private:
    //! Text
    QString mText;
    //! Current progress value
    qreal mCurProgress;
    //! Progress value queue
    QQueue<qreal> mProgressQueue;
    //! Timer updates animation progress
    QTimer *mTimer;
    //! Frame rate
    qreal mFrameRate;
    //! Width
    qreal mWidth;
    //! Height
    qreal mHeight;
    //! Step width
    qreal mStepWidth;
    //! Brush
    QBrush mBrush;
    //! Progress brush
    QBrush mProgressBrush;
    //! Pen
    QPen mPen;
    //! Radius of rounded rectangle on the X axis
    qreal mRoundedRectXRadius;
    //! Radius of rounded rectangle on the Y axis
    qreal mRoundedRectYRadius;
    //! Text font
    QFont mTextFont;
    //! Text pen
    QPen mTextPen;
    //! Progress text visibility property
    bool mProgressTextVisible;
};
//------------------------------------------------------------------------------
#endif // SCGPROGRESSBAR_H
