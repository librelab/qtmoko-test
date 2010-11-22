/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtNetwork module of the Qt Toolkit.
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

#include "qlocalsocket.h"
#include "qlocalsocket_p.h"

#include <private/qthread_p.h>
#include <qcoreapplication.h>
#include <qdebug.h>

QT_BEGIN_NAMESPACE

#define NOTIFYTIMEOUT 100

void QLocalSocketPrivate::init()
{
    Q_Q(QLocalSocket);
    QObject::connect(&dataNotifier, SIGNAL(timeout()), q, SLOT(_q_notified()));
    overlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
}

void QLocalSocketPrivate::setErrorString(const QString &function)
{
    Q_Q(QLocalSocket);
    BOOL windowsError = GetLastError();
    QLocalSocket::LocalSocketState currentState = state;

    // If the connectToServer fails due to WaitNamedPipe() time-out, assume ConnectionError  
    if (state == QLocalSocket::ConnectingState && windowsError == ERROR_SEM_TIMEOUT)
        windowsError = ERROR_NO_DATA;

    switch (windowsError) {
    case ERROR_PIPE_NOT_CONNECTED:
    case ERROR_BROKEN_PIPE:
    case ERROR_NO_DATA:
        error = QLocalSocket::ConnectionError;
        errorString = QLocalSocket::tr("%1: Connection error").arg(function);
        state = QLocalSocket::UnconnectedState;
        break;
    case ERROR_FILE_NOT_FOUND:
        error = QLocalSocket::ServerNotFoundError;
        errorString = QLocalSocket::tr("%1: Invalid name").arg(function);
        state = QLocalSocket::UnconnectedState;
        break;
    default:
        error = QLocalSocket::UnknownSocketError;
        errorString = QLocalSocket::tr("%1: Unknown error %2").arg(function).arg(windowsError);
#if defined QLOCALSOCKET_DEBUG
        qWarning() << "QLocalSocket error not handled:" << errorString;
#endif
        state = QLocalSocket::UnconnectedState;
    }

    if (currentState != state) {
        q->emit stateChanged(state);
        if (state == QLocalSocket::UnconnectedState)
            q->emit disconnected();
    }
    emit q->error(error);
}

QLocalSocketPrivate::QLocalSocketPrivate() : QIODevicePrivate(),
       handle(INVALID_HANDLE_VALUE),
       pipeWriter(0),
       readBufferMaxSize(0),
       error(QLocalSocket::UnknownSocketError),
       readyReadEmitted(false),
       pipeClosed(false),
       state(QLocalSocket::UnconnectedState)
{
}

void QLocalSocket::connectToServer(const QString &name, OpenMode openMode)
{
    Q_D(QLocalSocket);
    if (state() == ConnectedState || state() == ConnectingState)
        return;

    d->error = QLocalSocket::UnknownSocketError;
    d->errorString = QString();
    d->state = ConnectingState;
    emit stateChanged(d->state);
    if (name.isEmpty()) {
        d->error = QLocalSocket::ServerNotFoundError;
        setErrorString(QLocalSocket::tr("%1: Invalid name").arg(QLatin1String("QLocalSocket::connectToServer")));
        d->state = UnconnectedState;
        emit error(d->error);
        emit stateChanged(d->state);
        return;
    }

    QString pipePath = QLatin1String("\\\\.\\pipe\\");
    if (name.startsWith(pipePath))
        d->fullServerName = name;
    else
        d->fullServerName = pipePath + name;
    // Try to open a named pipe
    HANDLE localSocket;
    forever {
        DWORD permissions = (openMode & QIODevice::ReadOnly) ? GENERIC_READ : 0;
        permissions |= (openMode & QIODevice::WriteOnly) ? GENERIC_WRITE : 0;
        QT_WA({
        localSocket = CreateFileW(
                       (TCHAR*)d->fullServerName.utf16(),   // pipe name
                       permissions,
                       0,              // no sharing
                       NULL,           // default security attributes
                       OPEN_EXISTING,  // opens existing pipe
                       FILE_FLAG_OVERLAPPED,
                       NULL);          // no template file
        }, {
        localSocket = CreateFileA(
                       d->fullServerName.toLocal8Bit().constData(), // pipe name
                       permissions,
                       0,              // no sharing
                       NULL,           // default security attributes
                       OPEN_EXISTING,  // opens existing pipe
                       FILE_FLAG_OVERLAPPED,
                       NULL);          // no template file
        });
        if (localSocket != INVALID_HANDLE_VALUE)
            break;
        DWORD error = GetLastError();
        // It is really an error only if it is not ERROR_PIPE_BUSY
        if (ERROR_PIPE_BUSY != error) {
            break;
        }

        // All pipe instances are busy, so wait until connected or up to 5 seconds.
        QT_WA({
            if (!WaitNamedPipeW((TCHAR*)d->fullServerName.utf16(), 5000))
                break;
        }, {
            if (!WaitNamedPipeA(d->fullServerName.toLocal8Bit().constData(), 5000))
                break;
        });
    }

    if (localSocket == INVALID_HANDLE_VALUE) {
        d->setErrorString(QLatin1String("QLocalSocket::connectToServer"));
        d->fullServerName = QString();
        return;
    }

    // we have a valid handle
    d->serverName = name;
    if (setSocketDescriptor((quintptr)localSocket), openMode) {
        d->handle = localSocket;
        emit connected();
    }
}

// This is reading from the buffer
qint64 QLocalSocket::readData(char *data, qint64 maxSize)
{
    Q_D(QLocalSocket);
    if (d->readBuffer.isEmpty()) {
        if (!d->readFromSocket()) {
            if (d->pipeClosed)
                return -1;
            return 0;
        }
    }

    if (!d->dataNotifier.isActive() && d->threadData->eventDispatcher)
        d->dataNotifier.start(NOTIFYTIMEOUT);

    if (d->readBuffer.isEmpty())
        return qint64(0);

    // If readFromSocket() read data, copy it to its destination.
    if (maxSize == 1) {
        *data = d->readBuffer.getChar();
        return 1;
    }

    qint64 bytesToRead = qMin(qint64(d->readBuffer.size()), maxSize);
    qint64 readSoFar = 0;
    while (readSoFar < bytesToRead) {
        const char *ptr = d->readBuffer.readPointer();
        int bytesToReadFromThisBlock = qMin(int(bytesToRead - readSoFar),
                                            d->readBuffer.nextDataBlockSize());
        memcpy(data + readSoFar, ptr, bytesToReadFromThisBlock);
        readSoFar += bytesToReadFromThisBlock;
        d->readBuffer.free(bytesToReadFromThisBlock);
    }
    return readSoFar;
}

/*!
    \internal
    read from the socket
 */
qint64 QLocalSocketPrivate::readData(char *data, qint64 maxSize)
{
    DWORD bytesRead = 0;
    overlapped.Offset = 0;
    overlapped.OffsetHigh = 0;
    bool success = ReadFile(handle, data, maxSize, &bytesRead, &overlapped);
    if (!success && GetLastError() == ERROR_IO_PENDING)
        if (GetOverlappedResult(handle, &overlapped, &bytesRead, TRUE))
            success = true;
    if (!success) {
        setErrorString(QLatin1String("QLocalSocket::readData"));
        return 0;
    }
    return bytesRead;
}

/*!
    \internal
    Reads data from the socket into the readbuffer
 */
bool QLocalSocketPrivate::readFromSocket()
{
    qint64 bytesToRead = bytesAvailable();
    if (bytesToRead == 0)
        return false;

    if (readBufferMaxSize && bytesToRead
                     > (readBufferMaxSize - readBuffer.size()))
        bytesToRead = readBufferMaxSize - readBuffer.size();

    char *ptr = readBuffer.reserve(bytesToRead);
    qint64 readBytes = readData(ptr, bytesToRead);
    if (readBytes == 0) {
        readBuffer.chop(bytesToRead);
        return false;
    }
    readyReadEmitted = false;
    readBuffer.chop(int(bytesToRead - (readBytes < 0 ? qint64(0) : readBytes)));
    return true;
}

qint64 QLocalSocket::writeData(const char *data, qint64 maxSize)
{
    Q_D(QLocalSocket);
    if (!d->pipeWriter) {
        d->pipeWriter = new QWindowsPipeWriter(d->handle, this);
        d->pipeWriter->start();
        connect(d->pipeWriter, SIGNAL(canWrite()), this, SLOT(_q_canWrite()));
    }
    return d->pipeWriter->write(data, maxSize);
}

void QLocalSocket::abort()
{
    close();
}

/*!
    The number of bytes available from the pipe
  */
qint64 QLocalSocketPrivate::bytesAvailable()
{
    Q_Q(QLocalSocket);
    if (q->state() != QLocalSocket::ConnectedState)
        return 0;
    DWORD bytes;
    if (PeekNamedPipe(handle, NULL, 0, NULL, &bytes, NULL)) {
        return bytes;
    } else {
        if (!pipeClosed) {
            pipeClosed = true;
            QTimer::singleShot(0, q, SLOT(_q_pipeClosed()));
        }
    }
    return 0;
}

void QLocalSocketPrivate::_q_pipeClosed()
{
    Q_Q(QLocalSocket);
    q->close();
}

qint64 QLocalSocket::bytesAvailable() const
{
    Q_D(const QLocalSocket);
    qint64 available = QIODevice::bytesAvailable();
    available += (qint64) d->readBuffer.size();
    return available;
}

qint64 QLocalSocket::bytesToWrite() const
{
    Q_D(const QLocalSocket);
    return (d->pipeWriter) ? d->pipeWriter->bytesToWrite() : 0;
}

bool QLocalSocket::canReadLine() const
{
    Q_D(const QLocalSocket);
    if (state() != ConnectedState)
        return false;
    return (d->readBuffer.indexOf('\n') != -1 || QIODevice::canReadLine());
}

void QLocalSocket::close()
{
    Q_D(QLocalSocket);
    if (state() == UnconnectedState)
        return;

    QIODevice::close();
    d->state = ClosingState;
    emit stateChanged(d->state);
    d->readyReadEmitted = false;
    emit readChannelFinished();
    d->serverName = QString();
    d->fullServerName = QString();

    if (state() != UnconnectedState && bytesToWrite() > 0) {
        disconnectFromServer();
        return;
    }
    d->pipeClosed = false;
    DisconnectNamedPipe(d->handle);
    CloseHandle(d->handle);
    d->handle = INVALID_HANDLE_VALUE;
    d->state = UnconnectedState;
    emit stateChanged(d->state);
    emit disconnected();
    if (d->pipeWriter) {
        delete d->pipeWriter;
        d->pipeWriter = 0;
    }
    d->dataNotifier.stop();
}

bool QLocalSocket::flush()
{
    Q_D(QLocalSocket);
    if (d->pipeWriter)
        return d->pipeWriter->waitForWrite(0);
    return false;
}

void QLocalSocket::disconnectFromServer()
{
    Q_D(QLocalSocket);
    flush();
    if (d->pipeWriter && d->pipeWriter->bytesToWrite() != 0) {
        d->state = QLocalSocket::ClosingState;
        emit stateChanged(d->state);
    } else {
        close();
    }
}

QLocalSocket::LocalSocketError QLocalSocket::error() const
{
    Q_D(const QLocalSocket);
    return d->error;
}

bool QLocalSocket::setSocketDescriptor(quintptr socketDescriptor,
              LocalSocketState socketState, OpenMode openMode)
{
    Q_D(QLocalSocket);
    d->readBuffer.clear();
    QIODevice::open(openMode);
    d->handle = (int*)socketDescriptor;
    d->state = socketState;
    emit stateChanged(d->state);
    if (d->threadData->eventDispatcher)
        d->dataNotifier.start(NOTIFYTIMEOUT);
    return true;
}

void QLocalSocketPrivate::_q_canWrite()
{
    Q_Q(QLocalSocket);
    if (state == QLocalSocket::ClosingState)
        q->close();
}

void QLocalSocketPrivate::_q_notified()
{
    Q_Q(QLocalSocket);
    if (0 != bytesAvailable()) {
        if (readBufferMaxSize == 0 || readBuffer.size() < readBufferMaxSize) {
            if (!readFromSocket()) {
                return;
            }
            // wait until buffer is cleared before starting again
            if (readBufferMaxSize && readBuffer.size() == readBufferMaxSize) {
                dataNotifier.stop();
            }
        }
        if (!readyReadEmitted) {
            readyReadEmitted = true;
            q->emit readyRead();
        }
    }
}

quintptr QLocalSocket::socketDescriptor() const
{
    Q_D(const QLocalSocket);
    return (quintptr)d->handle;
}

qint64 QLocalSocket::readBufferSize() const
{
    Q_D(const QLocalSocket);
    return d->readBufferMaxSize;
}

void QLocalSocket::setReadBufferSize(qint64 size)
{
    Q_D(QLocalSocket);
    d->readBufferMaxSize = size;
}

bool QLocalSocket::waitForConnected(int msecs)
{
    Q_UNUSED(msecs);
    return (state() == ConnectedState);
}

bool QLocalSocket::waitForDisconnected(int msecs)
{
    Q_D(QLocalSocket);
    if (state() == UnconnectedState)
        return false;
    QIncrementalSleepTimer timer(msecs);
    forever {
        d->_q_notified();
	if (d->pipeClosed)
	    close();
        if (state() == UnconnectedState)
            return true;
        Sleep(timer.nextSleepTime());
        if (timer.hasTimedOut())
            break;
    }

    return false;
}

bool QLocalSocket::isValid() const
{
    Q_D(const QLocalSocket);
    return (d->handle != INVALID_HANDLE_VALUE);
}

bool QLocalSocket::waitForReadyRead(int msecs)
{
    Q_D(QLocalSocket);
    QIncrementalSleepTimer timer(msecs);
    forever {
        d->_q_notified();
        if (bytesAvailable() > 0) {
            if (!d->readyReadEmitted) {
                d->readyReadEmitted = true;
                emit readyRead();
            }
            return true;
        }

        Sleep(timer.nextSleepTime());
        if (timer.hasTimedOut())
            break;
    }

    return false;
}

bool QLocalSocket::waitForBytesWritten(int msecs)
{
    Q_D(const QLocalSocket);
    if (!d->pipeWriter)
        return false;

    QIncrementalSleepTimer timer(msecs);
    forever {
        if (d->pipeWriter->hadWritten())
            return true;

        if (d->pipeWriter->bytesToWrite() == 0)
            return false;

        // Wait for the pipe writer to acknowledge that it has
        // written. This will succeed if either the pipe writer has
        // already written the data, or if it manages to write data
        // within the given timeout.
        if (d->pipeWriter->waitForWrite(0))
            return true;

        Sleep(timer.nextSleepTime());
        if (timer.hasTimedOut())
            break;
    }

    return false;
}

QT_END_NAMESPACE
