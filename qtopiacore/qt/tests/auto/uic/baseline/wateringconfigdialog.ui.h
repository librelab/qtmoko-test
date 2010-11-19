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
** Form generated from reading ui file 'wateringconfigdialog.ui'
**
** Created: Thu Jul 10 09:47:35 2008
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef WATERINGCONFIGDIALOG_H
#define WATERINGCONFIGDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTimeEdit>
#include <QtGui/QVBoxLayout>
#include "helpbrowser.h"

QT_BEGIN_NAMESPACE

class Ui_WateringConfigDialog
{
public:
    QVBoxLayout *vboxLayout;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QComboBox *plantComboBox;
    QSpacerItem *spacerItem;
    QLabel *label_2;
    QCheckBox *temperatureCheckBox;
    QSpacerItem *spacerItem1;
    QSpinBox *temperatureSpinBox;
    QSpacerItem *spacerItem2;
    QCheckBox *rainCheckBox;
    QSpacerItem *spacerItem3;
    QSpinBox *rainSpinBox;
    QSpacerItem *spacerItem4;
    QSpacerItem *spacerItem5;
    QLabel *label;
    QTimeEdit *startTimeEdit;
    QLabel *label_4;
    QSpinBox *amountSpinBox;
    QLabel *label_5;
    QComboBox *sourceComboBox;
    QLabel *label_6;
    QCheckBox *filterCheckBox;
    QSpacerItem *spacerItem6;
    QSpacerItem *spacerItem7;
    QGridLayout *gridLayout1;
    QSpacerItem *spacerItem8;
    HelpBrowser *helpBrowser;
    QLabel *helpLabel;
    QFrame *line;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *WateringConfigDialog)
    {
        if (WateringConfigDialog->objectName().isEmpty())
            WateringConfigDialog->setObjectName(QString::fromUtf8("WateringConfigDialog"));
        WateringConfigDialog->resize(334, 550);
        vboxLayout = new QVBoxLayout(WateringConfigDialog);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_3 = new QLabel(WateringConfigDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        plantComboBox = new QComboBox(WateringConfigDialog);
        plantComboBox->setObjectName(QString::fromUtf8("plantComboBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(plantComboBox->sizePolicy().hasHeightForWidth());
        plantComboBox->setSizePolicy(sizePolicy);

        gridLayout->addWidget(plantComboBox, 0, 1, 1, 3);

        spacerItem = new QSpacerItem(67, 16, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(spacerItem, 1, 0, 1, 1);

        label_2 = new QLabel(WateringConfigDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        temperatureCheckBox = new QCheckBox(WateringConfigDialog);
        temperatureCheckBox->setObjectName(QString::fromUtf8("temperatureCheckBox"));

        gridLayout->addWidget(temperatureCheckBox, 3, 1, 1, 3);

        spacerItem1 = new QSpacerItem(16, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem1, 4, 1, 1, 1);

        temperatureSpinBox = new QSpinBox(WateringConfigDialog);
        temperatureSpinBox->setObjectName(QString::fromUtf8("temperatureSpinBox"));
        temperatureSpinBox->setEnabled(false);
        temperatureSpinBox->setMinimum(10);
        temperatureSpinBox->setMaximum(60);
        temperatureSpinBox->setValue(20);

        gridLayout->addWidget(temperatureSpinBox, 4, 2, 1, 1);

        spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem2, 4, 3, 1, 1);

        rainCheckBox = new QCheckBox(WateringConfigDialog);
        rainCheckBox->setObjectName(QString::fromUtf8("rainCheckBox"));

        gridLayout->addWidget(rainCheckBox, 5, 1, 1, 3);

        spacerItem3 = new QSpacerItem(16, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem3, 6, 1, 1, 1);

        rainSpinBox = new QSpinBox(WateringConfigDialog);
        rainSpinBox->setObjectName(QString::fromUtf8("rainSpinBox"));
        rainSpinBox->setEnabled(false);
        rainSpinBox->setMinimum(1);

        gridLayout->addWidget(rainSpinBox, 6, 2, 1, 1);

        spacerItem4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem4, 6, 3, 1, 1);

        spacerItem5 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(spacerItem5, 7, 2, 1, 1);

        label = new QLabel(WateringConfigDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 8, 0, 1, 1);

        startTimeEdit = new QTimeEdit(WateringConfigDialog);
        startTimeEdit->setObjectName(QString::fromUtf8("startTimeEdit"));

        gridLayout->addWidget(startTimeEdit, 8, 1, 1, 3);

        label_4 = new QLabel(WateringConfigDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 9, 0, 1, 1);

        amountSpinBox = new QSpinBox(WateringConfigDialog);
        amountSpinBox->setObjectName(QString::fromUtf8("amountSpinBox"));
        amountSpinBox->setMinimum(100);
        amountSpinBox->setMaximum(10000);
        amountSpinBox->setSingleStep(100);
        amountSpinBox->setValue(1000);

        gridLayout->addWidget(amountSpinBox, 9, 1, 1, 3);

        label_5 = new QLabel(WateringConfigDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 10, 0, 1, 1);

        sourceComboBox = new QComboBox(WateringConfigDialog);
        sourceComboBox->setObjectName(QString::fromUtf8("sourceComboBox"));

        gridLayout->addWidget(sourceComboBox, 10, 1, 1, 3);

        label_6 = new QLabel(WateringConfigDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 11, 0, 1, 1);

        filterCheckBox = new QCheckBox(WateringConfigDialog);
        filterCheckBox->setObjectName(QString::fromUtf8("filterCheckBox"));

        gridLayout->addWidget(filterCheckBox, 11, 1, 1, 2);

        spacerItem6 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(spacerItem6, 12, 0, 1, 1);

        spacerItem7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem7, 4, 4, 1, 1);


        vboxLayout->addLayout(gridLayout);

        gridLayout1 = new QGridLayout();
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        spacerItem8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout1->addItem(spacerItem8, 0, 1, 1, 1);

        helpBrowser = new HelpBrowser(WateringConfigDialog);
        helpBrowser->setObjectName(QString::fromUtf8("helpBrowser"));

        gridLayout1->addWidget(helpBrowser, 1, 0, 1, 2);

        helpLabel = new QLabel(WateringConfigDialog);
        helpLabel->setObjectName(QString::fromUtf8("helpLabel"));

        gridLayout1->addWidget(helpLabel, 0, 0, 1, 1);


        vboxLayout->addLayout(gridLayout1);

        line = new QFrame(WateringConfigDialog);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        vboxLayout->addWidget(line);

        buttonBox = new QDialogButtonBox(WateringConfigDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);

        vboxLayout->addWidget(buttonBox);


        retranslateUi(WateringConfigDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), WateringConfigDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), WateringConfigDialog, SLOT(reject()));
        QObject::connect(temperatureCheckBox, SIGNAL(toggled(bool)), temperatureSpinBox, SLOT(setEnabled(bool)));
        QObject::connect(rainCheckBox, SIGNAL(toggled(bool)), rainSpinBox, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(WateringConfigDialog);
    } // setupUi

    void retranslateUi(QDialog *WateringConfigDialog)
    {
        WateringConfigDialog->setWindowTitle(QApplication::translate("WateringConfigDialog", "Watering Configuration", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("WateringConfigDialog", "Plant:", 0, QApplication::UnicodeUTF8));
        plantComboBox->clear();
        plantComboBox->insertItems(0, QStringList()
         << QApplication::translate("WateringConfigDialog", "Squash", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("WateringConfigDialog", "Bean", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("WateringConfigDialog", "Carrot", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("WateringConfigDialog", "Strawberry", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("WateringConfigDialog", "Raspberry", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("WateringConfigDialog", "Blueberry", 0, QApplication::UnicodeUTF8)
        );
        label_2->setText(QApplication::translate("WateringConfigDialog", "Water when:", 0, QApplication::UnicodeUTF8));
        temperatureCheckBox->setText(QApplication::translate("WateringConfigDialog", "Temperature is higher than:", 0, QApplication::UnicodeUTF8));
        temperatureSpinBox->setSpecialValueText(QString());
        temperatureSpinBox->setSuffix(QApplication::translate("WateringConfigDialog", "C", 0, QApplication::UnicodeUTF8));
        rainCheckBox->setText(QApplication::translate("WateringConfigDialog", "Rain less than:", 0, QApplication::UnicodeUTF8));
        rainSpinBox->setSpecialValueText(QString());
        rainSpinBox->setSuffix(QApplication::translate("WateringConfigDialog", "mm", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("WateringConfigDialog", "Starting Time:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("WateringConfigDialog", "Amount:", 0, QApplication::UnicodeUTF8));
        amountSpinBox->setSuffix(QApplication::translate("WateringConfigDialog", "l", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("WateringConfigDialog", "Source:", 0, QApplication::UnicodeUTF8));
        sourceComboBox->clear();
        sourceComboBox->insertItems(0, QStringList()
         << QApplication::translate("WateringConfigDialog", "Foundain", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("WateringConfigDialog", "River", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("WateringConfigDialog", "Lake", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("WateringConfigDialog", "Public Water System", 0, QApplication::UnicodeUTF8)
        );
        label_6->setText(QApplication::translate("WateringConfigDialog", "Filter:", 0, QApplication::UnicodeUTF8));
        filterCheckBox->setText(QString());
        helpLabel->setText(QApplication::translate("WateringConfigDialog", "<a href=\"test\">Show Details</a>", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(WateringConfigDialog);
    } // retranslateUi

};

namespace Ui {
    class WateringConfigDialog: public Ui_WateringConfigDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // WATERINGCONFIGDIALOG_H
