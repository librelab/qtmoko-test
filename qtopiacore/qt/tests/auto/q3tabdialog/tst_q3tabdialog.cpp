/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/


#include <QtTest/QtTest>

#include <qapplication.h>
#include <qdebug.h>
#include <q3tabdialog.h>
#include <qtabbar.h>

//TESTED_CLASS=
//TESTED_FILES=

class tst_Q3TabDialog : public QObject
{
Q_OBJECT

public:
    tst_Q3TabDialog();
    virtual ~tst_Q3TabDialog();

private slots:
    void getSetCheck();
};

tst_Q3TabDialog::tst_Q3TabDialog()
{
}

tst_Q3TabDialog::~tst_Q3TabDialog()
{
}

class My3TabDialog : public Q3TabDialog
{
public:
    My3TabDialog() : Q3TabDialog() {}
    void setTabBar(QTabBar* bar) { Q3TabDialog::setTabBar(bar); }
    QTabBar* tabBar() const { return Q3TabDialog::tabBar(); }
};

// Testing get/set functions
void tst_Q3TabDialog::getSetCheck()
{
    My3TabDialog obj1;
    // QTabBar* Q3TabDialog::tabBar()
    // void Q3TabDialog::setTabBar(QTabBar*)
    QTabBar *var1 = new QTabBar;
    obj1.setTabBar(var1);
    QCOMPARE(var1, obj1.tabBar());

    QTabBar * const oldTabBar = obj1.tabBar();
    obj1.setTabBar((QTabBar *)0);
    QCOMPARE(obj1.tabBar(), oldTabBar);

    delete var1;
}

QTEST_MAIN(tst_Q3TabDialog)
#include "tst_q3tabdialog.moc"
