/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtGui module of the Qt Toolkit.
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

#ifndef QITEMSELECTIONMODEL_P_H
#define QITEMSELECTIONMODEL_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "private/qobject_p.h"

QT_BEGIN_NAMESPACE

#ifndef QT_NO_ITEMVIEWS
class QItemSelectionModelPrivate: public QObjectPrivate
{
    Q_DECLARE_PUBLIC(QItemSelectionModel)
public:
    QItemSelectionModelPrivate()
      : model(0),
        currentCommand(QItemSelectionModel::NoUpdate),
        tableSelected(false) {}

    QItemSelection expandSelection(const QItemSelection &selection,
                                   QItemSelectionModel::SelectionFlags command) const;

    void _q_rowsAboutToBeRemoved(const QModelIndex &parent, int start, int end);
    void _q_columnsAboutToBeRemoved(const QModelIndex &parent, int start, int end);
    void _q_rowsAboutToBeInserted(const QModelIndex &parent, int start, int end);
    void _q_columnsAboutToBeInserted(const QModelIndex &parent, int start, int end);
    void _q_layoutAboutToBeChanged();
    void _q_layoutChanged();

    inline void remove(QList<QItemSelectionRange> &r)
    {
        QList<QItemSelectionRange>::const_iterator it = r.constBegin();
        for (; it != r.constEnd(); ++it)
            ranges.removeAll(*it);
    }

    inline void finalize()
    {
        ranges.merge(currentSelection, currentCommand);
        if (!currentSelection.isEmpty())  // ### perhaps this should be in QList
            currentSelection.clear();
    }

    QPointer<QAbstractItemModel> model;
    QItemSelection ranges;
    QItemSelection currentSelection;
    QPersistentModelIndex currentIndex;
    QItemSelectionModel::SelectionFlags currentCommand;
    QList<QPersistentModelIndex> savedPersistentIndexes;
    QList<QPersistentModelIndex> savedPersistentCurrentIndexes;
    // optimization when all indexes are selected
    bool tableSelected;
    QPersistentModelIndex tableParent;
    int tableColCount, tableRowCount;
};

#endif // QT_NO_ITEMVIEWS

QT_END_NAMESPACE

#endif // QITEMSELECTIONMODEL_P_H
