/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtOpenGL module of the Qt Toolkit.
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

#ifndef QGRAPHICSCONTEXT_OPENGL2_P_H
#define QGRAPHICSCONTEXT_OPENGL2_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <private/qpaintengineex_p.h>

class QGL2PaintEngineExPrivate;


class QOpenGLPaintEngineState : public QPainterState
{
public:
    QOpenGLPaintEngineState(QOpenGLPaintEngineState &other);
    QOpenGLPaintEngineState();
    ~QOpenGLPaintEngineState();

    QRegion clipRegion;
    bool hasClipping;
    QRect fastClip;
};


class QGL2PaintEngineEx : public QPaintEngineEx
{
    Q_DECLARE_PRIVATE(QGL2PaintEngineEx)
public:
    QGL2PaintEngineEx();
    ~QGL2PaintEngineEx();

    bool begin(QPaintDevice *device);
    bool end();

    virtual void fill(const QVectorPath &path, const QBrush &brush);
    virtual void stroke(const QVectorPath &path, const QPen &pen);
    virtual void clip(const QVectorPath &path, Qt::ClipOperation op);

    virtual void clipEnabledChanged();
    virtual void penChanged();
    virtual void brushChanged();
    virtual void brushOriginChanged();
    virtual void opacityChanged();
    virtual void compositionModeChanged();
    virtual void renderHintsChanged();
    virtual void transformChanged();


    virtual void drawPixmap(const QRectF &r, const QPixmap &pm, const QRectF &sr);

    virtual void drawImage(const QRectF &r, const QImage &pm, const QRectF &sr,
                           Qt::ImageConversionFlags flags = Qt::AutoColor);
    virtual void drawTextItem(const QPointF &p, const QTextItem &textItem);
    void drawCachedGlyphs(const QPointF &p, const QTextItemInt &ti);

    Type type() const { return OpenGL; }


    // State stuff is just for clipping and ripped off from QGLPaintEngine
    void setState(QPainterState *s);
    QPainterState *createState(QPainterState *orig) const;
    inline QOpenGLPaintEngineState *state() {
        return static_cast<QOpenGLPaintEngineState *>(QPaintEngineEx::state());
    }
    inline const QOpenGLPaintEngineState *state() const {
        return static_cast<const QOpenGLPaintEngineState *>(QPaintEngineEx::state());
    }
    void updateClipRegion(const QRegion &clipRegion, Qt::ClipOperation op);

private:
    Q_DISABLE_COPY(QGL2PaintEngineEx)
};



#endif
