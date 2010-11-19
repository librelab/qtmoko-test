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

/********************************************************************************
** Form generated from reading ui file 'validators.ui'
**
** Created: Thu Jul 10 09:47:35 2008
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef VALIDATORS_H
#define VALIDATORS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "ledwidget.h"
#include "localeselector.h"

QT_BEGIN_NAMESPACE

class Ui_ValidatorsForm
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    LocaleSelector *localeSelector;
    QSpacerItem *spacerItem;
    QGroupBox *groupBox;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout1;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpinBox *minVal;
    QLabel *label_2;
    QSpinBox *maxVal;
    QFrame *frame;
    QVBoxLayout *vboxLayout2;
    LEDWidget *ledWidget;
    QLabel *label_7;
    QSpacerItem *spacerItem1;
    QLineEdit *editor;
    QGroupBox *groupBox_2;
    QVBoxLayout *vboxLayout3;
    QHBoxLayout *hboxLayout2;
    QGridLayout *gridLayout1;
    QLabel *label_3;
    QDoubleSpinBox *doubleMinVal;
    QLabel *label_5;
    QComboBox *doubleFormat;
    QLabel *label_4;
    QDoubleSpinBox *doubleMaxVal;
    QLabel *label_6;
    QSpinBox *doubleDecimals;
    QFrame *frame_2;
    QVBoxLayout *vboxLayout4;
    LEDWidget *doubleLedWidget;
    QLabel *label_8;
    QSpacerItem *spacerItem2;
    QLineEdit *doubleEditor;
    QSpacerItem *spacerItem3;
    QHBoxLayout *hboxLayout3;
    QSpacerItem *spacerItem4;
    QPushButton *pushButton;

    void setupUi(QWidget *ValidatorsForm)
    {
        if (ValidatorsForm->objectName().isEmpty())
            ValidatorsForm->setObjectName(QString::fromUtf8("ValidatorsForm"));
        ValidatorsForm->resize(526, 668);
        vboxLayout = new QVBoxLayout(ValidatorsForm);
#ifndef Q_OS_MAC
        vboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout->setMargin(9);
#endif
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        hboxLayout->setMargin(0);
#endif
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        localeSelector = new LocaleSelector(ValidatorsForm);
        localeSelector->setObjectName(QString::fromUtf8("localeSelector"));

        hboxLayout->addWidget(localeSelector);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);


        vboxLayout->addLayout(hboxLayout);

        groupBox = new QGroupBox(ValidatorsForm);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        vboxLayout1 = new QVBoxLayout(groupBox);
#ifndef Q_OS_MAC
        vboxLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout1->setMargin(9);
#endif
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        hboxLayout1 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        hboxLayout1->setMargin(0);
#endif
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        gridLayout = new QGridLayout();
#ifndef Q_OS_MAC
        gridLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout->setMargin(0);
#endif
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        minVal = new QSpinBox(groupBox);
        minVal->setObjectName(QString::fromUtf8("minVal"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(minVal->sizePolicy().hasHeightForWidth());
        minVal->setSizePolicy(sizePolicy);
        minVal->setMinimum(-1000000);
        minVal->setMaximum(1000000);

        gridLayout->addWidget(minVal, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        maxVal = new QSpinBox(groupBox);
        maxVal->setObjectName(QString::fromUtf8("maxVal"));
        sizePolicy.setHeightForWidth(maxVal->sizePolicy().hasHeightForWidth());
        maxVal->setSizePolicy(sizePolicy);
        maxVal->setMinimum(-1000000);
        maxVal->setMaximum(1000000);
        maxVal->setValue(1000);

        gridLayout->addWidget(maxVal, 1, 1, 1, 1);


        hboxLayout1->addLayout(gridLayout);

        frame = new QFrame(groupBox);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        vboxLayout2 = new QVBoxLayout(frame);
#ifndef Q_OS_MAC
        vboxLayout2->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout2->setMargin(9);
#endif
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        ledWidget = new LEDWidget(frame);
        ledWidget->setObjectName(QString::fromUtf8("ledWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ledWidget->sizePolicy().hasHeightForWidth());
        ledWidget->setSizePolicy(sizePolicy1);
        ledWidget->setPixmap(QPixmap(QString::fromUtf8(":/ledoff.png")));
        ledWidget->setAlignment(Qt::AlignCenter);

        vboxLayout2->addWidget(ledWidget);

        label_7 = new QLabel(frame);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        vboxLayout2->addWidget(label_7);


        hboxLayout1->addWidget(frame);


        vboxLayout1->addLayout(hboxLayout1);

        spacerItem1 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        vboxLayout1->addItem(spacerItem1);

        editor = new QLineEdit(groupBox);
        editor->setObjectName(QString::fromUtf8("editor"));

        vboxLayout1->addWidget(editor);


        vboxLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(ValidatorsForm);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        vboxLayout3 = new QVBoxLayout(groupBox_2);
#ifndef Q_OS_MAC
        vboxLayout3->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout3->setMargin(9);
#endif
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        hboxLayout2 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout2->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        hboxLayout2->setMargin(0);
#endif
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        gridLayout1 = new QGridLayout();
#ifndef Q_OS_MAC
        gridLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout1->setMargin(0);
#endif
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout1->addWidget(label_3, 0, 0, 1, 1);

        doubleMinVal = new QDoubleSpinBox(groupBox_2);
        doubleMinVal->setObjectName(QString::fromUtf8("doubleMinVal"));
        sizePolicy.setHeightForWidth(doubleMinVal->sizePolicy().hasHeightForWidth());
        doubleMinVal->setSizePolicy(sizePolicy);
        doubleMinVal->setMinimum(-100000);
        doubleMinVal->setMaximum(100000);
        doubleMinVal->setValue(0);

        gridLayout1->addWidget(doubleMinVal, 0, 1, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout1->addWidget(label_5, 0, 2, 1, 1);

        doubleFormat = new QComboBox(groupBox_2);
        doubleFormat->setObjectName(QString::fromUtf8("doubleFormat"));

        gridLayout1->addWidget(doubleFormat, 0, 3, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout1->addWidget(label_4, 1, 0, 1, 1);

        doubleMaxVal = new QDoubleSpinBox(groupBox_2);
        doubleMaxVal->setObjectName(QString::fromUtf8("doubleMaxVal"));
        sizePolicy.setHeightForWidth(doubleMaxVal->sizePolicy().hasHeightForWidth());
        doubleMaxVal->setSizePolicy(sizePolicy);
        doubleMaxVal->setMinimum(-100000);
        doubleMaxVal->setMaximum(100000);
        doubleMaxVal->setValue(1000);

        gridLayout1->addWidget(doubleMaxVal, 1, 1, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout1->addWidget(label_6, 1, 2, 1, 1);

        doubleDecimals = new QSpinBox(groupBox_2);
        doubleDecimals->setObjectName(QString::fromUtf8("doubleDecimals"));
        doubleDecimals->setValue(2);

        gridLayout1->addWidget(doubleDecimals, 1, 3, 1, 1);


        hboxLayout2->addLayout(gridLayout1);

        frame_2 = new QFrame(groupBox_2);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        vboxLayout4 = new QVBoxLayout(frame_2);
#ifndef Q_OS_MAC
        vboxLayout4->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout4->setMargin(9);
#endif
        vboxLayout4->setObjectName(QString::fromUtf8("vboxLayout4"));
        doubleLedWidget = new LEDWidget(frame_2);
        doubleLedWidget->setObjectName(QString::fromUtf8("doubleLedWidget"));
        doubleLedWidget->setPixmap(QPixmap(QString::fromUtf8(":/ledoff.png")));
        doubleLedWidget->setAlignment(Qt::AlignCenter);

        vboxLayout4->addWidget(doubleLedWidget);

        label_8 = new QLabel(frame_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        vboxLayout4->addWidget(label_8);


        hboxLayout2->addWidget(frame_2);


        vboxLayout3->addLayout(hboxLayout2);

        spacerItem2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        vboxLayout3->addItem(spacerItem2);

        doubleEditor = new QLineEdit(groupBox_2);
        doubleEditor->setObjectName(QString::fromUtf8("doubleEditor"));

        vboxLayout3->addWidget(doubleEditor);


        vboxLayout->addWidget(groupBox_2);

        spacerItem3 = new QSpacerItem(20, 111, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacerItem3);

        hboxLayout3 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout3->setSpacing(6);
#endif
        hboxLayout3->setMargin(0);
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        spacerItem4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout3->addItem(spacerItem4);

        pushButton = new QPushButton(ValidatorsForm);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        hboxLayout3->addWidget(pushButton);


        vboxLayout->addLayout(hboxLayout3);


        retranslateUi(ValidatorsForm);
        QObject::connect(pushButton, SIGNAL(clicked()), ValidatorsForm, SLOT(close()));

        QMetaObject::connectSlotsByName(ValidatorsForm);
    } // setupUi

    void retranslateUi(QWidget *ValidatorsForm)
    {
        ValidatorsForm->setWindowTitle(QApplication::translate("ValidatorsForm", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("ValidatorsForm", "QIntValidator", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ValidatorsForm", "Min:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ValidatorsForm", "Max:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("ValidatorsForm", "editingFinished()", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("ValidatorsForm", "QDoubleValidator", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ValidatorsForm", "Min:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("ValidatorsForm", "Format:", 0, QApplication::UnicodeUTF8));
        doubleFormat->clear();
        doubleFormat->insertItems(0, QStringList()
         << QApplication::translate("ValidatorsForm", "Standard", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ValidatorsForm", "Scientific", 0, QApplication::UnicodeUTF8)
        );
        label_4->setText(QApplication::translate("ValidatorsForm", "Max:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("ValidatorsForm", "Decimals:", 0, QApplication::UnicodeUTF8));
        doubleLedWidget->setText(QString());
        label_8->setText(QApplication::translate("ValidatorsForm", "editingFinished()", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("ValidatorsForm", "Quit", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(ValidatorsForm);
    } // retranslateUi

};

namespace Ui {
    class ValidatorsForm: public Ui_ValidatorsForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // VALIDATORS_H
