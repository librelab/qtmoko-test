CONFIG += qtestlib
SOURCES         += tst_qitemmodel.cpp
TARGET          = tst_qitemmodel

QT += sql

# NOTE: The deployment of the sqldrivers is disabled on purpose.
#       If we deploy the plugins, they are loaded twice when running
#       the tests on the autotest system. In that case we run out of
#       memory on Windows Mobile 5.

#wince*: {
#   plugFiles.sources = $$QT_BUILD_TREE/plugins/sqldrivers/*.dll
#   plugFiles.path    = sqldrivers
#   DEPLOYMENT += plugFiles 
#}
