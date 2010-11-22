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
#include "../shared/shared.h"
#include <qdir.h>

int main(int argc, char **argv)
{
    QString appBundlePath;
    if (argc > 1)
        appBundlePath = QString::fromLocal8Bit(argv[1]);

    if (argc < 2 || appBundlePath.startsWith("-")) {
        qDebug() << "Usage: macdeployqt app-bundle [options]";
        qDebug() << "";
        qDebug() << "Options:";
        qDebug() << "   -no-plugins: Skip plugin deployment";
        qDebug() << "   -dmg       : Create a .dmg disk image";
        qDebug() << "   -no-strip  : Don't run 'strip' on the binaries";
        qDebug() << "";
        qDebug() << "macdeployqt takes an application bundle as input and makes it";
        qDebug() << "self-contained by copying in the Qt frameworks and plugins that";
        qDebug() << "the application uses.";
        qDebug() << "";
        qDebug() << "Plugins related to a framework are copied in with the";
        qDebug() << "framework. The accessibilty, image formats, and text codec";
        qDebug() << "plugins are always copied, unless \"-no-plugins\" is specified.";
        qDebug() << "";
        qDebug() << "See the \"Deploying an Application on Qt/Mac\" topic in the";
        qDebug() << "documentation for more information about deployment on Mac OS X.";

        return 0;
    }
    
    if (appBundlePath.endsWith("/"))
        appBundlePath.chop(1);
    
    if (QDir().exists(appBundlePath) == false) {
        qDebug() << "Error: Could not find app bundle" << appBundlePath;
        return 0;
    }

    bool plugins = true;
    bool dmg = false;
    extern bool runStripEnabled;

    for (int i = 2; i < argc; ++i) {
        QByteArray argument = QByteArray(argv[i]);
        if (argument == QByteArray("-no-plugins")) {
            plugins = false;
        } else if (argument == QByteArray("-dmg")) {
            dmg = true;
        } else if (argument == QByteArray("-no-strip")) {
            runStripEnabled = false;
        } else if (argument.startsWith("-")) {
            qDebug() << "Error: Unknown option" << argument << "\n";
            return 0;
        }
     }

    DeploymentInfo deploymentInfo  = deployQtFrameworks(appBundlePath);

    if (plugins) {
        if (deploymentInfo.qtPath.isEmpty())
            deploymentInfo.pluginPath = "/Developer/Applications/Qt/plugins"; // Assume binary package.
        else
            deploymentInfo.pluginPath = deploymentInfo.qtPath + "/plugins";

        qDebug() << "";
        qDebug() << "Deploying plugins from" << deploymentInfo.pluginPath;
        deployPlugins(appBundlePath, deploymentInfo);
        createQtConf(appBundlePath);
    }

    if (dmg) {
        createDiskImage(appBundlePath);
    }
}

