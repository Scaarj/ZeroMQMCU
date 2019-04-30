#include "socket.h"
#include "map.h"
extern int __bss_end;
extern void *__brkval;
int memoryFree();

//#define PUBLISHER_SOCKET
#define SUBSCRIBER_SOCKET

#ifdef PUBLISHER_SOCKET
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
zmq::socket_t publisher(ZMQ_PUB);
uint16_t port = 5555;

void setup() {
    Serial.begin(115200);

    Serial.println("Start ethernet.");
    while(!Ethernet.begin(mac)) {
    }

    Serial.print("Start publisher");
    publisher.bind(port);
    randomSeed(analogRead(0));

    DDRD |= B10000000;
    PORTD &= (~B10000000);

}

void loop() {
    char *msg = "head1 1234";
    PORTD |= B10000000;
    publisher.send(msg);
    PORTD &= (~B10000000);
}

#elif defined SUBSCRIBER_SOCKET
byte mac[] = { 0x16, 0xD5, 0x98, 0x5B, 0x56, 0xEF };
zmq::socket_t subscriber(ZMQ_SUB);
_IPAddress  addr(192, 168, 1, 107);
uint16_t    port = 5555;

void setup() {
    Serial.begin(115200);

    Serial.println("Start ethernet.");
    while(!Ethernet.begin(mac)) {
    }

    Serial.print("Connect subscribe");
    subscriber.setsockopt(ZMQ_SUBSCRIBE, "head1", 5);
    subscriber.connect(addr, port);

    for(int i = 0; i < 8; ++i) {
        w5500.writeSnMR(i, 0x20);
    }

    DDRD |= B10000000;
    PORTD &= (~B10000000);
}

void loop() {
    char *msg;
    //PORTD |= B10000000;
    subscriber.recv(msg);
    //PORTD &= (~B10000000);
    //Serial.println(msg);
    zmq::free_msg(msg);
}
#endif

int memoryFree()
{
    int freeValue;
    if((int)__brkval == 0)
        freeValue = ((int)&freeValue) - ((int)&__bss_end);
    else
        freeValue = ((int)&freeValue) - ((int)__brkval);
    return freeValue;
}
