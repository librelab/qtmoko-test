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
** Form generated from reading ui file 'languagesdialog.ui'
**
** Created: Fri May 15 16:58:03 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef LANGUAGESDIALOG_H
#define LANGUAGESDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LanguagesDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTreeWidget *languagesList;
    QHBoxLayout *hboxLayout;
    QToolButton *upButton;
    QToolButton *downButton;
    QToolButton *removeButton;
    QToolButton *openFileButton;
    QSpacerItem *spacerItem;
    QPushButton *okButton;

    void setupUi(QDialog *LanguagesDialog)
    {
        if (LanguagesDialog->objectName().isEmpty())
            LanguagesDialog->setObjectName(QString::fromUtf8("LanguagesDialog"));
        LanguagesDialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(LanguagesDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        languagesList = new QTreeWidget(LanguagesDialog);
        languagesList->setObjectName(QString::fromUtf8("languagesList"));
        languagesList->setIndentation(0);

        verticalLayout->addWidget(languagesList);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        upButton = new QToolButton(LanguagesDialog);
        upButton->setObjectName(QString::fromUtf8("upButton"));
        upButton->setEnabled(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/up.png"), QSize(), QIcon::Normal, QIcon::Off);
        upButton->setIcon(icon);

        hboxLayout->addWidget(upButton);

        downButton = new QToolButton(LanguagesDialog);
        downButton->setObjectName(QString::fromUtf8("downButton"));
        downButton->setEnabled(false);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/down.png"), QSize(), QIcon::Normal, QIcon::Off);
        downButton->setIcon(icon1);

        hboxLayout->addWidget(downButton);

        removeButton = new QToolButton(LanguagesDialog);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));
        removeButton->setEnabled(false);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/editdelete.png"), QSize(), QIcon::Normal, QIcon::Off);
        removeButton->setIcon(icon2);

        hboxLayout->addWidget(removeButton);

        openFileButton = new QToolButton(LanguagesDialog);
        openFileButton->setObjectName(QString::fromUtf8("openFileButton"));
        openFileButton->setEnabled(true);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/mac/fileopen.png"), QSize(), QIcon::Normal, QIcon::Off);
        openFileButton->setIcon(icon3);

        hboxLayout->addWidget(openFileButton);

        spacerItem = new QSpacerItem(121, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(LanguagesDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);


        verticalLayout->addLayout(hboxLayout);


        retranslateUi(LanguagesDialog);
        QObject::connect(okButton, SIGNAL(clicked()), LanguagesDialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(LanguagesDialog);
    } // setupUi

    void retranslateUi(QDialog *LanguagesDialog)
    {
        LanguagesDialog->setWindowTitle(QApplication::translate("LanguagesDialog", "Auxiliary Languages", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = languagesList->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("LanguagesDialog", "File", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(0, QApplication::translate("LanguagesDialog", "Locale", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        upButton->setToolTip(QApplication::translate("LanguagesDialog", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Move selected language up</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        upButton->setText(QApplication::translate("LanguagesDialog", "up", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        downButton->setToolTip(QApplication::translate("LanguagesDialog", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\">Move selected language down</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        downButton->setText(QApplication::translate("LanguagesDialog", "down", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        removeButton->setToolTip(QApplication::translate("LanguagesDialog", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Remove selected language</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        removeButton->setText(QApplication::translate("LanguagesDialog", "remove", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        openFileButton->setToolTip(QApplication::translate("LanguagesDialog", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Open auxiliary language files</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        openFileButton->setText(QApplication::translate("LanguagesDialog", "...", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("LanguagesDialog", "OK", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(LanguagesDialog);
    } // retranslateUi

};

namespace Ui {
    class LanguagesDialog: public Ui_LanguagesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // LANGUAGESDIALOG_H
