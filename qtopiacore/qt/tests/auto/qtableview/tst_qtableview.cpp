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


#include <QtGui/QtGui>
#include <QtTest/QtTest>

//TESTED_CLASS=
//TESTED_FILES=

// Will try to wait for the condition while allowing event processing
// for a maximum of 2 seconds.
#define WAIT_FOR_CONDITION(expr, expected) \
    do { \
        const int step = 100; \
        for (int i = 0; i < 2000 && expr != expected; i+=step) { \
            QTest::qWait(step); \
        } \
    } while(0)

typedef QList<int> IntList;
Q_DECLARE_METATYPE(IntList)

typedef QList<bool> BoolList;
Q_DECLARE_METATYPE(BoolList)

class tst_QTableView : public QObject
{
    Q_OBJECT

public:
    tst_QTableView();
    virtual ~tst_QTableView();

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private slots:
    void getSetCheck();

    void noDelegate();
    void noModel();
    void emptyModel();

    void removeRows_data();
    void removeRows();

    void removeColumns_data();
    void removeColumns();

    void keyboardNavigation_data();
    void keyboardNavigation();

    void headerSections_data();
    void headerSections();

    void moveCursor_data();
    void moveCursor();

    void hideRows_data();
    void hideRows();

    void hideColumns_data();
    void hideColumns();

    void selection_data();
    void selection();

    void selectRow_data();
    void selectRow();

    void selectColumn_data();
    void selectColumn();

    void visualRect_data();
    void visualRect();

    void fetchMore();
    void setHeaders();

    void resizeRowsToContents_data();
    void resizeRowsToContents();

    void resizeColumnsToContents_data();
    void resizeColumnsToContents();

    void rowViewportPosition_data();
    void rowViewportPosition();

    void rowAt_data();
    void rowAt();

    void rowHeight_data();
    void rowHeight();

    void columnViewportPosition_data();
    void columnViewportPosition();

    void columnAt_data();
    void columnAt();

    void columnWidth_data();
    void columnWidth();

    void hiddenRow_data();
    void hiddenRow();

    void hiddenColumn_data();
    void hiddenColumn();

    void sortingEnabled_data();
    void sortingEnabled();

    void scrollTo_data();
    void scrollTo();

    void indexAt_data();
    void indexAt();

    void span_data();
    void span();
    void spans();
    void spans_data();

    void checkHeaderReset();
    void checkHeaderMinSize();

    void resizeToContents();

    void tabFocus();
    void bigModel();
    void selectionSignal();

    // task-specific tests:
    void task173773_updateVerticalHeader();
    void task227953_setRootIndex();

    void mouseWheel_data();
    void mouseWheel();

    void addColumnWhileEditing();
};

// Testing get/set functions
void tst_QTableView::getSetCheck()
{
    QTableView obj1;

    obj1.setSortingEnabled(false);
    QCOMPARE(false, obj1.isSortingEnabled());
    obj1.setSortingEnabled(true);
    QCOMPARE(true, obj1.isSortingEnabled());

    obj1.setShowGrid(false);
    QCOMPARE(false, obj1.showGrid());
    obj1.setShowGrid(true);
    QCOMPARE(true, obj1.showGrid());

    obj1.setGridStyle(Qt::NoPen);
    QCOMPARE(Qt::NoPen, obj1.gridStyle());
    obj1.setGridStyle(Qt::SolidLine);
    QCOMPARE(Qt::SolidLine, obj1.gridStyle());

    obj1.setRootIndex(QModelIndex());
    QCOMPARE(QModelIndex(), obj1.rootIndex());
    QStandardItemModel model(10, 10);
    obj1.setModel(&model);
    QModelIndex index = model.index(0, 0);
    obj1.setRootIndex(index);
    QCOMPARE(index, obj1.rootIndex());

    QHeaderView *var1 = new QHeaderView(Qt::Horizontal);
    obj1.setHorizontalHeader(var1);
    QCOMPARE(var1, obj1.horizontalHeader());
    obj1.setHorizontalHeader((QHeaderView *)0);
    QCOMPARE(var1, obj1.horizontalHeader());
    delete var1;

    QHeaderView *var2 = new QHeaderView(Qt::Vertical);
    obj1.setVerticalHeader(var2);
    QCOMPARE(var2, obj1.verticalHeader());
    obj1.setVerticalHeader((QHeaderView *)0);
    QCOMPARE(var2, obj1.verticalHeader());
    delete var2;

    QCOMPARE(obj1.isCornerButtonEnabled(), true);
    obj1.setCornerButtonEnabled(false);
    QCOMPARE(obj1.isCornerButtonEnabled(), false);
}

class QtTestTableModel: public QAbstractTableModel
{
    Q_OBJECT

signals:
    void invalidIndexEncountered() const;

public:
    QtTestTableModel(int rows = 0, int columns = 0, QObject *parent = 0)
        : QAbstractTableModel(parent),
          row_count(rows),
          column_count(columns),
          can_fetch_more(false),
          fetch_more_count(0) {}

    int rowCount(const QModelIndex& = QModelIndex()) const { return row_count; }
    int columnCount(const QModelIndex& = QModelIndex()) const { return column_count; }
    bool isEditable(const QModelIndex &) const { return true; }

    QVariant data(const QModelIndex &idx, int role) const
    {
        if (!idx.isValid() || idx.row() >= row_count || idx.column() >= column_count) {
            qWarning() << "Invalid modelIndex [%d,%d,%p]" << idx;
            emit invalidIndexEncountered();
            return QVariant();
        }

        if (role == Qt::DisplayRole || role == Qt::EditRole)
            return QString("[%1,%2,%3]").arg(idx.row()).arg(idx.column()).arg(0);

        return QVariant();
    }

    void removeLastRow()
    {
        beginRemoveRows(QModelIndex(), row_count - 1, row_count - 1);
        --row_count;
        endRemoveRows();
    }

    void removeAllRows()
    {
        beginRemoveRows(QModelIndex(), 0, row_count - 1);
        row_count = 0;
        endRemoveRows();
    }

    void removeLastColumn()
    {
        beginRemoveColumns(QModelIndex(), column_count - 1, column_count - 1);
        --column_count;
        endRemoveColumns();
    }

    void removeAllColumns()
    {
        beginRemoveColumns(QModelIndex(), 0, column_count - 1);
        column_count = 0;
        endRemoveColumns();
    }

    bool canFetchMore(const QModelIndex &) const
    {
        return can_fetch_more;
    }

    void fetchMore(const QModelIndex &)
    {
        ++fetch_more_count;
    }

    void reset()
    {
        QAbstractTableModel::reset();
    }

    int row_count;
    int column_count;
    bool can_fetch_more;
    int fetch_more_count;
};

class QtTestTableView : public QTableView
{
Q_OBJECT

public:
    QtTestTableView(QWidget *parent = 0) : QTableView(parent), checkSignalOrder(false), hasCurrentChanged(0), hasSelectionChanged(0) {}

    void setModel(QAbstractItemModel *model)
    {
        QTableView::setModel(model);
        connect(selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
                     this, SLOT(currentChanged(QModelIndex,QModelIndex)));
        connect(selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                     this, SLOT(itemSelectionChanged(QItemSelection,QItemSelection)));
    }

    enum CursorAction {
        MoveUp       = QAbstractItemView::MoveUp,
        MoveDown     = QAbstractItemView::MoveDown,
        MoveLeft     = QAbstractItemView::MoveLeft,
        MoveRight    = QAbstractItemView::MoveRight,
        MoveHome     = QAbstractItemView::MoveHome,
        MoveEnd      = QAbstractItemView::MoveEnd,
        MovePageUp   = QAbstractItemView::MovePageUp,
        MovePageDown = QAbstractItemView::MovePageDown,
        MoveNext     = QAbstractItemView::MoveNext,
        MovePrevious = QAbstractItemView::MovePrevious
    };

    QModelIndex moveCursor(QtTestTableView::CursorAction cursorAction,
                           Qt::KeyboardModifiers modifiers)
    {
        return QTableView::moveCursor((QAbstractItemView::CursorAction)cursorAction, modifiers);
    }

    int columnWidthHint(int column) const
    {
        return sizeHintForColumn(column);
    }

    int rowHeightHint(int row) const
    {
        return sizeHintForRow(row);
    }

    bool isIndexHidden(const QModelIndex &index) const
    {
        return QTableView::isIndexHidden(index);
    }

    void setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command)
    {
        QTableView::setSelection(rect, command);
    }

    QModelIndexList selectedIndexes() const
    {
        return QTableView::selectedIndexes();
    }

    bool checkSignalOrder;
    using QTableView::wheelEvent;
public slots:
    void currentChanged(QModelIndex , QModelIndex ) {
        hasCurrentChanged++;
        if (checkSignalOrder)
            QVERIFY(hasCurrentChanged > hasSelectionChanged);
    }

    void itemSelectionChanged(QItemSelection , QItemSelection ) {
        hasSelectionChanged++;
        if (checkSignalOrder)
            QVERIFY(hasCurrentChanged >= hasSelectionChanged);
    }
private:
    int hasCurrentChanged;
    int hasSelectionChanged;

};

class QtTestItemDelegate : public QItemDelegate
{
public:
    QSize sizeHint(const QStyleOptionViewItem&, const QModelIndex&) const
    {
        return hint;
    }

    QSize hint;
};

tst_QTableView::tst_QTableView()
{
}

tst_QTableView::~tst_QTableView()
{
}

void tst_QTableView::initTestCase()
{
#ifdef Q_OS_WINCE //disable magic for WindowsCE
    qApp->setAutoMaximizeThreshold(-1);
#endif
}

void tst_QTableView::cleanupTestCase()
{
}

void tst_QTableView::init()
{
}

void tst_QTableView::cleanup()
{
}

void tst_QTableView::noDelegate()
{
    QtTestTableModel model(3, 3);
    QTableView view;
    view.setModel(&model);
    view.setItemDelegate(0);
    view.show();
}

void tst_QTableView::noModel()
{
    QTableView view;
    view.show();
}

void tst_QTableView::emptyModel()
{
    QtTestTableModel model;
    QTableView view;
    QSignalSpy spy(&model, SIGNAL(invalidIndexEncountered()));
    view.setModel(&model);
    view.show();
    QCOMPARE(spy.count(), 0);
}

void tst_QTableView::removeRows_data()
{
    QTest::addColumn<int>("rowCount");
    QTest::addColumn<int>("columnCount");

    QTest::newRow("2x2") << 2 << 2;
    QTest::newRow("10x10") << 10  << 10;
}

void tst_QTableView::removeRows()
{
    QFETCH(int, rowCount);
    QFETCH(int, columnCount);

    QtTestTableModel model(rowCount, columnCount);
    QSignalSpy spy(&model, SIGNAL(invalidIndexEncountered()));

    QTableView view;
    view.setModel(&model);
    view.show();

    model.removeLastRow();
    QCOMPARE(spy.count(), 0);

    model.removeAllRows();
    QCOMPARE(spy.count(), 0);
}

void tst_QTableView::removeColumns_data()
{
    QTest::addColumn<int>("rowCount");
    QTest::addColumn<int>("columnCount");

    QTest::newRow("2x2") << 2 << 2;
    QTest::newRow("10x10") << 10  << 10;
}

void tst_QTableView::removeColumns()
{
    QFETCH(int, rowCount);
    QFETCH(int, columnCount);

    QtTestTableModel model(rowCount, columnCount);
    QSignalSpy spy(&model, SIGNAL(invalidIndexEncountered()));

    QTableView view;
    view.setModel(&model);
    view.show();

    model.removeLastColumn();
    QCOMPARE(spy.count(), 0);

    model.removeAllColumns();
    QCOMPARE(spy.count(), 0);
}

void tst_QTableView::keyboardNavigation_data()
{
    QTest::addColumn<int>("rowCount");
    QTest::addColumn<int>("columnCount");
    QTest::addColumn<bool>("tabKeyNavigation");
    QTest::addColumn<IntList>("keyPresses");

    QTest::newRow("16x16 model") << 16  << 16 << true
                                 << (IntList()
                                     << Qt::Key_Up
                                     << Qt::Key_Up
                                     << Qt::Key_Right
                                     << Qt::Key_Right
                                     << Qt::Key_Up
                                     << Qt::Key_Left
                                     << Qt::Key_Left
                                     << Qt::Key_Up
                                     << Qt::Key_Down
                                     << Qt::Key_Up
                                     << Qt::Key_Up
                                     << Qt::Key_Up
                                     << Qt::Key_Up
                                     << Qt::Key_Up
                                     << Qt::Key_Up
                                     << Qt::Key_Left
                                     << Qt::Key_Left
                                     << Qt::Key_Up
                                     << Qt::Key_Down
                                     << Qt::Key_Down
                                     << Qt::Key_Tab
                                     << Qt::Key_Backtab);


    QTest::newRow("no tab") << 8  << 8 <<  false
                                 << (IntList()
                                     << Qt::Key_Up
                                     << Qt::Key_Up
                                     << Qt::Key_Right
                                     << Qt::Key_Right
                                     << Qt::Key_Up
                                     << Qt::Key_Left
                                     << Qt::Key_Left
                                     << Qt::Key_Up
                                     << Qt::Key_Down
                                     << Qt::Key_Up
                                     << Qt::Key_Up
                                     << Qt::Key_Up
                                     << Qt::Key_Up
                                     << Qt::Key_Up
                                     << Qt::Key_Up
                                     << Qt::Key_Left
                                     << Qt::Key_Left
                                     << Qt::Key_Up
                                     << Qt::Key_Down
                                     << Qt::Key_Down
                                     << Qt::Key_Tab
                                     << Qt::Key_Backtab);
}

void tst_QTableView::keyboardNavigation()
{
    QFETCH(int, rowCount);
    QFETCH(int, columnCount);
    QFETCH(bool, tabKeyNavigation);
    QFETCH(IntList, keyPresses);

    QtTestTableModel model(rowCount, columnCount);
    QTableView view;
    view.setModel(&model);

    view.show();
    view.setTabKeyNavigation(tabKeyNavigation);

    QModelIndex index = model.index(rowCount - 1, columnCount - 1);
    view.setCurrentIndex(index);

    QApplication::instance()->processEvents();

    int row = rowCount - 1;
    int column = columnCount - 1;
    for (int i = 0; i < keyPresses.count(); ++i) {

        Qt::Key key = (Qt::Key)keyPresses.at(i);

        switch (key) {
        case Qt::Key_Up:
            row = qMax(0, row - 1);
            break;
        case Qt::Key_Down:
            row = qMin(rowCount - 1, row + 1);
            break;
        case Qt::Key_Backtab:
            if (!tabKeyNavigation)
                break;
        case Qt::Key_Left:
            column = qMax(0, column - 1);
            break;
        case Qt::Key_Tab:
            if (!tabKeyNavigation)
                break;
        case Qt::Key_Right:
            column = qMin(columnCount - 1, column + 1);
            break;
        default:
            break;
        }

        QTest::keyClick(&view, key);
        QApplication::instance()->processEvents();

        QModelIndex index = model.index(row, column);
        QCOMPARE(view.currentIndex(), index);
    }
}

void tst_QTableView::headerSections_data()
{
    QTest::addColumn<int>("rowCount");
    QTest::addColumn<int>("columnCount");
    QTest::addColumn<int>("row");
    QTest::addColumn<int>("column");
    QTest::addColumn<int>("rowHeight");
    QTest::addColumn<int>("columnWidth");

    QTest::newRow("") << 10 << 10 << 5 << 5 << 30 << 30;
}

void tst_QTableView::headerSections()
{
    QFETCH(int, rowCount);
    QFETCH(int, columnCount);
    QFETCH(int, row);
    QFETCH(int, column);
    QFETCH(int, rowHeight);
    QFETCH(int, columnWidth);

    QtTestTableModel model(rowCount, columnCount);

    QTableView view;
    QHeaderView *hheader = view.horizontalHeader();
    QHeaderView *vheader = view.verticalHeader();

    view.setModel(&model);
    view.show();

    hheader->doItemsLayout();
    vheader->doItemsLayout();

    QCOMPARE(hheader->count(), model.columnCount());
    QCOMPARE(vheader->count(), model.rowCount());

    view.setRowHeight(row, rowHeight);
    QCOMPARE(view.rowHeight(row), rowHeight);
    view.hideRow(row);
    QCOMPARE(view.rowHeight(row), 0);
    view.showRow(row);
    QCOMPARE(view.rowHeight(row), rowHeight);

    view.setColumnWidth(column, columnWidth);
    QCOMPARE(view.columnWidth(column), columnWidth);
    view.hideColumn(column);
    QCOMPARE(view.columnWidth(column), 0);
    view.showColumn(column);
    QCOMPARE(view.columnWidth(column), columnWidth);
}

typedef QPair<int,int> IntPair;
Q_DECLARE_METATYPE(IntPair)

void tst_QTableView::moveCursor_data()
{
    QTest::addColumn<int>("rowCount");
    QTest::addColumn<int>("columnCount");
    QTest::addColumn<int>("hideRow");
    QTest::addColumn<int>("hideColumn");

    QTest::addColumn<int>("startRow");
    QTest::addColumn<int>("startColumn");

    QTest::addColumn<int>("cursorMoveAction");
    QTest::addColumn<int>("modifier");

    QTest::addColumn<int>("expectedRow");
    QTest::addColumn<int>("expectedColumn");
    QTest::addColumn<IntPair>("moveRow");
    QTest::addColumn<IntPair>("moveColumn");

    // MoveRight
    QTest::newRow("MoveRight (0,0)")
        << 4 << 4 << -1 << -1
        << 0 << 0
        << int(QtTestTableView::MoveRight) << int(Qt::NoModifier)
        << 0 << 1 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MoveRight (3,0)")
        << 4 << 4 << -1 << -1
        << 3 << 0
        << int(QtTestTableView::MoveRight) << int(Qt::NoModifier)
        << 3 << 1 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MoveRight (3,3)")
        << 4 << 4 << -1 << -1
        << 3 << 3
        << int(QtTestTableView::MoveRight) << int(Qt::NoModifier)
        << 3 << 3 << IntPair(0,0) << IntPair(0,0); // ###

    QTest::newRow("MoveRight, hidden column 1 (0,0)")
        << 4 << 4 << -1 << 1
        << 0 << 0
        << int(QtTestTableView::MoveRight) << int(Qt::NoModifier)
        << 0 << 2 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MoveRight, hidden column 3 (0,2)")
        << 4 << 4 << -1 << 3
        << 0 << 2
        << int(QtTestTableView::MoveRight) << int(Qt::NoModifier)
        << 0 << 2 << IntPair(0,0) << IntPair(0,0); // ###

    // MoveNext should in addition wrap
    QTest::newRow("MoveNext (0,0)")
        << 4 << 4 << -1 << -1
        << 0 << 0
        << int(QtTestTableView::MoveNext) << int(Qt::NoModifier)
        << 0 << 1 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MoveNext (0,2)")
        << 4 << 4 << -1 << -1
        << 0 << 2
        << int(QtTestTableView::MoveNext) << int(Qt::NoModifier)
        << 0 << 3 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MoveNext, wrap (0,3)")
        << 4 << 4 << -1 << -1
        << 0 << 3
        << int(QtTestTableView::MoveNext) << int(Qt::NoModifier)
        << 1 << 0 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MoveNext, wrap (3,3)")
        << 4 << 4 << -1 << -1
        << 3 << 3
        << int(QtTestTableView::MoveNext) << int(Qt::NoModifier)
        << 0 << 0 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MoveNext, hidden column 1 (0,0)")
        << 4 << 4 << -1 << 1
        << 0 << 0
        << int(QtTestTableView::MoveNext) << int(Qt::NoModifier)
        << 0 << 2 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MoveNext, wrap, hidden column 3 (0,2)")
        << 4 << 4 << -1 << 3
        << 0 << 2
        << int(QtTestTableView::MoveNext) << int(Qt::NoModifier)
        << 1 << 0 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MoveNext, wrap, hidden column 3 (3,2)")
        << 4 << 4 << -1 << 3
        << 3 << 2
        << int(QtTestTableView::MoveNext) << int(Qt::NoModifier)
        << 0 << 0 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MoveNext, wrapy, wrapx, hidden column 3, hidden row 3 (2,2)")
        << 4 << 4 << 3 << 3
        << 2 << 2
        << int(QtTestTableView::MoveNext) << int(Qt::NoModifier)
        << 0 << 0 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MoveNext, wrap, hidden column 2, moved column from 3 to 0. (0,2)")
        << 4 << 4 << -1 << 2
        << 0 << 2
        << int(QtTestTableView::MoveNext) << int(Qt::NoModifier)
        << 1 << 0 << IntPair(0,0) << IntPair(3,0);

    // MoveLeft
    QTest::newRow("MoveLeft (0,0)")
        << 4 << 4 << -1 << -1
        << 0 << 0
        << int(QtTestTableView::MoveLeft) << int(Qt::NoModifier)
        << 0 << 0 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MoveLeft (0,3)")
        << 4 << 4 << -1 << -1
        << 0 << 3
        << int(QtTestTableView::MoveLeft) << int(Qt::NoModifier)
        << 0 << 2 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MoveLeft (1,0)")
        << 4 << 4 << -1 << -1
        << 1 << 0
        << int(QtTestTableView::MoveLeft) << int(Qt::NoModifier)
        << 1 << 0 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MoveLeft, hidden column 0 (0,2)")
        << 4 << 4 << -1 << 1
        << 0 << 2
        << int(QtTestTableView::MoveLeft) << int(Qt::NoModifier)
        << 0 << 0 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MoveLeft, hidden column 0 (0,1)")
        << 4 << 4 << -1 << 0
        << 0 << 1
        << int(QtTestTableView::MoveLeft) << int(Qt::NoModifier)
        << 0 << 1 << IntPair(0,0) << IntPair(0,0);

    // MovePrevious should in addition wrap
    QTest::newRow("MovePrevious (0,3)")
        << 4 << 4 << -1 << -1
        << 0 << 3
        << int(QtTestTableView::MovePrevious) << int(Qt::NoModifier)
        << 0 << 2 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MovePrevious (0,1)")
        << 4 << 4 << -1 << -1
        << 0 << 1
        << int(QtTestTableView::MovePrevious) << int(Qt::NoModifier)
        << 0 << 0 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MovePrevious, wrap (1,0)")
        << 4 << 4 << -1 << -1
        << 1 << 0
        << int(QtTestTableView::MovePrevious) << int(Qt::NoModifier)
        << 0 << 3 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MovePrevious, wrap, (0,0)")
        << 4 << 4 << -1 << -1
        << 0 << 0
        << int(QtTestTableView::MovePrevious) << int(Qt::NoModifier)
        << 3 << 3 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MovePrevious, hidden column 1 (0,2)")
        << 4 << 4 << -1 << 1
        << 0 << 2
        << int(QtTestTableView::MovePrevious) << int(Qt::NoModifier)
        << 0 << 0 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MovePrevious, wrap, hidden column 3 (0,2)")
        << 4 << 4 << -1 << 3
        << 0 << 2
        << int(QtTestTableView::MovePrevious) << int(Qt::NoModifier)
        << 0 << 1 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MovePrevious, wrapy, hidden column 0 (0,1)")
        << 4 << 4 << -1 << 0
        << 0 << 1
        << int(QtTestTableView::MovePrevious) << int(Qt::NoModifier)
        << 3 << 3 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MovePrevious, wrap, hidden column 0, hidden row 0 (1,1)")
        << 4 << 4 << 0 << 0
        << 1 << 1
        << int(QtTestTableView::MovePrevious) << int(Qt::NoModifier)
        << 3 << 3 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MovePrevious, wrap, hidden column 1, moved column from 0 to 3. (1,2)")
        << 4 << 4 << -1 << 1
        << 1 << 2
        << int(QtTestTableView::MovePrevious) << int(Qt::NoModifier)
        << 0 << 0 << IntPair(0,0) << IntPair(0,3);

    // MoveDown
    QTest::newRow("MoveDown (0,0)")
        << 4 << 4 << -1 << -1
        << 0 << 0
        << int(QtTestTableView::MoveDown) << int(Qt::NoModifier)
        << 1 << 0 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MoveDown (3,0)")
        << 4 << 4 << -1 << -1
        << 3 << 0
        << int(QtTestTableView::MoveDown) << int(Qt::NoModifier)
        << 3 << 0 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MoveDown (3,3)")
        << 4 << 4 << -1 << -1
        << 3 << 3
        << int(QtTestTableView::MoveDown) << int(Qt::NoModifier)
        << 3 << 3 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MoveDown, hidden row 1 (0,0)")
        << 4 << 4 << 1 << -1
        << 0 << 0
        << int(QtTestTableView::MoveDown) << int(Qt::NoModifier)
        << 2 << 0 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MoveDown, hidden row 3 (2,0)")
        << 4 << 4 << 3 << -1
        << 2 << 0
        << int(QtTestTableView::MoveDown) << int(Qt::NoModifier)
        << 2 << 0 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MoveDown, hidden row 0 hidden column 0 (0,0)")
        << 4 << 4 << 0 << 0
        << 0 << 0
        << int(QtTestTableView::MoveDown) << int(Qt::NoModifier)
        << 1 << 1 << IntPair(0,0) << IntPair(0,0);

    // MoveUp
    QTest::newRow("MoveUp (0,0)")
        << 4 << 4 << -1 << -1
        << 0 << 0
        << int(QtTestTableView::MoveUp) << int(Qt::NoModifier)
        << 0 << 0 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MoveUp (3, 0)")
        << 4 << 4 << -1 << -1
        << 3 << 0
        << int(QtTestTableView::MoveUp) << int(Qt::NoModifier)
        << 2 << 0 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MoveUp (0,1)")
        << 4 << 4 << -1 << -1
        << 0 << 1
        << int(QtTestTableView::MoveUp) << int(Qt::NoModifier)
        << 0 << 1 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MoveUp, hidden row 1 (2,0)")
        << 4 << 4 << 1 << -1
        << 2 << 0
        << int(QtTestTableView::MoveUp) << int(Qt::NoModifier)
        << 0 << 0 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MoveUp, hidden row (1,0)")
        << 4 << 4 << 0 << -1
        << 1 << 0
        << int(QtTestTableView::MoveUp) << int(Qt::NoModifier)
        << 1 << 0 << IntPair(0,0) << IntPair(0,0);

    // MoveHome
    QTest::newRow("MoveHome (0,0)")
        << 4 << 4 << -1 << -1
        << 0 << 0
        << int(QtTestTableView::MoveHome) << int(Qt::NoModifier)
        << 0 << 0 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MoveHome (3,3)")
        << 4 << 4 << -1 << -1
        << 3 << 3
        << int(QtTestTableView::MoveHome) << int(Qt::NoModifier)
        << 3 << 0 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MoveHome, hidden column 0 (3,3)")
        << 4 << 4 << -1 << 0
        << 3 << 3
        << int(QtTestTableView::MoveHome) << int(Qt::NoModifier)
        << 3 << 1 << IntPair(0,0) << IntPair(0,0);

    // Use Ctrl modifier
    QTest::newRow("MoveHome + Ctrl (0,0)")
        << 4 << 4 << -1 << -1
        << 0 << 0
        << int(QtTestTableView::MoveHome) << int(Qt::ControlModifier)
        << 0 << 0 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MoveHome + Ctrl (3,3)")
        << 4 << 4 << -1 << -1
        << 3 << 3
        << int(QtTestTableView::MoveHome) << int(Qt::ControlModifier)
        << 0 << 0 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MoveHome + Ctrl, hidden column 0, hidden row 0 (3,3)")
        << 4 << 4 << 0 << 0
        << 3 << 3
        << int(QtTestTableView::MoveHome) << int(Qt::ControlModifier)
        << 1 << 1 << IntPair(0,0) << IntPair(0,0);

    // MoveEnd
    QTest::newRow("MoveEnd (0,0)")
        << 4 << 4 << -1 << -1
        << 0 << 0
        << int(QtTestTableView::MoveEnd) << int(Qt::NoModifier)
        << 0 << 3 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MoveEnd (3,3)")
        << 4 << 4 << -1 << -1
        << 3 << 3
        << int(QtTestTableView::MoveEnd) << int(Qt::NoModifier)
        << 3 << 3 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MoveEnd, hidden column (0,0)")
        << 4 << 4 << -1 << 3
        << 0 << 0
        << int(QtTestTableView::MoveEnd) << int(Qt::NoModifier)
        << 0<< 2 << IntPair(0,0) << IntPair(0,0);

    // Use Ctrl modifier
    QTest::newRow("MoveEnd + Ctrl (0,0)")
        << 4 << 4 << -1 << -1
        << 0 << 0
        << int(QtTestTableView::MoveEnd) << int(Qt::ControlModifier)
        << 3 << 3 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MoveEnd + Ctrl (3,3)")
        << 4 << 4 << -1 << -1
        << 3 << 3
        << int(QtTestTableView::MoveEnd) << int(Qt::ControlModifier)
        << 3 << 3 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MoveEnd + Ctrl, hidden column 3 (0,0)")
        << 4 << 4 << -1 << 3
        << 0 << 0
        << int(QtTestTableView::MoveEnd) << int(Qt::ControlModifier)
        << 3 << 2 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MoveEnd + Ctrl, hidden column 3, hidden row 3 (0,0)")
        << 4 << 4 << 3 << 3
        << 0 << 0
        << int(QtTestTableView::MoveEnd) << int(Qt::ControlModifier)
        << 2 << 2 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MovePageUp (0,0)")
        << 4 << 4 << -1 << -1
        << 0 << 0
        << int(QtTestTableView::MovePageUp) << 0
        << 0 << 0 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MovePageUp (3,3)")
        << 4 << 4 << -1 << -1
        << 3 << 3
        << int(QtTestTableView::MovePageUp) << 0
        << 0 << 3 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MovePageDown (3, 3)")
        << 4 << 4 << -1 << -1
        << 3 << 3
        << int(QtTestTableView::MovePageDown) << 0
        << 3 << 3 << IntPair(0,0) << IntPair(0,0);

    QTest::newRow("MovePageDown (0, 3)")
        << 4 << 4 << -1 << -1
        << 0 << 3
        << int(QtTestTableView::MovePageDown) << 0
        << 3 << 3 << IntPair(0,0) << IntPair(0,0);
}

void tst_QTableView::moveCursor()
{
    QFETCH(int, rowCount);
    QFETCH(int, columnCount);
    QFETCH(int, hideRow);
    QFETCH(int, hideColumn);
    QFETCH(int, startRow);
    QFETCH(int, startColumn);
    QFETCH(int, cursorMoveAction);
    QFETCH(int, modifier);
    QFETCH(int, expectedRow);
    QFETCH(int, expectedColumn);
    QFETCH(IntPair, moveRow);
    QFETCH(IntPair, moveColumn);

    QtTestTableModel model(rowCount, columnCount);
    QtTestTableView view;

    view.setModel(&model);
    view.hideRow(hideRow);
    view.hideColumn(hideColumn);
    if (moveColumn.first != moveColumn.second)
        view.horizontalHeader()->moveSection(moveColumn.first, moveColumn.second);
    if (moveRow.first != moveRow.second)
        view.verticalHeader()->moveSection(moveRow.first, moveRow.second);

    view.show();

    QModelIndex index = model.index(startRow, startColumn);
    view.setCurrentIndex(index);

    QModelIndex newIndex = view.moveCursor((QtTestTableView::CursorAction)cursorMoveAction,
                                           (Qt::KeyboardModifiers)modifier);
    // expected fails, task 119433
    if(newIndex.row() == -1)
        return;
    QCOMPARE(newIndex.row(), expectedRow);
    QCOMPARE(newIndex.column(), expectedColumn);
}

void tst_QTableView::hideRows_data()
{
    QTest::addColumn<int>("rowCount");
    QTest::addColumn<int>("columnCount");
    QTest::addColumn<int>("showRow"); // hide, then show
    QTest::addColumn<int>("hideRow"); // hide only
    QTest::addColumn<int>("row");
    QTest::addColumn<int>("column");
    QTest::addColumn<int>("rowSpan");
    QTest::addColumn<int>("columnSpan");

    QTest::newRow("show row 0, hide row 3, no span")
      << 10 << 10
      << 0
      << 3
      << -1 << -1
      << 1 << 1;

    QTest::newRow("show row 0, hide row 3, span")
      << 10 << 10
      << 0
      << 3
      << 0 << 0
      << 3 << 2;
}

void tst_QTableView::hideRows()
{
    QFETCH(int, rowCount);
    QFETCH(int, columnCount);
    QFETCH(int, showRow);
    QFETCH(int, hideRow);
    QFETCH(int, row);
    QFETCH(int, column);
    QFETCH(int, rowSpan);
    QFETCH(int, columnSpan);

    QtTestTableModel model(rowCount, columnCount);
    QTableView view;

    view.setModel(&model);
    view.setSpan(row, column, rowSpan, columnSpan);

    view.hideRow(showRow);
    QVERIFY(view.isRowHidden(showRow));

    view.hideRow(hideRow);
    QVERIFY(view.isRowHidden(hideRow));

    view.showRow(showRow);
    QVERIFY(!view.isRowHidden(showRow));
    QVERIFY(view.isRowHidden(hideRow));
}

void tst_QTableView::hideColumns_data()
{
    QTest::addColumn<int>("rowCount");
    QTest::addColumn<int>("columnCount");
    QTest::addColumn<int>("showColumn"); // hide, then show
    QTest::addColumn<int>("hideColumn"); // hide only
    QTest::addColumn<int>("row");
    QTest::addColumn<int>("column");
    QTest::addColumn<int>("rowSpan");
    QTest::addColumn<int>("columnSpan");

    QTest::newRow("show col 0, hide col 3, no span")
      << 10 << 10
      << 0
      << 3
      << -1 << -1
      << 1 << 1;

    QTest::newRow("show col 0, hide col 3, span")
      << 10 << 10
      << 0
      << 3
      << 0 << 0
      << 3 << 2;
}

void tst_QTableView::hideColumns()
{
    QFETCH(int, rowCount);
    QFETCH(int, columnCount);
    QFETCH(int, showColumn);
    QFETCH(int, hideColumn);
    QFETCH(int, row);
    QFETCH(int, column);
    QFETCH(int, rowSpan);
    QFETCH(int, columnSpan);

    QtTestTableModel model(rowCount, columnCount);

    QTableView view;
    view.setModel(&model);
    view.setSpan(row, column, rowSpan, columnSpan);

    view.hideColumn(showColumn);
    QVERIFY(view.isColumnHidden(showColumn));

    view.hideColumn(hideColumn);
    QVERIFY(view.isColumnHidden(hideColumn));

    view.showColumn(showColumn);
    QVERIFY(!view.isColumnHidden(showColumn));
    QVERIFY(view.isColumnHidden(hideColumn));
}

void tst_QTableView::selection_data()
{
    QTest::addColumn<int>("rowCount");
    QTest::addColumn<int>("columnCount");
    QTest::addColumn<int>("row");
    QTest::addColumn<int>("column");
    QTest::addColumn<int>("rowSpan");
    QTest::addColumn<int>("columnSpan");
    QTest::addColumn<int>("hideRow");
    QTest::addColumn<int>("hideColumn");
    QTest::addColumn<int>("moveRowFrom");
    QTest::addColumn<int>("moveRowTo");
    QTest::addColumn<int>("moveColumnFrom");
    QTest::addColumn<int>("moveColumnTo");
    QTest::addColumn<int>("rowHeight");
    QTest::addColumn<int>("columnWidth");
    QTest::addColumn<int>("x");
    QTest::addColumn<int>("y");
    QTest::addColumn<int>("width");
    QTest::addColumn<int>("height");
    QTest::addColumn<int>("command");
    QTest::addColumn<int>("selectedCount"); // ### make this more detailed

    QTest::newRow("no span, no hidden, no moved, 3x3 select")
      << 10 << 10                          // dim
      << -1 << -1                          // pos
      << 1 << 1                            // span
      << -1 << -1                          // hide
      << -1 << -1                          // move row
      << -1 << -1                          // move col
      << 40 << 40                          // cell size
      << 20 << 20 << 80 << 80              // rect
      << int(QItemSelectionModel::Select)  // command
      << 9;                                // selected count

    QTest::newRow("row span, no hidden, no moved, 3x3 select")
      << 10 << 10                          // dim
      << 1 << 1                            // pos
      << 2 << 1                            // span
      << -1 << -1                          // hide
      << -1 << -1                          // move row
      << -1 << -1                          // move col
      << 40 << 40                          // cell size
      << 20 << 20 << 80 << 80              // rect
      << int(QItemSelectionModel::Select)  // command
      << 8;                                // selected count

    QTest::newRow("col span, no hidden, no moved, 3x3 select")
      << 10 << 10                          // dim
      << 1 << 1                            // pos
      << 1 << 2                            // span
      << -1 << -1                          // hide
      << -1 << -1                          // move row
      << -1 << -1                          // move col
      << 40 << 40                          // cell size
      << 20 << 20 << 80 << 80              // rect
      << int(QItemSelectionModel::Select)  // command
      << 8;                                // selected count

    QTest::newRow("no span, row hidden, no moved, 3x3 select")
      << 10 << 10                          // dim
      << -1 << -1                          // pos
      << 1 << 1                            // span
      << 1 << -1                           // hide
      << -1 << -1                          // move row
      << -1 << -1                          // move col
      << 40 << 40                          // cell size
      << 20 << 20 << 80 << 80              // rect
      << int(QItemSelectionModel::Select)  // command
      << 9;                                // selected count

    QTest::newRow("no span, col hidden, no moved, 3x3 select")
      << 10 << 10                          // dim
      << -1 << -1                          // pos
      << 1 << 1                            // span
      << -1 << 1                           // hide
      << -1 << -1                          // move row
      << -1 << -1                          // move col
      << 40 << 40                          // cell size
      << 20 << 20 << 80 << 80              // rect
      << int(QItemSelectionModel::Select)  // command
      << 9;                                // selected count

    QTest::newRow("no span, no hidden, row moved, 3x3 select")
      << 10 << 10                          // dim
      << -1 << -1                          // pos
      << 1 << 1                            // span
      << -1 << -1                          // hide
      << 1 << 3                            // move row
      << -1 << -1                          // move col
      << 40 << 40                          // cell size
      << 20 << 20 << 80 << 80              // rect
      << int(QItemSelectionModel::Select)  // command
      << 9;                                // selected count

    QTest::newRow("no span, no hidden, col moved, 3x3 select")
      << 10 << 10                          // dim
      << -1 << -1                          // pos
      << 1 << 1                            // span
      << -1 << -1                          // hide
      << -1 << -1                          // move row
      << 1 << 3                            // move col
      << 40 << 40                          // cell size
      << 20 << 20 << 80 << 80              // rect
      << int(QItemSelectionModel::Select)  // command
      << 9;                                // selected count
}

void tst_QTableView::selection()
{
    QFETCH(int, rowCount);
    QFETCH(int, columnCount);
    QFETCH(int, row);
    QFETCH(int, column);
    QFETCH(int, rowSpan);
    QFETCH(int, columnSpan);
    QFETCH(int, hideRow);
    QFETCH(int, hideColumn);
    QFETCH(int, moveRowFrom);
    QFETCH(int, moveRowTo);
    QFETCH(int, moveColumnFrom);
    QFETCH(int, moveColumnTo);
    QFETCH(int, rowHeight);
    QFETCH(int, columnWidth);
    QFETCH(int, x);
    QFETCH(int, y);
    QFETCH(int, width);
    QFETCH(int, height);
    QFETCH(int, command);
    QFETCH(int, selectedCount);

    QtTestTableModel model(rowCount, columnCount);

    QtTestTableView view;
    view.show();
    view.setModel(&model);

    view.setSpan(row, column, rowSpan, columnSpan);

    view.hideRow(hideRow);
    view.hideColumn(hideColumn);

    view.verticalHeader()->moveSection(moveRowFrom, moveRowTo);
    view.horizontalHeader()->moveSection(moveColumnFrom, moveColumnTo);

    for (int r = 0; r < rowCount; ++r)
        view.setRowHeight(r, rowHeight);
    for (int c = 0; c < columnCount; ++c)
        view.setColumnWidth(c, columnWidth);

    view.setSelection(QRect(x, y, width, height),
		      QItemSelectionModel::SelectionFlags(command));

    QCOMPARE(view.selectedIndexes().count(), selectedCount);
}

void tst_QTableView::selectRow_data()
{
    QTest::addColumn<int>("rowCount");
    QTest::addColumn<int>("columnCount");
    QTest::addColumn<int>("row");
    QTest::addColumn<int>("mode");
    QTest::addColumn<int>("behavior");
    QTest::addColumn<int>("selectedItems");

    QTest::newRow("SingleSelection and SelectItems")
        << 10 << 10
        << 0
        << (int)QAbstractItemView::SingleSelection
        << (int)QAbstractItemView::SelectItems
        << 0;

    QTest::newRow("SingleSelection and SelectRows")
        << 10 << 10
        << 0
        << (int)QAbstractItemView::SingleSelection
        << (int)QAbstractItemView::SelectRows
        << 10;

    QTest::newRow("SingleSelection and SelectColumns")
        << 10 << 10
        << 0
        << (int)QAbstractItemView::SingleSelection
        << (int)QAbstractItemView::SelectColumns
        << 0;

    QTest::newRow("MultiSelection and SelectItems")
        << 10 << 10
        << 0
        << (int)QAbstractItemView::MultiSelection
        << (int)QAbstractItemView::SelectItems
        << 10;

    QTest::newRow("MultiSelection and SelectRows")
        << 10 << 10
        << 0
        << (int)QAbstractItemView::MultiSelection
        << (int)QAbstractItemView::SelectRows
        << 10;

    QTest::newRow("MultiSelection and SelectColumns")
        << 10 << 10
        << 0
        << (int)QAbstractItemView::MultiSelection
        << (int)QAbstractItemView::SelectColumns
        << 0;

    QTest::newRow("ExtendedSelection and SelectItems")
        << 10 << 10
        << 0
        << (int)QAbstractItemView::ExtendedSelection
        << (int)QAbstractItemView::SelectItems
        << 10;

    QTest::newRow("ExtendedSelection and SelectRows")
        << 10 << 10
        << 0
        << (int)QAbstractItemView::ExtendedSelection
        << (int)QAbstractItemView::SelectRows
        << 10;

    QTest::newRow("ExtendedSelection and SelectColumns")
        << 10 << 10
        << 0
        << (int)QAbstractItemView::ExtendedSelection
        << (int)QAbstractItemView::SelectColumns
        << 0;

    QTest::newRow("ContiguousSelection and SelectItems")
        << 10 << 10
        << 0
        << (int)QAbstractItemView::ContiguousSelection
        << (int)QAbstractItemView::SelectItems
        << 10;

    QTest::newRow("ContiguousSelection and SelectRows")
        << 10 << 10
        << 0
        << (int)QAbstractItemView::ContiguousSelection
        << (int)QAbstractItemView::SelectRows
        << 10;

    QTest::newRow("ContiguousSelection and SelectColumns")
        << 10 << 10
        << 0
        << (int)QAbstractItemView::ContiguousSelection
        << (int)QAbstractItemView::SelectColumns
        << 0;
}

void tst_QTableView::selectRow()
{
    QFETCH(int, rowCount);
    QFETCH(int, columnCount);
    QFETCH(int, row);
    QFETCH(int, mode);
    QFETCH(int, behavior);
    QFETCH(int, selectedItems);

    QtTestTableModel model(rowCount, columnCount);
    QTableView view;

    view.setModel(&model);
    view.setSelectionMode((QAbstractItemView::SelectionMode)mode);
    view.setSelectionBehavior((QAbstractItemView::SelectionBehavior)behavior);

    QCOMPARE(view.selectionModel()->selectedIndexes().count(), 0);

    view.selectRow(row);

    //test we have 10 items selected
    QCOMPARE(view.selectionModel()->selectedIndexes().count(), selectedItems);
    //test that all 10 items are in the same row
    for (int i = 0; selectedItems > 0 && i < rowCount; ++i)
        QCOMPARE(view.selectionModel()->selectedIndexes().at(i).row(), row);
}

void tst_QTableView::selectColumn_data()
{
    QTest::addColumn<int>("rowCount");
    QTest::addColumn<int>("columnCount");
    QTest::addColumn<int>("column");
    QTest::addColumn<int>("mode");
    QTest::addColumn<int>("behavior");
    QTest::addColumn<int>("selectedItems");

        QTest::newRow("SingleSelection and SelectItems")
            << 10 << 10
            << 0
            << (int)QAbstractItemView::SingleSelection
            << (int)QAbstractItemView::SelectItems
            << 0;

        QTest::newRow("SingleSelection and SelectRows")
            << 10 << 10
            << 0
            << (int)QAbstractItemView::SingleSelection
            << (int)QAbstractItemView::SelectRows
            << 0;

        QTest::newRow("SingleSelection and SelectColumns")
            << 10 << 10
            << 0
            << (int)QAbstractItemView::SingleSelection
            << (int)QAbstractItemView::SelectColumns
            << 10;

        QTest::newRow("MultiSelection and SelectItems")
            << 10 << 10
            << 0
            << (int)QAbstractItemView::MultiSelection
            << (int)QAbstractItemView::SelectItems
            << 10;

        QTest::newRow("MultiSelection and SelectRows")
            << 10 << 10
            << 0
            << (int)QAbstractItemView::MultiSelection
            << (int)QAbstractItemView::SelectRows
            << 0;

        QTest::newRow("MultiSelection and SelectColumns")
            << 10 << 10
            << 0
            << (int)QAbstractItemView::MultiSelection
            << (int)QAbstractItemView::SelectColumns
            << 10;

        QTest::newRow("ExtendedSelection and SelectItems")
            << 10 << 10
            << 0
            << (int)QAbstractItemView::ExtendedSelection
            << (int)QAbstractItemView::SelectItems
            << 10;

        QTest::newRow("ExtendedSelection and SelectRows")
            << 10 << 10
            << 0
            << (int)QAbstractItemView::ExtendedSelection
            << (int)QAbstractItemView::SelectRows
            << 0;

        QTest::newRow("ExtendedSelection and SelectColumns")
            << 10 << 10
            << 0
            << (int)QAbstractItemView::ExtendedSelection
            << (int)QAbstractItemView::SelectColumns
            << 10;

        QTest::newRow("ContiguousSelection and SelectItems")
            << 10 << 10
            << 0
            << (int)QAbstractItemView::ContiguousSelection
            << (int)QAbstractItemView::SelectItems
            << 10;

        QTest::newRow("ContiguousSelection and SelectRows")
            << 10 << 10
            << 0
            << (int)QAbstractItemView::ContiguousSelection
            << (int)QAbstractItemView::SelectRows
            << 0;

        QTest::newRow("ContiguousSelection and SelectColumns")
            << 10 << 10
            << 0
            << (int)QAbstractItemView::ContiguousSelection
            << (int)QAbstractItemView::SelectColumns
            << 10;
}

void tst_QTableView::selectColumn()
{
    QFETCH(int, rowCount);
    QFETCH(int, columnCount);
    QFETCH(int, column);
    QFETCH(int, mode);
    QFETCH(int, behavior);
    QFETCH(int, selectedItems);

    QtTestTableModel model(rowCount, columnCount);

    QTableView view;
    view.setModel(&model);
    view.setSelectionMode((QAbstractItemView::SelectionMode)mode);
    view.setSelectionBehavior((QAbstractItemView::SelectionBehavior)behavior);

    QCOMPARE(view.selectionModel()->selectedIndexes().count(), 0);

    view.selectColumn(column);

    QCOMPARE(view.selectionModel()->selectedIndexes().count(), selectedItems);
    for (int i = 0; selectedItems > 0 && i < columnCount; ++i)
        QCOMPARE(view.selectionModel()->selectedIndexes().at(i).column(), column);
}

Q_DECLARE_METATYPE(QRect)
void tst_QTableView::visualRect_data()
{
    QTest::addColumn<int>("rowCount");
    QTest::addColumn<int>("columnCount");
    QTest::addColumn<int>("hideRow");
    QTest::addColumn<int>("hideColumn");
    QTest::addColumn<int>("row");
    QTest::addColumn<int>("column");
    QTest::addColumn<int>("rowHeight");
    QTest::addColumn<int>("columnWidth");
    QTest::addColumn<QRect>("expectedRect");

    QTest::newRow("(0,0)")
        << 10 << 10
        << -1 << -1
        << 0 << 0
        << 20 << 30
        << QRect(0, 0, 29, 19);

    QTest::newRow("(0,0) hidden row")
        << 10 << 10
        << 0 << -1
        << 0 << 0
        << 20 << 30
        << QRect();

    QTest::newRow("(0,0) hidden column")
        << 10 << 10
        << -1 << 0
        << 0 << 0
        << 20 << 30
        << QRect();

    QTest::newRow("(0,0) hidden row and column")
        << 10 << 10
        << 0 << 0
        << 0 << 0
        << 20 << 30
        << QRect();

    QTest::newRow("(0,0) out of bounds")
        << 10 << 10
        << -1 << -1
        << 20 << 20
        << 20 << 30
        << QRect();

    QTest::newRow("(5,5), hidden row")
        << 10 << 10
        << 5 << -1
        << 5 << 5
        << 20 << 30
        << QRect();

    QTest::newRow("(9,9)")
        << 10 << 10
        << -1 << -1
        << 9 << 9
        << 20 << 30
        << QRect(30*9, 20*9, 29, 19);
}

void tst_QTableView::visualRect()
{
    QFETCH(int, rowCount);
    QFETCH(int, columnCount);
    QFETCH(int, hideRow);
    QFETCH(int, hideColumn);
    QFETCH(int, row);
    QFETCH(int, column);
    QFETCH(int, rowHeight);
    QFETCH(int, columnWidth);
    QFETCH(QRect, expectedRect);

    QtTestTableModel model(rowCount, columnCount);

    QTableView view;
    view.setModel(&model);
    // Make sure that it has 1 pixel between each cell.
    view.setGridStyle(Qt::SolidLine);
    for (int i = 0; i < view.verticalHeader()->count(); ++i)
        view.verticalHeader()->resizeSection(i, rowHeight);
    for (int i = 0; i < view.horizontalHeader()->count(); ++i)
        view.horizontalHeader()->resizeSection(i, columnWidth);

    view.hideRow(hideRow);
    view.hideColumn(hideColumn);

    QRect rect = view.visualRect(model.index(row, column));
    QCOMPARE(rect, expectedRect);
}

void tst_QTableView::fetchMore()
{
    QtTestTableModel model(64, 64);

    model.can_fetch_more = true;

    QTableView view;
    view.setModel(&model);
    view.show();

    QCOMPARE(model.fetch_more_count, 0);
    view.verticalScrollBar()->setValue(view.verticalScrollBar()->maximum());
    QVERIFY(model.fetch_more_count > 0);

    model.fetch_more_count = 0; //reset
    view.scrollToTop();
    QCOMPARE(model.fetch_more_count, 0);

    view.scrollToBottom();
    QVERIFY(model.fetch_more_count > 0);

    model.fetch_more_count = 0; //reset
    view.scrollToTop();
    view.setCurrentIndex(model.index(0, 0));
    QCOMPARE(model.fetch_more_count, 0);

    for (int i = 0; i < 64; ++i)
        QTest::keyClick(&view, Qt::Key_Down);
    QCOMPARE(view.currentIndex(), model.index(63, 0));
    QVERIFY(model.fetch_more_count > 0);
}

void tst_QTableView::setHeaders()
{
    QTableView view;

    // Make sure we don't delete ourselves
    view.setVerticalHeader(view.verticalHeader());
    view.verticalHeader()->count();
    view.setHorizontalHeader(view.horizontalHeader());
    view.horizontalHeader()->count();

    // Try passing around a header without it being deleted
    QTableView view2;
    view2.setVerticalHeader(view.verticalHeader());
    view2.setHorizontalHeader(view.horizontalHeader());
    view.setHorizontalHeader(new QHeaderView(Qt::Horizontal));
    view.setVerticalHeader(new QHeaderView(Qt::Vertical));
    view2.verticalHeader()->count();
    view2.horizontalHeader()->count();

}

void tst_QTableView::resizeRowsToContents_data()
{
    QTest::addColumn<int>("rowCount");
    QTest::addColumn<int>("columnCount");
    QTest::addColumn<bool>("showGrid");
    QTest::addColumn<int>("cellWidth");
    QTest::addColumn<int>("cellHeight");
    QTest::addColumn<int>("rowHeight");
    QTest::addColumn<int>("columnWidth");

    QTest::newRow("10x10 grid shown 40x40")
        << 10 << 10 << false << 40 << 40 << 40 << 40;

    QTest::newRow("10x10 grid not shown 40x40")
        << 10 << 10 << true << 40 << 40 << 41 << 41;
}

void tst_QTableView::resizeRowsToContents()
{
    QFETCH(int, rowCount);
    QFETCH(int, columnCount);
    QFETCH(bool, showGrid);
    QFETCH(int, cellWidth);
    QFETCH(int, cellHeight);
    QFETCH(int, rowHeight);
    QFETCH(int, columnWidth);
    Q_UNUSED(columnWidth);

    QtTestTableModel model(rowCount, columnCount);
    QtTestTableView view;
    QtTestItemDelegate delegate;

    view.setModel(&model);
    view.setItemDelegate(&delegate);
    view.setShowGrid(showGrid); // the grid will add to the row height

    delegate.hint = QSize(cellWidth, cellHeight);

    QSignalSpy resizedSpy(view.verticalHeader(), SIGNAL(sectionResized(int, int, int)));
    view.resizeRowsToContents();

    QCOMPARE(resizedSpy.count(), model.rowCount());
    for (int r = 0; r < model.rowCount(); ++r)
        QCOMPARE(view.rowHeight(r), rowHeight);
}

void tst_QTableView::resizeColumnsToContents_data()
{
    QTest::addColumn<int>("rowCount");
    QTest::addColumn<int>("columnCount");
    QTest::addColumn<bool>("showGrid");
    QTest::addColumn<int>("cellWidth");
    QTest::addColumn<int>("cellHeight");
    QTest::addColumn<int>("rowHeight");
    QTest::addColumn<int>("columnWidth");

    QTest::newRow("10x10 grid shown 40x40")
        << 10 << 10 << false << 40 << 40 << 40 << 40;

    QTest::newRow("10x10 grid not shown 40x40")
        << 10 << 10 << true << 40 << 40 << 41 << 41;
}

void tst_QTableView::resizeColumnsToContents()
{
    QFETCH(int, rowCount);
    QFETCH(int, columnCount);
    QFETCH(bool, showGrid);
    QFETCH(int, cellWidth);
    QFETCH(int, cellHeight);
    QFETCH(int, rowHeight);
    QFETCH(int, columnWidth);
    Q_UNUSED(rowHeight);

    QtTestTableModel model(rowCount, columnCount);
    QtTestTableView view;
    QtTestItemDelegate delegate;

    view.setModel(&model);
    view.setItemDelegate(&delegate);
    view.setShowGrid(showGrid); // the grid will add to the row height

    delegate.hint = QSize(cellWidth, cellHeight);

    QSignalSpy resizedSpy(view.horizontalHeader(), SIGNAL(sectionResized(int, int, int)));
    view.resizeColumnsToContents();

    QCOMPARE(resizedSpy.count(), model.columnCount());
    for (int c = 0; c < model.columnCount(); ++c)
        QCOMPARE(view.columnWidth(c), columnWidth);
}

void tst_QTableView::rowViewportPosition_data()
{
    QTest::addColumn<int>("rowCount");
    QTest::addColumn<int>("rowHeight");
    QTest::addColumn<int>("row");
    QTest::addColumn<int>("verticalScrollMode");
    QTest::addColumn<int>("verticalScrollValue");
    QTest::addColumn<int>("rowViewportPosition");

    QTest::newRow("row 0, scroll per item 0")
        << 10 << 40 << 0 << int(QAbstractItemView::ScrollPerItem) << 0 << 0;

    QTest::newRow("row 1, scroll per item, 0")
        << 10 << 40 << 1 << int(QAbstractItemView::ScrollPerItem) << 0 << 1 * 40;

    QTest::newRow("row 1, scroll per item, 1")
        << 10 << 40 << 1 << int(QAbstractItemView::ScrollPerItem) << 1 << 0;

    QTest::newRow("row 5, scroll per item, 0")
        << 10 << 40 << 5 << int(QAbstractItemView::ScrollPerItem) << 0 << 5 * 40;

    QTest::newRow("row 5, scroll per item, 5")
        << 10 << 40 << 5 << int(QAbstractItemView::ScrollPerItem) << 5 << 0;

    QTest::newRow("row 9, scroll per item, 0")
        << 10 << 40 << 9 << int(QAbstractItemView::ScrollPerItem) << 0 << 9 * 40;

    QTest::newRow("row 9, scroll per item, 5")
        << 10 << 40 << 9 << int(QAbstractItemView::ScrollPerItem) << 5 << 4 * 40;

    QTest::newRow("row 0, scroll per pixel 0")
        << 10 << 40 << 0 << int(QAbstractItemView::ScrollPerPixel) << 0 << 0;

    QTest::newRow("row 1, scroll per pixel, 0")
        << 10 << 40 << 1 << int(QAbstractItemView::ScrollPerPixel) << 0 << 1 * 40;

    QTest::newRow("row 1, scroll per pixel, 1")
        << 10 << 40 << 1 << int(QAbstractItemView::ScrollPerPixel) << 1 * 40 << 0;

    QTest::newRow("row 5, scroll per pixel, 0")
        << 10 << 40 << 5 << int(QAbstractItemView::ScrollPerPixel) << 0 << 5 * 40;

    QTest::newRow("row 5, scroll per pixel, 5")
        << 10 << 40 << 5 << int(QAbstractItemView::ScrollPerPixel) << 5 * 40 << 0;

    QTest::newRow("row 9, scroll per pixel, 0")
        << 10 << 40 << 9 << int(QAbstractItemView::ScrollPerPixel) << 0 << 9 * 40;

    QTest::newRow("row 9, scroll per pixel, 5")
        << 10 << 40 << 9 << int(QAbstractItemView::ScrollPerPixel) << 5 * 40 << 4 * 40;
}

void tst_QTableView::rowViewportPosition()
{
    QFETCH(int, rowCount);
    QFETCH(int, rowHeight);
    QFETCH(int, row);
    QFETCH(int, verticalScrollMode);
    QFETCH(int, verticalScrollValue);
    QFETCH(int, rowViewportPosition);

    QtTestTableModel model(rowCount, 1);
    QtTestTableView view;
    view.resize(100, 2 * rowHeight);
    view.show();

    view.setModel(&model);
    for (int r = 0; r < rowCount; ++r)
        view.setRowHeight(r, rowHeight);

    view.setVerticalScrollMode((QAbstractItemView::ScrollMode)verticalScrollMode);
    view.verticalScrollBar()->setValue(verticalScrollValue);

    QCOMPARE(view.rowViewportPosition(row), rowViewportPosition);
}

void tst_QTableView::rowAt_data()
{
    QTest::addColumn<int>("rowCount");
    QTest::addColumn<int>("rowHeight");
    QTest::addColumn<IntList>("hiddenRows");
    QTest::addColumn<int>("coordinate");
    QTest::addColumn<int>("row");

    QTest::newRow("row at 100") << 5 << 40 << IntList() << 100 << 2;
    QTest::newRow("row at 180") << 5 << 40 << IntList() << 180 << 4;
    QTest::newRow("row at 20")  << 5 << 40 << IntList() <<  20 << 0;

    // ### expand the dataset to include hidden rows
}

void tst_QTableView::rowAt()
{
    QFETCH(int, rowCount);
    QFETCH(int, rowHeight);
    QFETCH(IntList, hiddenRows);
    QFETCH(int, coordinate);
    QFETCH(int, row);

    QtTestTableModel model(rowCount, 1);
    QtTestTableView view;
    view.resize(100, 2 * rowHeight);

    view.setModel(&model);

    for (int r = 0; r < rowCount; ++r)
        view.setRowHeight(r, rowHeight);

    for (int i = 0; i < hiddenRows.count(); ++i)
        view.hideRow(hiddenRows.at(i));

    QCOMPARE(view.rowAt(coordinate), row);
}

void tst_QTableView::rowHeight_data()
{
    QTest::addColumn<int>("rowCount");
    QTest::addColumn<IntList>("rowHeights");
    QTest::addColumn<BoolList>("hiddenRows");

    QTest::newRow("increasing")
      << 5
      << (IntList() << 20 << 30 << 40 << 50 << 60)
      << (BoolList() << false << false << false << false << false);

    QTest::newRow("decreasing")
      << 5
      << (IntList() << 60 << 50 << 40 << 30 << 20)
      << (BoolList() << false << false << false << false << false);

    QTest::newRow("random")
      << 5
      << (IntList() << 87 << 34 << 68 << 91 << 27)
      << (BoolList() << false << false << false << false << false);

    // ### expand the dataset to include hidden rows
}

void tst_QTableView::rowHeight()
{
    QFETCH(int, rowCount);
    QFETCH(IntList, rowHeights);
    QFETCH(BoolList, hiddenRows);

    QtTestTableModel model(rowCount, 1);
    QtTestTableView view;

    view.setModel(&model);

    for (int r = 0; r < rowCount; ++r) {
        view.setRowHeight(r, rowHeights.at(r));
        view.setRowHidden(r, hiddenRows.at(r));
    }

    for (int r = 0; r < rowCount; ++r) {
        if (hiddenRows.at(r))
            QCOMPARE(view.rowHeight(r), 0);
        else
            QCOMPARE(view.rowHeight(r), rowHeights.at(r));
    }
}

void tst_QTableView::columnViewportPosition_data()
{
    QTest::addColumn<int>("columnCount");
    QTest::addColumn<int>("columnWidth");
    QTest::addColumn<int>("column");
    QTest::addColumn<int>("horizontalScrollMode");
    QTest::addColumn<int>("horizontalScrollValue");
    QTest::addColumn<int>("columnViewportPosition");

    QTest::newRow("column 0, scroll per item 0")
        << 10 << 40 << 0 << int(QAbstractItemView::ScrollPerItem) << 0 << 0;

    QTest::newRow("column 1, scroll per item, 0")
        << 10 << 40 << 1 << int(QAbstractItemView::ScrollPerItem) << 0 << 1 * 40;

    QTest::newRow("column 1, scroll per item, 1")
        << 10 << 40 << 1 << int(QAbstractItemView::ScrollPerItem) << 1 << 0;

    QTest::newRow("column 5, scroll per item, 0")
        << 10 << 40 << 5 << int(QAbstractItemView::ScrollPerItem) << 0 << 5 * 40;

    QTest::newRow("column 5, scroll per item, 5")
        << 10 << 40 << 5 << int(QAbstractItemView::ScrollPerItem) << 5 << 0;

    QTest::newRow("column 9, scroll per item, 0")
        << 10 << 40 << 9 << int(QAbstractItemView::ScrollPerItem) << 0 << 9 * 40;

    QTest::newRow("column 9, scroll per item, 5")
        << 10 << 40 << 9 << int(QAbstractItemView::ScrollPerItem) << 5 << 4 * 40;

    QTest::newRow("column 0, scroll per pixel 0")
        << 10 << 40 << 0 << int(QAbstractItemView::ScrollPerPixel) << 0 << 0;

    QTest::newRow("column 1, scroll per pixel 0")
        << 10 << 40 << 1 << int(QAbstractItemView::ScrollPerPixel) << 0 << 1 * 40;

    QTest::newRow("column 1, scroll per pixel 1")
        << 10 << 40 << 1 << int(QAbstractItemView::ScrollPerPixel) << 1 * 40 << 0;

    QTest::newRow("column 5, scroll per pixel 0")
        << 10 << 40 << 5 << int(QAbstractItemView::ScrollPerPixel) << 0 << 5 * 40;

    QTest::newRow("column 5, scroll per pixel 5")
        << 10 << 40 << 5 << int(QAbstractItemView::ScrollPerPixel) << 5 * 40 << 0;

    QTest::newRow("column 9, scroll per pixel 0")
        << 10 << 40 << 9 << int(QAbstractItemView::ScrollPerPixel) << 0 << 9 * 40;

    QTest::newRow("column 9, scroll per pixel 5")
        << 10 << 40 << 9 << int(QAbstractItemView::ScrollPerPixel) << 5 * 40 << 4 * 40;
}

void tst_QTableView::columnViewportPosition()
{
    QFETCH(int, columnCount);
    QFETCH(int, columnWidth);
    QFETCH(int, column);
    QFETCH(int, horizontalScrollMode);
    QFETCH(int, horizontalScrollValue);
    QFETCH(int, columnViewportPosition);

    QtTestTableModel model(1, columnCount);
    QtTestTableView view;
    view.resize(2 * columnWidth, 100);
    view.show();

    view.setModel(&model);
    for (int c = 0; c < columnCount; ++c)
        view.setColumnWidth(c, columnWidth);

    view.setHorizontalScrollMode((QAbstractItemView::ScrollMode)horizontalScrollMode);
    view.horizontalScrollBar()->setValue(horizontalScrollValue);

    QCOMPARE(view.columnViewportPosition(column), columnViewportPosition);
}

void tst_QTableView::columnAt_data()
{
    QTest::addColumn<int>("columnCount");
    QTest::addColumn<int>("columnWidth");
    QTest::addColumn<IntList>("hiddenColumns");
    QTest::addColumn<int>("coordinate");
    QTest::addColumn<int>("column");

    QTest::newRow("column at 100") << 5 << 40 << IntList() << 100 << 2;
    QTest::newRow("column at 180") << 5 << 40 << IntList() << 180 << 4;
    QTest::newRow("column at 20")  << 5 << 40 << IntList() <<  20 << 0;

    // ### expand the dataset to include hidden coumns
}

void tst_QTableView::columnAt()
{
    QFETCH(int, columnCount);
    QFETCH(int, columnWidth);
    QFETCH(IntList, hiddenColumns);
    QFETCH(int, coordinate);
    QFETCH(int, column);

    QtTestTableModel model(1, columnCount);
    QtTestTableView view;
    view.resize(2 * columnWidth, 100);

    view.setModel(&model);

    for (int c = 0; c < columnCount; ++c)
        view.setColumnWidth(c, columnWidth);

    for (int i = 0; i < hiddenColumns.count(); ++i)
        view.hideColumn(hiddenColumns.at(i));

    QCOMPARE(view.columnAt(coordinate), column);
}

void tst_QTableView::columnWidth_data()
{
    QTest::addColumn<int>("columnCount");
    QTest::addColumn<IntList>("columnWidths");
    QTest::addColumn<BoolList>("hiddenColumns");

    QTest::newRow("increasing")
      << 5
      << (IntList() << 20 << 30 << 40 << 50 << 60)
      << (BoolList() << false << false << false << false << false);

    QTest::newRow("decreasing")
      << 5
      << (IntList() << 60 << 50 << 40 << 30 << 20)
      << (BoolList() << false << false << false << false << false);

    QTest::newRow("random")
      << 5
      << (IntList() << 87 << 34 << 68 << 91 << 27)
      << (BoolList() << false << false << false << false << false);

    // ### expand the dataset to include hidden columns
}

void tst_QTableView::columnWidth()
{
    QFETCH(int, columnCount);
    QFETCH(IntList, columnWidths);
    QFETCH(BoolList, hiddenColumns);

    QtTestTableModel model(1, columnCount);
    QtTestTableView view;

    view.setModel(&model);

    for (int c = 0; c < columnCount; ++c) {
        view.setColumnWidth(c, columnWidths.at(c));
        view.setColumnHidden(c, hiddenColumns.at(c));
    }

    for (int c = 0; c < columnCount; ++c) {
        if (hiddenColumns.at(c))
            QCOMPARE(view.columnWidth(c), 0);
        else
            QCOMPARE(view.columnWidth(c), columnWidths.at(c));
    }
}

void tst_QTableView::hiddenRow_data()
{
    QTest::addColumn<int>("rowCount");
    QTest::addColumn<BoolList>("hiddenRows");

    QTest::newRow("first hidden")
      << 5 << (BoolList() << true << false << false << false << false);

    QTest::newRow("last hidden")
      << 5 << (BoolList() << false << false << false << false << true);

    QTest::newRow("none hidden")
      << 5 << (BoolList() << false << false << false << false << false);

    QTest::newRow("all hidden")
      << 5 << (BoolList() << true << true << true << true << true);
 }

void tst_QTableView::hiddenRow()
{
    QFETCH(int, rowCount);
    QFETCH(BoolList, hiddenRows);


    QtTestTableModel model(rowCount, 1);
    QtTestTableView view;

    view.setModel(&model);

    for (int r = 0; r < rowCount; ++r)
        QVERIFY(!view.isRowHidden(r));

    for (int r = 0; r < rowCount; ++r)
        view.setRowHidden(r, hiddenRows.at(r));

    for (int r = 0; r < rowCount; ++r)
        QCOMPARE(view.isRowHidden(r), hiddenRows.at(r));

    for (int r = 0; r < rowCount; ++r)
        view.setRowHidden(r, false);

    for (int r = 0; r < rowCount; ++r)
        QVERIFY(!view.isRowHidden(r));
}

void tst_QTableView::hiddenColumn_data()
{
    QTest::addColumn<int>("columnCount");
    QTest::addColumn<BoolList>("hiddenColumns");

    QTest::newRow("first hidden")
      << 5 << (BoolList() << true << false << false << false << false);

    QTest::newRow("last hidden")
      << 5 << (BoolList() << false << false << false << false << true);

    QTest::newRow("none hidden")
      << 5 << (BoolList() << false << false << false << false << false);

    QTest::newRow("all hidden")
      << 5 << (BoolList() << true << true << true << true << true);
}

void tst_QTableView::hiddenColumn()
{
    QFETCH(int, columnCount);
    QFETCH(BoolList, hiddenColumns);

    QtTestTableModel model(1, columnCount);
    QtTestTableView view;

    view.setModel(&model);

    for (int c = 0; c < columnCount; ++c)
        QVERIFY(!view.isColumnHidden(c));

    for (int c = 0; c < columnCount; ++c)
        view.setColumnHidden(c, hiddenColumns.at(c));

    for (int c = 0; c < columnCount; ++c)
        QCOMPARE(view.isColumnHidden(c), hiddenColumns.at(c));

    for (int c = 0; c < columnCount; ++c)
        view.setColumnHidden(c, false);

    for (int c = 0; c < columnCount; ++c)
        QVERIFY(!view.isColumnHidden(c));
}

void tst_QTableView::sortingEnabled_data()
{
//    QTest::addColumn<int>("columnCount");
}

void tst_QTableView::sortingEnabled()
{
//    QFETCH(int, columnCount);
}

void tst_QTableView::scrollTo_data()
{
    QTest::addColumn<int>("verticalScrollMode");
    QTest::addColumn<int>("horizontalScrollMode");
    QTest::addColumn<int>("rowCount");
    QTest::addColumn<int>("columnCount");
    QTest::addColumn<int>("rowHeight");
    QTest::addColumn<int>("columnWidth");
    QTest::addColumn<int>("hiddenRow");
    QTest::addColumn<int>("hiddenColumn");
    QTest::addColumn<int>("row");
    QTest::addColumn<int>("column");
    QTest::addColumn<int>("rowSpan");
    QTest::addColumn<int>("columnSpan");
    QTest::addColumn<int>("horizontalScroll");
    QTest::addColumn<int>("verticalScroll");
    QTest::addColumn<int>("scrollHint");
    QTest::addColumn<int>("expectedHorizontalScroll");
    QTest::addColumn<int>("expectedVerticalScroll");

    QTest::newRow("no hidden, no span, no scroll, per item")
        << (int)QAbstractItemView::ScrollPerItem
        << (int)QAbstractItemView::ScrollPerItem
        << 10 << 10  // table
        << 40 << 40  // size
        << -1 << -1  // hide
        << 0 << 0    // cell
        << 1 << 1    // span
        << 0 << 0    // scroll
        << (int)QAbstractItemView::PositionAtTop
        << 0 << 0;   // expected

    QTest::newRow("no hidden, no span, no scroll, per pixel")
        << (int)QAbstractItemView::ScrollPerPixel
        << (int)QAbstractItemView::ScrollPerPixel
        << 10 << 10  // table
        << 40 << 40  // size
        << -1 << -1  // hide
        << 0 << 0    // cell
        << 1 << 1    // span
        << 0 << 0    // scroll
        << (int)QAbstractItemView::PositionAtTop
        << 0 << 0;   // expected

    QTest::newRow("hidden, no span, no scroll, per item")
        << (int)QAbstractItemView::ScrollPerItem
        << (int)QAbstractItemView::ScrollPerItem
        << 10 << 10  // table
        << 40 << 40  // size
        << 3 << 3    // hide
        << 5 << 5    // cell
        << 1 << 1    // span
        << 0 << 0    // scroll
        << (int)QAbstractItemView::PositionAtTop
        << 4 << 4;   // expected
}

void tst_QTableView::scrollTo()
{
    QFETCH(int, horizontalScrollMode);
    QFETCH(int, verticalScrollMode);
    QFETCH(int, rowCount);
    QFETCH(int, columnCount);
    QFETCH(int, rowHeight);
    QFETCH(int, columnWidth);
    QFETCH(int, hiddenRow);
    QFETCH(int, hiddenColumn);
    QFETCH(int, row);
    QFETCH(int, column);
    QFETCH(int, rowSpan);
    QFETCH(int, columnSpan);
    QFETCH(int, horizontalScroll);
    QFETCH(int, verticalScroll);
    QFETCH(int, scrollHint);
    QFETCH(int, expectedHorizontalScroll);
    QFETCH(int, expectedVerticalScroll);

    QtTestTableModel model(rowCount, columnCount);
    QtTestTableView view;

    view.show();
    view.resize(columnWidth * 2, rowHeight * 2);
    QTest::qWait(0);

    view.setModel(&model);
    view.setSpan(row, column, rowSpan, columnSpan);
    view.hideRow(hiddenRow);
    view.hideColumn(hiddenColumn);
    view.setHorizontalScrollMode((QAbstractItemView::ScrollMode)horizontalScrollMode);
    view.setVerticalScrollMode((QAbstractItemView::ScrollMode)verticalScrollMode);

    for (int r = 0; r < rowCount; ++r)
        view.setRowHeight(r, rowHeight);
    for (int c = 0; c < columnCount; ++c)
        view.setColumnWidth(c, columnWidth);

    QTest::qWait(50); // ### needed to pass the test
    view.horizontalScrollBar()->setValue(horizontalScroll);
    view.verticalScrollBar()->setValue(verticalScroll);

    QModelIndex index = model.index(row, column);
    QVERIFY(index.isValid());
    view.scrollTo(index, (QAbstractItemView::ScrollHint)scrollHint);
    QCOMPARE(view.verticalScrollBar()->value(), expectedVerticalScroll);
    QCOMPARE(view.horizontalScrollBar()->value(), expectedHorizontalScroll);
}

void tst_QTableView::indexAt_data()
{
    QTest::addColumn<int>("rowCount");
    QTest::addColumn<int>("columnCount");

    QTest::addColumn<int>("rowHeight");
    QTest::addColumn<int>("columnWidth");

    QTest::addColumn<int>("hiddenRow");
    QTest::addColumn<int>("hiddenColumn");

    QTest::addColumn<int>("row");
    QTest::addColumn<int>("column");
    QTest::addColumn<int>("rowSpan");
    QTest::addColumn<int>("columnSpan");
    QTest::addColumn<int>("horizontalScroll");
    QTest::addColumn<int>("verticalScroll");
    QTest::addColumn<int>("x");
    QTest::addColumn<int>("y");
    QTest::addColumn<int>("expectedRow");
    QTest::addColumn<int>("expectedColumn");

    QTest::newRow("no hidden, no span, no scroll, (20,20)")
      << 10 << 10  // dim
      << 40 << 40  // size
      << -1 << -1  // hide
      << -1 << -1  // pos
      << 1 << 1    // span
      << 0 << 0    // scroll
      << 20 << 20  // point
      << 0 << 0;   // expected

    QTest::newRow("row hidden, no span, no scroll, at (20,20)")
      << 10 << 10  // dim
      << 40 << 40  // size
      << 0 << -1   // hide
      << -1 << -1  // pos
      << 1 << 1    // span
      << 0 << 0    // scroll
      << 20 << 20  // point
      << 1 << 0;   // expected

    QTest::newRow("col hidden, no span, no scroll, at (20,20)")
      << 10 << 10  // dim
      << 40 << 40  // size
      << -1 << 0   // hide
      << -1 << -1  // pos
      << 1 << 1    // span
      << 0 << 0    // scroll
      << 20 << 20  // point
      << 0 << 1;   // expected

    QTest::newRow("no hidden, row span, no scroll, at (60,20)")
      << 10 << 10  // dim
      << 40 << 40  // size
      << -1 << -1  // hide
      << 0 << 0    // pos
      << 2 << 1    // span
      << 0 << 0    // scroll
      << 20 << 60  // point
      << 0 << 0;   // expected


    QTest::newRow("no hidden, col span, no scroll, at (60,20)")
      << 10 << 10  // dim
      << 40 << 40  // size
      << -1 << -1  // hide
      << 0 << 0    // pos
      << 1 << 2    // span
      << 0 << 0    // scroll
      << 60 << 20  // point
      << 0 << 0;   // expected

    QTest::newRow("no hidden, no span, scroll (5,0), at (20,20)")
      << 10 << 10  // dim
      << 40 << 40  // size
      << -1 << -1  // hide
      << -1 << -1  // pos
      << 1 << 1    // span
      << 5 << 0    // scroll
      << 20 << 20  // point
      << 0 << 5;   // expected

    QTest::newRow("no hidden, no span, scroll (0,5), at (20,20)")
      << 10 << 10  // dim
      << 40 << 40  // size
      << -1 << -1  // hide
      << -1 << -1  // pos
      << 1 << 1    // span
      << 0 << 5    // scroll
      << 20 << 20  // point
      << 5 << 0;   // expected

    QTest::newRow("no hidden, no span, scroll (5,5), at (20,20)")
      << 10 << 10  // dim
      << 40 << 40  // size
      << -1 << -1  // hide
      << -1 << -1  // pos
      << 1 << 1    // span
      << 5 << 5    // scroll
      << 20 << 20  // point
      << 5 << 5;   // expected
}

void tst_QTableView::indexAt()
{
    QFETCH(int, rowCount);
    QFETCH(int, columnCount);
    QFETCH(int, rowHeight);
    QFETCH(int, columnWidth);
    QFETCH(int, hiddenRow);
    QFETCH(int, hiddenColumn);
    QFETCH(int, row);
    QFETCH(int, column);
    QFETCH(int, rowSpan);
    QFETCH(int, columnSpan);
    QFETCH(int, horizontalScroll);
    QFETCH(int, verticalScroll);
    QFETCH(int, x);
    QFETCH(int, y);
    QFETCH(int, expectedRow);
    QFETCH(int, expectedColumn);

    QtTestTableModel model(rowCount, columnCount);
    QtTestTableView view;

    view.show();
    view.setModel(&model);
    view.setSpan(row, column, rowSpan, columnSpan);
    view.hideRow(hiddenRow);
    view.hideColumn(hiddenColumn);

    for (int r = 0; r < rowCount; ++r)
        view.setRowHeight(r, rowHeight);
    for (int c = 0; c < columnCount; ++c)
        view.setColumnWidth(c, columnWidth);

    QTest::qWait(0); // ### needed to pass the test
    view.horizontalScrollBar()->setValue(horizontalScroll);
    view.verticalScrollBar()->setValue(verticalScroll);

    QModelIndex index = view.indexAt(QPoint(x, y));
    QCOMPARE(index.row(), expectedRow);
    QCOMPARE(index.column(), expectedColumn);
}

void tst_QTableView::span_data()
{
    QTest::addColumn<int>("rowCount");
    QTest::addColumn<int>("columnCount");
    QTest::addColumn<int>("hiddenRow");
    QTest::addColumn<int>("hiddenColumn");
    QTest::addColumn<int>("row");
    QTest::addColumn<int>("column");
    QTest::addColumn<int>("rowSpan");
    QTest::addColumn<int>("columnSpan");
    QTest::addColumn<int>("expectedRowSpan");
    QTest::addColumn<int>("expectedColumnSpan");
    QTest::addColumn<bool>("clear");

    QTest::newRow("top left 2x2")
      << 10 << 10
      << -1 << -1
      << 0 << 0
      << 2 << 2
      << 2 << 2
      << false;

    QTest::newRow("top left 1x2")
      << 10 << 10
      << 3 << 3
      << 0 << 0
      << 1 << 2
      << 1 << 2
      << false;

    QTest::newRow("top left 2x1")
      << 10 << 10
      << -1 << -1
      << 0 << 0
      << 2 << 1
      << 2 << 1
      << false;

    QTest::newRow("top left 2x0")
      << 10 << 10
      << -1 << -1
      << 0 << 0
      << 2 << 0
      << 2 << 0
      << false;

    QTest::newRow("top left 0x2")
      << 10 << 10
      << -1 << -1
      << 0 << 0
      << 0 << 2
      << 0 << 2
      << false;

    QTest::newRow("invalid 2x2")
      << 10 << 10
      << -1 << -1
      << -1 << -1
      << 2 << 2
      << 1 << 1
      << false;

    QTest::newRow("top left 2x2")
      << 10 << 10
      << -1 << -1
      << 0 << 0
      << 2 << 2
      << 2 << 2
      << false;

    QTest::newRow("bottom right 2x2")
      << 10 << 10
      << -1 << -1
      << 8 << 8
      << 2 << 2
      << 2 << 2
      << false;

    QTest::newRow("invalid span 2x2")
      << 10 << 10
      << -1 << -1
      << 8 << 8
      << 2 << 2
      << 2 << 2
      << false;

    QTest::newRow("invalid span 3x3")
      << 10 << 10
      << -1 << -1
      << 6 << 6
      << 3 << 3
      << 3 << 3
      << true;

}

void tst_QTableView::span()
{
    QFETCH(int, rowCount);
    QFETCH(int, columnCount);
    QFETCH(int, hiddenRow);
    QFETCH(int, hiddenColumn);
    QFETCH(int, row);
    QFETCH(int, column);
    QFETCH(int, rowSpan);
    QFETCH(int, columnSpan);
    QFETCH(int, expectedRowSpan);
    QFETCH(int, expectedColumnSpan);
    QFETCH(bool, clear);

    QtTestTableModel model(rowCount, columnCount);
    QtTestTableView view;

    view.setModel(&model);
    view.show();

    view.setSpan(row, column, rowSpan, columnSpan);
    if (clear) {
        model.removeLastRow();
        model.removeLastRow();
        view.update();
    }

    view.hideRow(hiddenRow);
    view.hideColumn(hiddenColumn);
    view.show();

    QCOMPARE(view.rowSpan(row, column), expectedRowSpan);
    QCOMPARE(view.columnSpan(row, column), expectedColumnSpan);

    if (hiddenRow > -1) {
        QModelIndex hidden = model.index(hiddenRow, columnCount - 1);
	QVERIFY(view.isIndexHidden(hidden));
    }

    if (hiddenColumn > -1) {
        QModelIndex hidden = model.index(rowCount - 1, hiddenColumn);
        QVERIFY(view.isIndexHidden(hidden));
    }

    view.clearSpans();
    QCOMPARE(view.rowSpan(row, column), 1);
    QCOMPARE(view.columnSpan(row, column), 1);
}

typedef QVector<QRect> SpanList;
Q_DECLARE_METATYPE(SpanList)

void tst_QTableView::spans_data()
{
    QTest::addColumn<int>("rows");
    QTest::addColumn<int>("columns");
    QTest::addColumn<SpanList>("spans");
    QTest::addColumn<bool>("hideRowLastRowOfFirstSpan");
    QTest::addColumn<QPoint>("pos");
    QTest::addColumn<int>("expectedRowSpan");
    QTest::addColumn<int>("expectedColumnSpan");

    QTest::newRow("1x3 span, query 3,0")
      << 5 << 5
      << (SpanList() << QRect(3, 0, 1, 3))
      << false //no hidden row
      << QPoint(3, 0)
      << 1
      << 3;

    QTest::newRow("1x3 span, query 3,1")
      << 5 << 5
      << (SpanList() << QRect(3, 0, 1, 3))
      << false //no hidden row
      << QPoint(3, 1)
      << 1
      << 3;

    QTest::newRow("1x3 span, query 3,2")
      << 5 << 5
      << (SpanList() << QRect(3, 0, 1, 3))
      << false //no hidden row
      << QPoint(3, 2)
      << 1
      << 3;

    QTest::newRow("two 1x2 spans at the same column, query at 3,0")
      << 5 << 5
      << (SpanList() << QRect(3, 0, 1, 2) << QRect(4, 0, 1, 2))
      << false //no hidden row
      << QPoint(3, 0)
      << 1
      << 2;

    QTest::newRow("two 1x2 spans at the same column, query at 4,0")
      << 5 << 5
      << (SpanList() << QRect(3, 0, 1, 2) << QRect(4, 0, 1, 2))
      << false //no hidden row
      << QPoint(4, 0)
      << 1
      << 2;

    QTest::newRow("how to order spans (1,1)")
      << 5 << 5
      << (SpanList() << QRect(1, 1, 3, 1) << QRect(1, 2, 2, 1))
      << false //no hidden row
      << QPoint(1, 1)
      << 3
      << 1;

    QTest::newRow("how to order spans (2,1)")
      << 5 << 5
      << (SpanList() << QRect(1, 1, 3, 1) << QRect(1, 2, 2, 1))
      << false //no hidden row
      << QPoint(2, 1)
      << 3
      << 1;

    QTest::newRow("how to order spans (3,1)")
      << 5 << 5
      << (SpanList() << QRect(1, 1, 3, 1) << QRect(1, 2, 2, 1))
      << false //no hidden row
      << QPoint(3, 1)
      << 3
      << 1;

    QTest::newRow("how to order spans (1,2)")
      << 5 << 5
      << (SpanList() << QRect(1, 1, 3, 1) << QRect(1, 2, 2, 1))
      << false //no hidden row
      << QPoint(1, 2)
      << 2
      << 1;

    QTest::newRow("how to order spans (2,2)")
      << 5 << 5
      << (SpanList() << QRect(1, 1, 3, 1) << QRect(1, 2, 2, 1))
      << false //no hidden row
      << QPoint(2, 2)
      << 2
      << 1;

    QTest::newRow("spans with hidden rows")
      << 3 << 2
      << (SpanList() << QRect(0, 0, 2, 2) << QRect(2, 0, 1, 2))
      << true //we hide the last row of the first span
      << QPoint(2, 0)
      << 1
      << 2;
}

void tst_QTableView::spans()
{
    QFETCH(int, rows);
    QFETCH(int, columns);
    QFETCH(SpanList, spans);
    QFETCH(bool, hideRowLastRowOfFirstSpan);
    QFETCH(QPoint, pos);
    QFETCH(int, expectedRowSpan);
    QFETCH(int, expectedColumnSpan);

    QtTestTableModel model(rows, columns);
    QtTestTableView view;

    view.setModel(&model);
    view.show();

    for (int i = 0; i < spans.count(); ++i) {
        QRect sp = spans.at(i);
        view.setSpan(sp.x(), sp.y(), sp.width(), sp.height());
    }

    if (hideRowLastRowOfFirstSpan) {
        view.setRowHidden(spans.at(0).bottom(), true);
        //we check that the span didn't break the visual rects of the model indexes
        QRect first = view.visualRect( model.index(spans.at(0).top(), 0));
        QRect next = view.visualRect( model.index(spans.at(0).bottom() + 1, 0));
        QVERIFY(first.intersected(next).isEmpty());
    }

    QCOMPARE(view.columnSpan(pos.x(), pos.y()), expectedColumnSpan);
    QCOMPARE(view.rowSpan(pos.x(), pos.y()), expectedRowSpan);
}

class Model : public QAbstractTableModel {

Q_OBJECT

public:
    Model(QObject * parent = 0) : QAbstractTableModel(parent) {
    }

    int rowCount(const QModelIndex &) const {
        return rows;
    }
    int columnCount(const QModelIndex &) const {
        return columns;
    }
    QVariant data(const QModelIndex &, int) const
    {
        return QVariant();
    }
    void res() { reset(); }

    int rows;
    int columns;
};

void tst_QTableView::checkHeaderReset()
{
    QTableView view;
    Model m;
    m.rows = 3;
    m.columns = 3;
    view.setModel(&m);

    m.rows = 4;
    m.columns = 4;
    m.res();
    QCOMPARE(view.horizontalHeader()->count(), 4);
}

void tst_QTableView::checkHeaderMinSize()
{
    //tests if the minimumsize is of a header is taken into account
    //while computing QTableView geometry. For that we test the position of the
    //viewport.
    QTableView view;
    QStringListModel m;
    m.setStringList( QStringList() << QLatin1String("one cell is enough"));
    view.setModel(&m);

    //setting the minimum height on the horizontal header
    //and the minimum width on the vertical header
    view.horizontalHeader()->setMinimumHeight(50);
    view.verticalHeader()->setMinimumWidth(100);

    view.show();

    QVERIFY( view.verticalHeader()->y() >= view.horizontalHeader()->minimumHeight());
    QVERIFY( view.horizontalHeader()->x() >= view.verticalHeader()->minimumWidth());
}

void tst_QTableView::resizeToContents()
{
    //checks that the resize to contents is consistent
    QTableWidget table(2,3);
    QTableWidget table2(2,3);
    QTableWidget table3(2,3);


    table.setHorizontalHeaderItem(0, new QTableWidgetItem("A Lot of text here: BLA BLA BLA"));
    table2.setHorizontalHeaderItem(0, new QTableWidgetItem("A Lot of text here: BLA BLA BLA"));
    table3.setHorizontalHeaderItem(0, new QTableWidgetItem("A Lot of text here: BLA BLA BLA"));
    table.horizontalHeader()->setVisible(false);
    table2.horizontalHeader()->setVisible(false);
    table.verticalHeader()->setVisible(false);
    table2.verticalHeader()->setVisible(false);


    for(int i = 0;i<table.columnCount();i++) {
        table.resizeColumnToContents(i);
    }
    for(int i = 0;i<table.rowCount();i++) {
        table.resizeRowToContents(i);
    }
    table2.resizeColumnsToContents();
    table2.resizeRowsToContents();
    table3.resizeColumnsToContents();
    table3.resizeRowsToContents();

    //now let's check the row/col sizes
    for(int i = 0;i<table.columnCount();i++) {
        QVERIFY( table.columnWidth(i) == table2.columnWidth(i));
        QVERIFY( table2.columnWidth(i) == table3.columnWidth(i));
    }
    for(int i = 0;i<table.rowCount();i++) {
        QVERIFY( table.rowHeight(i) == table2.rowHeight(i));
        QVERIFY( table2.rowHeight(i) == table3.rowHeight(i));
    }

}


void tst_QTableView::tabFocus()
{
    // QTableView enables tabKeyNavigation by default, but you should be able
    // to change focus on an empty table view, or on a table view that doesn't
    // have this property set.
    QWidget window;

    QTableView *view = new QTableView(&window);
    QLineEdit *edit = new QLineEdit(&window);

    window.show();
//wait for window manager:
#ifdef Q_WS_QWS
    qApp->processEvents();
#endif
    window.setFocus();
    QTest::qWait(100);
    window.activateWindow();
    QTest::qWait(100);

    qApp->processEvents();

    WAIT_FOR_CONDITION(window.hasFocus(), true);

    qApp->processEvents();

    // window
    QVERIFY(window.hasFocus());
    QVERIFY(!view->hasFocus());
    QVERIFY(!edit->hasFocus());

    for (int i = 0; i < 2; ++i) {
        // tab to view
        QTest::keyPress(qApp->focusWidget(), Qt::Key_Tab);
        QVERIFY(!window.hasFocus());
        QVERIFY(view->hasFocus());
        QVERIFY(!edit->hasFocus());

        // tab to edit
        QTest::keyPress(qApp->focusWidget(), Qt::Key_Tab);
        QVERIFY(!window.hasFocus());
        QVERIFY(!view->hasFocus());
        QVERIFY(edit->hasFocus());
    }

    // backtab to view
    QTest::keyPress(qApp->focusWidget(), Qt::Key_Backtab);
    QVERIFY(!window.hasFocus());
    QVERIFY(view->hasFocus());
    QVERIFY(!edit->hasFocus());

    // backtab to edit
    QTest::keyPress(qApp->focusWidget(), Qt::Key_Backtab);
    QVERIFY(!window.hasFocus());
    QVERIFY(!view->hasFocus());
    QVERIFY(edit->hasFocus());

    QStandardItemModel *model = new QStandardItemModel;
    view->setModel(model);

    // backtab to view
    QTest::keyPress(qApp->focusWidget(), Qt::Key_Backtab);
    QVERIFY(!window.hasFocus());
    QVERIFY(view->hasFocus());
    QVERIFY(!edit->hasFocus());

    // backtab to edit
    QTest::keyPress(qApp->focusWidget(), Qt::Key_Backtab);
    QVERIFY(!window.hasFocus());
    QVERIFY(!view->hasFocus());
    QVERIFY(edit->hasFocus());

    model->insertRow(0, new QStandardItem("Hei"));
    model->insertRow(0, new QStandardItem("Hei"));
    model->insertRow(0, new QStandardItem("Hei"));

    // backtab to view
    QTest::keyPress(qApp->focusWidget(), Qt::Key_Backtab);
    QVERIFY(!window.hasFocus());
    QVERIFY(view->hasFocus());
    QVERIFY(!edit->hasFocus());

    // backtab to edit doesn't work
    QTest::keyPress(qApp->focusWidget(), Qt::Key_Backtab);
    QVERIFY(!window.hasFocus());
    QVERIFY(view->hasFocus());
    QVERIFY(!edit->hasFocus());

    view->setTabKeyNavigation(false);

    // backtab to edit
    QTest::keyPress(qApp->focusWidget(), Qt::Key_Backtab);
    QVERIFY(!window.hasFocus());
    QVERIFY(!view->hasFocus());
    QVERIFY(edit->hasFocus());

    QTest::keyPress(qApp->focusWidget(), Qt::Key_Tab);
    QVERIFY(view->hasFocus());
    QTest::keyPress(qApp->focusWidget(), Qt::Key_Tab);
    QVERIFY(edit->hasFocus());

    delete model;
}

class BigModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    virtual QVariant data(const QModelIndex &index,
                          int role = Qt::DisplayRole) const
    {
        if (role == Qt::DisplayRole)
            return QString("%1 - %2").arg(index.column()).arg(index.row());
        return QVariant();
    }


    int rowCount(const QModelIndex & parent = QModelIndex()) const
    {
        Q_UNUSED(parent);
        return 10000000;
    }

    int columnCount(const QModelIndex & parent = QModelIndex()) const
    {
        Q_UNUSED(parent);
        return 20000000;
    }
};

void tst_QTableView::bigModel()
{
    //should not crash
    QTableView view;
    BigModel model;
    view.setModel(&model);
    view.show();
    view.setSpan(10002,10002,6,6);
    QTest::qWait(100);
    view.resize(1000,1000);
    QTest::qWait(100);
    view.scrollTo(model.index(10010,10010));
    QTest::qWait(100);
}

void tst_QTableView::selectionSignal()
{
    QtTestTableModel model(10, 10);
    QtTestTableView view;
    view.checkSignalOrder = true;
    view.setModel(&model);
    view.resize(200, 200);
    view.show();
    WAIT_FOR_CONDITION(view.isVisible(), true);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, view.visualRect(model.index(2, 0)).center());
}

class task173773_EventFilter : public QObject
{
    int paintEventCount_;
public:
    task173773_EventFilter() : paintEventCount_(0) {}
    int paintEventCount() const { return paintEventCount_; }
private:
    bool eventFilter(QObject *obj, QEvent *e)
    {
        Q_UNUSED(obj);
        if (e->type() == QEvent::Paint)
            ++paintEventCount_;
        return false;
    }
};

void tst_QTableView::task173773_updateVerticalHeader()
{
    QStandardItemModel model(2, 1);
    model.setData(model.index(0, 0), 0);
    model.setData(model.index(1, 0), 1);

    QSortFilterProxyModel proxyModel;
    proxyModel.setSourceModel(&model);

    QTableView view;
    view.setModel(&proxyModel);
    view.setSortingEnabled(true);
    view.show();
#ifdef Q_WS_X11
    qt_x11_wait_for_window_manager(&view);
#endif
    QTest::qWait(100);

    view.sortByColumn(0, Qt::AscendingOrder);
    QTest::qWait(100);

    task173773_EventFilter eventFilter;
    view.verticalHeader()->viewport()->installEventFilter(&eventFilter);

    view.sortByColumn(0, Qt::DescendingOrder);
    QTest::qWait(100);

    // ### note: this test may occasionally pass even if the bug is present!
    QVERIFY(eventFilter.paintEventCount() > 0);
}

void tst_QTableView::task227953_setRootIndex()
{
	QTableView tableView;

    //model = tree with two items with tables as children
    QStandardItemModel model;
    QStandardItem item1, item2;
    model.appendColumn(QList<QStandardItem*>() << &item1 << &item2);


    //setup the first table as a child of the first item
    for ( int row = 0; row < 40; ++row ) {
        item1.appendRow(QList<QStandardItem*>() << new QStandardItem(QString("row %0").arg(row)));
    }

    //setup the second table as a child of the second item
    for ( int row = 0; row < 10; ++row ) {
        item2.appendRow(QList<QStandardItem*>() << new QStandardItem(QString("row %0").arg(row)));
    }

    tableView.setModel(&model);
    
    //show the first 10 rows of the first table
    QModelIndex root = model.indexFromItem(&item1);
	tableView.setRootIndex(root);
	for (int i = 10; i != 40; ++i) {
		tableView.setRowHidden(i, true);
	}
	
    QCOMPARE(tableView.verticalHeader()->count(), 40);
    QCOMPARE(tableView.verticalHeader()->hiddenSectionCount(), 30);

	//show the first 10 rows of the second table
	tableView.setRootIndex(model.indexFromItem(&item2));

    QCOMPARE(tableView.verticalHeader()->count(), 10);
    QCOMPARE(tableView.verticalHeader()->hiddenSectionCount(), 0);
    QVERIFY(!tableView.verticalHeader()->isHidden());
}


void tst_QTableView::mouseWheel_data()
{
    QTest::addColumn<int>("scrollMode");
    QTest::addColumn<int>("delta");
    QTest::addColumn<int>("horizontalPositon");
    QTest::addColumn<int>("verticalPosition");

    QTest::newRow("scroll up per item")
            << int(QAbstractItemView::ScrollPerItem) << 120
            << 10 - qApp->wheelScrollLines() << 10 - qApp->wheelScrollLines();
    QTest::newRow("scroll down per item")
            << int(QAbstractItemView::ScrollPerItem) << -120
            << 10 + qApp->wheelScrollLines() << 10 + qApp->wheelScrollLines();
    QTest::newRow("scroll down per pixel")
            << int(QAbstractItemView::ScrollPerPixel) << -120
            << 10 + qApp->wheelScrollLines() * 89 << 10 + qApp->wheelScrollLines() * 28;
}

void tst_QTableView::mouseWheel()
{
    QFETCH(int, scrollMode);
    QFETCH(int, delta);
    QFETCH(int, horizontalPositon);
    QFETCH(int, verticalPosition);

    QtTestTableModel model(100, 100);
    QtTestTableView view;
    view.resize(500, 500);
    for (int r = 0; r < 100; ++r)
        view.setRowHeight(r, 50);
    for (int c = 0; c < 100; ++c)
        view.setColumnWidth(c, 100);
    view.show();

    view.setModel(&model);

    view.setHorizontalScrollMode((QAbstractItemView::ScrollMode)scrollMode);
    view.setVerticalScrollMode((QAbstractItemView::ScrollMode)scrollMode);
    view.horizontalScrollBar()->setValue(10);
    view.verticalScrollBar()->setValue(10);

    QPoint pos(100,100);
    QWheelEvent verticalEvent(pos, delta, 0, 0, Qt::Vertical);
    QWheelEvent horizontalEvent(pos, delta, 0, 0, Qt::Horizontal);
    view.wheelEvent(&horizontalEvent);
    QVERIFY(qAbs(view.horizontalScrollBar()->value() - horizontalPositon) < 10);
    view.wheelEvent(&verticalEvent);
    QVERIFY(qAbs(view.verticalScrollBar()->value() - verticalPosition) < 10);
}

void tst_QTableView::addColumnWhileEditing()
{
    QTableView view;
    QStandardItemModel model(1, 10);
    view.setModel(&model);
    QModelIndex last = model.index(0,9);
    view.show();

    view.openPersistentEditor(last);
    view.scrollTo(last);

    //let's see if the editor is moved to the right location
    //after adding a column
    model.setColumnCount(model.columnCount() + 1);
    QPointer<QLineEdit> editor = qFindChild<QLineEdit*>(&view);
    QVERIFY(editor);
    QCOMPARE(editor->geometry(), view.visualRect(last));

    //let's see if the editor is moved to the right location
    //after removing a column
    view.scrollTo(model.index(0, model.columnCount()-1));
    model.setColumnCount(model.columnCount() - 1);
    QVERIFY(editor);
    QCOMPARE(editor->geometry(), view.visualRect(last));
}


QTEST_MAIN(tst_QTableView)
#include "tst_qtableview.moc"
