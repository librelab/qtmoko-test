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
** Form generated from reading ui file 'qtresourceeditordialog.ui'
**
** Created: Mon Jun 16 17:45:38 2008
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef QTRESOURCEEDITORDIALOG_H
#define QTRESOURCEEDITORDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QToolButton>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtResourceEditorDialog
{
public:
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QListWidget *qrcFileList;
    QToolButton *newQrcButton;
    QToolButton *removeQrcButton;
    QSpacerItem *spacerItem;
    QToolButton *importQrcButton;
    QWidget *widget;
    QGridLayout *gridLayout1;
    QTreeView *resourceTreeView;
    QToolButton *newResourceButton;
    QToolButton *addResourceButton;
    QToolButton *removeResourceButton;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *QtResourceEditorDialog)
    {
        if (QtResourceEditorDialog->objectName().isEmpty())
            QtResourceEditorDialog->setObjectName(QString::fromUtf8("QtResourceEditorDialog"));
        QtResourceEditorDialog->resize(469, 317);
        verticalLayout = new QVBoxLayout(QtResourceEditorDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        splitter = new QSplitter(QtResourceEditorDialog);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        qrcFileList = new QListWidget(layoutWidget);
        qrcFileList->setObjectName(QString::fromUtf8("qrcFileList"));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(qrcFileList->sizePolicy().hasHeightForWidth());
        qrcFileList->setSizePolicy(sizePolicy);

        gridLayout->addWidget(qrcFileList, 0, 0, 1, 4);

        newQrcButton = new QToolButton(layoutWidget);
        newQrcButton->setObjectName(QString::fromUtf8("newQrcButton"));

        gridLayout->addWidget(newQrcButton, 1, 0, 1, 1);

        removeQrcButton = new QToolButton(layoutWidget);
        removeQrcButton->setObjectName(QString::fromUtf8("removeQrcButton"));

        gridLayout->addWidget(removeQrcButton, 1, 2, 1, 1);

        spacerItem = new QSpacerItem(21, 20, QSizePolicy::Ignored, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem, 1, 3, 1, 1);

        importQrcButton = new QToolButton(layoutWidget);
        importQrcButton->setObjectName(QString::fromUtf8("importQrcButton"));

        gridLayout->addWidget(importQrcButton, 1, 1, 1, 1);

        splitter->addWidget(layoutWidget);
        widget = new QWidget(splitter);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout1 = new QGridLayout(widget);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        gridLayout1->setContentsMargins(0, 0, 0, 0);
        resourceTreeView = new QTreeView(widget);
        resourceTreeView->setObjectName(QString::fromUtf8("resourceTreeView"));

        gridLayout1->addWidget(resourceTreeView, 0, 0, 1, 4);

        newResourceButton = new QToolButton(widget);
        newResourceButton->setObjectName(QString::fromUtf8("newResourceButton"));

        gridLayout1->addWidget(newResourceButton, 1, 0, 1, 1);

        addResourceButton = new QToolButton(widget);
        addResourceButton->setObjectName(QString::fromUtf8("addResourceButton"));

        gridLayout1->addWidget(addResourceButton, 1, 1, 1, 1);

        removeResourceButton = new QToolButton(widget);
        removeResourceButton->setObjectName(QString::fromUtf8("removeResourceButton"));

        gridLayout1->addWidget(removeResourceButton, 1, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout1->addItem(horizontalSpacer, 1, 3, 1, 1);

        splitter->addWidget(widget);

        verticalLayout->addWidget(splitter);

        buttonBox = new QDialogButtonBox(QtResourceEditorDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(QtResourceEditorDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), QtResourceEditorDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), QtResourceEditorDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(QtResourceEditorDialog);
    } // setupUi

    void retranslateUi(QDialog *QtResourceEditorDialog)
    {
        QtResourceEditorDialog->setWindowTitle(QApplication::translate("QtResourceEditorDialog", "Dialog", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        newQrcButton->setToolTip(QApplication::translate("QtResourceEditorDialog", "New File", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        newQrcButton->setText(QApplication::translate("QtResourceEditorDialog", "N", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        removeQrcButton->setToolTip(QApplication::translate("QtResourceEditorDialog", "Remove File", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        removeQrcButton->setText(QApplication::translate("QtResourceEditorDialog", "R", 0, QApplication::UnicodeUTF8));
        importQrcButton->setText(QApplication::translate("QtResourceEditorDialog", "I", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        newResourceButton->setToolTip(QApplication::translate("QtResourceEditorDialog", "New Resource", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        newResourceButton->setText(QApplication::translate("QtResourceEditorDialog", "N", 0, QApplication::UnicodeUTF8));
        addResourceButton->setText(QApplication::translate("QtResourceEditorDialog", "A", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        removeResourceButton->setToolTip(QApplication::translate("QtResourceEditorDialog", "Remove Resource or File", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        removeResourceButton->setText(QApplication::translate("QtResourceEditorDialog", "R", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(QtResourceEditorDialog);
    } // retranslateUi

};

namespace Ui {
    class QtResourceEditorDialog: public Ui_QtResourceEditorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // QTRESOURCEEDITORDIALOG_H
