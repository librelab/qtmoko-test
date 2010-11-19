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


#include <qstatusbar.h>
#include <QLabel>
#include <QMainWindow>
#include <QSizeGrip>

//TESTED_CLASS=
//TESTED_FILES=

class tst_QStatusBar: public QObject
{
    Q_OBJECT

public:
    tst_QStatusBar();
    virtual ~tst_QStatusBar();


protected slots:
    void messageChanged(const QString&);

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private slots:
    void tempMessage();
    void insertWidget();
    void insertPermanentWidget();
    void setSizeGripEnabled();
    void task194017_hiddenWidget();

private:
    QStatusBar *testWidget;
    QString currentMessage;
};

tst_QStatusBar::tst_QStatusBar()
{
}

tst_QStatusBar::~tst_QStatusBar()
{
}

void tst_QStatusBar::init()
{
    testWidget = new QStatusBar;
    connect(testWidget, SIGNAL(messageChanged(QString)), this, SLOT(messageChanged(QString)));

    QWidget *item1 = new QWidget(testWidget);
    testWidget->addWidget(item1);
}

void tst_QStatusBar::cleanup()
{
    delete testWidget;
}

void tst_QStatusBar::initTestCase()
{
}

void tst_QStatusBar::cleanupTestCase()
{
}

void tst_QStatusBar::messageChanged(const QString &m)
{
    currentMessage = m;
}

void tst_QStatusBar::tempMessage()
{
    QVERIFY(testWidget->currentMessage().isNull());
    QVERIFY(currentMessage.isNull());

    testWidget->showMessage("Ready", 500);
    QCOMPARE(testWidget->currentMessage(), QString("Ready"));
    QCOMPARE(testWidget->currentMessage(), currentMessage);

    QTest::qWait(1000);

    QVERIFY(testWidget->currentMessage().isNull());
    QVERIFY(currentMessage.isNull());

    testWidget->showMessage("Ready again", 500);
    QCOMPARE(testWidget->currentMessage(), QString("Ready again"));
    QCOMPARE(testWidget->currentMessage(), currentMessage);

    testWidget->clearMessage();
    QVERIFY(testWidget->currentMessage().isNull());
    QVERIFY(currentMessage.isNull());
}

void tst_QStatusBar::insertWidget()
{
    QStatusBar sb;
    sb.addPermanentWidget(new QLabel("foo"));
    QTest::ignoreMessage(QtWarningMsg, "QStatusBar::insertWidget: Index out of range (-1), appending widget");
    QCOMPARE(sb.insertWidget(-1, new QLabel("foo")), 0);
    QTest::ignoreMessage(QtWarningMsg, "QStatusBar::insertWidget: Index out of range (2), appending widget");
    QCOMPARE(sb.insertWidget(2, new QLabel("foo")), 1);
    QCOMPARE(sb.insertWidget(0, new QLabel("foo")), 0);
    QCOMPARE(sb.insertWidget(3, new QLabel("foo")), 3);
}

void tst_QStatusBar::insertPermanentWidget()
{
    QStatusBar sb;
    sb.addWidget(new QLabel("foo"));
    QTest::ignoreMessage(QtWarningMsg, "QStatusBar::insertPermanentWidget: Index out of range (-1), appending widget");
    QCOMPARE(sb.insertPermanentWidget(-1, new QLabel("foo")), 1);
    QTest::ignoreMessage(QtWarningMsg, "QStatusBar::insertPermanentWidget: Index out of range (0), appending widget");
    QCOMPARE(sb.insertPermanentWidget(0, new QLabel("foo")), 2);
    QCOMPARE(sb.insertPermanentWidget(2, new QLabel("foo")), 2);
    QTest::ignoreMessage(QtWarningMsg, "QStatusBar::insertPermanentWidget: Index out of range (5), appending widget");
    QCOMPARE(sb.insertPermanentWidget(5, new QLabel("foo")), 4);
    QCOMPARE(sb.insertWidget(1, new QLabel("foo")), 1);
    QTest::ignoreMessage(QtWarningMsg, "QStatusBar::insertPermanentWidget: Index out of range (1), appending widget");
    QCOMPARE(sb.insertPermanentWidget(1, new QLabel("foo")), 6);
}

void tst_QStatusBar::setSizeGripEnabled()
{
    QMainWindow mainWindow;
    QPointer<QStatusBar> statusBar = mainWindow.statusBar();
    QVERIFY(statusBar);
    mainWindow.show();
#ifdef Q_WS_X11
    qt_x11_wait_for_window_manager(&mainWindow);
#endif

    QVERIFY(statusBar->isVisible());
    QPointer<QSizeGrip> sizeGrip = qFindChild<QSizeGrip *>(statusBar);
    QVERIFY(sizeGrip);
    QVERIFY(sizeGrip->isVisible());

    statusBar->setSizeGripEnabled(true);
    QVERIFY(sizeGrip);
    QVERIFY(sizeGrip->isVisible());

    statusBar->hide();
    QVERIFY(!sizeGrip->isVisible());
    statusBar->show();
    QVERIFY(sizeGrip->isVisible());

    sizeGrip->setVisible(false);
    QVERIFY(!sizeGrip->isVisible());
    statusBar->hide();
    statusBar->show();
    QVERIFY(!sizeGrip->isVisible());

    statusBar->setSizeGripEnabled(false);
    QVERIFY(!sizeGrip);

    qApp->processEvents();
    mainWindow.showFullScreen();
#ifdef Q_WS_X11
    qt_x11_wait_for_window_manager(&mainWindow);
#endif
    qApp->processEvents();

    mainWindow.setStatusBar(new QStatusBar(&mainWindow));
    //we now call deleteLater on the previous statusbar
    QCoreApplication::sendPostedEvents(0, QEvent::DeferredDelete);
    QVERIFY(!statusBar);
    statusBar = mainWindow.statusBar();
    QVERIFY(statusBar);

    sizeGrip = qFindChild<QSizeGrip *>(statusBar);
    QVERIFY(sizeGrip);
    QVERIFY(!sizeGrip->isVisible());

    statusBar->setSizeGripEnabled(true);
    QVERIFY(!sizeGrip->isVisible());

    qApp->processEvents();
    mainWindow.showNormal();
#ifdef Q_WS_X11
    qt_x11_wait_for_window_manager(&mainWindow);
#endif
    qApp->processEvents();
    QVERIFY(sizeGrip->isVisible());
}

void tst_QStatusBar::task194017_hiddenWidget()
{
    QStatusBar sb;

    QWidget *label= new QLabel("bar",&sb);
    sb.addWidget(label);
    sb.show();
    QVERIFY(label->isVisible());
    sb.showMessage("messssage");
    QVERIFY(!label->isVisible());
    sb.hide();
    QVERIFY(!label->isVisible());
    sb.show();
    QVERIFY(!label->isVisible());
    sb.clearMessage();
    QVERIFY(label->isVisible());
    label->hide();
    QVERIFY(!label->isVisible());
    sb.showMessage("messssage");
    QVERIFY(!label->isVisible());
    sb.clearMessage();
    QVERIFY(!label->isVisible());
    sb.hide();
    QVERIFY(!label->isVisible());
    sb.show();
    QVERIFY(!label->isVisible());
}


QTEST_MAIN(tst_QStatusBar)
#include "tst_qstatusbar.moc"
