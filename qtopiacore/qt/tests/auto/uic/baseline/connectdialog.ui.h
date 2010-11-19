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
** Form generated from reading ui file 'connectdialog.ui'
**
** Created: Thu Jul 10 09:47:34 2008
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ConnectDialog
{
public:
    QGridLayout *gridLayout;
    QGroupBox *signalGroupBox;
    QVBoxLayout *vboxLayout;
    QListWidget *signalList;
    QHBoxLayout *hboxLayout;
    QToolButton *editSignalsButton;
    QSpacerItem *spacerItem;
    QGroupBox *slotGroupBox;
    QVBoxLayout *vboxLayout1;
    QListWidget *slotList;
    QHBoxLayout *hboxLayout1;
    QToolButton *editSlotsButton;
    QSpacerItem *spacerItem1;
    QCheckBox *showAllCheckBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ConnectDialog)
    {
        if (ConnectDialog->objectName().isEmpty())
            ConnectDialog->setObjectName(QString::fromUtf8("ConnectDialog"));
        ConnectDialog->resize(585, 361);
        gridLayout = new QGridLayout(ConnectDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        signalGroupBox = new QGroupBox(ConnectDialog);
        signalGroupBox->setObjectName(QString::fromUtf8("signalGroupBox"));
        vboxLayout = new QVBoxLayout(signalGroupBox);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        signalList = new QListWidget(signalGroupBox);
        signalList->setObjectName(QString::fromUtf8("signalList"));
        signalList->setTextElideMode(Qt::ElideMiddle);

        vboxLayout->addWidget(signalList);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        editSignalsButton = new QToolButton(signalGroupBox);
        editSignalsButton->setObjectName(QString::fromUtf8("editSignalsButton"));

        hboxLayout->addWidget(editSignalsButton);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);


        vboxLayout->addLayout(hboxLayout);


        gridLayout->addWidget(signalGroupBox, 0, 0, 1, 2);

        slotGroupBox = new QGroupBox(ConnectDialog);
        slotGroupBox->setObjectName(QString::fromUtf8("slotGroupBox"));
        vboxLayout1 = new QVBoxLayout(slotGroupBox);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        slotList = new QListWidget(slotGroupBox);
        slotList->setObjectName(QString::fromUtf8("slotList"));
        slotList->setTextElideMode(Qt::ElideMiddle);

        vboxLayout1->addWidget(slotList);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        editSlotsButton = new QToolButton(slotGroupBox);
        editSlotsButton->setObjectName(QString::fromUtf8("editSlotsButton"));

        hboxLayout1->addWidget(editSlotsButton);

        spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem1);


        vboxLayout1->addLayout(hboxLayout1);


        gridLayout->addWidget(slotGroupBox, 0, 2, 1, 1);

        showAllCheckBox = new QCheckBox(ConnectDialog);
        showAllCheckBox->setObjectName(QString::fromUtf8("showAllCheckBox"));

        gridLayout->addWidget(showAllCheckBox, 1, 0, 1, 1);

        buttonBox = new QDialogButtonBox(ConnectDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 1, 1, 2);


        retranslateUi(ConnectDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ConnectDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ConnectDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ConnectDialog);
    } // setupUi

    void retranslateUi(QDialog *ConnectDialog)
    {
        ConnectDialog->setWindowTitle(QApplication::translate("ConnectDialog", "Configure Connection", 0, QApplication::UnicodeUTF8));
        signalGroupBox->setTitle(QApplication::translate("ConnectDialog", "GroupBox", 0, QApplication::UnicodeUTF8));
        editSignalsButton->setText(QApplication::translate("ConnectDialog", "Edit...", 0, QApplication::UnicodeUTF8));
        slotGroupBox->setTitle(QApplication::translate("ConnectDialog", "GroupBox", 0, QApplication::UnicodeUTF8));
        editSlotsButton->setText(QApplication::translate("ConnectDialog", "Edit...", 0, QApplication::UnicodeUTF8));
        showAllCheckBox->setText(QApplication::translate("ConnectDialog", "Show signals and slots inherited from QWidget", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(ConnectDialog);
    } // retranslateUi

};

namespace Ui {
    class ConnectDialog: public Ui_ConnectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CONNECTDIALOG_H
