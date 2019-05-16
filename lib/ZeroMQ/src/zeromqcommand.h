#ifndef ZeroMQCommand_H
#define ZeroMQCommand_H
#include "zmq.h"

#define SZ_GREETINGS    10
#define SZ_HANDSHAKE    54
#define SZ_PROPERTIES   27

class ZeroMQCommand
{
public:
    ZeroMQCommand();
    static int properties(uint8_t *&msg,
                               uint8_t &sz,
                               socket_type _type,
                               const uint8_t *idenity = nullptr,
                               const size_t sz_identity = 0);
    static int check_greeting();
    static int check_handshake();
    static int check_properties();
private:
    static void write_ready(uint8_t *&ptr);
    static void write_socket(uint8_t *&ptr, const socket_type _type);
    static void write_identity(uint8_t *&ptr,
                        const uint8_t *identity,
                        const size_t sz_identity);
    static size_t message_size(const socket_type _type, const size_t sz_identity);


};

#endif // ZeroMQCommand_H
