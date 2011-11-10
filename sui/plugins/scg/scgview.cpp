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
#include "scgview.h"

#include <QKeyEvent>

SCgView::SCgView(QWidget *parent) :
    QGraphicsView(parent)
{
}

SCgView::~SCgView()
{
}

void SCgView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control)
        setDragMode(QGraphicsView::ScrollHandDrag);

    QGraphicsView::keyPressEvent(event);
}

void SCgView::keyReleaseEvent(QKeyEvent *event)
{

    if (event->key() == Qt::Key_Control)
        setDragMode(QGraphicsView::RubberBandDrag);

    QGraphicsView::keyReleaseEvent(event);
}
