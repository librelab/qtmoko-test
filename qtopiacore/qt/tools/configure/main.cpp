/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the tools applications of the Qt Toolkit.
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

/*
** Configure tool
**
*/

#include "configureapp.h"

QT_BEGIN_NAMESPACE

int runConfigure( int argc, char** argv )
{
    Configure app( argc, argv );
    if (!app.isOk())
        return 3;

    app.parseCmdLine();
#if !defined(EVAL)
    app.validateArgs();
#endif
    if( app.displayHelp() )
	return 1;

    // Read license now, and exit if it doesn't pass.
    // This lets the user see the command-line options of configure
    // without having to load and parse the license file.
    app.readLicense();
    if (!app.isOk())
        return 3;

    // Auto-detect modules and settings.
    app.autoDetection();

    // After reading all command-line arguments, and doing all the
    // auto-detection, it's time to do some last minute validation.
    // If the validation fails, we cannot continue.
    if (!app.verifyConfiguration())
        return 3;

    app.generateOutputVars();

#if !defined(EVAL)
    if( !app.isDone() )
	app.generateCachefile();
    if( !app.isDone() )
        app.generateBuildKey();
    if( !app.isDone() )
	app.generateConfigfiles();
    if( !app.isDone() )
	app.displayConfig();
    if( !app.isDone() )
	app.generateHeaders();
    if( !app.isDone() )
	app.buildQmake();
    if( !app.isOk() )
	return 2;
#endif
    if( !app.isDone() )
	app.generateMakefiles();
    if( app.isOk() )
	app.buildHostTools();
    if( !app.isDone() )
	app.showSummary();

    return 0;
}

QT_END_NAMESPACE

int main( int argc, char** argv )
{
    QT_USE_NAMESPACE
    return runConfigure(argc, argv);
}
