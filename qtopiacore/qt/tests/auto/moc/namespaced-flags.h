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
#include <QObject>

namespace Foo {
    class Bar : public QObject {
        Q_OBJECT
        Q_FLAGS( Flags )
        Q_PROPERTY( Flags flags READ flags WRITE setFlags )
    public:
        explicit Bar( QObject * parent=0 ) : QObject( parent ), mFlags() {}

        enum Flag { Read=1, Write=2 };
        Q_DECLARE_FLAGS( Flags, Flag )

        void setFlags( Flags f ) { mFlags = f; }
        Flags flags() const { return mFlags; }

    private:
        Flags mFlags;
    };

    class Baz : public QObject {
        Q_OBJECT
        //Q_PROPERTY( Bar::Flags flags READ flags WRITE setFlags ) // triggers assertion
        Q_PROPERTY( Foo::Bar::Flags flags READ flags WRITE setFlags ) // fails to compile, or with the same assertion if moc fix is applied
    public:
        explicit Baz( QObject * parent=0 ) : QObject( parent ), mFlags() {}

        void setFlags( Bar::Flags f ) { mFlags = f; }
        Bar::Flags flags() const { return mFlags; }
    private:
        Bar::Flags mFlags;
    };
}

Q_DECLARE_OPERATORS_FOR_FLAGS( Foo::Bar::Flags )
