/****************************************************************************
**
** This file is part of the Qt Extended Opensource Package.
**
** Copyright (C) 2009 Trolltech ASA.
**
** Contact: Qt Extended Information (info@qtextended.org)
**
** This file may be used under the terms of the GNU General Public License
** version 2.0 as published by the Free Software Foundation and appearing
** in the file LICENSE.GPL included in the packaging of this file.
**
** Please review the following information to ensure GNU General Public
** Licensing requirements will be met:
**     http://www.fsf.org/licensing/licenses/info/GPLv2.html.
**
**
****************************************************************************/
#ifndef REGISTRYHELPER_H
#define REGISTRYHELPER_H

#include <qdwin32config.h>
#include <windows.h>
#include <QString>
#include <QStringList>

namespace QDWIN32 {

QDWIN32_EXPORT QString readRegKey( HKEY hive, const QString &path, const QString &key = QString() );
QDWIN32_EXPORT QString findSubKey( HKEY hive, const QString &path, const QString &key = QString() );
QDWIN32_EXPORT HKEY openRegKey( HKEY hive, const QString &path );
QDWIN32_EXPORT QStringList readRegKeys( HKEY hKey );

};

#endif