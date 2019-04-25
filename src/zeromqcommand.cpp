#include "zeromqcommand.h"

ZeroMQCommand::ZeroMQCommand()
{

}

int ZeroMQCommand::properties(uint8_t *&full_msg,
                                    uint8_t &sz_full_msg,
                                    socket_type _type,
                                    const uint8_t *idenity, const size_t sz_identity)
{
    // read property from reply server and check it
    //if(check_input_property() == -1)
    //    return -1;

    // get full size of propert message with 2 bytes of head
    sz_full_msg = message_size(_type, sz_identity);
    if(sz_full_msg == 0)
        return -1;

    full_msg = new uint8_t[sz_full_msg];
    full_msg[0] = 0x04;
    // write size of message without head
    full_msg[1] = sz_full_msg - 2;

    // start from 2 index in array
    uint8_t *ptr = (full_msg + 2);
    write_ready(ptr);
    write_socket(ptr, _type);

    // identity used for REQ/REP protocols
    if(sz_identity)
        write_identity(ptr, idenity, sz_identity);

    return 0;
}

void ZeroMQCommand::write_ready(uint8_t *&ptr)
{
    uint8_t sz_ready = sizeof(KEY_WORDS::Ready) - 1;
    memcpy(ptr, &sz_ready, sizeof(sz_ready));
    ptr++;
    memcpy(ptr, KEY_WORDS::Ready, sz_ready);
    ptr += sz_ready;
}

void ZeroMQCommand::write_socket(uint8_t *&ptr, const socket_type _type)
{
    uint8_t sz_socket_type = sizeof(KEY_WORDS::SocketType) - 1;
    uint8_t sz_socket = 0;

    memcpy(ptr, &sz_socket_type, sizeof(sz_socket_type));
    ptr++;
    memcpy(ptr, KEY_WORDS::SocketType, sz_socket_type);
    ptr += sz_socket_type;

    uint8_t sz_separator = 3;
    memcpy(ptr, KEY_WORDS::Separator, sz_separator);
    ptr += sz_separator;

    switch (_type) {
    case ZMQ_REQ:
        sz_socket = sizeof(KEY_WORDS::Req) - 1;
        memcpy(ptr, &sz_socket, sizeof(sz_socket));
        ptr++;
        memcpy(ptr, KEY_WORDS::Req, sz_socket);
        ptr += sz_socket;
        break;
    case ZMQ_SUB:
        sz_socket = sizeof(KEY_WORDS::Sub) - 1;
        memcpy(ptr, &sz_socket, sizeof(sz_socket));
        ptr++;
        memcpy(ptr, KEY_WORDS::Sub, sz_socket);
        ptr += sz_socket;
        break;
    case ZMQ_PUB:
        sz_socket = sizeof(KEY_WORDS::Pub) - 1;
        memcpy(ptr, &sz_socket, sizeof(sz_socket));
        ptr++;
        memcpy(ptr, KEY_WORDS::Pub, sz_socket);
        ptr += sz_socket;
        break;
    case ZMQ_REP:
        sz_socket = sizeof(KEY_WORDS::Rep) - 1;
        memcpy(ptr, &sz_socket, sizeof(sz_socket));
        ptr++;
        memcpy(ptr, KEY_WORDS::Rep, sz_socket);
        ptr += sz_socket;
        break;
    default:
        break;
    }
}

void ZeroMQCommand::write_identity(uint8_t *&ptr,
                                    const uint8_t *identity,
                                    const size_t sz_identity)
{
    uint8_t sz_word_identity = sizeof(KEY_WORDS::Identity) - 1;
    memcpy(ptr, &sz_word_identity, sizeof(sz_word_identity));
    ptr++;
    memcpy(ptr, KEY_WORDS::Identity, sz_word_identity);
    ptr += sz_word_identity;
    memcpy(ptr, identity, sz_identity);
    ptr += sz_identity;
}

size_t ZeroMQCommand::message_size(const socket_type _type, const size_t sz_identity)
{
    // Sizeof(null terminated string) ==
    // == sizeof(uint8_t) + sizeof(sending string without null terminate)
    uint8_t sz_full_msg = 0;
    uint8_t sz_ready = sizeof(KEY_WORDS::Ready);
    uint8_t sz_socket_type = sizeof(KEY_WORDS::SocketType);
    uint8_t sz_separator = 3;
    uint8_t sz_socket = 0;
    uint8_t sz_word_identity = 0;

    switch (_type) {
    case ZMQ_REQ:
        sz_socket = sizeof(KEY_WORDS::Req);
        sz_word_identity = sizeof(KEY_WORDS::Identity);
        break;
    case ZMQ_SUB:
        sz_socket = sizeof(KEY_WORDS::Sub);
        break;
    case ZMQ_PUB:
        sz_socket = sizeof(KEY_WORDS::Pub);
        break;
    case ZMQ_REP:
        sz_socket = sizeof(KEY_WORDS::Rep);
        sz_word_identity = sizeof(KEY_WORDS::Identity);
        break;
    default:
        return 0;
        break;
    }

    // 2 bytes is head of property message
    sz_full_msg = 2 + sz_ready + sz_socket_type + sz_separator +
            sz_socket + sz_word_identity + sz_identity;
    return sz_full_msg;
}

int ZeroMQCommand::check_greeting()
{
    uint8_t answer[10];
}

int ZeroMQCommand::check_handshake()
{
    uint8_t answer[54];
}

int ZeroMQCommand::check_properties()
{
    uint8_t answer[27];
}
