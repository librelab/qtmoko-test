/* -------------------------------------------------------------------------- */
/*                                                                            */
/* [MyPty.C]               Pseudo Terminal Device                             */
/*                                                                            */
/* -------------------------------------------------------------------------- */
/*                                                                            */
/* Copyright (c) 1997,1998 by Lars Doelle <lars.doelle@on-line.de>            */
/*                                                                            */
/* This file is part of Konsole - an X terminal for KDE                       */
/* -------------------------------------------------------------------------- */
/*									      */
/* Ported Konsole to Qt/Embedded                                              */
/*									      */
/* Copyright (C) 2000 by John Ryland <jryland@trolltech.com>                  */
/*									      */
/* -------------------------------------------------------------------------- */

/* If you're compiling konsole on non-Linux platforms and find
   problems that you can track down to this file, please have
   a look into ../README.ports, too.
*/

/*! \file
*/

/*! \class TEPty

    \brief Ptys provide a pseudo terminal connection to a program.

    Although closely related to pipes, these pseudo terminal connections have
    some ability, that makes it nessesary to uses them. Most importent, they
    know about changing screen sizes and UNIX job control.

    Within the terminal emulation framework, this class represents the
    host side of the terminal together with the connecting serial line.

    One can create many instances of this class within a program.
    As a side effect of using this class, a signal(2) handler is
    installed on SIGCHLD.

    \par FIXME

    [NOTE: much of the technical stuff below will be replaced by forkpty.]

    publish the SIGCHLD signal if not related to an instance.

    clearify TEPty::done vs. TEPty::~TEPty semantics.
    check if pty is restartable via run after done.

    \par Pseudo terminals

    Pseudo terminals are a unique feature of UNIX, and always come in form of
    pairs of devices (/dev/ptyXX and /dev/ttyXX), which are connected to each
    other by the operating system. One may think of them as two serial devices
    linked by a null-modem cable. Being based on devices the number of
    simultanous instances of this class is (globally) limited by the number of
    those device pairs, which is 256.

    Another technic are UNIX 98 PTY's. These are supported also, and prefered
    over the (obsolete) predecessor.

    There's a sinister ioctl(2), signal(2) and job control stuff
    nessesary to make everything work as it should.
*/
#include "procctl.h"
#include "MyPty.h"

/* QT */
#include <qsocketnotifier.h>
#include <qfile.h>

/* STD */
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/wait.h>


#ifdef HAVE_OPENPTY
#include <pty.h>
#endif

#undef VERBOSE_DEBUG


/* -------------------------------------------------------------------------- */

/*!
   Informs the client program about the
   actual size of the window.
*/

void MyPty::setWindowSize(int lines, int columns)
{
  struct winsize wsize;
  wsize.ws_row = (unsigned short)lines;
  wsize.ws_col = (unsigned short)columns;
  if(m_fd < 0) return;
  ioctl(m_fd,TIOCSWINSZ,(char *)&wsize);
  _size.setWidth(columns);
  _size.setHeight(lines);
}

QSize MyPty::windowSize()
{
  return _size;
}


void MyPty::donePty()
{
    // This is code from the Qt DumbTerminal example

    ::close(m_fd);

    if (m_cpid) {
	kill(m_cpid, SIGHUP);
	//waitpid(m_cpid, &status, 0);
        delete m_sn_e;
        delete m_sn_r;
        m_sn_e = 0l;
        m_sn_r = 0l;
    }

    m_cpid = 0;
    m_fd = -1;
    emit done(0);
}


const char* MyPty::deviceName()
{
    return m_ttynam;
}


void MyPty::error()
{
    // This is code from the Qt DumbTerminal example
    donePty();
}

int MyPty::start() {
    QStringList lis;
    int r =run(m_cmd.toLatin1(), lis, 0, 0);
    r = r;
    _running = true;

    return r;
}
/*!
    start the client program.
*/
int MyPty::run(const char* cmd, QStringList &, const char*, int)
{
    // This is code from the Qt DumbTerminal example
    m_cpid = fork();

    if ( !m_cpid ) {
	// child - exec shell on tty
	for (int sig = 1; sig < NSIG; sig++) signal(sig,SIG_DFL);
	int ttyfd = ::open(m_ttynam, O_RDWR);
	dup2(ttyfd, STDIN_FILENO);
	dup2(ttyfd, STDOUT_FILENO);
	dup2(ttyfd, STDERR_FILENO);
	// should be done with tty, so close it
	::close(ttyfd);
	static struct termios ttmode;
	if ( setsid() < 0 )
	    perror( "failed to set process group" );
#if defined (TIOCSCTTY)
	// grabbed from APUE by Stevens
	ioctl(STDIN_FILENO, TIOCSCTTY, 0);
#endif
	tcgetattr( STDIN_FILENO, &ttmode );
	ttmode.c_cc[VINTR] = 3;
	ttmode.c_cc[VERASE] = 8;
	tcsetattr( STDIN_FILENO, TCSANOW, &ttmode );
	setenv("TERM",m_term,1);
	setenv("COLORTERM","0",1);
        EnvironmentMap::Iterator it;
        for (it = m_env.begin(); it != m_env.end(); it++) {
            setenv(it.key().toLatin1(), it.value().toLatin1(), 1);
        }
	if (getuid() == 0) {
	    char msg[] = "WARNING: You are running this shell as root!\n";
	    write(ttyfd, msg, sizeof(msg));
	}
	execl(cmd, cmd, 0);

	donePty();
	exit(-1);
    }

    // parent - continue as a widget
    delete m_sn_r;
    m_sn_r = new QSocketNotifier(m_fd,QSocketNotifier::Read,this);
    delete m_sn_e;
    m_sn_e = new QSocketNotifier(m_fd,QSocketNotifier::Exception,this);
    connect(m_sn_r,SIGNAL(activated(int)),this,SLOT(readPty()));
    connect(m_sn_e,SIGNAL(activated(int)),this,SLOT(error()));

    return 0;
}

int MyPty::openPty()
{
    // This is code from the Qt DumbTerminal example
    int ptyfd = -1;

#ifdef HAVE_OPENPTY
    int ttyfd;
    if ( openpty(&ptyfd,&ttyfd,m_ttynam,0,0) )
	ptyfd = -1;
    else
	::close(ttyfd); // we open the ttynam ourselves.
#else
    for (const char* c0 = "pqrstuvwxyzabcde"; ptyfd < 0 && *c0 != 0; c0++) {
	for (const char* c1 = "0123456789abcdef"; ptyfd < 0 && *c1 != 0; c1++) {
	    sprintf(m_ptynam,"/dev/pty%c%c",*c0,*c1);
	    sprintf(m_ttynam,"/dev/tty%c%c",*c0,*c1);
	    if ((ptyfd = ::open(m_ptynam,O_RDWR)) >= 0) {
		if (geteuid() != 0 && !access(m_ttynam,R_OK|W_OK) == 0) {
		    ::close(ptyfd);
		    ptyfd = -1;
		}
	    }
	}
    }
#endif

    if ( ptyfd < 0 ) {
//	qApp->exit(1);
	return -1;
    }

    return ptyfd;
}

/*!
    Create an instance.
*/
MyPty::MyPty(const Profile& prof) : m_cpid(0)
{

    int term = prof.readNumEntry("Terminal", Profile::VT100 );
    _running = false;
    switch( term ) {
    default:
    case Profile::VT100:
    case Profile::VT102:
        m_term = "vt100";
        break;
    case Profile::Linux:
        m_term = "linux";
        break;
    case Profile::XTerm:
        m_term = "xterm";
        break;
    }
    m_sn_e = 0l;
    m_sn_r = 0l;
  m_fd = openPty();
  ProcCtl* ctl = ProcCtl::self();
  Q_UNUSED(ctl);
  reload(prof);
}

/*!
    Destructor.
    Note that the related client program is not killed
    (yet) when a instance is deleted.
*/
MyPty::~MyPty()
{
    donePty();
}
QString MyPty::identifier()const {
    return QString::fromLatin1("term");
}
QString MyPty::name()const{
    return identifier();
}
bool MyPty::open() {
    if (m_fd < 0)
        m_fd = openPty();

    start();
    return true;
}
void MyPty::close() {
    donePty();
    m_fd = openPty();
}
void MyPty::reload( const Profile& prof) {
    m_env.clear();
    m_cmd = prof.readEntry("Command", "/bin/bash");

    /*
     * Lets check if m_cmd actually
     * exists....
     * we try to use bin/bash and if
     * this fails we
     * will fallback to /bin/sh
     * which should be there 100%
     */
    if ( m_cmd.trimmed() == "/bin/bash" && !QFile::exists(QFile::encodeName(m_cmd) ) )        
            m_cmd = "/bin/sh";
        

    int envcount = prof.readNumEntry("EnvVars", 0);
    for (int i=0; i<envcount; i++) {
        QString name = prof.readEntry("Env_Name_" + QString::number(i), "");
        QString value = prof.readEntry("Env_Value_" + QString::number(i), "");
        if (!(name.isEmpty() || value.isEmpty())) {
            m_env.insert(name, value);
        }
    }
}
/*! sends len bytes through the line */
void MyPty::send(const char *buf, int len)
{
#ifdef VERBOSE_DEBUG
  // verbose debug
  printf("sending bytes:\n");
  for (uint i = 0; i < len; i++)
    printf("%c", buf[i]);
  printf("\n");
#endif

  ::write(m_fd, buf, len);
}

/*! indicates that a block of data is received */
void MyPty::readPty()
{
  QByteArray buf;
  buf.resize(4096);

  int len = ::read( m_fd, buf.data(), 4096 );

  if (len == -1 || len == 0) {
     donePty();
     return;
  }

  if (len < 0)
     return;


  buf.resize(len);
  emit received(buf.data(), len);

#ifdef VERBOSE_DEBUG
  // verbose debug
  printf("read bytes:\n");
  for (uint i = 0; i < buf.count(); i++)
    printf("%c", buf[i]);
  printf("\n");
#endif

}
QBitArray MyPty::supports()const {
    QBitArray ar(3);
    //autoconnect
    ar[0] = 1;
    //
    ar[1] = 0;
    ar[2] = 0;

    return ar;
}

bool MyPty::isRunning()
{
  return _running;
}

void MyPty::setWorkingDirectory(QString)
{
}
void MyPty::setUtf8Mode(bool)
{
}
void MyPty::setErase(char)
{
}
void MyPty::setWriteable(bool )
{
}

int MyPty::pid()
{
  return m_cpid;
}

