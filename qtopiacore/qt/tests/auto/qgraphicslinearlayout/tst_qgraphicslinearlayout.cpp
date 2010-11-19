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
#include <qgraphicslinearlayout.h>
#include <qgraphicsproxywidget.h>
#include <qgraphicswidget.h>
#include <qgraphicsscene.h>
#include <qgraphicsview.h>

class tst_QGraphicsLinearLayout : public QObject {
Q_OBJECT

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private slots:
    void qgraphicslinearlayout_data();
    void qgraphicslinearlayout();

    void alignment_data();
    void alignment();
    void count_data();
    void count();
    void dump_data();
    void dump();
    void geometry_data();
    void geometry();
    void insertItem_data();
    void insertItem();
    void insertStretch_data();
    void insertStretch();
    void invalidate_data();
    void invalidate();
    void itemAt_data();
    void itemAt();
    void orientation_data();
    void orientation();
    void removeAt_data();
    void removeAt();
    void removeItem_data();
    void removeItem();
    void setGeometry_data();
    void setGeometry();
    void setSpacing_data();
    void setSpacing();
    void setItemSpacing_data();
    void setItemSpacing();
    void itemSpacing();
    void setStretchFactor_data();
    void setStretchFactor();
    void defaultStretchFactors_data();
    void defaultStretchFactors();
    void sizeHint_data();
    void sizeHint();
    void updateGeometry();
    void layoutDirection();
    void removeLayout();

    // Task specific tests
    void task218400_insertStretchCrash();
};

// Subclass that exposes the protected functions.
class SubQGraphicsLinearLayout : public QGraphicsLinearLayout {
public:
    SubQGraphicsLinearLayout(Qt::Orientation orientation = Qt::Horizontal) : QGraphicsLinearLayout(orientation),
        graphicsSceneResize(0),
        layoutRequest(0),
        layoutDirectionChange(0)
        { }

    void widgetEvent(QEvent *e)
    {
        switch (e->type()) {
        case QEvent::GraphicsSceneResize:
            graphicsSceneResize++;
            break;
        case QEvent::LayoutRequest:
            layoutRequest++;
            break;
        case QEvent::LayoutDirectionChange:
            layoutDirectionChange++;
            break;
        default:
            break;
        }

        QGraphicsLinearLayout::widgetEvent(e);
    }

    int graphicsSceneResize;
    int layoutRequest;
    int layoutDirectionChange;
};

// This will be called before the first test function is executed.
// It is only called once.
void tst_QGraphicsLinearLayout::initTestCase()
{
}

// This will be called after the last test function is executed.
// It is only called once.
void tst_QGraphicsLinearLayout::cleanupTestCase()
{
}

// This will be called before each test function is executed.
void tst_QGraphicsLinearLayout::init()
{
}

// This will be called after every test function.
void tst_QGraphicsLinearLayout::cleanup()
{
}

class RectWidget : public QGraphicsWidget
{
public:
    RectWidget(QGraphicsItem *parent = 0, const QBrush &brush = QBrush()) : QGraphicsWidget(parent){ m_brush = brush;}

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) 
    {
        Q_UNUSED(option);
        Q_UNUSED(widget);
        painter->setBrush(m_brush);
        painter->drawRoundRect(rect());
    }
    
    void setSizeHint(Qt::SizeHint which, const QSizeF &size) {
        m_sizeHints[which] = size;
        updateGeometry();
    }
    
    virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const {
        if (m_sizeHints[which].isValid()) {
            return m_sizeHints[which];
        }
        return QGraphicsWidget::sizeHint(which, constraint);
    }

    QSizeF m_sizeHints[Qt::NSizeHints];
    QBrush m_brush;
};


Q_DECLARE_METATYPE(Qt::Orientation)
void tst_QGraphicsLinearLayout::qgraphicslinearlayout_data()
{
    QTest::addColumn<Qt::Orientation>("orientation");
    QTest::newRow("vertical") << Qt::Vertical;
    QTest::newRow("horizontal") << Qt::Horizontal;
}

void tst_QGraphicsLinearLayout::qgraphicslinearlayout()
{
    QFETCH(Qt::Orientation, orientation);
    SubQGraphicsLinearLayout layout(orientation);
    QVERIFY(layout.isLayout());

    qApp->processEvents();
    QCOMPARE(layout.graphicsSceneResize, 0);
    QCOMPARE(layout.layoutRequest, 0);
    QCOMPARE(layout.layoutDirectionChange, 0);

    layout.setOrientation(Qt::Vertical);
    layout.orientation();
    QTest::ignoreMessage(QtWarningMsg, "QGraphicsLinearLayout::insertItem: cannot insert null item");
    //QCOMPARE(layout.count(), 0);
    layout.addItem(0);
    //QCOMPARE(layout.count(), 0);
    layout.addStretch(0);
    //QCOMPARE(layout.count(), 1);
    QTest::ignoreMessage(QtWarningMsg, "QGraphicsLinearLayout::insertItem: cannot insert null item");
    layout.insertItem(0, 0);
    layout.insertStretch(0, 0);
    layout.removeItem(0);
    layout.removeAt(0);
    //QCOMPARE(layout.count(), 1);
    layout.setSpacing(0);
    layout.spacing();
    QTest::ignoreMessage(QtWarningMsg, "QGraphicsLinearLayout::setStretchFactor: cannot assign a stretch factor to a null item");
    layout.setStretchFactor(0, 0);
    QTest::ignoreMessage(QtWarningMsg, "QGraphicsLinearLayout::setStretchFactor: cannot return a stretch factor for a null item");
    layout.stretchFactor(0);
    layout.setAlignment(0, Qt::AlignHCenter);
    QCOMPARE(layout.alignment(0), 0);
    layout.setGeometry(QRectF());
    layout.geometry();
    //QCOMPARE(layout.count(), 1);
    layout.itemAt(0);
    layout.invalidate();
    layout.sizeHint(Qt::MinimumSize, QSizeF());
}

Q_DECLARE_METATYPE(Qt::AlignmentFlag)
void tst_QGraphicsLinearLayout::alignment_data()
{
    QTest::addColumn<Qt::Orientation>("orientation");
    QTest::addColumn<QSize>("newSize");
    QTest::newRow("h-defaultsize") << Qt::Horizontal << QSize();
    QTest::newRow("v-defaultsize") << Qt::Vertical << QSize();
    QTest::newRow("h-300") << Qt::Horizontal << QSize(300,100);
    QTest::newRow("v-300") << Qt::Vertical << QSize(100, 300);
}

void tst_QGraphicsLinearLayout::alignment()
{
    QFETCH(Qt::Orientation, orientation);
    QFETCH(QSize, newSize);

    //if (alignment == Qt::AlignAbsolute)
    //    QApplication::setLayoutDirection(Qt::RightToLeft);
    QGraphicsScene scene;
    QGraphicsView view(&scene);
    view.setSceneRect(0, 0, 320, 240);
    QGraphicsWidget *widget = new QGraphicsWidget(0, Qt::Window);
    SubQGraphicsLinearLayout &layout = *(new SubQGraphicsLinearLayout(orientation));
    scene.addItem(widget);
    widget->setLayout(&layout);

    static const Qt::Alignment alignmentsToTest[] = {
        (Qt::Alignment)0,
        Qt::AlignLeft,
        Qt::AlignRight,
        Qt::AlignHCenter,
        Qt::AlignTop,
        Qt::AlignBottom,
        Qt::AlignVCenter,
        Qt::AlignCenter,
        (Qt::Alignment)0,
        Qt::AlignLeft,
        Qt::AlignRight,
        Qt::AlignHCenter,
        Qt::AlignTop,
        Qt::AlignBottom,
        Qt::AlignVCenter,
        Qt::AlignCenter
    };

    int i;
    bool addWidget = true;
    for (i = 0; i < sizeof(alignmentsToTest)/sizeof(Qt::Alignment); ++i) {
        QGraphicsLayoutItem *loutItem; 
        Qt::Alignment align = alignmentsToTest[i];
        if (!align && i > 0)
            addWidget = false;
        if (addWidget)
            loutItem = new RectWidget(widget, QBrush(Qt::blue));
        else {
            SubQGraphicsLinearLayout *lay = new SubQGraphicsLinearLayout(Qt::Vertical);
            lay->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred, QSizePolicy::DefaultType);
            lay->setContentsMargins(0,0,0,0);
            QGraphicsWidget *w = new RectWidget(widget, QBrush(Qt::red));
            if (align) {
                w->setMinimumSize(QSizeF(10,10));
                w->setMaximumSize(QSizeF(10,10));
            } else {
                w->setMinimumSize(QSizeF(50,50));
                w->setMaximumSize(QSizeF(50,50));
            }
            lay->addItem(w);
            loutItem = lay;
        }
        if (align) {
            loutItem->setMinimumSize(QSizeF(10,10));
            loutItem->setMaximumSize(QSizeF(10,10));
        } else {
            loutItem->setMinimumSize(QSizeF(50,50));
            loutItem->setMaximumSize(QSizeF(50,50));
        }
        layout.addItem(loutItem);
        layout.setAlignment(loutItem, align);

    }
    layout.setContentsMargins(0,0,0,0);
    int spacing = 1;
    layout.setSpacing(spacing);
    if (newSize.isValid())
        widget->resize(newSize);
    view.show();
    widget->show();
    QApplication::processEvents();

    int x = 0;
    int y = 0;
    for (i = 0; i < layout.count(); ++i) {
        QGraphicsLayoutItem *item = layout.itemAt(i);
        Qt::Alignment align = layout.alignment(item);

        int w = 10;
        int h = 10;
        switch(align) {
            case Qt::AlignLeft:
                break;
            case Qt::AlignRight:
                if (orientation == Qt::Vertical)
                    x += 40;
                break;
            case Qt::AlignHCenter:
                if (orientation == Qt::Vertical)
                    x += 20;
                break;
            case Qt::AlignTop:
                break;
            case Qt::AlignBottom:
                if (orientation == Qt::Horizontal)
                    y += 40;
                break;
            case Qt::AlignVCenter:
                if (orientation == Qt::Horizontal)
                    y += 20;
                break;
            case Qt::AlignCenter:
                if (orientation == Qt::Horizontal)
                    y += 20;
                else
                    x += 20;
                break;
            case 0:
                w = 50;
                h = 50;
                break;
            default:
                break;
        }
        QRectF expectedGeometry(x, y, w, h);
        QCOMPARE(item->geometry(), expectedGeometry);
        if (orientation == Qt::Horizontal) {
            x += w;
            y = 0;
            x += spacing;
        } else {
            x = 0;
            y += h;
            y += spacing;
        }
    }
}

void tst_QGraphicsLinearLayout::count_data()
{
    QTest::addColumn<int>("itemCount");
    QTest::addColumn<int>("layoutCount");
    QTest::newRow("0, 0") << 0 << 0;
    QTest::newRow("0, 5") << 0 << 5;
    QTest::newRow("5, 0") << 5 << 0;
    QTest::newRow("5, 5") << 5 << 5;
}

// int count() const public
void tst_QGraphicsLinearLayout::count()
{
    QFETCH(int, itemCount);
    QFETCH(int, layoutCount);

    SubQGraphicsLinearLayout layout;
    QCOMPARE(layout.count(), 0);

    for (int i = 0; i < itemCount; ++i)
        layout.addItem(new QGraphicsWidget);
    QCOMPARE(layout.count(), itemCount);

    for (int i = 0; i < layoutCount; ++i)
        layout.addItem(new SubQGraphicsLinearLayout);
    QCOMPARE(layout.count(), itemCount + layoutCount);

    // see also removeAt()
}

void tst_QGraphicsLinearLayout::dump_data()
{
    QTest::addColumn<int>("itemCount");
    QTest::addColumn<int>("layoutCount");
    for (int i = -1; i < 3; ++i) {
        QTest::newRow(QString("%1, 0, 0").arg(i).toLatin1()) << 0 << 0;
        QTest::newRow(QString("%1, 0, 5").arg(i).toLatin1()) << 5 << 5;
        QTest::newRow(QString("%1, 5, 0").arg(i).toLatin1()) << 5 << 5;
        QTest::newRow(QString("%1, 5, 5").arg(i).toLatin1()) << 5 << 5;
    }
}

// void dump(int indent = 0) const public
void tst_QGraphicsLinearLayout::dump()
{
    QFETCH(int, itemCount);
    QFETCH(int, layoutCount);
    SubQGraphicsLinearLayout layout;
    for (int i = 0; i < itemCount; ++i)
        layout.addItem(new QGraphicsWidget);
    for (int i = 0; i < layoutCount; ++i)
        layout.addItem(new SubQGraphicsLinearLayout);
}

void tst_QGraphicsLinearLayout::geometry_data()
{
    QTest::addColumn<int>("itemCount");
    QTest::addColumn<int>("layoutCount");
    QTest::addColumn<int>("itemSpacing");
    QTest::addColumn<int>("spacing");
    QTest::addColumn<Qt::Orientation>("orientation");
    QTest::addColumn<QRectF>("rect");

    QTest::newRow("null") << 0 << 0 << 0 << 0 << Qt::Horizontal << QRectF();

    QTest::newRow("one item") << 1 << 0 << 0 << 0 << Qt::Horizontal << QRectF(0, 0, 10, 10);
    QTest::newRow("one layout") << 0 << 1 << 0 << 0 << Qt::Horizontal << QRectF(0, 0, 10, 10);
    QTest::newRow("two h") << 1 << 1 << 0 << 0 << Qt::Horizontal << QRectF(0, 0, 20, 10);
    QTest::newRow("two v") << 1 << 1 << 0 << 0 << Qt::Vertical << QRectF(0, 0, 10, 20);

    QTest::newRow("two w/itemspacing") << 1 << 1 << 5 << 0 << Qt::Horizontal << QRectF(0, 0, 25, 10);
    QTest::newRow("two w/spacing") << 1 << 1 << 8 << 0 << Qt::Horizontal << QRectF(0, 0, 28, 10);

    QTest::newRow("two w/itemspacing v") << 1 << 1 << 5 << 0 << Qt::Vertical << QRectF(0, 0, 10, 25);
    QTest::newRow("two w/spacing v") << 1 << 1 << 8 << 0 << Qt::Vertical << QRectF(0, 0, 10, 28);
}

// QRectF geometry() const public
void tst_QGraphicsLinearLayout::geometry()
{
    QFETCH(int, itemCount);
    QFETCH(int, layoutCount);
    QFETCH(int, itemSpacing);
    QFETCH(int, spacing);
    QFETCH(Qt::Orientation, orientation);
    QFETCH(QRectF, rect);
    QGraphicsScene scene;
    QGraphicsView view(&scene);
    QGraphicsWidget *widget = new QGraphicsWidget(0, Qt::Window);
    SubQGraphicsLinearLayout &layout = *(new SubQGraphicsLinearLayout(orientation));
    scene.addItem(widget);
    widget->setLayout(&layout);
    widget->setContentsMargins(0, 0, 0, 0);
    for (int i = 0; i < itemCount; ++i)
        layout.addItem(new QGraphicsWidget);
    for (int i = 0; i < layoutCount; ++i)
        layout.addItem(new SubQGraphicsLinearLayout);

    for (int i = 0; i < layout.count(); ++i) {
        QGraphicsLayoutItem *item = layout.itemAt(i);
        item->setMaximumSize(10, 10);
        item->setMinimumSize(10, 10);
    }
    layout.setItemSpacing(0, itemSpacing);
    layout.setSpacing(spacing);
    layout.setContentsMargins(0, 0, 0, 0);

    widget->show();
    view.show();
    QApplication::processEvents();
    QCOMPARE(layout.geometry(), rect);
    delete widget;
}

void tst_QGraphicsLinearLayout::insertItem_data()
{
    QTest::addColumn<int>("itemCount");
    QTest::addColumn<int>("layoutCount");
    QTest::addColumn<int>("insertItemAt");
    QTest::addColumn<bool>("isWidget");
    for (int i = -1; i < 4; ++i) {
        for (int j = 0; j < 2; ++j) {
            QTest::newRow(QString("0, 0, %1 %2").arg(i).arg(j).toLatin1()) << 0 << 0 << i << (bool)j;
            QTest::newRow(QString("1, 0, %1 %2").arg(i).arg(j).toLatin1()) << 1 << 0 << i << (bool)j;
            QTest::newRow(QString("0, 1, %1 %2").arg(i).arg(j).toLatin1()) << 0 << 1 << i << (bool)j;
            QTest::newRow(QString("2, 2, %1 %2").arg(i).arg(j).toLatin1()) << 2 << 2 << i << (bool)j;
        }
    }
}

// void insertItem(int index, QGraphicsLayoutItem* item) public
void tst_QGraphicsLinearLayout::insertItem()
{
    QFETCH(int, itemCount);
    QFETCH(int, layoutCount);
    QFETCH(int, insertItemAt);
    QFETCH(bool, isWidget);
    if (insertItemAt > layoutCount + itemCount)
        return;

    SubQGraphicsLinearLayout layout;
    for (int i = 0; i < itemCount; ++i)
        layout.addItem(new QGraphicsWidget);
    for (int i = 0; i < layoutCount; ++i)
        layout.addItem(new SubQGraphicsLinearLayout);

    QGraphicsLayoutItem *item = 0;
    if (isWidget)
        item = new QGraphicsWidget;
    else
        item = new SubQGraphicsLinearLayout;

    QSizeF oldSizeHint = layout.sizeHint(Qt::PreferredSize, QSizeF());
    layout.insertItem(insertItemAt, item);
    QCOMPARE(layout.count(), itemCount + layoutCount + 1);
    QCOMPARE(layout.itemAt(insertItemAt), insertItemAt == -1 ? (QGraphicsLayoutItem*)0 : item);

    layout.activate();
    QSizeF newSizeHint = layout.sizeHint(Qt::PreferredSize, QSizeF());
    if (!isWidget && layout.count() == 1)
        QCOMPARE(oldSizeHint.width(), newSizeHint.width());
    else if (itemCount + layoutCount > 0)
        QVERIFY(oldSizeHint.width() < newSizeHint.width());
}

void tst_QGraphicsLinearLayout::insertStretch_data()
{
    QTest::addColumn<int>("itemCount");
    QTest::addColumn<int>("layoutCount");
    QTest::addColumn<int>("insertItemAt");
    QTest::addColumn<int>("stretch");
    for (int i = -1; i < 4; ++i) {
        for (int j = 0; j < 2; ++j) {
            QTest::newRow(QString("0, 0, %1 %2").arg(i).arg(j).toLatin1()) << 0 << 0 << i << j;
            QTest::newRow(QString("1, 0, %1 %2").arg(i).arg(j).toLatin1()) << 1 << 0 << i << j;
            QTest::newRow(QString("0, 1, %1 %2").arg(i).arg(j).toLatin1()) << 0 << 1 << i << j;
            QTest::newRow(QString("2, 2, %1 %2").arg(i).arg(j).toLatin1()) << 2 << 2 << i << j;
        }
    }
}

// void insertStretch(int index, int stretch = 1) public
void tst_QGraphicsLinearLayout::insertStretch()
{
    QFETCH(int, itemCount);
    QFETCH(int, layoutCount);
    QFETCH(int, insertItemAt);
    QFETCH(int, stretch);
    if (insertItemAt > layoutCount + itemCount)
        return;

    QGraphicsScene scene;
    QGraphicsView view(&scene);
    QGraphicsWidget *widget = new QGraphicsWidget(0, Qt::Window);
    SubQGraphicsLinearLayout *layout = new SubQGraphicsLinearLayout;
    scene.addItem(widget);

    QList<QGraphicsWidget *>items;
    QGraphicsWidget *item = 0;
    for (int i = 0; i < itemCount; ++i) {
        item = new RectWidget;
        item->setMinimumSize(10, 10);
        item->setPreferredSize(25, 25);
        item->setMaximumSize(50, 50);
        layout->addItem(item);
    }
    for (int i = 0; i < layoutCount; ++i) {
        item = new RectWidget;
        item->setMinimumSize(10, 10);
        item->setPreferredSize(25, 25);
        item->setMaximumSize(50, 50);
        SubQGraphicsLinearLayout *sublayout = new SubQGraphicsLinearLayout;
        sublayout->addItem(item);
        layout->addItem(sublayout);
    }
    widget->setLayout(layout);
    layout->insertStretch(insertItemAt, stretch);
    QCOMPARE(layout->itemAt(insertItemAt), (QGraphicsLayoutItem*)0);
    QCOMPARE(layout->count(), itemCount + layoutCount + 1);

    layout->activate();
    view.show();
    widget->show();

    int prevStretch = -2;
    int prevWidth = -2;
    widget->resize((layoutCount + itemCount) * 25 + 25, 25);
    for (int i = 0; i < layout->count(); ++i) {
        if (QGraphicsLayoutItem *item = layout->itemAt(i)) {
            if (prevStretch != -2) {
                if (layout->stretchFactor(item) >= prevStretch) {
                    QVERIFY(item->geometry().width() >= prevWidth);
                } else {
                    QVERIFY(item->geometry().width() < prevWidth);
                }
            }
            prevStretch = layout->stretchFactor(item);
            prevWidth = (int)(item->geometry().width());
        }
    }

    //QTest::qWait(1000);
    delete widget;
}

void tst_QGraphicsLinearLayout::invalidate_data()
{
    QTest::addColumn<int>("count");
    QTest::newRow("0") << 0;
    QTest::newRow("1") << 1;
    QTest::newRow("2") << 2;
    QTest::newRow("3") << 3;
}

// void invalidate() public
void tst_QGraphicsLinearLayout::invalidate()
{
    QFETCH(int, count);
    QGraphicsScene scene;
    QGraphicsView view(&scene);
    QGraphicsWidget *widget = new QGraphicsWidget(0, Qt::Window);
    SubQGraphicsLinearLayout &layout = *(new SubQGraphicsLinearLayout);
    scene.addItem(widget);
    widget->setLayout(&layout);
    widget->setContentsMargins(0, 0, 0, 0);
    layout.setContentsMargins(0, 0, 0, 0);
    view.show();
    widget->show();

    layout.setContentsMargins(1, 2, 3, 4);
    qApp->processEvents();
    QCOMPARE(layout.layoutRequest, 1);

    layout.setOrientation(Qt::Vertical);
    qApp->processEvents();
    QCOMPARE(layout.layoutRequest, 2);

    for (int i = 0; i < count; ++i)
        layout.invalidate();        // Event is compressed, should only get one layoutrequest
    qApp->processEvents();
    QCOMPARE(layout.layoutRequest, count ? 3 : 2);
    delete widget;
}

void tst_QGraphicsLinearLayout::itemAt_data()
{
    QTest::addColumn<int>("index");
    QTest::newRow("-1") << -1;
    QTest::newRow("0") << 0;
    QTest::newRow("1") << 1;
    QTest::newRow("2") << 2;
}

// QGraphicsLayoutItem* itemAt(int index) const public
void tst_QGraphicsLinearLayout::itemAt()
{
    // see also the insertItem() etc tests
    QFETCH(int, index);
    SubQGraphicsLinearLayout layout;
    QCOMPARE(layout.itemAt(index), (QGraphicsLayoutItem*)0);
}

void tst_QGraphicsLinearLayout::orientation_data()
{
    QTest::addColumn<Qt::Orientation>("orientation");
    QTest::newRow("vertical") << Qt::Vertical;
    QTest::newRow("horizontal") << Qt::Horizontal;
}

// Qt::Orientation orientation() const public
void tst_QGraphicsLinearLayout::orientation()
{
    QFETCH(Qt::Orientation, orientation);
    
    QGraphicsScene scene;
    QGraphicsView view(&scene);
    QGraphicsWidget *widget = new QGraphicsWidget(0, Qt::Window);
    Qt::Orientation initialOrientation = (orientation == Qt::Vertical ? Qt::Horizontal : Qt::Vertical);
    SubQGraphicsLinearLayout &layout = *(new SubQGraphicsLinearLayout(initialOrientation));
    scene.addItem(widget);
    widget->setLayout(&layout);
    widget->setContentsMargins(0, 0, 0, 0);
    layout.setContentsMargins(0, 0, 0, 0);
    int i;
    int itemCount = 3;
    for (i = 0; i < itemCount; ++i)
        layout.addItem(new RectWidget);
    QCOMPARE(layout.orientation(), initialOrientation);
    QList<qreal> positions;

    view.show();
    widget->show();
    qApp->processEvents();

    for (i = 0; i < itemCount; ++i) {
        QGraphicsWidget *item = static_cast<QGraphicsWidget*>(layout.itemAt(i));
        qreal pos;
        if (initialOrientation == Qt::Horizontal)
            pos = item->pos().x();
        else 
            pos = item->pos().y();
        positions.append(pos);

    }

    layout.setOrientation(orientation);
    QCOMPARE(layout.orientation(), orientation);
	// important to resize to preferredsize when orientation is switched
    widget->resize(widget->effectiveSizeHint(Qt::PreferredSize));
    qApp->processEvents();
    for (i = 0; i < positions.count(); ++i) {
        QGraphicsWidget *item = static_cast<QGraphicsWidget*>(layout.itemAt(i));
        if (initialOrientation == Qt::Horizontal)
            QCOMPARE(item->pos().y(), positions.at(i));
        else 
            QCOMPARE(item->pos().x(), positions.at(i));
    }

    //QSKIP("LayoutdirectionChange should only posted when QGraphicsWidget::setLayoutDirection() is called, right?", SkipAll);

    //QCOMPARE(layout.layoutDirectionChange, 1);
}

void tst_QGraphicsLinearLayout::removeAt_data()
{
    QTest::addColumn<int>("itemCount");
    QTest::addColumn<int>("layoutCount");
    QTest::addColumn<int>("removeItemAt");
    QTest::addColumn<Qt::Orientation>("orientation");
    for (int i = -1; i < 4; ++i) {
        for (int k = 0; k < 2; ++k) {
            Qt::Orientation orientation = (k == 0) ? Qt::Vertical : Qt::Horizontal;
            QTest::newRow(QString("0, 0, %1").arg(i).toLatin1()) << 0 << 0 << i << orientation;
            QTest::newRow(QString("1, 0, %1").arg(i).toLatin1()) << 1 << 0 << i << orientation;
            QTest::newRow(QString("0, 1, %1").arg(i).toLatin1()) << 0 << 1 << i << orientation;
            QTest::newRow(QString("2, 2, %1").arg(i).toLatin1()) << 2 << 2 << i << orientation;
        }
    }
}

// void removeAt(int index) public
void tst_QGraphicsLinearLayout::removeAt()
{
    QFETCH(int, itemCount);
    QFETCH(int, layoutCount);
    QFETCH(int, removeItemAt);
    QFETCH(Qt::Orientation, orientation);
    if (removeItemAt >= layoutCount + itemCount)
        return;

    SubQGraphicsLinearLayout layout(orientation);
    for (int i = 0; i < itemCount; ++i)
        layout.addItem(new QGraphicsWidget);
    for (int i = 0; i < layoutCount; ++i)
        layout.addItem(new SubQGraphicsLinearLayout);
    QSizeF oldSizeHint = layout.sizeHint(Qt::PreferredSize, QSizeF());

    QGraphicsLayoutItem *w = layout.itemAt(removeItemAt);
    QGraphicsLayoutItem *wParent = 0;
    if (w) {
        wParent = w->parentLayoutItem();
        QCOMPARE(wParent, static_cast<QGraphicsLayoutItem *>(&layout));
    }
    layout.removeAt(removeItemAt);
    if (w) {
        wParent = w->parentLayoutItem();
        QCOMPARE(wParent, static_cast<QGraphicsLayoutItem *>(0));
    }
    delete w;
    QCOMPARE(layout.count(), itemCount + layoutCount - ((removeItemAt == -1) ? 0 : 1));

    layout.activate();
    QSizeF newSizeHint = layout.sizeHint(Qt::PreferredSize, QSizeF());
    if (orientation == Qt::Horizontal)
        QVERIFY(oldSizeHint.width() >= newSizeHint.width());
    else
        QVERIFY(oldSizeHint.height() >= newSizeHint.height());
}

void tst_QGraphicsLinearLayout::removeItem_data()
{
    QTest::addColumn<int>("itemCount");
    QTest::addColumn<int>("layoutCount");
    QTest::addColumn<int>("removeItemAt");
    for (int i = -1; i < 4; ++i) {
        QTest::newRow(QString("0, 0, %1").arg(i).toLatin1()) << 0 << 0 << i;
        QTest::newRow(QString("1, 0, %1").arg(i).toLatin1()) << 1 << 0 << i;
        QTest::newRow(QString("0, 1, %1").arg(i).toLatin1()) << 0 << 1 << i;
        QTest::newRow(QString("2, 2, %1").arg(i).toLatin1()) << 2 << 2 << i;
    }
}

// void removeItem(QGraphicsLayoutItem* item) public
void tst_QGraphicsLinearLayout::removeItem()
{
    QFETCH(int, itemCount);
    QFETCH(int, layoutCount);
    QFETCH(int, removeItemAt);
    if (removeItemAt >= layoutCount + itemCount)
        return;

    SubQGraphicsLinearLayout layout;
    for (int i = 0; i < itemCount; ++i)
        layout.addItem(new QGraphicsWidget);
    for (int i = 0; i < layoutCount; ++i)
        layout.addItem(new SubQGraphicsLinearLayout);

    QGraphicsLayoutItem *w = layout.itemAt(removeItemAt);
    QSizeF oldSizeHint = layout.sizeHint(Qt::PreferredSize, QSizeF());
    layout.removeItem(w);
    delete w;
    QCOMPARE(layout.count(), itemCount + layoutCount - ((removeItemAt == -1) ? 0 : 1));

    layout.activate();
    QSizeF newSizeHint = layout.sizeHint(Qt::PreferredSize, QSizeF());
    QVERIFY(oldSizeHint.width() >= newSizeHint.width());
}

void tst_QGraphicsLinearLayout::setGeometry_data()
{
    QTest::addColumn<QRectF>("rect");
    QTest::newRow("null") << QRectF();
    QTest::newRow("small") << QRectF(0, 0, 10, 10);
}

// void setGeometry(QRectF const& rect) public
void tst_QGraphicsLinearLayout::setGeometry()
{
    QFETCH(QRectF, rect);
    QGraphicsScene scene;
    QGraphicsView view(&scene);
    QGraphicsWidget *widget = new QGraphicsWidget(0, Qt::Window);
    SubQGraphicsLinearLayout &layout = *(new SubQGraphicsLinearLayout);
    scene.addItem(widget);
    widget->setLayout(&layout);
    widget->setContentsMargins(0, 0, 0, 0);
    layout.setContentsMargins(0, 0, 0, 0);
    layout.setMaximumSize(100, 100);
    view.show();
    widget->show();
    QApplication::processEvents();
    widget->setGeometry(rect);
    QCOMPARE(layout.geometry(), rect);
    // see also geometry()
    delete widget;
}

void tst_QGraphicsLinearLayout::setSpacing_data()
{
    QTest::addColumn<qreal>("spacing");
    QTest::newRow("0") << (qreal)0;
    QTest::newRow("5") << (qreal)5;
    QTest::newRow("3.3") << (qreal)3.3;
    QTest::newRow("-4.3") << (qreal)4.3;
}

// void setSpacing(qreal spacing) public
void tst_QGraphicsLinearLayout::setSpacing()
{
    QFETCH(qreal, spacing);
    
    QGraphicsScene scene;
    QGraphicsView view(&scene);
    QGraphicsWidget *widget = new QGraphicsWidget(0, Qt::Window);
    SubQGraphicsLinearLayout &layout = *(new SubQGraphicsLinearLayout);
    scene.addItem(widget);
    widget->setLayout(&layout);
    layout.setContentsMargins(0, 0, 0, 0);

    qreal oldSpacing = layout.spacing();
    if (oldSpacing != -1) {
        for (int i = 0; i < 3; ++i)
            layout.addItem(new QGraphicsWidget);
        QSizeF oldSizeHint = layout.sizeHint(Qt::PreferredSize);

        layout.setSpacing(spacing);
        QCOMPARE(layout.spacing(), spacing);

        view.show();
        widget->show();
        QApplication::processEvents();
        QSizeF newSizeHint = layout.sizeHint(Qt::PreferredSize);

        QCOMPARE(oldSizeHint.width() - oldSpacing * 2, newSizeHint.width() - spacing * 2);
    } else {
        QSKIP("This style uses non-uniform spacings (layoutSpacingImplementation() is reimplemented)", SkipAll);
    }
    delete widget;
}

void tst_QGraphicsLinearLayout::setItemSpacing_data()
{
    QTest::addColumn<int>("index");
    QTest::addColumn<int>("spacing");

    QTest::newRow("0 at 0") << 0 << 0;
    QTest::newRow("10 at 0") << 0 << 10;
    QTest::newRow("10 at 1") << 1 << 10;
    QTest::newRow("10 at the end") << 4 << 10;
}

void tst_QGraphicsLinearLayout::setItemSpacing()
{
    QFETCH(int, index);
    QFETCH(int, spacing);

    QGraphicsScene scene;
    QGraphicsView view(&scene);
    QGraphicsWidget *widget = new QGraphicsWidget(0, Qt::Window);
    SubQGraphicsLinearLayout *layout = new SubQGraphicsLinearLayout;
    scene.addItem(widget);
    widget->setLayout(layout);
    layout->setContentsMargins(0, 0, 0, 0);
    for (int i = 0; i < 5; ++i) {
        QGraphicsWidget *w = new QGraphicsWidget;
        layout->addItem(w);
    }
    QSizeF oldSizeHint = layout->sizeHint(Qt::PreferredSize);
    qreal oldSpacing = 0;
    if (index < layout->count() - 1)
        oldSpacing = layout->spacing();
    else
        spacing = 0;

    layout->setItemSpacing(index, spacing);
    view.show();
    QApplication::processEvents();
    QSizeF newSizeHint = layout->sizeHint(Qt::PreferredSize);
    if (oldSpacing >= 0) {
        QCOMPARE(newSizeHint.width() - spacing, oldSizeHint.width() - oldSpacing);
    } else {
        QSKIP("This style uses non-uniform spacings (layoutSpacingImplementation() is reimplemented)", SkipAll);
    }
    delete widget;
}

void tst_QGraphicsLinearLayout::itemSpacing()
{
    QGraphicsScene scene;
    QGraphicsView view(&scene);
    QGraphicsWidget *widget = new QGraphicsWidget(0, Qt::Window);
    SubQGraphicsLinearLayout *layout = new SubQGraphicsLinearLayout;
    scene.addItem(widget);
    widget->setLayout(layout);
    layout->setContentsMargins(0, 0, 0, 0);
    for (int i = 0; i < 5; ++i) {
        QGraphicsWidget *w = new QGraphicsWidget;
        layout->addItem(w);
    }

    // Check defaults
    qreal defaultSpacing = layout->spacing();
    if (defaultSpacing >= 0) {
        QCOMPARE(layout->itemSpacing(0), defaultSpacing);
    } else {
        // all widgets are the same, so the spacing should be uniform
        QCOMPARE(layout->itemSpacing(0), layout->itemSpacing(1));
    }

    layout->setItemSpacing(1, 42);
    QCOMPARE(layout->itemSpacing(1), qreal(42));

    // try to unset
    layout->setItemSpacing(1, -1);
    QCOMPARE(layout->itemSpacing(1), defaultSpacing);

    delete widget;
}

/**
 * The stretch factors are not applied linearly, but they are used together with both the preferred size, maximum size to form the
 * internal effective stretch factor.
 * There is only need to apply stretch factors if the size of the layout is different than the layouts preferred size. 
 * (If the size of the layout is the preferred size, then all items should get their preferred sizes.
 * However, imagine this use case:
 * Layout
 *          +----------+----------+----------+
 * name     |    A     |    B     |    C     |
 * stretch  |    1     |    2     |    3     |
 * sizehints|[5,10,50] |[5,10,50] |[5,10,50] |
 *          +----------+----------+----------+
 *
 * layout->resize(120, h)
 *
 * In QLayout, C would become 50, B would become 50 and A would get 20. When scaling a layout this would give a jerky feeling, since
 * the item with the highest stretch factor will first resize. When that has reached its maximum the next candidate for stretch will 
 * resize, and finally, item with the lowest stretch factor will resize.
 * In QGraphicsLinearLayout we try to scale all items so that they all reach their maximum at the same time. This means that
 * their relative sizes are not proportional to their stretch factors.
 */

typedef QList<int> IntList;
Q_DECLARE_METATYPE(IntList)
Q_DECLARE_METATYPE(qreal)

void tst_QGraphicsLinearLayout::setStretchFactor_data()
{
    QTest::addColumn<qreal>("totalSize");
    QTest::addColumn<IntList>("stretches");

    QTest::newRow(QString("60 [1,2]").toLatin1()) << qreal(60.0) << (IntList() << 1 << 2);
    QTest::newRow(QString("60 [1,2,3]").toLatin1()) << qreal(60.0) << (IntList() << 1 << 2 << 3);
    QTest::newRow(QString("120 [1,2,3,6]").toLatin1()) << qreal(120.0) << (IntList() << 1 << 2 << 3 << 6);
}

// void setStretchFactor(QGraphicsLayoutItem* item, int stretch) public
void tst_QGraphicsLinearLayout::setStretchFactor()
{
    QFETCH(qreal, totalSize);
    QFETCH(IntList, stretches);
    //QSKIP("Seems to be some problems with stretch factors. Talk with Jasmin", SkipAll);
    QGraphicsScene scene;
    QGraphicsView view(&scene);
    QGraphicsWidget *widget = new QGraphicsWidget(0, Qt::Window);
    SubQGraphicsLinearLayout &layout = *(new SubQGraphicsLinearLayout);
    scene.addItem(widget);
    widget->setLayout(&layout);
    layout.setContentsMargins(0, 0, 0, 0);
    layout.setSpacing(0.0);
    widget->setContentsMargins(0, 0, 0, 0);


    int i;
    for (i = 0; i < stretches.count(); ++i) {
        QGraphicsWidget *item = new RectWidget(widget);
        item->setMinimumSize(5,5);
        item->setPreferredSize(10,5);
        item->setMaximumSize(50,5);
        layout.addItem(item);
        layout.setStretchFactor(item, stretches.at(i));
    }

    widget->resize(totalSize, 10);
    QApplication::processEvents();

    view.show();
    widget->show();
    
    qreal firstStretch = -1;
    qreal firstExtent = -1.;
    qreal sumExtent = 0;
    for (i = 0; i < stretches.count(); ++i) {
        QGraphicsWidget *item = static_cast<QGraphicsWidget*>(layout.itemAt(i));
        qreal extent = item->size().width();
        qreal stretch = (qreal)stretches.at(i);
        if (firstStretch != -1 && firstExtent != -1) {
            // The resulting widths does not correspond linearly to the stretch factors.
            if (stretch == firstStretch)
                QCOMPARE(extent, firstExtent);
            else if (stretch > firstStretch)
                QVERIFY(extent > firstExtent);
            else 
                QVERIFY(extent < firstExtent);
        } else {
            firstStretch = (qreal)stretch;
            firstExtent = extent;
        }
        sumExtent+= extent;
    }
    QCOMPARE(sumExtent, totalSize);
    
    delete widget;
}

void tst_QGraphicsLinearLayout::defaultStretchFactors_data()
{
    QTest::addColumn<Qt::Orientation>("orientation");
    QTest::addColumn<int>("count");
    QTest::addColumn<IntList>("preferredSizeHints");
    QTest::addColumn<IntList>("stretches");
    QTest::addColumn<IntList>("ignoreFlag");
    QTest::addColumn<QSizeF>("newSize");
    QTest::addColumn<IntList>("expectedSizes");

    QTest::newRow("hor") << Qt::Horizontal << 3
                            << (IntList() << 20 << 40 << 60)
                            << (IntList())
                            << (IntList())
                            << QSizeF()
                            << (IntList() << 20 << 40 << 60);

    QTest::newRow("ver") << Qt::Vertical << 3
                            << (IntList() << 20 << 40 << 60)
                            << (IntList())
                            << (IntList())
                            << QSizeF()
                            << (IntList() << 20 << 40 << 60);

    QTest::newRow("hor,ignore123") << Qt::Horizontal << 3
                            << (IntList() << 20 << 40 << 60)
                            << (IntList())
                            << (IntList() << 1 << 1 << 1)
                            << QSizeF()
                            << (IntList() << 0 << 0 << 0);

    QTest::newRow("hor,ignore23") << Qt::Horizontal << 3
                            << (IntList() << 10 << 10 << 10)
                            << (IntList())
                            << (IntList() << 0 << 1 << 1)
                            << QSizeF(200, 50)
                            << (IntList());     //### stretches are not linear.

    QTest::newRow("hor,ignore2") << Qt::Horizontal << 3
                            << (IntList() << 10 << 10 << 10)
                            << (IntList())
                            << (IntList() << 0 << 1 << 0)
                            << QSizeF()
                            << (IntList() << 10 << 0 << 10);

}

void tst_QGraphicsLinearLayout::defaultStretchFactors()
{
    QFETCH(Qt::Orientation, orientation);
    QFETCH(int, count);
    QFETCH(IntList, preferredSizeHints);
    QFETCH(IntList, stretches);
    QFETCH(IntList, ignoreFlag);
    QFETCH(QSizeF, newSize);
    QFETCH(IntList, expectedSizes);

    QGraphicsScene scene;
    QGraphicsView view(&scene);
    QGraphicsWidget *widget = new QGraphicsWidget(0, Qt::Window);
    SubQGraphicsLinearLayout *layout = new SubQGraphicsLinearLayout(orientation);
    scene.addItem(widget);
    widget->setLayout(layout);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0.0);
    widget->setContentsMargins(0, 0, 0, 0);

    int i;
    for (i = 0; i < count; ++i) {
        RectWidget *item = new RectWidget(widget);
        layout->addItem(item);
        if (preferredSizeHints.value(i, -1) >= 0) {
            item->setSizeHint(Qt::PreferredSize, QSizeF(preferredSizeHints.at(i), preferredSizeHints.at(i)));
        }
        if (stretches.value(i, -1) >= 0) {
            layout->setStretchFactor(item, stretches.at(i));
        }
        if (ignoreFlag.value(i, 0) != 0) {
            QSizePolicy sp = item->sizePolicy();
            if (orientation == Qt::Horizontal)
                sp.setHorizontalPolicy(QSizePolicy::Policy(sp.horizontalPolicy() | QSizePolicy::IgnoreFlag));
            else 
                sp.setVerticalPolicy(QSizePolicy::Policy(sp.verticalPolicy() | QSizePolicy::IgnoreFlag));
            item->setSizePolicy(sp);
        }
    }

    QApplication::processEvents();

    widget->show();
    view.show();
    view.resize(400,300);
    if (newSize.isValid())
        widget->resize(newSize);
    
    QApplication::processEvents();
    for (i = 0; i < count; ++i) {
        QSizeF itemSize = layout->itemAt(i)->geometry().size();
        if (orientation == Qt::Vertical)
            itemSize.transpose();
        if (i < expectedSizes.count())
            QCOMPARE(itemSize.width(), qreal(expectedSizes.at(i)));
    }
    
    delete widget;
}

Q_DECLARE_METATYPE(Qt::SizeHint)
void tst_QGraphicsLinearLayout::sizeHint_data()
{
    QTest::addColumn<Qt::SizeHint>("which");
    QTest::addColumn<QSizeF>("constraint");
    QTest::addColumn<qreal>("spacing");
    QTest::addColumn<qreal>("layoutMargin");
    QTest::addColumn<QSizeF>("sizeHint");

    QTest::newRow("minimumSize") << Qt::MinimumSize << QSizeF() << qreal(0.0) << qreal(0.0) << QSizeF(30, 10);
    QTest::newRow("preferredSize") << Qt::PreferredSize << QSizeF() << qreal(0.0) << qreal(0.0) << QSizeF(75, 25);
    QTest::newRow("maximumSize") << Qt::MaximumSize << QSizeF() << qreal(0.0) << qreal(0.0) << QSizeF(150, 50);
    QTest::newRow("minimumSize, spacing=3") << Qt::MinimumSize << QSizeF() << qreal(3.0) << qreal(0.0) << QSizeF(30 + 2*3, 10);
    QTest::newRow("minimumSize, spacing=3, layoutMargin=10") << Qt::MinimumSize << QSizeF() << qreal(3.0) << qreal(10.0) << QSizeF(30 + 2*3 + 2*10, 10 + 2*10);
    QTest::newRow("minimumSize, spacing=0, layoutMargin=7") << Qt::MinimumSize << QSizeF() << qreal(0.0) << qreal(7.0) << QSizeF(30 + 0 + 2*7, 10 + 2*7);
}

// QSizeF sizeHint(Qt::SizeHint which, QSizeF const& constraint) const public
void tst_QGraphicsLinearLayout::sizeHint()
{
    QFETCH(Qt::SizeHint, which);
    QFETCH(QSizeF, constraint);
    QFETCH(qreal, spacing);
    QFETCH(qreal, layoutMargin);
    QFETCH(QSizeF, sizeHint);

    QGraphicsScene scene;
    QGraphicsView view(&scene);
    QGraphicsWidget *widget = new QGraphicsWidget(0, Qt::Window);
    SubQGraphicsLinearLayout &layout = *(new SubQGraphicsLinearLayout);
    scene.addItem(widget);
    widget->setLayout(&layout);
    layout.setContentsMargins(layoutMargin, layoutMargin, layoutMargin, layoutMargin);
    layout.setSpacing(spacing);
    for (int i = 0; i < 3; ++i) {
        QGraphicsWidget *item = new QGraphicsWidget(widget);
        item->setMinimumSize(10, 10);
        item->setPreferredSize(25, 25);
        item->setMaximumSize(50, 50);
        layout.addItem(item);
    }
    QApplication::processEvents();
    QCOMPARE(layout.sizeHint(which, constraint), sizeHint);
    delete widget;
}

void tst_QGraphicsLinearLayout::updateGeometry()
{
    QGraphicsScene scene;
    QGraphicsView view(&scene);

    QGraphicsWidget *window = new QGraphicsWidget(0, Qt::Window);
    QGraphicsWidget *w1 = new QGraphicsWidget(window);
    w1->setMinimumSize(100, 40);
    SubQGraphicsLinearLayout *layout = new SubQGraphicsLinearLayout;
    layout->addItem(w1);
    scene.addItem(window);
    window->setLayout(layout);
    layout->setContentsMargins(0, 0, 0, 0);
    QCOMPARE(w1->parentLayoutItem(), static_cast<QGraphicsLayoutItem*>(layout));
    QCOMPARE(layout->parentLayoutItem(), static_cast<QGraphicsLayoutItem*>(window));
    
    view.show();
    QApplication::processEvents();
    QCOMPARE(window->size().toSize(), QSize(100, 50));
    w1->setMinimumSize(110, 60);
    QApplication::processEvents();
    QCOMPARE(window->size().toSize(), QSize(110, 60));
    QApplication::processEvents();

    {
        delete window;
        window = new QGraphicsWidget(0, Qt::Window);
        SubQGraphicsLinearLayout *layout2a = new SubQGraphicsLinearLayout;
        QGraphicsWidget *w1 = new QGraphicsWidget(window);
        w1->setMinimumSize(110, 50);
        layout2a->addItem(w1);
        SubQGraphicsLinearLayout *layout2 = new SubQGraphicsLinearLayout;
        layout2->addItem(layout2a);
        layout2->setContentsMargins(1, 1, 1, 1);
        layout2a->setContentsMargins(1, 1, 1, 1);
        window->setLayout(layout2);
        QApplication::processEvents();
        QCOMPARE(w1->parentLayoutItem(), static_cast<QGraphicsLayoutItem*>(layout2a));
        QCOMPARE(layout2a->parentLayoutItem(), static_cast<QGraphicsLayoutItem*>(layout2));
        QCOMPARE(layout2->parentLayoutItem(), static_cast<QGraphicsLayoutItem*>(window));
        QCOMPARE(window->size().toSize(), QSize(114, 54));
        QApplication::processEvents();
        w1->setMinimumSize(120, 60);
        QApplication::processEvents();
        QCOMPARE(window->size().toSize(), QSize(124, 64));    
    }

    {
        delete window;
        window = new QGraphicsWidget(0, Qt::Window);
        scene.addItem(window);
        window->show();
        QGraphicsWidget *w1 = new QGraphicsWidget(window);
        w1->setMinimumSize(100, 50);
        SubQGraphicsLinearLayout *layout2a = new SubQGraphicsLinearLayout;
        layout2a->addItem(w1);
        SubQGraphicsLinearLayout *layout2 = new SubQGraphicsLinearLayout;
        layout2->addItem(layout2a);
        layout2a->setContentsMargins(1, 1, 1, 1);
        window->setLayout(layout2);
        QApplication::processEvents();
        qreal left, top, right, bottom;
        layout2->getContentsMargins(&left, &top, &right, &bottom);
        QCOMPARE(window->size().toSize(), QSize(102 +left + right, 52 + top + bottom));
    }

    {
        delete window;
        window = new QGraphicsWidget(0, Qt::Window);
        scene.addItem(window);
        QGraphicsWidget *w1 = new QGraphicsWidget(window);
        w1->setMinimumSize(100, 50);
        window->setLayout(0);
        SubQGraphicsLinearLayout *layout2a = new SubQGraphicsLinearLayout;
        layout2a->addItem(w1);
        SubQGraphicsLinearLayout *layout2 = new SubQGraphicsLinearLayout;
        layout2->addItem(layout2a);
        window->resize(200, 80);
        window->setLayout(layout2);
        window->show();
        QApplication::processEvents();
        QCOMPARE(window->size().toSize(), QSize(200, 80));
    }

}

void tst_QGraphicsLinearLayout::layoutDirection()
{
    QGraphicsScene scene;
    QGraphicsView view(&scene);

    QGraphicsWidget *window = new QGraphicsWidget(0, Qt::Window);
    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout;
    layout->setContentsMargins(1, 2, 3, 4);
    RectWidget *w1 = new RectWidget;
    w1->setPreferredSize(20, 20);
    w1->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    layout->addItem(w1);
    RectWidget *w2 = new RectWidget;
    w2->setPreferredSize(20, 20);
    w2->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    layout->addItem(w2);
    
    scene.addItem(window);
    window->setLayout(layout);
    view.show();
    window->resize(50, 20);
    window->setLayoutDirection(Qt::LeftToRight);
    QApplication::processEvents();
    QCOMPARE(w1->geometry().left(), 1.0);
    QCOMPARE(w1->geometry().right(), 21.0);
    QCOMPARE(w2->geometry().left(), 27.0);
    QCOMPARE(w2->geometry().right(), 47.0);

    window->setLayoutDirection(Qt::RightToLeft);
    QApplication::processEvents();
    QCOMPARE(w1->geometry().right(), 49.0);
    QCOMPARE(w1->geometry().left(), 29.0);
    QCOMPARE(w2->geometry().right(), 23.0);
    QCOMPARE(w2->geometry().left(),  3.0);
    
    delete window;
}

void tst_QGraphicsLinearLayout::removeLayout()
{
    QGraphicsScene scene;
    RectWidget *textEdit = new RectWidget;
    RectWidget *pushButton = new RectWidget;
    scene.addItem(textEdit);
    scene.addItem(pushButton);

    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout;
    layout->addItem(textEdit);
    layout->addItem(pushButton);

    QGraphicsWidget *form = new QGraphicsWidget;
    form->setLayout(layout);
    scene.addItem(form);

    QGraphicsView view(&scene);
    view.show();
    QTest::qWait(20);

    QRectF r1 = textEdit->geometry();
    QRectF r2 = pushButton->geometry();
    form->setLayout(0);
    //documentation of QGraphicsWidget::setLayout:
    //If layout is 0, the widget is left without a layout. Existing subwidgets' geometries will remain unaffected.
    QCOMPARE(textEdit->geometry(), r1);
    QCOMPARE(pushButton->geometry(), r2);
}

void tst_QGraphicsLinearLayout::task218400_insertStretchCrash()
{
    QGraphicsScene *scene = new QGraphicsScene;
    QGraphicsWidget *a = scene->addWidget(new QWidget);
    QGraphicsWidget *b = scene->addWidget(new QWidget);

    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout;
    layout->addItem(a);
    layout->addItem(b);
    layout->insertStretch(0); // inserts gap in item grid in the layout engine

    QGraphicsWidget *form  = new QGraphicsWidget;
    form->setLayout(layout); // crash
}

QTEST_MAIN(tst_QGraphicsLinearLayout)
#include "tst_qgraphicslinearlayout.moc"
