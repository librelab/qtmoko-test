############################################################
# Project file for autotest for file q3filedialog.h
############################################################

load(qttest_p4)
QT += qt3support
requires(contains(QT_CONFIG,qt3support))

SOURCES += tst_q3filedialog.cpp


