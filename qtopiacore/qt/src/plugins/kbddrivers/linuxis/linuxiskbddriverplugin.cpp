/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the plugins of the Qt Toolkit.
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

#include "linuxiskbddriverplugin.h"
#include "linuxiskbdhandler.h"

#include <qdebug.h>
#if 1
#define qLog(x) qDebug()
#else
#define qLog(x) while (0) qDebug()
#endif

LinuxInputSubsystemKbdDriverPlugin::LinuxInputSubsystemKbdDriverPlugin( QObject *parent )
    : QKbdDriverPlugin( parent )
{
}

LinuxInputSubsystemKbdDriverPlugin::~LinuxInputSubsystemKbdDriverPlugin()
{
}

QWSKeyboardHandler* LinuxInputSubsystemKbdDriverPlugin::create(const QString &driver, const QString &device)
{
    if (device.isEmpty()) {
	return create( driver );
    }
    if( driver.toLower() == "linuxis" || driver.toLower() == "linuxiskbdhandler" ) {
        qLog(Input) << "Before call LinuxInputSubsystemKbdHandler(" << device << ")";
        return new LinuxInputSubsystemKbdHandler(device);
    }
    return 0;
}

QWSKeyboardHandler* LinuxInputSubsystemKbdDriverPlugin::create( const QString &driver)
{
    if( driver.toLower() == "linuxis" || driver.toLower() == "linuxiskbdhandler" ) {
        qLog(Input) << "Before call LinuxInputSubsystemKbdHandler()";
        return new LinuxInputSubsystemKbdHandler();
    }
    return 0;
}

QStringList LinuxInputSubsystemKbdDriverPlugin::keys() const
{
    return QStringList() << "linuxis" << "linuxiskbdhandler";
}

Q_EXPORT_PLUGIN2(qwslinuxiskbdhandler, LinuxInputSubsystemKbdDriverPlugin)
