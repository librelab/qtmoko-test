############################################################
# Project file for autotest for file q3tabdialog.h
############################################################

load(qttest_p4)
QT += qt3support
requires(contains(QT_CONFIG,qt3support))

SOURCES += tst_q3tabdialog.cpp


