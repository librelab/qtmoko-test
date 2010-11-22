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

#include "qhttpnetworkrequest_p.h"

#ifndef QT_NO_HTTP

QT_BEGIN_NAMESPACE

QHttpNetworkRequestPrivate::QHttpNetworkRequestPrivate(QHttpNetworkRequest::Operation op,
        QHttpNetworkRequest::Priority pri, const QUrl &newUrl)
    : QHttpNetworkHeaderPrivate(newUrl), operation(op), priority(pri), data(0),
      autoDecompress(false)
{
}

QHttpNetworkRequestPrivate::QHttpNetworkRequestPrivate(const QHttpNetworkRequestPrivate &other)
    : QHttpNetworkHeaderPrivate(other)
{
    operation = other.operation;
    priority = other.priority;
    data = other.data;
    autoDecompress = other.autoDecompress;
}

QHttpNetworkRequestPrivate::~QHttpNetworkRequestPrivate()
{
}

bool QHttpNetworkRequestPrivate::operator==(const QHttpNetworkRequestPrivate &other) const
{
    return QHttpNetworkHeaderPrivate::operator==(other)
        && (operation == other.operation)
        && (data == other.data);
}

QByteArray QHttpNetworkRequestPrivate::methodName() const
{
    QByteArray ba;
    switch (operation) {
    case QHttpNetworkRequest::Options:
        ba += "OPTIONS";
        break;
    case QHttpNetworkRequest::Get:
        ba += "GET";
        break;
    case QHttpNetworkRequest::Head:
        ba += "HEAD";
        break;
    case QHttpNetworkRequest::Post:
        ba += "POST";
        break;
    case QHttpNetworkRequest::Put:
        ba += "PUT";
        break;
    case QHttpNetworkRequest::Delete:
        ba += "DELETE";
        break;
    case QHttpNetworkRequest::Trace:
        ba += "TRACE";
        break;
    case QHttpNetworkRequest::Connect:
        ba += "CONNECT";
        break;
    default:
        break;
    }
    return ba;
}

QByteArray QHttpNetworkRequestPrivate::uri(bool throughProxy) const
{
    QUrl::FormattingOptions format(QUrl::RemoveFragment);

    // for POST, query data is send as content
    if (operation == QHttpNetworkRequest::Post && !data)
        format |= QUrl::RemoveQuery;
    // for requests through proxy, the Request-URI contains full url
    if (throughProxy)
        format |= QUrl::RemoveUserInfo;
    else
        format |= QUrl::RemoveScheme | QUrl::RemoveAuthority;
    QByteArray uri = url.toEncoded(format);
    if (uri.isEmpty() || (throughProxy && url.path().isEmpty()))
        uri += '/';
    return uri;
}

QByteArray QHttpNetworkRequestPrivate::header(const QHttpNetworkRequest &request, bool throughProxy)
{
    QByteArray ba = request.d->methodName();
    QByteArray uri = request.d->uri(throughProxy);
    ba += " " + uri;

    QString majorVersion = QString::number(request.majorVersion());
    QString minorVersion = QString::number(request.minorVersion());
    ba += " HTTP/" + majorVersion.toLatin1() + "." + minorVersion.toLatin1() + "\r\n";

    QList<QPair<QByteArray, QByteArray> > fields = request.header();
    QList<QPair<QByteArray, QByteArray> >::const_iterator it = fields.constBegin();
    for (; it != fields.constEnd(); ++it)
        ba += it->first + ": " + it->second + "\r\n";
    if (request.d->operation == QHttpNetworkRequest::Post) {
        // add content type, if not set in the request
        if (request.headerField("content-type").isEmpty())
            ba += "Content-Type: application/x-www-form-urlencoded\r\n";
        if (!request.d->data && request.d->url.hasQuery()) {
            QByteArray query = request.d->url.encodedQuery();
            ba += "Content-Length: "+ QByteArray::number(query.size()) + "\r\n";
            ba += "\r\n";
            ba += query;
        } else {
            ba += "\r\n";
        }
    } else {
        ba += "\r\n";
    }
     return ba;
}


// QHttpNetworkRequest

QHttpNetworkRequest::QHttpNetworkRequest(const QUrl &url, Operation operation, Priority priority)
    : d(new QHttpNetworkRequestPrivate(operation, priority, url))
{
}

QHttpNetworkRequest::QHttpNetworkRequest(const QHttpNetworkRequest &other)
    : QHttpNetworkHeader(other), d(other.d)
{
}

QHttpNetworkRequest::~QHttpNetworkRequest()
{
}

QUrl QHttpNetworkRequest::url() const
{
    return d->url;
}
void QHttpNetworkRequest::setUrl(const QUrl &url)
{
    d->url = url;
}

qint64 QHttpNetworkRequest::contentLength() const
{
    return d->contentLength();
}

void QHttpNetworkRequest::setContentLength(qint64 length)
{
    d->setContentLength(length);
}

QList<QPair<QByteArray, QByteArray> > QHttpNetworkRequest::header() const
{
    return d->fields;
}

QByteArray QHttpNetworkRequest::headerField(const QByteArray &name, const QByteArray &defaultValue) const
{
    return d->headerField(name, defaultValue);
}

void QHttpNetworkRequest::setHeaderField(const QByteArray &name, const QByteArray &data)
{
    d->setHeaderField(name, data);
}

QHttpNetworkRequest &QHttpNetworkRequest::operator=(const QHttpNetworkRequest &other)
{
    d = other.d;
    return *this;
}

bool QHttpNetworkRequest::operator==(const QHttpNetworkRequest &other) const
{
    return d->operator==(*other.d);
}

QHttpNetworkRequest::Operation QHttpNetworkRequest::operation() const
{
    return d->operation;
}

void QHttpNetworkRequest::setOperation(Operation operation)
{
    d->operation = operation;
}

QHttpNetworkRequest::Priority QHttpNetworkRequest::priority() const
{
    return d->priority;
}

void QHttpNetworkRequest::setPriority(Priority priority)
{
    d->priority = priority;
}

QIODevice *QHttpNetworkRequest::data() const
{
    return d->data;
}

void QHttpNetworkRequest::setData(QIODevice *data)
{
    d->data = data;
}

int QHttpNetworkRequest::majorVersion() const
{
    return 1;
}

int QHttpNetworkRequest::minorVersion() const
{
    return 1;
}


QT_END_NAMESPACE

#endif

