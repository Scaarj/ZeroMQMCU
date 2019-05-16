#ifndef ZMQ_H
#define ZMQ_H
#include "list.h"
#include <avr/pgmspace.h>

#define WIZNET5500

#ifdef WIZNET5500
#include "Ethernet/Ethernet2.h"
#include "Ethernet/EthernetUdp2.h"
#include "Ethernet/EthernetClient.h"
#include "Ethernet/EthernetServer.h"
#elif (defined WIZNET5100) || (defined WIZNET5200)
#include "Ethernet.h"
#include "EthernetUdp.h"
#include "EthernetClient.h"
#include "EthernetServer.h"
#endif


#define ZMQ_MAJOR_VERSION 0x03

int compare_msg(const uint8_t *_msg1, const uint8_t *_msg2, size_t _sz);

namespace KEY_WORDS {
    const uint8_t GREETINGS[] =  {0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
                                0x00, 0x00, 0x01, 0x7f, ZMQ_MAJOR_VERSION};
    const uint8_t HANDSHAKE[] = {0x00, 0x4e, 0x55, 0x4c, 0x4c, 0x00,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                0x00, 0x00, 0x00, 0x00, 0x00};
    const char Ready[] =        "READY";
    const char Identity[] =     "Identity";
    const char SocketType[] =   "Socket-Type";
    const char Req[] =          "REQ";
    const char Rep[] =          "REP";
    const char Sub[] =          "SUB";
    const char Pub[] =          "PUB";
    const char ReqRepHead[] =   {0x01, 0x00, 0x00};
    const char Separator[64] =  { 0 };
}

enum transport {
    ZMQ_TCP,
    ZMQ_UDP
};

enum socket_type {
    ZMQ_REQ = 0,
    ZMQ_REP,
    ZMQ_SUB,
    ZMQ_PUB,
    ZMQ_UNKNOW
};

#endif // ZMQ_H
