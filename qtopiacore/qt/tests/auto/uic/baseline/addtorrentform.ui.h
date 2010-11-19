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
** Form generated from reading ui file 'addtorrentform.ui'
**
** Created: Thu Jul 10 09:47:34 2008
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef ADDTORRENTFORM_H
#define ADDTORRENTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddTorrentFile
{
public:
    QVBoxLayout *vboxLayout;
    QGroupBox *groupBox;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label_4;
    QLineEdit *torrentFile;
    QLabel *label_2;
    QPushButton *browseTorrents;
    QLabel *label_5;
    QLabel *label_3;
    QLabel *label_6;
    QTextEdit *torrentContents;
    QLineEdit *destinationFolder;
    QLabel *announceUrl;
    QLabel *label;
    QPushButton *browseDestination;
    QLabel *label_7;
    QLabel *commentLabel;
    QLabel *creatorLabel;
    QLabel *sizeLabel;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *AddTorrentFile)
    {
        if (AddTorrentFile->objectName().isEmpty())
            AddTorrentFile->setObjectName(QString::fromUtf8("AddTorrentFile"));
        AddTorrentFile->resize(464, 385);
        AddTorrentFile->setSizeGripEnabled(false);
        AddTorrentFile->setModal(true);
        vboxLayout = new QVBoxLayout(AddTorrentFile);
#ifndef Q_OS_MAC
        vboxLayout->setSpacing(6);
#endif
        vboxLayout->setMargin(8);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        groupBox = new QGroupBox(AddTorrentFile);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        widget = new QWidget(groupBox);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 40, 364, 33));
        gridLayout = new QGridLayout(groupBox);
#ifndef Q_OS_MAC
        gridLayout->setSpacing(6);
#endif
        gridLayout->setMargin(8);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 6, 0, 1, 1);

        torrentFile = new QLineEdit(groupBox);
        torrentFile->setObjectName(QString::fromUtf8("torrentFile"));

        gridLayout->addWidget(torrentFile, 0, 1, 1, 2);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        browseTorrents = new QPushButton(groupBox);
        browseTorrents->setObjectName(QString::fromUtf8("browseTorrents"));
        browseTorrents->setDefault(true);

        gridLayout->addWidget(browseTorrents, 0, 3, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        gridLayout->addWidget(label_5, 5, 0, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 4, 0, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 2, 0, 1, 1);

        torrentContents = new QTextEdit(groupBox);
        torrentContents->setObjectName(QString::fromUtf8("torrentContents"));
        torrentContents->setFocusPolicy(Qt::NoFocus);
        torrentContents->setTabChangesFocus(true);
        torrentContents->setLineWrapMode(QTextEdit::NoWrap);
        torrentContents->setReadOnly(true);

        gridLayout->addWidget(torrentContents, 5, 1, 1, 3);

        destinationFolder = new QLineEdit(groupBox);
        destinationFolder->setObjectName(QString::fromUtf8("destinationFolder"));
        destinationFolder->setFocusPolicy(Qt::StrongFocus);

        gridLayout->addWidget(destinationFolder, 6, 1, 1, 2);

        announceUrl = new QLabel(groupBox);
        announceUrl->setObjectName(QString::fromUtf8("announceUrl"));

        gridLayout->addWidget(announceUrl, 1, 1, 1, 3);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        browseDestination = new QPushButton(groupBox);
        browseDestination->setObjectName(QString::fromUtf8("browseDestination"));

        gridLayout->addWidget(browseDestination, 6, 3, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 3, 0, 1, 1);

        commentLabel = new QLabel(groupBox);
        commentLabel->setObjectName(QString::fromUtf8("commentLabel"));

        gridLayout->addWidget(commentLabel, 3, 1, 1, 3);

        creatorLabel = new QLabel(groupBox);
        creatorLabel->setObjectName(QString::fromUtf8("creatorLabel"));

        gridLayout->addWidget(creatorLabel, 2, 1, 1, 3);

        sizeLabel = new QLabel(groupBox);
        sizeLabel->setObjectName(QString::fromUtf8("sizeLabel"));

        gridLayout->addWidget(sizeLabel, 4, 1, 1, 3);


        vboxLayout->addWidget(groupBox);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setMargin(0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(AddTorrentFile);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setEnabled(false);

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(AddTorrentFile);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        vboxLayout->addLayout(hboxLayout);

        QWidget::setTabOrder(torrentFile, browseTorrents);
        QWidget::setTabOrder(browseTorrents, torrentContents);
        QWidget::setTabOrder(torrentContents, destinationFolder);
        QWidget::setTabOrder(destinationFolder, browseDestination);
        QWidget::setTabOrder(browseDestination, okButton);
        QWidget::setTabOrder(okButton, cancelButton);

        retranslateUi(AddTorrentFile);
        QObject::connect(okButton, SIGNAL(clicked()), AddTorrentFile, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), AddTorrentFile, SLOT(reject()));

        QMetaObject::connectSlotsByName(AddTorrentFile);
    } // setupUi

    void retranslateUi(QDialog *AddTorrentFile)
    {
        AddTorrentFile->setWindowTitle(QApplication::translate("AddTorrentFile", "Add a torrent", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("AddTorrentFile", "Select a torrent source", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("AddTorrentFile", "Destination:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("AddTorrentFile", "Tracker URL:", 0, QApplication::UnicodeUTF8));
        browseTorrents->setText(QApplication::translate("AddTorrentFile", "Browse", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("AddTorrentFile", "File(s):", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("AddTorrentFile", "Size:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("AddTorrentFile", "Creator:", 0, QApplication::UnicodeUTF8));
        announceUrl->setText(QApplication::translate("AddTorrentFile", "<none>", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AddTorrentFile", "Torrent file:", 0, QApplication::UnicodeUTF8));
        browseDestination->setText(QApplication::translate("AddTorrentFile", "Browse", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("AddTorrentFile", "Comment:", 0, QApplication::UnicodeUTF8));
        commentLabel->setText(QApplication::translate("AddTorrentFile", "<none>", 0, QApplication::UnicodeUTF8));
        creatorLabel->setText(QApplication::translate("AddTorrentFile", "<none>", 0, QApplication::UnicodeUTF8));
        sizeLabel->setText(QApplication::translate("AddTorrentFile", "0", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("AddTorrentFile", "&OK", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("AddTorrentFile", "&Cancel", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(AddTorrentFile);
    } // retranslateUi

};

namespace Ui {
    class AddTorrentFile: public Ui_AddTorrentFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // ADDTORRENTFORM_H
