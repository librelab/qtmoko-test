TEMPLATE=app
CONFIG+=qtopia no_quicklaunch no_singleexec
TARGET=qterminal

DEFINES+=\
    HAVE_OPENPTY \
    QTOPIA_PHONE
LIBS+=-lutil

# I18n info
#STRING_LANGUAGE=en_US
############LANGUAGES=en_US

# Package info
pkg [
    name=qterminal
    desc="Terminal for Qtopia"
    license=GPLv2
    version=1.0
    maintainer="Alessandro Briosi <tsdogs@briosix.org>"
]

# Input files
HEADERS=\
    BlockArray.h\
    Character.h\
    CharacterColor.h\
    ColorScheme.h\
    DefaultTranslatorText.h\
    Emulation.h\
    Filter.h\
    History.h\
    io_layer.h\
    KeyboardTranslator.h\
    LineFont.h\
    MainWindow.h\
    MyPty.h\
    Preferences.h\
    procctl.h\
    profile.h\
    Screen.h\
    ScreenWindow.h\
    Session.h\
    ShellCommand.h\
    TerminalCharacterDecoder.h\
    TerminalDisplay.h\
    Vt102Emulation.h

SOURCES=\
    BlockArray.cpp\
    ColorScheme.cpp\
    Emulation.cpp\
    Filter.cpp\
    History.cpp\
    io_layer.cpp\
    KeyboardTranslator.cpp\
    main.cpp\
    MainWindow.cpp\
    MyPty.cpp\
    Preferences.cpp\
    procctl.cpp\
    profile.cpp\
    Screen.cpp\
    ScreenWindow.cpp\
    Session.cpp\
    ShellCommand.cpp\
    TerminalCharacterDecoder.cpp\
    TerminalDisplay.cpp\
    Vt102Emulation.cpp

# Install rules
target [
    hint=sxe
    domain=trusted
]

desktop [
    hint=desktop
    files=qterminal.desktop
    path=/apps/Applications
]

pics [
    hint=pics
    files=pics/*
    path=/pics/qterminal
]

config [
    hint=image
    files=config/*
    path=/etc
]
