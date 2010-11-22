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

#ifndef QDIRECTFBSCREEN_H
#define QDIRECTFBSCREEN_H

#include <QtGui/qscreen_qws.h>
#include <directfb.h>
#include <directfb_version.h>

QT_BEGIN_HEADER

QT_MODULE(Gui)

#define Q_DIRECTFB_VERSION ((DIRECTFB_MAJOR_VERSION << 16) | (DIRECTFB_MINOR_VERION << 8) | DIRECTFB_MICRO_VERSION)

#define DIRECTFB_DECLARE_OPERATORS_FOR_FLAGS(F)                         \
    static inline F operator~(F f) { return F(~int(f)); } \
    static inline F operator&(F left, F right) { return F(int(left) & int(right)); } \
    static inline F operator|(F left, F right) { return F(int(left) | int(right)); } \
    static inline F &operator|=(F &left, F right) { left = (left | right); return left; } \
    static inline F &operator&=(F &left, F right) { left = (left & right); return left; }

DIRECTFB_DECLARE_OPERATORS_FOR_FLAGS(DFBInputDeviceCapabilities);
DIRECTFB_DECLARE_OPERATORS_FOR_FLAGS(DFBWindowDescriptionFlags);
DIRECTFB_DECLARE_OPERATORS_FOR_FLAGS(DFBSurfaceDescriptionFlags);
DIRECTFB_DECLARE_OPERATORS_FOR_FLAGS(DFBSurfaceCapabilities);
DIRECTFB_DECLARE_OPERATORS_FOR_FLAGS(DFBSurfaceLockFlags);
DIRECTFB_DECLARE_OPERATORS_FOR_FLAGS(DFBSurfaceBlittingFlags);
DIRECTFB_DECLARE_OPERATORS_FOR_FLAGS(DFBSurfaceDrawingFlags);
DIRECTFB_DECLARE_OPERATORS_FOR_FLAGS(DFBSurfaceFlipFlags);

class QDirectFBScreenPrivate;
class Q_GUI_EXPORT QDirectFBScreen : public QScreen
{
public:
    QDirectFBScreen(int display_id);
    ~QDirectFBScreen();

    enum DirectFBFlag {
        NoFlags = 0x00,
        VideoOnly = 0x01,
        SystemOnly = 0x02,
        BoundingRectFlip = 0x04
    };

    Q_DECLARE_FLAGS(DirectFBFlags, DirectFBFlag);

    DirectFBFlags directFBFlags() const;

    bool connect(const QString &displaySpec);
    void disconnect();
    bool initDevice();
    void shutdownDevice();

    void exposeRegion(QRegion r, int changing);
    void scroll(const QRegion &region, const QPoint &offset);
    void solidFill(const QColor &color, const QRegion &region);

    void setMode(int width, int height, int depth);
    void blank(bool on);

    QWSWindowSurface *createSurface(QWidget *widget) const;
    QWSWindowSurface *createSurface(const QString &key) const;

    static inline QDirectFBScreen *instance() {
        QScreen *inst = QScreen::instance();
        Q_ASSERT(!inst || inst->classId() == QScreen::DirectFBClass);
        return static_cast<QDirectFBScreen*>(inst);
    }

    IDirectFB *dfb();
    IDirectFBSurface *dfbSurface();
#ifndef QT_NO_DIRECTFB_LAYER
    IDirectFBDisplayLayer *dfbDisplayLayer();
#endif

    // Track surface creation/release so we can release all on exit
    enum SurfaceCreationOption {
        DontTrackSurface = 0,
        TrackSurface = 1
    };
    Q_DECLARE_FLAGS(SurfaceCreationOptions, SurfaceCreationOption);
    IDirectFBSurface *createDFBSurface(const QImage &image,
                                       SurfaceCreationOptions options);
    IDirectFBSurface *createDFBSurface(const QSize &size,
                                       QImage::Format format,
                                       SurfaceCreationOptions options);
    IDirectFBSurface *copyDFBSurface(IDirectFBSurface *src,
                                     QImage::Format format,
                                     SurfaceCreationOptions options);
    IDirectFBSurface *copyToDFBSurface(const QImage &image,
                                       QImage::Format format,
                                       SurfaceCreationOptions options);
    void flipSurface(IDirectFBSurface *surface, DFBSurfaceFlipFlags flipFlags,
                     const QRegion &region, const QPoint &offset);
    void releaseDFBSurface(IDirectFBSurface *surface);
    void erase(const QRegion &region);

    static int depth(DFBSurfacePixelFormat format);

    static DFBSurfacePixelFormat getSurfacePixelFormat(QImage::Format format);
    static DFBSurfaceDescription getSurfaceDescription(const QImage &image);
    static DFBSurfaceDescription getSurfaceDescription(const uint *buffer,
                                                       int length);
    static QImage::Format getImageFormat(IDirectFBSurface *surface);
    static bool initSurfaceDescriptionPixelFormat(DFBSurfaceDescription *description, QImage::Format format);
    static inline bool isPremultiplied(QImage::Format format);
    static inline bool hasAlpha(DFBSurfacePixelFormat format);
    static inline bool hasAlpha(IDirectFBSurface *surface);
    QImage::Format alphaPixmapFormat() const;

#ifndef QT_NO_DIRECTFB_PALETTE
    static void setSurfaceColorTable(IDirectFBSurface *surface,
                                     const QImage &image);
#endif

    static uchar *lockSurface(IDirectFBSurface *surface, uint flags, int *bpl = 0);
private:
    IDirectFBSurface *createDFBSurface(DFBSurfaceDescription desc,
                                       SurfaceCreationOptions options);
    QDirectFBScreenPrivate *d_ptr;
    friend class SurfaceCache;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QDirectFBScreen::SurfaceCreationOptions);
Q_DECLARE_OPERATORS_FOR_FLAGS(QDirectFBScreen::DirectFBFlags);

inline bool QDirectFBScreen::isPremultiplied(QImage::Format format)
{
    switch (format) {
    case QImage::Format_ARGB32_Premultiplied:
    case QImage::Format_ARGB8565_Premultiplied:
    case QImage::Format_ARGB6666_Premultiplied:
    case QImage::Format_ARGB8555_Premultiplied:
    case QImage::Format_ARGB4444_Premultiplied:
        return true;
    default:
        break;
    }
    return false;
}

inline bool QDirectFBScreen::hasAlpha(DFBSurfacePixelFormat format)
{
    switch (format) {
    case DSPF_ARGB1555:
    case DSPF_ARGB:
    case DSPF_LUT8:
    case DSPF_AiRGB:
    case DSPF_A1:
    case DSPF_ARGB2554:
    case DSPF_ARGB4444:
#if (Q_DIRECTFB_VERSION >= 0x000923)
    case DSPF_AYUV:
#endif
#if (Q_DIRECTFB_VERSION >= 0x010000)
    case DSPF_A4:
    case DSPF_ARGB1666:
    case DSPF_ARGB6666:
    case DSPF_LUT2:
#endif
        return true;
    default:
        return false;
    }
}

inline bool QDirectFBScreen::hasAlpha(IDirectFBSurface *surface)
{
    Q_ASSERT(surface);
    DFBSurfacePixelFormat format;
    surface->GetPixelFormat(surface, &format);
    return QDirectFBScreen::hasAlpha(format);
}

QT_END_HEADER

#endif // QDIRECTFBSCREEN_H
