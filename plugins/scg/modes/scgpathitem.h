/*
 * SCgLinePathItem.h
 *
 *  Created on: 18.07.2011
 *      Author: ZooNer
 */

#ifndef SCGLINEPATHITEM_H_
#define SCGLINEPATHITEM_H_

#include <QObject>

#include <QPointF>
#include <QPen>
#include <QGraphicsPathItem>

class QGraphicsScene;

/*! This item(actually helper class who drawn path item) is drawn while user specifying SCgPointObject's shape.
 *
 */
class SCgPathItem:public QObject
{
    Q_OBJECT
public:
    /*!
     * @param closed flag is used only for SCgContours.
     */
    explicit SCgPathItem(QGraphicsScene* scene, bool closed = false, QObject* parent = 0);
    virtual ~SCgPathItem();

    //! Clears item points, but doesn't delete it from scene.
    void clear();

    //! Appends new point to path. @note point should be in scene coordinate system.
    void pushPoint(const QPointF& point);

    //! Deletes last added point from the path.
    void popPoint();

    //! Updates whole item with given last point.(usually it's mouse position)
    void update(const QPointF& lastPoint);

    //! @return List of points
    QVector<QPointF> points() const
    {
        return mPoints;
    }

    //! @return pen used for drawing current path.
    QPen pen() const
    {
        return mPath.pen();
    }

    //! @return path, already drawn.
    QPainterPath path() const
    {
        return mPath.path();
    }

    //! sets a pen, item will drawn with.
    void setPen(const QPen& pen);

private:
    //! updates path with points in mPoints.
    void updatePath();

    /*!
     * Updates a line between the last point and given point (usually mouse position)
     */
    void updateLastLine(QPointF mousePos);

    QGraphicsPathItem mPath;

    QVector<QPointF> mPoints;

    // We use separate closing lines (not draw all path itself)
    // because of performance issue. If we draw all path in one QGraphicsPathItem, we'll need
    // to update(redraw) whole path on each user's action (mouse move, or changing path's points).
    // With this lines, we update only them.
    QGraphicsLineItem mLastLine;
    // only for closed paths.
    QGraphicsLineItem* mClosingLine;

    // specifies if path is closed.
    bool mIsClosed;
};

#endif /* SCGLINEPATHITEM_H_ */
