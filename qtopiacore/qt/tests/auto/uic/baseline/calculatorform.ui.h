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
** Form generated from reading ui file 'calculatorform.ui'
**
** Created: Thu Jul 10 09:47:34 2008
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef CALCULATORFORM_H
#define CALCULATORFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CalculatorForm
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout;
    QLabel *label;
    QSpinBox *inputSpinBox1;
    QLabel *label_3;
    QVBoxLayout *vboxLayout1;
    QLabel *label_2;
    QSpinBox *inputSpinBox2;
    QLabel *label_3_2;
    QVBoxLayout *vboxLayout2;
    QLabel *label_2_2_2;
    QLabel *outputWidget;
    QSpacerItem *spacerItem;
    QSpacerItem *spacerItem1;

    void setupUi(QWidget *CalculatorForm)
    {
        if (CalculatorForm->objectName().isEmpty())
            CalculatorForm->setObjectName(QString::fromUtf8("CalculatorForm"));
        CalculatorForm->resize(276, 98);
        QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(5));
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CalculatorForm->sizePolicy().hasHeightForWidth());
        CalculatorForm->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(CalculatorForm);
#ifndef Q_OS_MAC
        gridLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout->setMargin(9);
#endif
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setObjectName(QString::fromUtf8(""));
        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setMargin(1);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setObjectName(QString::fromUtf8(""));
        vboxLayout = new QVBoxLayout();
#ifndef Q_OS_MAC
        vboxLayout->setSpacing(6);
#endif
        vboxLayout->setMargin(1);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        vboxLayout->setObjectName(QString::fromUtf8(""));
        label = new QLabel(CalculatorForm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(1, 1, 45, 19));

        vboxLayout->addWidget(label);

        inputSpinBox1 = new QSpinBox(CalculatorForm);
        inputSpinBox1->setObjectName(QString::fromUtf8("inputSpinBox1"));
        inputSpinBox1->setGeometry(QRect(1, 26, 45, 25));
        inputSpinBox1->setMouseTracking(true);

        vboxLayout->addWidget(inputSpinBox1);


        hboxLayout->addLayout(vboxLayout);

        label_3 = new QLabel(CalculatorForm);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(54, 1, 7, 52));
        label_3->setAlignment(Qt::AlignCenter);

        hboxLayout->addWidget(label_3);

        vboxLayout1 = new QVBoxLayout();
#ifndef Q_OS_MAC
        vboxLayout1->setSpacing(6);
#endif
        vboxLayout1->setMargin(1);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        vboxLayout1->setObjectName(QString::fromUtf8(""));
        label_2 = new QLabel(CalculatorForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(1, 1, 45, 19));

        vboxLayout1->addWidget(label_2);

        inputSpinBox2 = new QSpinBox(CalculatorForm);
        inputSpinBox2->setObjectName(QString::fromUtf8("inputSpinBox2"));
        inputSpinBox2->setGeometry(QRect(1, 26, 45, 25));
        inputSpinBox2->setMouseTracking(true);

        vboxLayout1->addWidget(inputSpinBox2);


        hboxLayout->addLayout(vboxLayout1);

        label_3_2 = new QLabel(CalculatorForm);
        label_3_2->setObjectName(QString::fromUtf8("label_3_2"));
        label_3_2->setGeometry(QRect(120, 1, 7, 52));
        label_3_2->setAlignment(Qt::AlignCenter);

        hboxLayout->addWidget(label_3_2);

        vboxLayout2 = new QVBoxLayout();
#ifndef Q_OS_MAC
        vboxLayout2->setSpacing(6);
#endif
        vboxLayout2->setMargin(1);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        vboxLayout2->setObjectName(QString::fromUtf8(""));
        label_2_2_2 = new QLabel(CalculatorForm);
        label_2_2_2->setObjectName(QString::fromUtf8("label_2_2_2"));
        label_2_2_2->setGeometry(QRect(1, 1, 37, 17));

        vboxLayout2->addWidget(label_2_2_2);

        outputWidget = new QLabel(CalculatorForm);
        outputWidget->setObjectName(QString::fromUtf8("outputWidget"));
        outputWidget->setGeometry(QRect(1, 24, 37, 27));
        outputWidget->setFrameShape(QFrame::Box);
        outputWidget->setFrameShadow(QFrame::Sunken);
        outputWidget->setAlignment(Qt::AlignAbsolute|Qt::AlignBottom|Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignHorizontal_Mask|Qt::AlignJustify|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing|Qt::AlignVCenter|Qt::AlignVertical_Mask);

        vboxLayout2->addWidget(outputWidget);


        hboxLayout->addLayout(vboxLayout2);


        gridLayout->addLayout(hboxLayout, 0, 0, 1, 1);

        spacerItem = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(spacerItem, 1, 0, 1, 1);

        spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem1, 0, 1, 1, 1);


        retranslateUi(CalculatorForm);

        QMetaObject::connectSlotsByName(CalculatorForm);
    } // setupUi

    void retranslateUi(QWidget *CalculatorForm)
    {
        CalculatorForm->setWindowTitle(QApplication::translate("CalculatorForm", "Calculator Builder", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CalculatorForm", "Input 1", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("CalculatorForm", "+", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("CalculatorForm", "Input 2", 0, QApplication::UnicodeUTF8));
        label_3_2->setText(QApplication::translate("CalculatorForm", "=", 0, QApplication::UnicodeUTF8));
        label_2_2_2->setText(QApplication::translate("CalculatorForm", "Output", 0, QApplication::UnicodeUTF8));
        outputWidget->setText(QApplication::translate("CalculatorForm", "0", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(CalculatorForm);
    } // retranslateUi

};

namespace Ui {
    class CalculatorForm: public Ui_CalculatorForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CALCULATORFORM_H
