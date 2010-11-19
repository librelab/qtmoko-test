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
** Form generated from reading ui file 'pathpage.ui'
**
** Created: Thu Jul 10 09:47:35 2008
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef PATHPAGE_H
#define PATHPAGE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PathPage
{
public:
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLineEdit *filterLineEdit;
    QSpacerItem *spacerItem;
    QLabel *label;
    QListWidget *pathListWidget;
    QPushButton *addButton;
    QPushButton *removeButton;
    QSpacerItem *spacerItem1;
    QSpacerItem *spacerItem2;

    void setupUi(QWidget *PathPage)
    {
        if (PathPage->objectName().isEmpty())
            PathPage->setObjectName(QString::fromUtf8("PathPage"));
        PathPage->resize(417, 243);
        gridLayout = new QGridLayout(PathPage);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(PathPage);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        filterLineEdit = new QLineEdit(PathPage);
        filterLineEdit->setObjectName(QString::fromUtf8("filterLineEdit"));

        gridLayout->addWidget(filterLineEdit, 0, 1, 1, 2);

        spacerItem = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(spacerItem, 1, 1, 1, 1);

        label = new QLabel(PathPage);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 2, 0, 1, 3);

        pathListWidget = new QListWidget(PathPage);
        pathListWidget->setObjectName(QString::fromUtf8("pathListWidget"));

        gridLayout->addWidget(pathListWidget, 3, 0, 3, 3);

        addButton = new QPushButton(PathPage);
        addButton->setObjectName(QString::fromUtf8("addButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(addButton->sizePolicy().hasHeightForWidth());
        addButton->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(addButton, 3, 3, 1, 1);

        removeButton = new QPushButton(PathPage);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));
        sizePolicy1.setHeightForWidth(removeButton->sizePolicy().hasHeightForWidth());
        removeButton->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(removeButton, 4, 3, 1, 1);

        spacerItem1 = new QSpacerItem(20, 51, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(spacerItem1, 5, 3, 1, 1);

        spacerItem2 = new QSpacerItem(20, 31, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(spacerItem2, 6, 2, 1, 1);


        retranslateUi(PathPage);

        QMetaObject::connectSlotsByName(PathPage);
    } // setupUi

    void retranslateUi(QWidget *PathPage)
    {
        PathPage->setWindowTitle(QApplication::translate("PathPage", "Form", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("PathPage", "File filters:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("PathPage", "Documentation source file paths:", 0, QApplication::UnicodeUTF8));
        addButton->setText(QApplication::translate("PathPage", "Add", 0, QApplication::UnicodeUTF8));
        removeButton->setText(QApplication::translate("PathPage", "Remove", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(PathPage);
    } // retranslateUi

};

namespace Ui {
    class PathPage: public Ui_PathPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // PATHPAGE_H
