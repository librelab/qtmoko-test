/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the plugins of the Qt Toolkit.
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

#ifndef QDIRECTFBPIXMAP_H
#define QDIRECTFBPIXMAP_H

#include <QtGui/private/qpixmapdata_p.h>
#include <QtGui/private/qpaintengine_raster_p.h>
#include "qdirectfbpaintdevice.h"
#include <directfb.h>

QT_BEGIN_HEADER

QT_MODULE(Gui)

class QDirectFBPaintEngine;

class QDirectFBPixmapData : public QPixmapData, public QDirectFBPaintDevice
{
public:
    QDirectFBPixmapData(QDirectFBScreen *screen, PixelType pixelType);
    ~QDirectFBPixmapData();

    // Re-implemented from QPixmapData:
    void resize(int width, int height);
    void fromImage(const QImage &image, Qt::ImageConversionFlags flags);
    void copy(const QPixmapData *data, const QRect &rect);
    void fill(const QColor &color);
    inline bool hasAlphaChannel() const { return alpha; }
    QPixmap transformed(const QTransform &matrix,
                        Qt::TransformationMode mode) const;
    QImage toImage() const;
    QPaintEngine* paintEngine() const;
    virtual QImage *buffer();
    QImage *buffer(DFBSurfaceLockFlags lockFlags);

    // Pure virtual in QPixmapData, so re-implement here and delegate to QDirectFBPaintDevice
    int metric(QPaintDevice::PaintDeviceMetric m) const {return QDirectFBPaintDevice::metric(m);}
    inline QImage::Format pixelFormat() const { return format; }
    static bool hasAlphaChannel(const QImage &img);
private:
    void invalidate();
    QImage::Format format;
    bool alpha;
};

QT_END_HEADER

#endif // QDIRECTFBPIXMAP_H
