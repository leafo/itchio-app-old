# C++ flags for extra error checking.
# TODO Uncomment the flags when the project is out of its beta phase.
QMAKE_CXXFLAGS += -Wall -Wextra #-Werror -Wundef -Woverloaded-virtual -Wshadow

CONFIG += link_pkgconfig c++11

PKGCONFIG += openssl

# Turn on debugging to enable features that are disabled when the QT_NO_DEBUG is set, e.g. Q_ASSERT.
#CONFIG += debug
