/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the documentation of the Qt Toolkit.
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

#include "tst_qwidget_mac_helpers.h"
#include <private/qt_mac_p.h>
#include <private/qt_cocoa_helpers_mac_p.h>


QString nativeWindowTitle(QWidget *window, Qt::WindowState state)
{
    OSWindowRef windowRef = qt_mac_window_for(window);
    QCFString macTitle;
    if (state == Qt::WindowMinimized) {
#ifndef QT_MAC_USE_COCOA
        CopyWindowAlternateTitle(windowRef, &macTitle);
#else
        macTitle = reinterpret_cast<CFStringRef>([[windowRef miniwindowTitle] retain]);
#endif
    } else {
#ifndef QT_MAC_USE_COCOA
        CopyWindowTitleAsCFString(windowRef, &macTitle);
#else
        macTitle = reinterpret_cast<CFStringRef>([[windowRef title] retain]);
#endif
    }
    return macTitle;
}

bool nativeWindowModified(QWidget *widget)
{
#ifndef QT_MAC_USE_COCOA
    return IsWindowModified(qt_mac_window_for(widget));
#else
    return [qt_mac_window_for(widget) isDocumentEdited];
#endif
}
