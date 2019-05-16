win32 {
    HOMEDIR += $$(USERPROFILE)
}
else {
    HOMEDIR += $$(HOME)
}

INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/cores/arduino"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/variants/standard"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-atmelavr/avr/include"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-atmelavr/lib/gcc/avr/4.9.2/include"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-atmelavr/lib/gcc/avr/4.9.2/include-fixed"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/tool-unity"

DEFINES += "F_CPU=16000000L"
DEFINES += "PLATFORMIO=30504"
DEFINES += "ARDUINO_AVR_UNO"
DEFINES += "ARDUINO_ARCH_AVR"
DEFINES += "ARDUINO=10805"
DEFINES += "__AVR_ATmega328P__"

OTHER_FILES += platformio.ini

HEADERS += src/zeromqclient.h \
    lib/ZeroMQ/src/Ethernet/Dhcp.h \
    lib/ZeroMQ/src/Ethernet/Ethernet2.h \
    lib/ZeroMQ/src/Ethernet/EthernetClient.h \
    lib/ZeroMQ/src/Ethernet/EthernetServer.h \
    lib/ZeroMQ/src/Ethernet/EthernetUdp2.h \
    lib/ZeroMQ/src/Ethernet/IPAddress.h \
    lib/ZeroMQ/src/Ethernet/utility/SPI.h \
    lib/ZeroMQ/src/Ethernet/utility/socket.h \
    lib/ZeroMQ/src/Ethernet/utility/util.h \
    lib/ZeroMQ/src/Ethernet/utility/w5500.h \
    lib/ZeroMQ/src/context.h \
    lib/ZeroMQ/src/list.h \
    lib/ZeroMQ/src/map.h \
    lib/ZeroMQ/src/options.h \
    lib/ZeroMQ/src/pub.h \
    lib/ZeroMQ/src/rep.h \
    lib/ZeroMQ/src/req.h \
    lib/ZeroMQ/src/singleton.h \
    lib/ZeroMQ/src/socket.h \
    lib/ZeroMQ/src/socket_base.h \
    lib/ZeroMQ/src/sub.h \
    lib/ZeroMQ/src/tools.h \
    lib/ZeroMQ/src/util.h \
    lib/ZeroMQ/src/zeromqclient.h \
    lib/ZeroMQ/src/zeromqcommand.h \
    lib/ZeroMQ/src/zmq.h
SOURCES += src/options.cpp \
    lib/ZeroMQ/src/Ethernet/Dhcp.cpp \
    lib/ZeroMQ/src/Ethernet/Ethernet2.cpp \
    lib/ZeroMQ/src/Ethernet/EthernetClient.cpp \
    lib/ZeroMQ/src/Ethernet/EthernetServer.cpp \
    lib/ZeroMQ/src/Ethernet/EthernetUdp2.cpp \
    lib/ZeroMQ/src/Ethernet/IPAddress.cpp \
    lib/ZeroMQ/src/Ethernet/utility/SPI.cpp \
    lib/ZeroMQ/src/Ethernet/utility/socket.cpp \
    lib/ZeroMQ/src/Ethernet/utility/w5500.cpp \
    lib/ZeroMQ/src/context.cpp \
    lib/ZeroMQ/src/list.cpp \
    lib/ZeroMQ/src/map.cpp \
    lib/ZeroMQ/src/options.cpp \
    lib/ZeroMQ/src/pub.cpp \
    lib/ZeroMQ/src/rep.cpp \
    lib/ZeroMQ/src/req.cpp \
    lib/ZeroMQ/src/singleton.cpp \
    lib/ZeroMQ/src/socket.cpp \
    lib/ZeroMQ/src/socket_base.cpp \
    lib/ZeroMQ/src/sub.cpp \
    lib/ZeroMQ/src/zeromqclient.cpp \
    lib/ZeroMQ/src/zeromqcommand.cpp \
    lib/ZeroMQ/src/zmq.cpp
HEADERS += src/rep.h
HEADERS += src/sub.h
HEADERS += src/singleton.h
SOURCES += src/zmq.cpp
HEADERS += src/pub.h
HEADERS += src/tools.h
HEADERS += src/list.h
HEADERS += src/map.h
HEADERS += src/context.h
SOURCES += src/socket.cpp
SOURCES += src/rep.cpp
HEADERS += src/socket_base.h
SOURCES += src/context.cpp
SOURCES += src/main.cpp
SOURCES += src/list.cpp
HEADERS += src/req.h
SOURCES += src/zeromqclient.cpp
HEADERS += src/zmq.h
SOURCES += src/pub.cpp
SOURCES += src/req.cpp
SOURCES += src/singleton.cpp
HEADERS += src/options.h
SOURCES += src/zeromqcommand.cpp
SOURCES += src/sub.cpp
HEADERS += src/zeromqcommand.h
SOURCES += src/socket_base.cpp
HEADERS += src/socket.h
SOURCES += src/map.cpp
HEADERS += src/Ethernet/IPAddress.h
SOURCES += src/Ethernet/EthernetServer.cpp
HEADERS += src/Ethernet/util.h
HEADERS += src/Ethernet/Dhcp.h
SOURCES += src/Ethernet/IPAddress.cpp
SOURCES += src/Ethernet/Dhcp.cpp
HEADERS += src/Ethernet/Ethernet2.h
HEADERS += src/Ethernet/EthernetUdp2.h
SOURCES += src/Ethernet/EthernetClient.cpp
HEADERS += src/Ethernet/EthernetServer.h
SOURCES += src/Ethernet/Ethernet2.cpp
SOURCES += src/Ethernet/EthernetUdp2.cpp
HEADERS += src/Ethernet/EthernetClient.h
HEADERS += src/Ethernet/utility/util.h
HEADERS += src/Ethernet/utility/SPI.h
SOURCES += src/Ethernet/utility/w5500.cpp
SOURCES += src/Ethernet/utility/socket.cpp
HEADERS += src/Ethernet/utility/w5500.h
SOURCES += src/Ethernet/utility/SPI.cpp
HEADERS += src/Ethernet/utility/socket.h
