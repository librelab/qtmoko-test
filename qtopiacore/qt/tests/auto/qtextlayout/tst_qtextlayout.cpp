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


/*
    !!!!!! Warning !!!!!
    Please don't save this file in emacs. It contains utf8 text sequences emacs will
    silently convert to a series of question marks.
 */
#include <QtTest/QtTest>



#include <private/qtextengine_p.h>
#include <qtextlayout.h>

#include <qdebug.h>


#define TESTFONT_SIZE 12



//TESTED_CLASS=
//TESTED_FILES=

class tst_QTextLayout : public QObject
{
    Q_OBJECT

public:
    tst_QTextLayout();
    virtual ~tst_QTextLayout();


public slots:
    void init();
    void cleanup();
private slots:
    void getSetCheck();
    void lineBreaking();
    void simpleBoundingRect();
    void threeLineBoundingRect();
    void boundingRectWithLongLineAndNoWrap();
    void forcedBreaks();
    void breakAny();
    void noWrap();
    void cursorToXForInlineObjects();
    void cursorToXForSetColumns();
    void defaultWordSeparators_data();
    void defaultWordSeparators();
    void cursorMovementInsideSpaces();
    void charWordStopOnLineSeparator();
    void xToCursorAtEndOfLine();
    void boundingRectTopLeft();
    void charStopForSurrogatePairs();
    void tabStops();
    void integerOverflow();
    void testDefaultTabs();
    void testTabs();
    void testMultilineTab();
    void testRightTab();
    void testTabsInAlignedParag();
    void testCenteredTab();
    void testDelimiterTab();
    void testMultiTab();
    void testTabDPIScale();
    void tabsForRtl();
    void tabHeight();
    void capitalization_allUpperCase();
    void capitalization_allLowerCase();
    void capitalization_smallCaps();
    void capitalization_capitalize();
    void longText();
    void widthOfTabs();

    // QTextLine stuff
    void setNumColumnsWrapAtWordBoundaryOrAnywhere();
    void setNumColumnsWordWrap();
    void smallTextLengthNoWrap();
    void smallTextLengthWordWrap();
    void smallTextLengthWrapAtWordBoundaryOrAnywhere();
    void testLineBreakingAllSpaces();


private:
    QFont testFont;
};

// Testing get/set functions
void tst_QTextLayout::getSetCheck()
{
    QString str("Bogus text");
    QTextLayout layout(str, testFont);
    layout.beginLayout();
    QTextEngine *engine = layout.engine();
    QTextInlineObject obj1(0, engine);
    // qreal QTextInlineObject::width()
    // void QTextInlineObject::setWidth(qreal)
    obj1.setWidth(0.0);
    QCOMPARE(0.0, obj1.width());
    obj1.setWidth(1.2);
    QVERIFY(1.0 < obj1.width());

    // qreal QTextInlineObject::ascent()
    // void QTextInlineObject::setAscent(qreal)
    obj1.setAscent(0.0);
    QCOMPARE(0.0, obj1.ascent());
    obj1.setAscent(1.2);
    QVERIFY(1.0 < obj1.ascent());

    // qreal QTextInlineObject::descent()
    // void QTextInlineObject::setDescent(qreal)
    obj1.setDescent(0.0);
    QCOMPARE(0.0, obj1.descent());
    obj1.setDescent(1.2);
    QVERIFY(1.0 < obj1.descent());

    QTextLayout obj2;
    // bool QTextLayout::cacheEnabled()
    // void QTextLayout::setCacheEnabled(bool)
    obj2.setCacheEnabled(false);
    QCOMPARE(false, obj2.cacheEnabled());
    obj2.setCacheEnabled(true);
    QCOMPARE(true, obj2.cacheEnabled());
}

QT_BEGIN_NAMESPACE
extern Q_GUI_EXPORT bool qt_enable_test_font;
QT_END_NAMESPACE

tst_QTextLayout::tst_QTextLayout()
{
    qt_enable_test_font = true;
}

tst_QTextLayout::~tst_QTextLayout()
{
}

void tst_QTextLayout::init()
{
    testFont = QFont();
    testFont.setFamily("__Qt__Box__Engine__");
    testFont.setPixelSize(TESTFONT_SIZE);
    testFont.setWeight(QFont::Normal);
    QCOMPARE(QFontMetrics(testFont).width('a'), testFont.pixelSize());
}

void tst_QTextLayout::cleanup()
{
    testFont = QFont();
}


void tst_QTextLayout::lineBreaking()
{
#if defined(Q_WS_X11)
    struct Breaks {
	const char *utf8;
	uchar breaks[32];
    };
    Breaks brks[] = {
	{ "11", { false, 0xff } },
	{ "aa", { false, 0xff } },
	{ "++", { false, 0xff } },
	{ "--", { false, 0xff } },
	{ "((", { false, 0xff } },
	{ "))", { false, 0xff } },
	{ "..", { false, 0xff } },
	{ "\"\"", { false, 0xff } },
	{ "$$", { false, 0xff } },
	{ "!!", { false, 0xff } },
	{ "??", { false, 0xff } },
	{ ",,", { false, 0xff } },

	{ ")()", { true, false, 0xff } },
	{ "?!?", { false, false, 0xff } },
	{ ".,.", { false, false, 0xff } },
	{ "+-+", { false, false, 0xff } },
	{ "+=+", { false, false, 0xff } },
	{ "+(+", { false, false, 0xff } },
	{ "+)+", { false, false, 0xff } },

	{ "a b", { false, true, 0xff } },
	{ "a(b", { false, false, 0xff } },
	{ "a)b", { false, false, 0xff } },
	{ "a-b", { false, true, 0xff } },
	{ "a.b", { false, false, 0xff } },
	{ "a+b", { false, false, 0xff } },
	{ "a?b", { false, false, 0xff } },
	{ "a!b", { false, false, 0xff } },
	{ "a$b", { false, false, 0xff } },
	{ "a,b", { false, false, 0xff } },
	{ "a/b", { false, false, 0xff } },
	{ "1/2", { false, false, 0xff } },
	{ "./.", { false, false, 0xff } },
	{ ",/,", { false, false, 0xff } },
	{ "!/!", { false, false, 0xff } },
	{ "\\/\\", { false, false, 0xff } },
	{ "1 2", { false, true, 0xff } },
	{ "1(2", { false, false, 0xff } },
	{ "1)2", { false, false, 0xff } },
	{ "1-2", { false, false, 0xff } },
	{ "1.2", { false, false, 0xff } },
	{ "1+2", { false, false, 0xff } },
	{ "1?2", { false, true, 0xff } },
	{ "1!2", { false, true, 0xff } },
	{ "1$2", { false, false, 0xff } },
	{ "1,2", { false, false, 0xff } },
	{ "1/2", { false, false, 0xff } },
	{ "\330\260\331\216\331\204\331\220\331\203\331\216", { false, false, false, false, false, 0xff } },
	{ "\330\247\331\204\331\205 \330\247\331\204\331\205", { false, false, false, true, false, false, 0xff } },
	{ "1#2", { false, false, 0xff } },
	{ "!#!", { false, false, 0xff } },
	{ 0, {} }
    };
    Breaks *b = brks;
    while (b->utf8) {
        QString str = QString::fromUtf8(b->utf8);
        QTextEngine engine(str, QFont());
        const HB_CharAttributes *attrs = engine.attributes();
        int i;
        for (i = 0; i < (int)str.length() - 1; ++i) {
            QVERIFY(b->breaks[i] != 0xff);
            if ( (attrs[i].lineBreakType != HB_NoBreak) != (bool)b->breaks[i] ) {
                qDebug("test case \"%s\" failed at char %d; break type: %d", b->utf8, i, attrs[i].lineBreakType);
                QCOMPARE( (attrs[i].lineBreakType != HB_NoBreak), (bool)b->breaks[i] );
            }
        }
        QVERIFY(attrs[i].lineBreakType == HB_ForcedBreak);
        QCOMPARE(b->breaks[i], (uchar)0xff);
        ++b;
    }
#else
    QSKIP("This test can not be run on non-X11 platforms", SkipAll);
#endif
}

void tst_QTextLayout::simpleBoundingRect()
{
    /* just check if boundingRect() gives sane values. The text is not broken. */

    QString hello("hello world");

    const int width = hello.length() * testFont.pixelSize();

    QTextLayout layout(hello, testFont);
    layout.beginLayout();

    QTextLine line = layout.createLine();
    line.setLineWidth(width);
    QCOMPARE(line.textLength(), hello.length());
    QCOMPARE(layout.boundingRect(), QRectF(0, 0, width, QFontMetrics(testFont).height()));
}

void tst_QTextLayout::threeLineBoundingRect()
{
#if defined(Q_WS_MAC)
    QSKIP("QTestFontEngine on the mac does not support logclusters at the moment", SkipAll);
#endif
    /* stricter check. break text into three lines */

    QString firstWord("hello");
    QString secondWord("world");
    QString thirdWord("test");
    QString text(firstWord + ' ' + secondWord + ' ' + thirdWord);

    const int firstLineWidth = firstWord.length() * testFont.pixelSize();
    const int secondLineWidth = secondWord.length() * testFont.pixelSize();
    const int thirdLineWidth = thirdWord.length() * testFont.pixelSize();

    const int longestLine = qMax(firstLineWidth, qMax(secondLineWidth, thirdLineWidth));

    QTextLayout layout(text, testFont);
    layout.beginLayout();

    int pos = 0;
    int y = 0;
    QTextLine line = layout.createLine();
    line.setLineWidth(firstLineWidth);
    line.setPosition(QPoint(0, y));
    QCOMPARE(line.textStart(), pos);
    // + 1 for trailing space
    QCOMPARE(line.textLength(), firstWord.length() + 1);
    QCOMPARE(qRound(line.naturalTextWidth()), firstLineWidth);

    pos += line.textLength();
    y += qRound(line.ascent() + line.descent());

    line = layout.createLine();
    line.setLineWidth(secondLineWidth);
    line.setPosition(QPoint(0, y));
    // + 1 for trailing space
    QCOMPARE(line.textStart(), pos);
    QCOMPARE(line.textLength(), secondWord.length() + 1);
    QCOMPARE(qRound(line.naturalTextWidth()), secondLineWidth);

    pos += line.textLength();
    y += qRound(line.ascent() + line.descent());

    line = layout.createLine();
    line.setLineWidth(secondLineWidth);
    line.setPosition(QPoint(0, y));
    // no trailing space here!
    QCOMPARE(line.textStart(), pos);
    QCOMPARE(line.textLength(), thirdWord.length());
    QCOMPARE(qRound(line.naturalTextWidth()), thirdLineWidth);
    y += qRound(line.ascent() + line.descent());

    QCOMPARE(layout.boundingRect(), QRectF(0, 0, longestLine, y + 1));
}

void tst_QTextLayout::boundingRectWithLongLineAndNoWrap()
{
    QString longString("thisisaverylongstringthatcannotbewrappedatallitjustgoesonandonlikeonebigword");

    const int width = longString.length() * testFont.pixelSize() / 20; // very small widthx

    QTextLayout layout(longString, testFont);
    layout.beginLayout();
    QTextLine line = layout.createLine();
    line.setLineWidth(width);

    QVERIFY(layout.boundingRect().width() >= line.width());
    QCOMPARE(layout.boundingRect().width(), line.naturalTextWidth());
}

void tst_QTextLayout::forcedBreaks()
{
    QString text = "A\n\nB\nC";
    text.replace('\n', QChar::LineSeparator);

    QTextLayout layout(text, testFont);

    layout.beginLayout();

    int pos = 0;

    QTextLine line = layout.createLine();
    line.setLineWidth(0x10000);
    QCOMPARE(line.textStart(), pos);
    QCOMPARE(line.textLength(),2);
    QCOMPARE(qRound(line.naturalTextWidth()),testFont.pixelSize());
    QCOMPARE((int) line.height(), testFont.pixelSize() + 1); // + 1 baseline
    QCOMPARE(line.xToCursor(0), line.textStart());
    pos += line.textLength();

    line = layout.createLine();
    line.setLineWidth(0x10000);
    QCOMPARE(line.textStart(),pos);
    QCOMPARE(line.textLength(),1);
    QCOMPARE(qRound(line.naturalTextWidth()), 0);
    QCOMPARE((int) line.height(), testFont.pixelSize() + 1); // + 1 baseline
    QCOMPARE(line.xToCursor(0), line.textStart());
    pos += line.textLength();

    line = layout.createLine();
    line.setLineWidth(0x10000);
    QCOMPARE(line.textStart(),pos);
    QCOMPARE(line.textLength(),2);
    QCOMPARE(qRound(line.naturalTextWidth()),testFont.pixelSize());
    QCOMPARE(qRound(line.height()), testFont.pixelSize() + 1); // + 1 baseline
    QCOMPARE(line.xToCursor(0), line.textStart());
    pos += line.textLength();

    line = layout.createLine();
    line.setLineWidth(0x10000);
    QCOMPARE(line.textStart(),pos);
    QCOMPARE(line.textLength(),1);
    QCOMPARE(qRound(line.naturalTextWidth()), testFont.pixelSize());
    QCOMPARE((int) line.height(), testFont.pixelSize() + 1); // + 1 baseline
    QCOMPARE(line.xToCursor(0), line.textStart());
}

void tst_QTextLayout::breakAny()
{
#if defined(Q_WS_MAC)
    QSKIP("QTestFontEngine on the mac does not support logclusters at the moment", SkipAll);
#endif
    QString text = "ABCD";

    QTextLayout layout(text, testFont);
    QTextLine line;

    QTextOption opt;
    opt.setWrapMode(QTextOption::WrapAnywhere);
    layout.setTextOption(opt);
    layout.beginLayout();

    line = layout.createLine();
    line.setLineWidth(testFont.pixelSize() * 2);
    QCOMPARE(line.textStart(), 0);
    QCOMPARE(line.textLength(), 2);

    line = layout.createLine();
    line.setLineWidth(testFont.pixelSize() * 2);
    QCOMPARE(line.textStart(), 2);
    QCOMPARE(line.textLength(), 2);

    line = layout.createLine();
    QVERIFY(!line.isValid());

    layout.endLayout();

    text = "ABCD EFGH";
    layout.setText(text);
    layout.beginLayout();

    line = layout.createLine();
    line.setLineWidth(testFont.pixelSize() * 7);
    QCOMPARE(line.textStart(), 0);
    QCOMPARE(line.textLength(), 7);

    layout.endLayout();
}

void tst_QTextLayout::noWrap()
{
#if defined(Q_WS_MAC)
    QSKIP("QTestFontEngine on the mac does not support logclusters at the moment", SkipAll);
#endif
    QString text = "AB CD";

    QTextLayout layout(text, testFont);
    QTextLine line;

    QTextOption opt;
    opt.setWrapMode(QTextOption::NoWrap);
    layout.setTextOption(opt);
    layout.beginLayout();

    line = layout.createLine();
    line.setLineWidth(testFont.pixelSize() * 2);
    QCOMPARE(line.textStart(), 0);
    QCOMPARE(line.textLength(), 5);

    line = layout.createLine();
    QVERIFY(!line.isValid());

    layout.endLayout();
}

void tst_QTextLayout::cursorToXForInlineObjects()
{
    QChar ch(QChar::ObjectReplacementCharacter);
    QString text(ch);
    QTextLayout layout(text, testFont);
    layout.beginLayout();

    QTextEngine *engine = layout.engine();
    const int item = engine->findItem(0);
    engine->layoutData->items[item].width = 32;

    QTextLine line = layout.createLine();
    line.setLineWidth(0x10000);

    QCOMPARE(line.cursorToX(0), qreal(0));
    QCOMPARE(line.cursorToX(1), qreal(32));
}

void tst_QTextLayout::cursorToXForSetColumns()
{
    QTextLayout lay("abc", testFont);
    QTextOption o = lay.textOption();
    o.setWrapMode(QTextOption::WrapAnywhere);

    // enable/disable this line for full effect ;)
    o.setAlignment(Qt::AlignHCenter);

    lay.setTextOption(o);
    lay.beginLayout();
    QTextLine line = lay.createLine();
    line.setNumColumns(1);
    lay.endLayout();
    QCOMPARE(line.cursorToX(0), 0.);
    QCOMPARE(line.cursorToX(1), (qreal) TESTFONT_SIZE);
}

void tst_QTextLayout::defaultWordSeparators_data()
{
    QTest::addColumn<QString>("text");
    QTest::addColumn<int>("startPos");
    QTest::addColumn<int>("endPos");

    QString separators(".,:;-<>[](){}=/+%&^*");
    separators += QLatin1String("!?");
    for (int i = 0; i < separators.count(); ++i) {
        QTest::newRow(QString::number(i).toAscii().data())
            << QString::fromLatin1("abcd") + separators.at(i) + QString::fromLatin1("efgh")
            <<  0 << 4;
    }

    QTest::newRow("nbsp")
            << QString::fromLatin1("abcd") + QString(QChar::Nbsp) + QString::fromLatin1("efgh")
            << 0 << 5;

    QTest::newRow("tab")
        << QString::fromLatin1("abcd") + QString::fromLatin1("\t") + QString::fromLatin1("efgh")
            << 0 << 5;

    QTest::newRow("lineseparator")
            << QString::fromLatin1("abcd") + QString(QChar::LineSeparator) + QString::fromLatin1("efgh")
            << 0 << 5;
}

void tst_QTextLayout::defaultWordSeparators()
{
    QFETCH(QString, text);
    QFETCH(int, startPos);
    QFETCH(int, endPos);
    QTextLayout layout(text, testFont);

    QCOMPARE(layout.nextCursorPosition(startPos, QTextLayout::SkipWords), endPos);
    QCOMPARE(layout.previousCursorPosition(endPos, QTextLayout::SkipWords), startPos);
}

void tst_QTextLayout::cursorMovementInsideSpaces()
{
    QTextLayout layout("ABC            DEF", testFont);

    QCOMPARE(layout.previousCursorPosition(6, QTextLayout::SkipWords), 0);
    QCOMPARE(layout.nextCursorPosition(6, QTextLayout::SkipWords), 15);
}

void tst_QTextLayout::charWordStopOnLineSeparator()
{
    const QChar lineSeparator(QChar::LineSeparator);
    QString txt;
    txt.append(lineSeparator);
    txt.append(lineSeparator);
    QTextLayout layout(txt, testFont);
    QTextEngine *engine = layout.engine();
    const HB_CharAttributes *attrs = engine->attributes();
    QVERIFY(attrs);
    QVERIFY(attrs[1].charStop);
}

void tst_QTextLayout::xToCursorAtEndOfLine()
{
#if defined(Q_WS_MAC)
    QSKIP("QTestFontEngine on the mac does not support logclusters at the moment", SkipAll);
#endif
    QString text = "FirstLine SecondLine";
    text.replace('\n', QChar::LineSeparator);

    const qreal firstLineWidth = QString("FirstLine").length() * testFont.pixelSize();

    QTextLayout layout(text, testFont);

    layout.beginLayout();
    QTextLine line = layout.createLine();
    QVERIFY(line.isValid());
    line.setLineWidth(firstLineWidth);
    QVERIFY(layout.createLine().isValid());
    QVERIFY(!layout.createLine().isValid());
    layout.endLayout();

    line = layout.lineAt(0);
    QCOMPARE(line.xToCursor(100000), 9);
    line = layout.lineAt(1);
    QCOMPARE(line.xToCursor(100000), 20);
}

void tst_QTextLayout::boundingRectTopLeft()
{
    QString text = "FirstLine\nSecondLine";
    text.replace('\n', QChar::LineSeparator);

    QTextLayout layout(text, testFont);

    layout.beginLayout();
    QTextLine firstLine = layout.createLine();
    QVERIFY(firstLine.isValid());
    firstLine.setPosition(QPointF(10, 10));
    QTextLine secondLine = layout.createLine();
    QVERIFY(secondLine.isValid());
    secondLine.setPosition(QPointF(20, 20));
    layout.endLayout();

    QCOMPARE(layout.boundingRect().topLeft(), firstLine.position());
}

void tst_QTextLayout::charStopForSurrogatePairs()
{
    QString txt;
    txt.append("a");
    txt.append(0xd87e);
    txt.append(0xdc25);
    txt.append("b");
    QTextLayout layout(txt, testFont);
    QTextEngine *engine = layout.engine();
    const HB_CharAttributes *attrs = engine->attributes();
    QVERIFY(attrs);
    QVERIFY(attrs[0].charStop);
    QVERIFY(attrs[1].charStop);
    QVERIFY(!attrs[2].charStop);
    QVERIFY(attrs[3].charStop);
}

void tst_QTextLayout::tabStops()
{
#if defined(Q_WS_MAC)
    QSKIP("QTestFontEngine on the mac does not support logclusters at the moment", SkipAll);
#endif
    QString txt("Hello there\tworld");
    QTextLayout layout(txt, testFont);
    layout.beginLayout();
    QTextLine line = layout.createLine();

    QVERIFY(line.isValid());
    line.setNumColumns(11);
    QCOMPARE(line.textLength(), TESTFONT_SIZE);

    line = layout.createLine();
    QVERIFY(line.isValid());
    line.setNumColumns(5);
    QCOMPARE(line.textLength(), 5);

    layout.endLayout();
}

void tst_QTextLayout::integerOverflow()
{
    QString txt("Hello world... ");

    for (int i = 0; i < 8; ++i)
        txt += txt;

    QTextLayout layout(txt, testFont);
    layout.beginLayout();
    QTextLine line = layout.createLine();

    QVERIFY(line.isValid());
    line.setLineWidth(INT_MAX);
    QCOMPARE(line.textLength(), txt.length());

    QVERIFY(!layout.createLine().isValid());

    layout.endLayout();
}

void tst_QTextLayout::setNumColumnsWrapAtWordBoundaryOrAnywhere()
{
    QString txt("This is a small test text");
    QTextLayout layout(txt, testFont);
    QTextOption option = layout.textOption();
    option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    layout.setTextOption(option);

    layout.beginLayout();
    QTextLine line1 = layout.createLine();
    QVERIFY(line1.isValid());
    line1.setNumColumns(1);

    // qDebug() << line1.naturalTextWidth();
    QCOMPARE(line1.textLength(), 1);
    QVERIFY(line1.naturalTextWidth() == testFont.pixelSize()); // contains only one character

    QTextLine line2 = layout.createLine();
    QVERIFY(line2.isValid());

    layout.endLayout();
}

void tst_QTextLayout::setNumColumnsWordWrap()
{
    QString txt("This is a small test text");
    QTextLayout layout(txt, testFont);
    QTextOption option = layout.textOption();
    option.setWrapMode(QTextOption::WordWrap);
    layout.setTextOption(option);

    layout.beginLayout();
    QTextLine line1 = layout.createLine();
    QVERIFY(line1.isValid());
    line1.setNumColumns(1);

    // qDebug() << line1.naturalTextWidth();
    QCOMPARE(line1.textLength(), 5);
    QVERIFY(line1.naturalTextWidth() > 20.0); // contains the whole first word.

    QTextLine line2 = layout.createLine();
    QVERIFY(line2.isValid());

    layout.endLayout();
}

void tst_QTextLayout::smallTextLengthNoWrap()
{
    QString txt("This is a small test text");
    QTextLayout layout(txt, testFont);
    QTextOption option = layout.textOption();
    option.setWrapMode(QTextOption::NoWrap);
    layout.setTextOption(option);

    /// NoWrap
    layout.beginLayout();
    QTextLine line1 = layout.createLine();
    QVERIFY(line1.isValid());
    line1.setLineWidth(5); // most certainly too short for the word 'This' to fit.

    QCOMPARE(line1.width(), 5.0);
    QVERIFY(line1.naturalTextWidth() > 70); // contains all the text.

    QTextLine line2 = layout.createLine();
    QVERIFY(! line2.isValid());

    layout.endLayout();
}

void tst_QTextLayout::smallTextLengthWordWrap()
{
    QString txt("This is a small test text");
    QTextLayout layout(txt, testFont);
    QTextOption option = layout.textOption();
    option.setWrapMode(QTextOption::WordWrap);
    layout.setTextOption(option);

    /// WordWrap
    layout.beginLayout();
    QTextLine line1 = layout.createLine();
    QVERIFY(line1.isValid());
    line1.setLineWidth(5); // most certainly too short for the word 'This' to fit.

    QCOMPARE(line1.width(), 5.0);
    QVERIFY(line1.naturalTextWidth() > 20.0); // contains the whole first word.
    QCOMPARE(line1.textLength(), 5);

    QTextLine line2 = layout.createLine();
    QVERIFY(line2.isValid());

    layout.endLayout();
}

void tst_QTextLayout::smallTextLengthWrapAtWordBoundaryOrAnywhere()
{
    QString txt("This is a small test text");
    QTextLayout layout(txt, testFont);
    QTextOption option = layout.textOption();
    option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    layout.setTextOption(option);

    layout.beginLayout();
    QTextLine line1 = layout.createLine();
    QVERIFY(line1.isValid());
    line1.setLineWidth(5); // most certainly too short for the word 'This' to fit.

    QCOMPARE(line1.width(), 5.0);
    // qDebug() << line1.naturalTextWidth();
    QCOMPARE(line1.textLength(), 1);
    QVERIFY(line1.naturalTextWidth() == testFont.pixelSize()); // contains just the characters that fit.

    QTextLine line2 = layout.createLine();
    QVERIFY(line2.isValid());

    layout.endLayout();
}

void tst_QTextLayout::testDefaultTabs()
{
    QTextLayout layout("Foo\tBar\ta slightly longer text\tend.", testFont);
    layout.beginLayout();
    QTextLine line = layout.createLine();
    line.setLineWidth(1000);
    layout.endLayout();

    //qDebug() << "After the tab: " << line.cursorToX(4);
    QCOMPARE(line.cursorToX(4), 80.); // default tab is 80
    QCOMPARE(line.cursorToX(8), 160.);
    QCOMPARE(line.cursorToX(31), 480.);

    QTextOption option = layout.textOption();
    option.setTabStop(90);
    layout.setTextOption(option);
    layout.beginLayout();
    line = layout.createLine();
    line.setLineWidth(1000);
    layout.endLayout();

    QCOMPARE(line.cursorToX(4), 90.);
    QCOMPARE(line.cursorToX(8), 180.);
    QCOMPARE(line.cursorToX(31), 450.);

    QList<QTextOption::Tab> tabs;
    QTextOption::Tab tab;
    tab.position = 110; // set one tab to 110, but since the rest is unset they will be at the normal interval again.
    tabs.append(tab);
    option.setTabs(tabs);
    layout.setTextOption(option);
    layout.beginLayout();
    line = layout.createLine();
    line.setLineWidth(1000);
    layout.endLayout();

    QCOMPARE(line.cursorToX(4), 110.);
    QCOMPARE(line.cursorToX(8), 180.);
    QCOMPARE(line.cursorToX(31), 450.);
}

void tst_QTextLayout::testTabs()
{
    QTextLayout layout("Foo\tBar.", testFont);
    QTextOption option = layout.textOption();
    option.setTabStop(150);
    layout.setTextOption(option);

    layout.beginLayout();
    QTextLine line = layout.createLine();
    line.setLineWidth(200.);
    layout.endLayout();

    QVERIFY(line.naturalTextWidth() > 150);
    QCOMPARE(line.cursorToX(4), 150.);
}

void tst_QTextLayout::testMultilineTab()
{
    QTextLayout layout("Lorem ipsum dolor sit\tBar.", testFont);
    // test if this works on the second line.
    layout.beginLayout();
    QTextLine line = layout.createLine();
    line.setLineWidth(220.); // moves 'sit' to next line.
    line = layout.createLine();
    line.setLineWidth(220.);
    layout.endLayout();

    QCOMPARE(line.cursorToX(22), 80.);
}

void tst_QTextLayout::testMultiTab()
{
    QTextLayout layout("Foo\t\t\tBar.", testFont);
    layout.beginLayout();
    QTextLine line = layout.createLine();
    line.setLineWidth(1000.);
    layout.endLayout();

    QCOMPARE(line.cursorToX(6), 80. * 3);
}

void tst_QTextLayout::testTabsInAlignedParag()
{
    QTextLayout layout("Foo\tsome more words", testFont);
    QTextOption option = layout.textOption();
    // right
    option.setAlignment(Qt::AlignRight);
    layout.setTextOption(option);

    layout.beginLayout();
    QTextLine line = layout.createLine();
    line.setLineWidth(300.);
    layout.endLayout();

    const qreal textWidth = 80 + 15 * TESTFONT_SIZE; // 15 chars right of the tab
    QCOMPARE(line.naturalTextWidth(), textWidth);
    QCOMPARE(line.cursorToX(0), 300. - textWidth);

    // centered
    option.setAlignment(Qt::AlignCenter);
    layout.setTextOption(option);

    layout.beginLayout();
    line = layout.createLine();
    line.setLineWidth(300.);
    layout.endLayout();

    QCOMPARE(line.naturalTextWidth(), textWidth);
    QCOMPARE(line.cursorToX(0), (300. - textWidth) / 2.);

    // justified
    option.setAlignment(Qt::AlignJustify);
    layout.setTextOption(option);

    layout.beginLayout();
    line = layout.createLine();
    line.setLineWidth(textWidth - 10); // make the last word slip to the next line so justification actually happens.
    layout.endLayout();

    QCOMPARE(line.cursorToX(0), 0.);
    QCOMPARE(line.cursorToX(4), 80.);

    //QTextLayout layout2("Foo\tUt wisi enim ad minim veniam, quis nostrud exerci tation ullamcorper suscipit lobortis", testFont); // means it will be more then one line long.
}

void tst_QTextLayout::testRightTab()
{
    QTextLayout layout("Foo\tLorem ipsum te sit\tBar baz\tText\tEnd", testFont);
    /*                     ^ a                 ^ b      ^ c   ^ d
     a = 4, b = 22, c = 30, d = 35 (position)

     I expect the output to be:
        Foo Lorem ipsum te
        sit      Bar Baz
        Text         End

     a) tab replaced with a single space due to the text not fitting before the tab.
     b) tab takes space so the text until the 3th tab fits to the tab pos.
     c) tab is after last tab (both auto and defined) and thus moves text to start of next line.
     d) tab takes space so text until enter fits to tab pos.
    */

    QTextOption option = layout.textOption();
    QList<QTextOption::Tab> tabs;
    QTextOption::Tab tab;
    tab.type = QTextOption::RightTab;
    tab.position = 190; // which means only 15(.8) chars of our test font fit left of it.
    tabs.append(tab);
    option.setTabs(tabs);
    layout.setTextOption(option);

    layout.beginLayout();
    QTextLine line1 = layout.createLine();
    line1.setLineWidth(220.);
    // qDebug() << "=====line 2";
    QTextLine line2 = layout.createLine();
    QVERIFY(line2.isValid());
    line2.setLineWidth(220.);
    // qDebug() << "=====line 3";
    QTextLine line3 = layout.createLine();
    QVERIFY(line3.isValid());
    line3.setLineWidth(220.);
    // qDebug() << "=====line 4";
    QTextLine line4 = layout.createLine();
    QVERIFY(! line4.isValid());
    layout.endLayout();
    // qDebug() << "--------";

    QCOMPARE(line1.cursorToX(4), 3. * TESTFONT_SIZE ); // a
    QCOMPARE(line1.textLength(), 19);
    QCOMPARE(line2.cursorToX(23), 190. - 7. * TESTFONT_SIZE); // b
    QCOMPARE(line2.textLength(), 12);
    QCOMPARE(line3.cursorToX(31), 0.); // c
    QCOMPARE(line3.cursorToX(36), 190 - 3. * TESTFONT_SIZE); // d
}

void tst_QTextLayout::testCenteredTab()
{
    QTextLayout layout("Foo\tBar", testFont);
    // test if centering the tab works.  We expect the center of 'Bar.' to be at the tab point.
    QTextOption option = layout.textOption();
    QList<QTextOption::Tab> tabs;
    QTextOption::Tab tab;
    tab.type = QTextOption::CenterTab;
    tab.position = 150;
    tabs.append(tab);
    option.setTabs(tabs);
    layout.setTextOption(option);

    layout.beginLayout();
    QTextLine line = layout.createLine();
    line.setLineWidth(200.);
    layout.endLayout();

    const qreal wordLength = 3 * TESTFONT_SIZE; // the length of 'Bar'
    QCOMPARE(line.cursorToX(4), 150 - wordLength / 2.);
}

void tst_QTextLayout::testDelimiterTab()
{
    QTextLayout layout("Foo\tBar. Barrabas", testFont);
    // try the different delimiter characters to see if the alignment works there.
    QTextOption option = layout.textOption();
    QList<QTextOption::Tab> tabs;
    QTextOption::Tab tab;
    tab.type = QTextOption::DelimiterTab;
    tab.delimiter = QChar('.');
    tab.position = 100;
    tabs.append(tab);
    option.setTabs(tabs);
    layout.setTextOption(option);

    layout.beginLayout();
    QTextLine line = layout.createLine();
    line.setLineWidth(200.);
    layout.endLayout();

    const qreal distanceBeforeTab = 3.5 * TESTFONT_SIZE; // the length of 'bar' and half the width of the dot.
    QCOMPARE(line.cursorToX(4), 100 - distanceBeforeTab);
}

void tst_QTextLayout::testLineBreakingAllSpaces()
{
    QTextLayout layout("                    123", testFont); // thats 20 spaces
    const qreal firstLineWidth = 17 * TESTFONT_SIZE;
    layout.beginLayout();
    QTextLine line1 = layout.createLine();
    line1.setLineWidth(firstLineWidth);
    QTextLine line2 = layout.createLine();
    line2.setLineWidth(1000); // the rest
    layout.endLayout();
    QCOMPARE(line1.width(), firstLineWidth);
    QCOMPARE(line1.naturalTextWidth(), 0.); // spaces don't take space
    QCOMPARE(line1.textLength(), 20);
    QCOMPARE(line2.textLength(), 3);
    QCOMPARE(line2.naturalTextWidth(), 3. * TESTFONT_SIZE);
}

void tst_QTextLayout::tabsForRtl()
{
    QString word(QChar(0x5e9)); // a hebrew character
    word = word + word + word;  // 3 hebrew characters ;)

    QTextLayout layout(word +'\t'+ word +'\t'+ word +'\t'+ word, testFont);
//QTextLayout layout(word +' '+ word +' '+ word +' '+ word, testFont);// tester ;)
    /*                             ^ a         ^ b         ^ c
     a = 4, b = 8, c = 12, d = 16 (position)

     a) Left tab in RTL is a righ tab; so a is at width - 80
     b) Like a
     c) right tab on RTL is a left tab; so its at width - 240
     d) center tab is still a centered tab.
    */

    QTextOption option = layout.textOption();
    QList<QTextOption::Tab> tabs;
    QTextOption::Tab tab;
    tab.position = 80;
    tabs.append(tab);
    tab.position = 160;
    tabs.append(tab);
    tab.position = 240;
    tab.type = QTextOption::RightTab;
    tabs.append(tab);
    option.setTabs(tabs);
    option.setTextDirection(Qt::RightToLeft);
    option.setAlignment(Qt::AlignRight);
    layout.setTextOption(option);

    layout.beginLayout();
    QTextLine line = layout.createLine();
    const qreal WIDTH = 400.;
    line.setLineWidth(WIDTH);
    layout.endLayout();

//qDebug() << "layout ended --------------";

    QCOMPARE(line.cursorToX(0), WIDTH);
    QCOMPARE(line.cursorToX(1), WIDTH - TESTFONT_SIZE); // check its right-aligned
    QCOMPARE(line.cursorToX(4), WIDTH - 80 + 3 * TESTFONT_SIZE);
    QCOMPARE(line.cursorToX(8), WIDTH - 160 + 3 * TESTFONT_SIZE);
    QCOMPARE(line.cursorToX(12), WIDTH - 240);
}

QT_BEGIN_NAMESPACE
extern int qt_defaultDpiY();
QT_END_NAMESPACE

void tst_QTextLayout::testTabDPIScale()
{
    #ifdef Q_OS_WINCE
    QSKIP("This test fails for large DPIs.", SkipAll);
    #endif

    class MyPaintDevice : public QPaintDevice {
        QPaintEngine *paintEngine () const { return 0; }
        int metric (QPaintDevice::PaintDeviceMetric metric) const {
            switch(metric) {
            case QPaintDevice::PdmWidth:
            case QPaintDevice::PdmHeight:
            case QPaintDevice::PdmWidthMM:
            case QPaintDevice::PdmHeightMM:
            case QPaintDevice::PdmNumColors:
                return INT_MAX;
            case QPaintDevice::PdmDepth:
                return 32;
            case QPaintDevice::PdmDpiX:
            case QPaintDevice::PdmDpiY:
            case QPaintDevice::PdmPhysicalDpiX:
            case QPaintDevice::PdmPhysicalDpiY:
                return 72;
            }
            return 0;
        }
    };

    MyPaintDevice pd;

    QTextLayout layout("text1\ttext2\ttext3\tend", testFont, &pd);

    QTextOption option = layout.textOption();
    QList<QTextOption::Tab> tabs;
    QTextOption::Tab tab;
    tab.position = 100;
    tabs.append(tab);

    tab.position = 200;
    tab.type = QTextOption::RightTab;
    tabs.append(tab);

    tab.position = 300;
    tab.type = QTextOption::CenterTab;
    tabs.append(tab);
    option.setTabs(tabs);
    layout.setTextOption(option);

    layout.beginLayout();
    QTextLine line = layout.createLine();
    line.setLineWidth(500.);
    layout.endLayout();
    QCOMPARE(line.cursorToX(0), 0.);
    QCOMPARE(line.cursorToX(1), (double) TESTFONT_SIZE); // check that the font does not resize
    qreal scale = 72 / (qreal) qt_defaultDpiY();
    // lets do the transformation of deminishing resolution that QFixed has as effect.
    int fixedScale = (int)( scale * qreal(64)); // into a QFixed
    scale = ((qreal)fixedScale)/(qreal)64;      // and out of a QFixed

    QCOMPARE(line.cursorToX(6), 100 * scale);
    QCOMPARE(line.cursorToX(12), 200 * scale - TESTFONT_SIZE * 5);
    QCOMPARE(line.cursorToX(18), 300 * scale - TESTFONT_SIZE * 3 / 2.0);
}

void tst_QTextLayout::tabHeight()
{
    QTextLayout layout("\t", testFont);
    layout.beginLayout();
    QTextLine line = layout.createLine();
    layout.endLayout();

    QCOMPARE(qRound(line.ascent()), QFontMetrics(testFont).ascent());
    QCOMPARE(qRound(line.descent()), QFontMetrics(testFont).descent());
}

void tst_QTextLayout::capitalization_allUpperCase()
{
    QFont font(testFont);
    font.setCapitalization(QFont::AllUppercase);
    QTextLayout layout("Test", font);
    layout.beginLayout();
    QTextLine line = layout.createLine();
    layout.endLayout();

    QTextEngine *engine = layout.engine();
    engine->itemize();
    QCOMPARE(engine->layoutData->items.count(), 1);
    QVERIFY(engine->layoutData->items.at(0).analysis.flags == QScriptAnalysis::Uppercase);
}

void tst_QTextLayout::capitalization_allLowerCase()
{
    QFont font(testFont);
    font.setCapitalization(QFont::AllLowercase);
    QTextLayout layout("Test", font);
    layout.beginLayout();
    QTextLine line = layout.createLine();
    layout.endLayout();

    QTextEngine *engine = layout.engine();
    engine->itemize();
    QCOMPARE(engine->layoutData->items.count(), 1);
    QVERIFY(engine->layoutData->items.at(0).analysis.flags == QScriptAnalysis::Lowercase);
}

void tst_QTextLayout::capitalization_smallCaps()
{
    QFont font(testFont);
    font.setCapitalization(QFont::SmallCaps);
    QTextLayout layout("Test", font);
    layout.beginLayout();
    QTextLine line = layout.createLine();
    layout.endLayout();

    QTextEngine *engine = layout.engine();
    engine->itemize();
    QCOMPARE(engine->layoutData->items.count(), 2);
    QVERIFY(engine->layoutData->items.at(0).analysis.flags == QScriptAnalysis::None);
    QVERIFY(engine->layoutData->items.at(1).analysis.flags == QScriptAnalysis::SmallCaps);
}

void tst_QTextLayout::capitalization_capitalize()
{
    QFont font(testFont);
    font.setCapitalization(QFont::Capitalize);
    QTextLayout layout("hello\tworld", font);
    layout.beginLayout();
    QTextLine line = layout.createLine();
    layout.endLayout();

    QTextEngine *engine = layout.engine();
    engine->itemize();
    QCOMPARE(engine->layoutData->items.count(), 5);
    QVERIFY(engine->layoutData->items.at(0).analysis.flags == QScriptAnalysis::Uppercase);
    QVERIFY(engine->layoutData->items.at(1).analysis.flags == QScriptAnalysis::None);
    QVERIFY(engine->layoutData->items.at(2).analysis.flags == QScriptAnalysis::Tab);
    QVERIFY(engine->layoutData->items.at(3).analysis.flags == QScriptAnalysis::Uppercase);
    QVERIFY(engine->layoutData->items.at(4).analysis.flags == QScriptAnalysis::None);
}

void tst_QTextLayout::longText()
{
    QString longText(128000, 'a');

    {
        QTextLayout layout(longText, testFont);
        layout.beginLayout();
        QTextLine line = layout.createLine();
        layout.endLayout();
        QVERIFY(line.isValid());
        QVERIFY(line.cursorToX(line.textLength() - 1) > 0);
    }

    for (int cap = QFont::MixedCase; cap < QFont::Capitalize + 1; ++cap) {
        QFont f(testFont);
        f.setCapitalization(QFont::Capitalization(cap));
        QTextLayout layout(longText, f);
        layout.beginLayout();
        QTextLine line = layout.createLine();
        layout.endLayout();
        QVERIFY(line.isValid());
        QVERIFY(line.cursorToX(line.textLength() - 1) > 0);
    }

    {
        QTextLayout layout(longText, testFont);
        layout.setFlags(Qt::TextForceLeftToRight);
        layout.beginLayout();
        QTextLine line = layout.createLine();
        layout.endLayout();
        QVERIFY(line.isValid());
        QVERIFY(line.cursorToX(line.textLength() - 1) > 0);
    }

    {
        QTextLayout layout(longText, testFont);
        layout.setFlags(Qt::TextForceRightToLeft);
        layout.beginLayout();
        QTextLine line = layout.createLine();
        layout.endLayout();
        QVERIFY(line.isValid());
        QVERIFY(line.cursorToX(line.textLength() - 1) > 0);
    }
}

void tst_QTextLayout::widthOfTabs()
{
    QTextEngine engine("ddd\t\t", testFont);
    engine.ignoreBidi = true;
    engine.itemize();
    QCOMPARE(qRound(engine.width(0, 5)), qRound(engine.boundingBox(0, 5).width));
}

QTEST_MAIN(tst_QTextLayout)
#include "tst_qtextlayout.moc"
