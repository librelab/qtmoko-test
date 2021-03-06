/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
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

#ifndef QAHIGLSCREEN_H
#define QAHIGLSCREEN_H

#include <QGLScreen>
#include <QWSServer>

QT_BEGIN_NAMESPACE
class QAhiGLScreenPrivate;
QT_END_NAMESPACE

//! [0]
class QAhiGLScreen : public QGLScreen
{
public:
    QAhiGLScreen(int displayId);
    virtual ~QAhiGLScreen();

    bool initDevice();
    bool connect(const QString &displaySpec);
    void disconnect();
    void shutdownDevice();

    void setMode(int width, int height, int depth);
    void blank(bool on);

    void exposeRegion(QRegion r, int changing);

    QWSWindowSurface* createSurface(QWidget *widget) const;
    QWSWindowSurface* createSurface(const QString &key) const;

    bool hasOpenGL();

private:
    void invalidateTexture(int windowIndex);
    void redrawScreen();
    void drawWindow(QWSWindow *win, qreal progress);
    void drawQuad(const QRect &textureGeometry,
                  const QRect &subGeometry,
                  const QRect &screenGeometry);
    void drawQuadWavyFlag(const QRect &textureGeometry,
                          const QRect &subTexGeometry,
                          const QRect &screenGeometry,
                          float progress);

    QAhiGLScreenPrivate *d_ptr;
    friend class QAhiGLScreenPrivate;
};
//! [0]

#endif // QAHIGLSCREEN_H
