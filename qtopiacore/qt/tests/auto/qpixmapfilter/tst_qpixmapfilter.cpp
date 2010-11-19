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
#include <qpixmap.h>
#include <private/qpixmapfilter_p.h>
#include <qpainter.h>

//TESTED_CLASS=
//TESTED_FILES=

class tst_QPixmapFilter : public QObject
{
    Q_OBJECT

public:
    tst_QPixmapFilter();
    virtual ~tst_QPixmapFilter();


public slots:
    void init();
    void cleanup();

private slots:
    void colorizeSetColor();
    void colorizeProcess();
    void colorizeDraw();
    void colorizeDrawSubRect();
    void colorizeProcessSubRect();
    void convolutionBoundingRectFor();
    void convolutionDrawSubRect();
    void dropShadowBoundingRectFor();

    void testDefaultImplementations();
};

class CustomFilter : public QPixmapFilter
{
public:
    enum { Type = QPixmapFilter::UserFilter + 1 };

    CustomFilter() : QPixmapFilter((QPixmapFilter::FilterType) Type, 0) { };

    void draw(QPainter *p, const QPointF &pt, const QPixmap &src, const QRectF &srcRect = QRectF()) const {
        p->drawPixmap(QRectF(pt, srcRect.size()), src, srcRect);
    }
};

tst_QPixmapFilter::tst_QPixmapFilter()
{
}

tst_QPixmapFilter::~tst_QPixmapFilter()
{
}

void tst_QPixmapFilter::init()
{
}

void tst_QPixmapFilter::cleanup()
{
}

void tst_QPixmapFilter::testDefaultImplementations()
{
    CustomFilter filter;
    QCOMPARE(filter.type(), (QPixmapFilter::FilterType) CustomFilter::Type);

    QCOMPARE(filter.boundingRectFor(QRectF(1, 2, 4, 8)), QRectF(1, 2, 4, 8));

    QPixmap src(10, 10);
    src.fill(Qt::blue);

    QPixmap test(src.size());
    QPainter p(&test);
    filter.draw(&p, QPointF(0, 0), src, src.rect());
    p.end();

    QCOMPARE(test.toImage().pixel(0, 0), 0xff0000ff);
}

void tst_QPixmapFilter::colorizeSetColor()
{
    QPixmapColorizeFilter filter;
    filter.setColor(QColor(50, 100, 200));
    QCOMPARE(filter.color(), QColor(50, 100, 200));
}

void tst_QPixmapFilter::colorizeProcess()
{
    QPixmapColorizeFilter filter;
    filter.setColor(QColor(100, 100, 100));

    QCOMPARE(filter.boundingRectFor(QRectF(0, 0, 50, 50)), QRectF(0, 0, 50, 50));
    QCOMPARE(filter.boundingRectFor(QRectF(30, 20, 10, 40)), QRectF(30, 20, 10, 40));
    QCOMPARE(filter.boundingRectFor(QRectF(2.2, 6.3, 11.4, 47.5)), QRectF(2.2, 6.3, 11.4, 47.5));

    QPixmap source("noise.png");
    QImage result(source.size(), QImage::Format_ARGB32_Premultiplied);
    result.fill(0);
    QPainter p(&result);
    filter.draw(&p, QPointF(0, 0), source);
    p.end();
    QImage resultImg = result;
    for(int y = 0; y < resultImg.height(); y++)
    {
        for(int x = 0; x < resultImg.width(); x++)
        {
            QRgb pixel = resultImg.pixel(x,y);
            QCOMPARE(qRed(pixel), qGreen(pixel));
            QCOMPARE(qGreen(pixel), qBlue(pixel));
        }
    }
}

void tst_QPixmapFilter::colorizeDraw()
{
    QPixmapColorizeFilter filter;
    filter.setColor(QColor(100, 100, 100));

    QPixmap pixmap("noise.png");
    QImage result(pixmap.size(), QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&result);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(result.rect(), QColor(128, 0, 0, 0));
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    filter.draw(&painter, QPointF(0, 0), pixmap);
    painter.end();

    QImage resultImg = result;
    for(int y = 0; y < resultImg.height(); y++)
    {
        for(int x = 0; x < resultImg.width(); x++)
        {
            QRgb pixel = resultImg.pixel(x,y);
            QCOMPARE(qRed(pixel), qGreen(pixel));
            QCOMPARE(qGreen(pixel), qBlue(pixel));
        }
    }
}

void tst_QPixmapFilter::colorizeDrawSubRect()
{
    QPixmapColorizeFilter filter;
    filter.setColor(QColor(255, 255, 255));

    QPixmap pixmap("noise.png");
    QImage result(pixmap.size(), QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&result);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(result.rect(), QColor(128, 0, 0, 255));
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    filter.draw(&painter, QPointF(16, 16), pixmap, QRectF(16, 16, 16, 16));
    painter.end();

    QImage resultImg = result;
    QImage sourceImg = pixmap.toImage();
    for(int y = 0; y < resultImg.height(); y++)
    {
        for(int x = 0; x < resultImg.width(); x++)
        {
            QRgb pixel = resultImg.pixel(x,y);
            if(x>=16 && x<32 && y>=16 && y<32) {
                QCOMPARE(qRed(pixel), qGreen(pixel));
                QCOMPARE(qGreen(pixel), qBlue(pixel));
            } else  {
                QCOMPARE(qRed(pixel), 128);
                QCOMPARE(qGreen(pixel), 0);
                QCOMPARE(qBlue(pixel), 0);
                QCOMPARE(qAlpha(pixel), 255);
            }
        }
    }
}

void tst_QPixmapFilter::colorizeProcessSubRect()
{
    QPixmapColorizeFilter filter;
    filter.setColor(QColor(200, 200, 200));

    QPixmap source("noise.png");
    QImage result(QSize(16, 16), QImage::Format_ARGB32_Premultiplied);
    result.fill(0);
    QPainter p(&result);
    filter.draw(&p, QPointF(0, 0), source, QRectF(16, 16, 16, 16));
    p.end();

    QImage resultImg = result;
    for(int y = 0; y < resultImg.height(); y++)
    {
        for(int x = 0; x < resultImg.width(); x++)
        {
            QRgb pixel = resultImg.pixel(x,y);
            QCOMPARE(qRed(pixel), qGreen(pixel));
            QCOMPARE(qGreen(pixel), qBlue(pixel));
        }
    }
}

void tst_QPixmapFilter::convolutionBoundingRectFor()
{
    QPixmapConvolutionFilter filter;
    QCOMPARE(filter.boundingRectFor(QRectF(0, 0, 50, 50)), QRectF(0, 0, 50, 50));
    QCOMPARE(filter.boundingRectFor(QRectF(30, 20, 10, 40)), QRectF(30, 20, 10, 40));
    QCOMPARE(filter.boundingRectFor(QRectF(2.2, 6.3, 11.4, 47.5)), QRectF(2.2, 6.3, 11.4, 47.5));
    qreal kernel[] = {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    };
    filter.setConvolutionKernel(kernel, 2, 2);
    QCOMPARE(filter.boundingRectFor(QRectF(0, 0, 50, 50)), QRectF(-1, -1, 51, 51));
    QCOMPARE(filter.boundingRectFor(QRectF(30, 20, 10, 40)), QRectF(29, 19, 11, 41));
    QCOMPARE(filter.boundingRectFor(QRectF(2.2, 6.3, 11.4, 47.5)), QRectF(1.2, 5.3, 12.4, 48.5));

    filter.setConvolutionKernel(kernel, 3, 3);
    QCOMPARE(filter.boundingRectFor(QRectF(0, 0, 50, 50)), QRectF(-1, -1, 52, 52));
    QCOMPARE(filter.boundingRectFor(QRectF(30, 20, 10, 40)), QRectF(29, 19, 12, 42));
    QCOMPARE(filter.boundingRectFor(QRectF(2.2, 6.3, 11.4, 47.5)), QRectF(1.2, 5.3, 13.4, 49.5));

    filter.setConvolutionKernel(kernel, 4, 4);
    QCOMPARE(filter.boundingRectFor(QRectF(0, 0, 50, 50)), QRectF(-2, -2, 53, 53));
    QCOMPARE(filter.boundingRectFor(QRectF(30, 20, 10, 40)), QRectF(28, 18, 13, 43));
    QCOMPARE(filter.boundingRectFor(QRectF(2.2, 6.3, 11.4, 47.5)), QRectF(0.2, 4.3, 14.4, 50.5));
}

void tst_QPixmapFilter::convolutionDrawSubRect()
{
    QPixmapConvolutionFilter filter;
    qreal kernel[] = {
        0, 0, 0,
        0, 0, 0,
        0, 0, 1
    };
    filter.setConvolutionKernel(kernel, 3, 3);

    QPixmap pixmap("noise.png");
    QImage result(pixmap.size(), QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&result);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(result.rect(), QColor(128, 0, 0, 255));
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    filter.draw(&painter, QPointF(16, 16), pixmap, QRectF(16, 16, 16, 16));
    painter.end();

    QImage resultImg = result;
    QImage sourceImg = pixmap.toImage();
    for(int y = 0; y < resultImg.height()-1; y++)
    {
        for(int x = 0; x < resultImg.width()-1; x++)
        {
            QRgb pixel = resultImg.pixel(x,y);
            QRgb srcPixel = sourceImg.pixel(x+1,y+1);
            if(x>=15 && x<33 && y>=15 && y<33) {
                QCOMPARE(pixel, srcPixel);
            } else  {
                QCOMPARE(qRed(pixel), 128);
                QCOMPARE(qGreen(pixel), 0);
                QCOMPARE(qBlue(pixel), 0);
                QCOMPARE(qAlpha(pixel), 255);
            }
        }
    }


    kernel[2] = 1;
    kernel[8] = 0;
    filter.setConvolutionKernel(kernel, 3, 3);

    QPainter painter2(&result);
    painter2.setCompositionMode(QPainter::CompositionMode_Source);
    painter2.fillRect(result.rect(), QColor(128, 0, 0, 255));
    painter2.setCompositionMode(QPainter::CompositionMode_SourceOver);
    filter.draw(&painter2, QPointF(16, 16), pixmap, QRectF(16, 16, 16, 16));
    painter2.end();

    resultImg = result;
    sourceImg = pixmap.toImage();
    for(int y = 1; y < resultImg.height(); y++)
    {
        for(int x = 0; x < resultImg.width()-1; x++)
        {
            QRgb pixel = resultImg.pixel(x,y);
            QRgb srcPixel = sourceImg.pixel(x+1,y-1);
            if(x>=15 && x<33 && y>=15 && y<33) {
                QCOMPARE(pixel, srcPixel);
            } else  {
                QCOMPARE(qRed(pixel), 128);
                QCOMPARE(qGreen(pixel), 0);
                QCOMPARE(qBlue(pixel), 0);
                QCOMPARE(qAlpha(pixel), 255);
            }
        }
    }

}

void tst_QPixmapFilter::dropShadowBoundingRectFor()
{
    QPixmapDropShadowFilter filter;
    filter.setBlurRadius(0);

    QCOMPARE(filter.blurRadius(), 0.0);

    filter.setOffset(QPointF(0,0));
    QCOMPARE(filter.boundingRectFor(QRectF(0, 0, 50, 50)), QRectF(0, 0, 50, 50));
    QCOMPARE(filter.boundingRectFor(QRectF(30, 20, 10, 40)), QRectF(30, 20, 10, 40));
    QCOMPARE(filter.boundingRectFor(QRectF(2.2, 6.3, 11.4, 47.5)), QRectF(2.2, 6.3, 11.4, 47.5));

    filter.setOffset(QPointF(1,1));
    QCOMPARE(filter.offset(), QPointF(1, 1));
    QCOMPARE(filter.boundingRectFor(QRectF(0, 0, 50, 50)), QRectF(0, 0, 51, 51));
    QCOMPARE(filter.boundingRectFor(QRectF(30, 20, 10, 40)), QRectF(30, 20, 11, 41));
    QCOMPARE(filter.boundingRectFor(QRectF(2.2, 6.3, 11.4, 47.5)), QRectF(2.2, 6.3, 12.4, 48.5));

    filter.setOffset(QPointF(-1,-1));
    QCOMPARE(filter.boundingRectFor(QRectF(0, 0, 50, 50)), QRectF(-1, -1, 51, 51));
    QCOMPARE(filter.boundingRectFor(QRectF(30, 20, 10, 40)), QRectF(29, 19, 11, 41));
    QCOMPARE(filter.boundingRectFor(QRectF(2.2, 6.3, 11.4, 47.5)), QRectF(1.2, 5.3, 12.4, 48.5));

    filter.setBlurRadius(2);
    filter.setOffset(QPointF(0,0));
    QCOMPARE(filter.boundingRectFor(QRectF(0, 0, 50, 50)), QRectF(-2, -2, 54, 54));
    QCOMPARE(filter.boundingRectFor(QRectF(30, 20, 10, 40)), QRectF(28, 18, 14, 44));
    QCOMPARE(filter.boundingRectFor(QRectF(2.2, 6.3, 11.4, 47.5)), QRectF(0.2, 4.3, 15.4, 51.5));

    filter.setOffset(QPointF(1,1));
    QCOMPARE(filter.boundingRectFor(QRectF(0, 0, 50, 50)), QRectF(-1, -1, 54, 54));
    QCOMPARE(filter.boundingRectFor(QRectF(30, 20, 10, 40)), QRectF(29, 19, 14, 44));
    QCOMPARE(filter.boundingRectFor(QRectF(2.2, 6.3, 11.4, 47.5)), QRectF(1.2, 5.3, 15.4, 51.5));

    filter.setOffset(QPointF(-10,-10));
    QCOMPARE(filter.boundingRectFor(QRectF(0, 0, 50, 50)), QRectF(-12, -12, 62, 62));
    QCOMPARE(filter.boundingRectFor(QRectF(30, 20, 10, 40)), QRectF(18, 8, 22, 52));
    QCOMPARE(filter.boundingRectFor(QRectF(2.2, 6.3, 11.4, 47.5)), QRectF(-9.8, -5.7, 23.4, 59.5));
}


QTEST_MAIN(tst_QPixmapFilter)
#include "tst_qpixmapfilter.moc"
