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

#include "precompiled.h"
#include "mainwindow.h"

void fileMessageOutput(QtMsgType type, const char *msg)
{
     switch (type)
     {
     case QtDebugMsg:
         *MainWindow::mLogStream << QString("Debug: %1\n").arg(QString(msg));
         break;
     case QtWarningMsg:
         *MainWindow::mLogStream << QString("Warning: %1\n").arg(QString(msg));
         break;
     case QtCriticalMsg:
         *MainWindow::mLogStream << QString("Critical: %1\n").arg(QString(msg));
         break;
     case QtFatalMsg:
         *MainWindow::mLogStream << QString("Fatal: %1\n").arg(QString(msg));
         abort();
     }
 }

QFile* MainWindow::mLogFile = 0;
QTextStream* MainWindow::mLogStream = 0;

QtMsgHandler default_handler;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    mRoot(0)
{
    mRoot = new suiRoot(this);
    mLogFile = new QFile("sui.log");
    mLogFile->open(QIODevice::WriteOnly | QIODevice::Text);
    mLogStream = new QTextStream(mLogFile);

    default_handler = qInstallMsgHandler(fileMessageOutput);

}

MainWindow::~MainWindow()
{
    qInstallMsgHandler(default_handler);
    mLogFile->close();
    delete mLogStream;
    delete mLogFile;
    delete mRoot;
}
