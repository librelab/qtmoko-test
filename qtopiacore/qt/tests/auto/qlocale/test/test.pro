load(qttest_p4)
SOURCES += ../tst_qlocale.cpp

!wince*: {
TARGET = ../tst_qlocale

win32: {
  CONFIG(debug, debug|release) {
    TARGET = ../../debug/tst_qlocale
} else {
    TARGET = ../../release/tst_qlocale
  }
}
} else {
   TARGET = tst_qlocale
}



QT = core
QT += network
embedded: QT += gui

wince*: {
   addFiles.sources = \
        ../syslocaleapp

   addFiles.path = \Program Files\tst_qlocale
   DEPLOYMENT += addFiles
}

