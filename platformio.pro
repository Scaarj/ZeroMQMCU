win32 {
    HOMEDIR += $$(USERPROFILE)
}
else {
    HOMEDIR += $$(HOME)
}

INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/cores/arduino"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/variants/standard"
INCLUDEPATH += "$${HOMEDIR}/Projects/ZeroMQMCU/lib/MemoryTest/src"
INCLUDEPATH += "$${HOMEDIR}/Projects/ZeroMQMCU/lib/ZeroMQ/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/libraries/__cores__/arduino/SPI/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/libraries/Ethernet/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/lib/OneWire_ID1"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/libraries/__cores__/arduino/EEPROM/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/libraries/__cores__/arduino/HID/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/libraries/__cores__/arduino/SoftwareSerial/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/libraries/__cores__/arduino/Wire/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/libraries/Adafruit_CircuitPlayground"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/libraries/Adafruit_CircuitPlayground/utility"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/libraries/Bridge/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/libraries/Esplora/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/libraries/Ethernet2/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/libraries/Firmata"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/libraries/Firmata/utility"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/libraries/GSM/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/libraries/Keyboard/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/libraries/LiquidCrystal/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/libraries/Mouse/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/libraries/RobotIRremote/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/libraries/Robot_Control/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/libraries/Robot_Motor/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/libraries/SD/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/libraries/Servo/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/libraries/SpacebrewYun/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/libraries/Stepper/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/libraries/TFT/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/libraries/Temboo/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/libraries/WiFi/src"
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

SOURCES += src/subscriber.cpp \
    lib/MemoryTest/src/memorytest.cpp \
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
    lib/ZeroMQ/src/zmq.cpp \
    test/main_test.cpp
SOURCES += src/main.cpp
SOURCES +=

HEADERS += \
    lib/MemoryTest/src/memorytest.h \
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
