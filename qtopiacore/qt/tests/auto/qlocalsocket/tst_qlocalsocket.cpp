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

#include <qtextstream.h>
#include <QtNetwork/qlocalsocket.h>
#include <QtNetwork/qlocalserver.h>
#include "../../shared/util.h"

//TESTED_CLASS=QLocalServer, QLocalSocket
//TESTED_FILES=network/socket/qlocalserver.cpp network/socket/qlocalsocket.cpp

Q_DECLARE_METATYPE(QLocalSocket::LocalSocketError)
Q_DECLARE_METATYPE(QLocalSocket::LocalSocketState)

class tst_QLocalSocket : public QObject
{
    Q_OBJECT

public:
    tst_QLocalSocket();
    virtual ~tst_QLocalSocket();

public Q_SLOTS:
    void init();
    void cleanup();

private slots:
    // basics
    void server_basic();
    void server_connectionsCount();
    void socket_basic();

    void listen_data();
    void listen();

    void listenAndConnect_data();
    void listenAndConnect();

    void sendData_data();
    void sendData();

    void fullPath();

    void hitMaximumConnections_data();
    void hitMaximumConnections();

    void setSocketDescriptor();

    void threadedConnection_data();
    void threadedConnection();

    void processConnection_data();
    void processConnection();

    void longPath();
    void waitForDisconnect();
    void waitForDisconnectByServer();

    void removeServer();

    void recycleServer();

    void debug();

};

tst_QLocalSocket::tst_QLocalSocket()
{
    if (!QFile::exists("lackey/lackey"
#ifdef Q_OS_WIN
    ".exe"
#endif
                ))
        qWarning() << "lackey executable doesn't exists!";
}

tst_QLocalSocket::~tst_QLocalSocket()
{
}

void tst_QLocalSocket::init()
{
    qRegisterMetaType<QLocalSocket::LocalSocketState>("QLocalSocket::LocalSocketState");
    qRegisterMetaType<QLocalSocket::LocalSocketError>("QLocalSocket::LocalSocketError");
}

void tst_QLocalSocket::cleanup()
{
}

class LocalServer : public QLocalServer
{
    Q_OBJECT

public:
    LocalServer() : QLocalServer()
    {
        connect(this, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
    }

    bool listen(const QString &name)
    {
        removeServer(name);
        return QLocalServer::listen(name);
    }

    QList<int> hits;

protected:
    void incomingConnection(quintptr socketDescriptor)
    {
        hits.append(socketDescriptor);
        QLocalServer::incomingConnection(socketDescriptor);
    }

private slots:
    void slotNewConnection() {
        QVERIFY(!hits.isEmpty());
        QVERIFY(hasPendingConnections());
    }
};

class LocalSocket : public QLocalSocket
{
    Q_OBJECT

public:
    LocalSocket(QObject *parent = 0) : QLocalSocket(parent)
    {
        connect(this, SIGNAL(connected()),
                this, SLOT(slotConnected()));
        connect(this, SIGNAL(disconnected()),
                this, SLOT(slotDisconnected()));
        connect(this, SIGNAL(error(QLocalSocket::LocalSocketError)),
                this, SLOT(slotError(QLocalSocket::LocalSocketError)));
        connect(this, SIGNAL(stateChanged(QLocalSocket::LocalSocketState)),
                this, SLOT(slotStateChanged(QLocalSocket::LocalSocketState)));
        connect(this, SIGNAL(readyRead()),
                this, SLOT(slotReadyRead()));
    }

private slots:
    void slotConnected()
    {
        QCOMPARE(state(), QLocalSocket::ConnectedState);
    }
    void slotDisconnected()
    {
        QCOMPARE(state(), QLocalSocket::UnconnectedState);
    }
    void slotError(QLocalSocket::LocalSocketError newError)
    {
        QVERIFY(errorString() != "Unknown error");
        QCOMPARE(error(), newError);
    }
    void slotStateChanged(QLocalSocket::LocalSocketState newState)
    {
        QCOMPARE(state(), newState);
    }
    void slotReadyRead()
    {
        QVERIFY(bytesAvailable() > 0);
    }
};

// basic test make sure no segfaults and check default values
void tst_QLocalSocket::server_basic()
{
    LocalServer server;
    QSignalSpy spyNewConnection(&server, SIGNAL(newConnection()));
    server.close();
    QCOMPARE(server.errorString(), QString());
    QCOMPARE(server.hasPendingConnections(), false);
    QCOMPARE(server.isListening(), false);
    QCOMPARE(server.maxPendingConnections(), 30);
    QCOMPARE(server.nextPendingConnection(), (QLocalSocket*)0);
    QCOMPARE(server.serverName(), QString());
    QCOMPARE(server.fullServerName(), QString());
    QCOMPARE(server.serverError(), QAbstractSocket::UnknownSocketError);
    server.setMaxPendingConnections(20);
    bool timedOut = true;
    QCOMPARE(server.waitForNewConnection(3000, &timedOut), false);
    QVERIFY(!timedOut);
    QCOMPARE(server.listen(QString()), false);

    QCOMPARE(server.hits.count(), 0);
    QCOMPARE(spyNewConnection.count(), 0);
}

void tst_QLocalSocket::server_connectionsCount()
{
    LocalServer server;
    server.setMaxPendingConnections(10);
    QCOMPARE(server.maxPendingConnections(), 10);
}

// basic test make sure no segfaults and check default values
void tst_QLocalSocket::socket_basic()
{
    LocalSocket socket;
    QSignalSpy spyConnected(&socket, SIGNAL(connected()));
    QSignalSpy spyDisconnected(&socket, SIGNAL(disconnected()));
    QSignalSpy spyError(&socket, SIGNAL(error(QLocalSocket::LocalSocketError)));
    QSignalSpy spyStateChanged(&socket, SIGNAL(stateChanged(QLocalSocket::LocalSocketState)));
    QSignalSpy spyReadyRead(&socket, SIGNAL(readyRead()));

    QCOMPARE(socket.serverName(), QString());
    QCOMPARE(socket.fullServerName(), QString());
    socket.abort();
    QVERIFY(socket.bytesAvailable() == 0);
    QVERIFY(socket.bytesToWrite() == 0);
    QCOMPARE(socket.canReadLine(), false);
    socket.close();
    socket.disconnectFromServer();
    QCOMPARE(QLocalSocket::UnknownSocketError, socket.error());
    QVERIFY(socket.errorString() != QString());
    QCOMPARE(socket.flush(), false);
    QCOMPARE(socket.isValid(), false);
    QVERIFY(socket.readBufferSize() == 0);
    socket.setReadBufferSize(0);
    //QCOMPARE(socket.socketDescriptor(), -1);
    QCOMPARE(socket.state(), QLocalSocket::UnconnectedState);
    QCOMPARE(socket.waitForConnected(0), false);
    QCOMPARE(socket.waitForDisconnected(0), false);
    QCOMPARE(socket.waitForReadyRead(0), false);

    QCOMPARE(spyConnected.count(), 0);
    QCOMPARE(spyDisconnected.count(), 0);
    QCOMPARE(spyError.count(), 0);
    QCOMPARE(spyStateChanged.count(), 0);
    QCOMPARE(spyReadyRead.count(), 0);
}

void tst_QLocalSocket::listen_data()
{
    QTest::addColumn<QString>("name");
    QTest::addColumn<bool>("canListen");
    QTest::addColumn<bool>("close");
    QTest::newRow("null") << QString() << false << false;
    QTest::newRow("tst_localsocket") << "tst_localsocket" << true << true;
    QTest::newRow("tst_localsocket") << "tst_localsocket" << true << false;
}

// start a server that listens, but don't connect a socket, make sure everything is in order
void tst_QLocalSocket::listen()
{
    LocalServer server;
    QSignalSpy spyNewConnection(&server, SIGNAL(newConnection()));

    QFETCH(QString, name);
    QFETCH(bool, canListen);
    QFETCH(bool, close);
    QVERIFY2((server.listen(name) == canListen), server.errorString().toLatin1().constData());

    // test listening
    QCOMPARE(server.serverName(), name);
    QVERIFY(server.fullServerName().contains(name));
    QCOMPARE(server.isListening(), canListen);
    QCOMPARE(server.hasPendingConnections(), false);
    QCOMPARE(server.nextPendingConnection(), (QLocalSocket*)0);
    QCOMPARE(server.hits.count(), 0);
    QCOMPARE(spyNewConnection.count(), 0);
    if (canListen) {
        QVERIFY(server.errorString() == QString());
        QCOMPARE(server.serverError(), QAbstractSocket::UnknownSocketError);
        // already isListening
        QVERIFY(!server.listen(name));
    } else {
        QVERIFY(server.errorString() != QString());
        QCOMPARE(server.serverError(), QAbstractSocket::HostNotFoundError);
    }
    QCOMPARE(server.maxPendingConnections(), 30);
    bool timedOut = false;
    QCOMPARE(server.waitForNewConnection(3000, &timedOut), false);
    QCOMPARE(timedOut, canListen);
    if (close)
        server.close();
}

void tst_QLocalSocket::listenAndConnect_data()
{
    QTest::addColumn<QString>("name");
    QTest::addColumn<bool>("canListen");
    QTest::addColumn<int>("connections");
    for (int i = 0; i < 3; ++i) {
        int connections = i;
        if (i == 2)
            connections = 5;
        QTest::newRow(QString("null %1").arg(i).toLatin1()) << QString() << false << connections;
        QTest::newRow(QString("tst_localsocket %1").arg(i).toLatin1()) << "tst_localsocket" << true << connections;
    }
}

void tst_QLocalSocket::listenAndConnect()
{
    LocalServer server;
    QSignalSpy spyNewConnection(&server, SIGNAL(newConnection()));

    QFETCH(QString, name);
    QFETCH(bool, canListen);

    QCOMPARE(server.listen(name), canListen);
    QTest::qWait(1000);
    //QVERIFY(!server.errorString().isEmpty());
    QCOMPARE(server.serverError(),
            canListen ? QAbstractSocket::UnknownSocketError : QAbstractSocket::HostNotFoundError);

    // test creating connection(s)
    QFETCH(int, connections);
    QList<QLocalSocket*> sockets;
    for (int i = 0; i < connections; ++i) {
        LocalSocket *socket = new LocalSocket;

        QSignalSpy spyConnected(socket, SIGNAL(connected()));
        QSignalSpy spyDisconnected(socket, SIGNAL(disconnected()));
        QSignalSpy spyError(socket, SIGNAL(error(QLocalSocket::LocalSocketError)));
        QSignalSpy spyStateChanged(socket, SIGNAL(stateChanged(QLocalSocket::LocalSocketState)));
        QSignalSpy spyReadyRead(socket, SIGNAL(readyRead()));

        socket->connectToServer(name);
#ifdef QT_LOCALSOCKET_TCP
        QTest::qWait(250);
#endif

        QCOMPARE(socket->serverName(), name);
        QVERIFY(socket->fullServerName().contains(name));
        sockets.append(socket);
        if (canListen) {
            QCOMPARE(socket->errorString(), QString("Unknown error"));
            QCOMPARE(socket->error(), QLocalSocket::UnknownSocketError);
            QCOMPARE(socket->state(), QLocalSocket::ConnectedState);
            //QVERIFY(socket->socketDescriptor() != -1);
            QCOMPARE(spyError.count(), 0);
        } else {
            QVERIFY(socket->errorString() != QString());
            QVERIFY(socket->error() != QLocalSocket::UnknownSocketError);
            QCOMPARE(socket->state(), QLocalSocket::UnconnectedState);
            //QVERIFY(socket->socketDescriptor() == -1);
            QCOMPARE(qVariantValue<QLocalSocket::LocalSocketError>(spyError.first()[0]),
                     QLocalSocket::ServerNotFoundError);
        }

        QVERIFY(socket->bytesAvailable() == 0);
        QVERIFY(socket->bytesToWrite() == 0);
        QCOMPARE(socket->canReadLine(), false);
        QCOMPARE(socket->flush(), false);
        QCOMPARE(socket->isValid(), canListen);
        QCOMPARE(socket->readBufferSize(), (qint64)0);
        QCOMPARE(socket->waitForConnected(0), canListen);
        QCOMPARE(socket->waitForReadyRead(0), false);

        QTRY_COMPARE(spyConnected.count(), canListen ? 1 : 0);
        QCOMPARE(spyDisconnected.count(), 0);

        // error signals
        QVERIFY(spyError.count() >= 0);
        if (canListen) {
            if (spyError.count() > 0)
                QCOMPARE(qVariantValue<QLocalSocket::LocalSocketError>(spyError.first()[0]),
                         QLocalSocket::SocketTimeoutError);
        } else {
            QCOMPARE(qVariantValue<QLocalSocket::LocalSocketError>(spyError.first()[0]),
                     QLocalSocket::ServerNotFoundError);
        }

        // Check first and last state
        QCOMPARE(qVariantValue<QLocalSocket::LocalSocketState>(spyStateChanged.first()[0]),
                 QLocalSocket::ConnectingState);
#if 0
        for (int j = 0; j < spyStateChanged.count(); ++j) {
            QLocalSocket::LocalSocketState s;
            s = qVariantValue<QLocalSocket::LocalSocketState>(spyStateChanged.at(j).at(0));
	    qDebug() << s;
        }
#endif
        if (canListen)
            QCOMPARE(qVariantValue<QLocalSocket::LocalSocketState>(spyStateChanged.last()[0]),
                     QLocalSocket::ConnectedState);
        QCOMPARE(spyStateChanged.count(), 2);
        QCOMPARE(spyReadyRead.count(), 0);

        bool timedOut = true;
        QCOMPARE(server.waitForNewConnection(3000, &timedOut), canListen);
        QVERIFY(!timedOut);
        QCOMPARE(server.hasPendingConnections(), canListen);
        QCOMPARE(server.isListening(), canListen);
        // NOTE: socket disconnecting is not tested here

        // server checks post connection
        if (canListen) {
            QCOMPARE(server.serverName(), name);
            QVERIFY(server.fullServerName().contains(name));
            QVERIFY(server.nextPendingConnection() != (QLocalSocket*)0);
            QTRY_COMPARE(server.hits.count(), i + 1);
            QCOMPARE(spyNewConnection.count(), i + 1);
            QVERIFY(server.errorString() == QString());
            QCOMPARE(server.serverError(), QAbstractSocket::UnknownSocketError);
        } else {
            QVERIFY(server.serverName().isEmpty());
            QVERIFY(server.fullServerName().isEmpty());
            QVERIFY(server.nextPendingConnection() == (QLocalSocket*)0);
            QCOMPARE(spyNewConnection.count(), 0);
            QCOMPARE(server.hits.count(), 0);
            QVERIFY(server.errorString() != QString());
            QCOMPARE(server.serverError(), QAbstractSocket::HostNotFoundError);
        }
    }
    qDeleteAll(sockets.begin(), sockets.end());

    server.close();

    QCOMPARE(server.hits.count(), (canListen ? connections : 0));
    QCOMPARE(spyNewConnection.count(), (canListen ? connections : 0));
}

void tst_QLocalSocket::sendData_data()
{
    listenAndConnect_data();
}

void tst_QLocalSocket::sendData()
{
    QFETCH(QString, name);
    QFETCH(bool, canListen);

    LocalServer server;
    QSignalSpy spy(&server, SIGNAL(newConnection()));

    QCOMPARE(server.listen(name), canListen);

    LocalSocket socket;
    QSignalSpy spyConnected(&socket, SIGNAL(connected()));
    QSignalSpy spyDisconnected(&socket, SIGNAL(disconnected()));
    QSignalSpy spyError(&socket, SIGNAL(error(QLocalSocket::LocalSocketError)));
    QSignalSpy spyStateChanged(&socket, SIGNAL(stateChanged(QLocalSocket::LocalSocketState)));
    QSignalSpy spyReadyRead(&socket, SIGNAL(readyRead()));

    // test creating a connection
    socket.connectToServer(name);
    bool timedOut = true;
    QCOMPARE(server.waitForNewConnection(3000, &timedOut), canListen);
#ifdef QT_LOCALSOCKET_TCP
    QTest::qWait(250);
#endif
    QVERIFY(!timedOut);
    QCOMPARE(spyConnected.count(), canListen ? 1 : 0);
    QCOMPARE(socket.state(), canListen ? QLocalSocket::ConnectedState : QLocalSocket::UnconnectedState);

    // test sending/receiving data
    if (server.hasPendingConnections()) {
        QString testLine = "test";
	for (int i = 0; i < 50000; ++i)
		testLine += "a";
        QLocalSocket *serverSocket = server.nextPendingConnection();
        QVERIFY(serverSocket);
        QCOMPARE(serverSocket->state(), QLocalSocket::ConnectedState);
        QTextStream out(serverSocket);
        QTextStream in(&socket);
        out << testLine << endl;
        bool wrote = serverSocket->waitForBytesWritten(3000);

        if (!socket.canReadLine())
            QVERIFY(socket.waitForReadyRead());

        QVERIFY(socket.bytesAvailable() >= 0);
        QCOMPARE(socket.bytesToWrite(), (qint64)0);
        QCOMPARE(socket.flush(), false);
        QCOMPARE(socket.isValid(), canListen);
        QCOMPARE(socket.readBufferSize(), (qint64)0);
        QCOMPARE(spyReadyRead.count(), 1);

        QVERIFY(testLine.startsWith(in.readLine()));
        QVERIFY(wrote || serverSocket->waitForBytesWritten(1000));
        QCOMPARE(serverSocket->errorString(), QString("Unknown error"));
        QCOMPARE(socket.errorString(), QString("Unknown error"));
    }

    socket.disconnectFromServer();
    QCOMPARE(spyConnected.count(), canListen ? 1 : 0);
    QCOMPARE(spyDisconnected.count(), canListen ? 1 : 0);
    QCOMPARE(spyError.count(), canListen ? 0 : 1);
    QCOMPARE(spyStateChanged.count(), canListen ? 4 : 2);
    QCOMPARE(spyReadyRead.count(), canListen ? 1 : 0);

    server.close();

    QCOMPARE(server.hits.count(), (canListen ? 1 : 0));
    QCOMPARE(spy.count(), (canListen ? 1 : 0));
}

// QLocalSocket/Server can take a name or path, check that it works as expected
void tst_QLocalSocket::fullPath()
{
    LocalServer server;
    QString name = "qlocalsocket_pathtest";
#if defined(QT_LOCALSOCKET_TCP)
    QString path = "QLocalServer";
#elif defined(Q_OS_WIN)
    QString path = "\\\\.\\pipe\\";
#else
    QString path = "/tmp";
#endif
    QString serverName = path + '/' + name;
    QVERIFY2(server.listen(serverName), server.errorString().toLatin1().constData());
    QCOMPARE(server.serverName(), serverName);
    QCOMPARE(server.fullServerName(), serverName);

    LocalSocket socket;
    socket.connectToServer(serverName);
    QCOMPARE(socket.serverName(), serverName);
    QCOMPARE(socket.fullServerName(), serverName);
    socket.disconnectFromServer();
#ifdef QT_LOCALSOCKET_TCP
    QTest::qWait(250);
#endif
    QCOMPARE(socket.serverName(), QString());
    QCOMPARE(socket.fullServerName(), QString());
}

void tst_QLocalSocket::hitMaximumConnections_data()
{
    QTest::addColumn<int>("max");
    QTest::newRow("none") << 0;
    QTest::newRow("1") << 1;
    QTest::newRow("3") << 3;
}

void tst_QLocalSocket::hitMaximumConnections()
{
    QFETCH(int, max);
    LocalServer server;
    QString name = "tst_localsocket";
    server.setMaxPendingConnections(max);
    QVERIFY2(server.listen(name), server.errorString().toLatin1().constData());
    int connections = server.maxPendingConnections() + 1;
    QList<QLocalSocket*> sockets;
    for (int i = 0; i < connections; ++i) {
        LocalSocket *socket = new LocalSocket;
        sockets.append(socket);
        socket->connectToServer(name);
    }
   bool timedOut = true;
   QVERIFY(server.waitForNewConnection(3000, &timedOut));
   QVERIFY(!timedOut);
   QVERIFY(server.hits.count() > 0);
   qDeleteAll(sockets.begin(), sockets.end());
}

// check that state and mode are kept
void tst_QLocalSocket::setSocketDescriptor()
{
    LocalSocket socket;
    quintptr minusOne = -1;
    socket.setSocketDescriptor(minusOne, QLocalSocket::ConnectingState, QIODevice::Append);
    QCOMPARE(socket.socketDescriptor(), minusOne);
    QCOMPARE(socket.state(), QLocalSocket::ConnectingState);
    QVERIFY((socket.openMode() & QIODevice::Append) != 0);
}

class Client : public QThread
{

public:
    void run()
    {
        QString testLine = "test";
        LocalSocket socket;
        QSignalSpy spyReadyRead(&socket, SIGNAL(readyRead()));
        int tries = 0;
        do {
            socket.connectToServer("qlocalsocket_threadtest");
            if (socket.error() != QLocalSocket::ServerNotFoundError
                && socket.error() != QLocalSocket::ConnectionRefusedError)
                break;
            QTest::qWait(100);
            ++tries;
        } while ((socket.error() == QLocalSocket::ServerNotFoundError
                  || socket.error() == QLocalSocket::ConnectionRefusedError)
		 && tries < 1000);
        if (tries == 0 && socket.state() != QLocalSocket::ConnectedState) {
            QVERIFY(socket.waitForConnected(3000));
            QVERIFY(socket.state() == QLocalSocket::ConnectedState);
        }

        // We should *not* have this signal yet!
        if (tries == 0)
            QCOMPARE(spyReadyRead.count(), 0);
        socket.waitForReadyRead();
        QCOMPARE(spyReadyRead.count(), 1);
        QTextStream in(&socket);
        QCOMPARE(in.readLine(), testLine);
        socket.close();
    }
};

class Server : public QThread
{

public:
    int clients;
    void run()
    {
        QString testLine = "test";
        LocalServer server;
        server.setMaxPendingConnections(10);
        QVERIFY2(server.listen("qlocalsocket_threadtest"),
                 server.errorString().toLatin1().constData());
        int done = clients;
        while (done > 0) {
            bool timedOut = true;
            QVERIFY(server.waitForNewConnection(3000, &timedOut));
            QVERIFY(!timedOut);
            QLocalSocket *serverSocket = server.nextPendingConnection();
            QVERIFY(serverSocket);
            QTextStream out(serverSocket);
            out << testLine << endl;
            QCOMPARE(serverSocket->state(), QLocalSocket::ConnectedState);
            QVERIFY2(serverSocket->waitForBytesWritten(), serverSocket->errorString().toLatin1().constData());
            QCOMPARE(serverSocket->errorString(), QString("Unknown error"));
            --done;
            delete serverSocket;
        }
        QCOMPARE(server.hits.count(), clients);
    }
};

void tst_QLocalSocket::threadedConnection_data()
{
    QTest::addColumn<int>("threads");
    QTest::newRow("1 client") << 1;
    QTest::newRow("2 clients") << 2;
#ifdef Q_OS_WINCE
    QTest::newRow("4 clients") << 4;
#endif
#ifndef Q_OS_WIN
    QTest::newRow("5 clients") << 5;
    QTest::newRow("10 clients") << 10;
#endif
#ifndef Q_OS_WINCE
    QTest::newRow("20 clients") << 20;
#endif
}

void tst_QLocalSocket::threadedConnection()
{
    QFETCH(int, threads);
    Server server;
    server.clients = threads;
    server.start();

    QList<Client*> clients;
    for (int i = 0; i < threads; ++i) {
        clients.append(new Client());
        clients.last()->start();
    }

    server.wait();
    while (!clients.isEmpty()) {
        QVERIFY(clients.first()->wait(30000));
        Client *client =clients.takeFirst();
	client->terminate();
	delete client;
    }
}

void tst_QLocalSocket::processConnection_data()
{
    QTest::addColumn<int>("processes");
    QTest::newRow("1 client") << 1;
#ifndef Q_OS_WIN
    QTest::newRow("2 clients") << 2;
    QTest::newRow("5 clients") << 5;
#endif
    QTest::newRow("30 clients") << 30;
}

/*!
    Create external processes that produce and consume.
 */
void tst_QLocalSocket::processConnection()
{
#if defined(QT_NO_PROCESS)
    QSKIP("Qt was compiled with QT_NO_PROCESS", SkipAll);
#else
    QFETCH(int, processes);
    QStringList serverArguments = QStringList() << SRCDIR "lackey/scripts/server.js" << QString::number(processes);
    QProcess producer;
    producer.setProcessChannelMode(QProcess::ForwardedChannels);
#ifdef Q_WS_QWS
    serverArguments << "-qws";
#endif
    QList<QProcess*> consumers;
    producer.start("lackey/lackey", serverArguments);
    QVERIFY(producer.waitForStarted(-1));
    QTest::qWait(2000);
    for (int i = 0; i < processes; ++i) {
       QStringList arguments = QStringList() << SRCDIR "lackey/scripts/client.js";
#ifdef Q_WS_QWS
       arguments << "-qws";
#endif
        QProcess *p = new QProcess;
        p->setProcessChannelMode(QProcess::ForwardedChannels);
        consumers.append(p);
        p->start("lackey/lackey", arguments);
    }

    while (!consumers.isEmpty()) {
        consumers.first()->waitForFinished(20000);
        QCOMPARE(consumers.first()->exitStatus(), QProcess::NormalExit);
        QCOMPARE(consumers.first()->exitCode(), 0);
        QProcess *consumer = consumers.takeFirst();
        consumer->terminate();
        delete consumer;
    }
    producer.waitForFinished(15000);
#endif
}

void tst_QLocalSocket::longPath()
{
#ifndef Q_OS_WIN
    QString name;
    for (int i = 0; i < 256; ++i)
        name += 'a';
    LocalServer server;
    QVERIFY(!server.listen(name));

    LocalSocket socket;
    socket.connectToServer(name);
    QCOMPARE(socket.state(), QLocalSocket::UnconnectedState);
#endif
}

void tst_QLocalSocket::waitForDisconnect()
{
    QString name = "tst_localsocket";
    LocalServer server;
    QVERIFY(server.listen(name));
    LocalSocket socket;
    socket.connectToServer(name);
    QVERIFY(socket.waitForConnected(3000));
    QVERIFY(server.waitForNewConnection(3000));
    QLocalSocket *serverSocket = server.nextPendingConnection();
    QVERIFY(serverSocket);
    socket.disconnectFromServer();
    QTime timer;
    timer.start();
    QVERIFY(serverSocket->waitForDisconnected(3000));
    QVERIFY(timer.elapsed() < 2000);
}

void tst_QLocalSocket::waitForDisconnectByServer()
{
    QString name = "tst_localsocket";
    LocalServer server;
    QVERIFY(server.listen(name));
    LocalSocket socket;
    QSignalSpy spy(&socket, SIGNAL(disconnected()));
    QVERIFY(spy.isValid());
    socket.connectToServer(name);
    QVERIFY(socket.waitForConnected(3000));
    QVERIFY(server.waitForNewConnection(3000));
    QLocalSocket *serverSocket = server.nextPendingConnection();
    QVERIFY(serverSocket);
    serverSocket->close();
    QVERIFY(serverSocket->state() == QLocalSocket::UnconnectedState);
    QVERIFY(socket.waitForDisconnected(3000));
    QCOMPARE(spy.count(), 1);
}

void tst_QLocalSocket::removeServer()
{
    // this is a hostile takeover, but recovering from a crash results in the same
    QLocalServer server, server2;
    QVERIFY(QLocalServer::removeServer("cleanuptest"));
    QVERIFY(server.listen("cleanuptest"));
#ifndef Q_OS_WIN
    // on Windows, there can be several sockets listening on the same pipe
    // on Unix, there can only be one socket instance
    QVERIFY(! server2.listen("cleanuptest"));
#endif
    QVERIFY(QLocalServer::removeServer("cleanuptest"));
    QVERIFY(server2.listen("cleanuptest"));
}

void tst_QLocalSocket::recycleServer()
{
    LocalServer server;
    QLocalSocket client;

    QVERIFY(server.listen("recycletest1"));
    client.connectToServer("recycletest1");
    QVERIFY(client.waitForConnected(201));
    QVERIFY(server.waitForNewConnection(201));
    QVERIFY(server.nextPendingConnection() != 0);

    server.close();
    client.disconnectFromServer();
    qApp->processEvents();

    QVERIFY(server.listen("recycletest2"));
    client.connectToServer("recycletest2");
    QVERIFY(client.waitForConnected(202));
    QVERIFY(server.waitForNewConnection(202));
    QVERIFY(server.nextPendingConnection() != 0);
}

void tst_QLocalSocket::debug()
{
    // Make sure this compiles
    qDebug() << QLocalSocket::ConnectionRefusedError << QLocalSocket::UnconnectedState;
}

QTEST_MAIN(tst_QLocalSocket)
#include "tst_qlocalsocket.moc"

