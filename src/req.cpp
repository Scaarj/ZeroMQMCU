#include "req.h"
#include "zeromqcommand.h"

req_t::req_t()
{

}

int req_t::connect(const _IPAddress &_address, const uint16_t &_port)
{
    if(socket.connect(_address, _port) != 1) {
           return -1;
       }

    // Temporary array. In future add identity variable for using in dealer/router protocols
    uint8_t msg_identity[] = {0x00, 0x00, 0x00, 0x00};


    uint8_t greetings[SZ_GREETINGS];
    socket.readBytes(greetings, SZ_GREETINGS);
    ZeroMQCommand::check_greeting();
    socket.write(KEY_WORDS::GREETINGS, sizeof(KEY_WORDS::GREETINGS));

    uint8_t handshake[SZ_HANDSHAKE];
    socket.readBytes(handshake, SZ_HANDSHAKE);
    ZeroMQCommand::check_handshake();
    socket.write(KEY_WORDS::HANDSHAKE, sizeof(KEY_WORDS::HANDSHAKE));

    uint8_t properties[SZ_PROPERTIES];
    socket.readBytes(properties, SZ_PROPERTIES);
    ZeroMQCommand::check_properties();
    uint8_t *prop_msg;
    uint8_t sz_prop;
    ZeroMQCommand::properties(prop_msg, sz_prop, ZMQ_REQ,
                               msg_identity, sizeof(msg_identity));
    socket.write(prop_msg, sz_prop);
    delete [] prop_msg;

    return 0;
}

int req_t::disconnect(const _IPAddress &_address, const uint16_t &_port)
{

}

int req_t::send(char *string)
{
    if(!socket.connected()) {
        connect(socket.address(), socket.destport());
    }

    uint8_t sz_head = sizeof(KEY_WORDS::ReqRepHead);
    uint8_t sz_string = strlen(string);
    uint8_t sz_full = sz_head + sizeof(uint8_t) + sz_string;
    uint8_t full_msg[sz_full];

    memcpy(full_msg, KEY_WORDS::ReqRepHead, sz_head);
    full_msg[sz_head] = sz_string;
    uint8_t head_offset = sz_head + sizeof(uint8_t);
    memcpy(full_msg + head_offset, string, sz_string);
    socket.write(full_msg, sz_full);

    return sz_full;
}

int req_t::recv(char *&string)
{
    uint8_t head[4];

    // blocking function, read head of zmq reply message
    while(socket.readBytes(head, sizeof(head)) != 4) {
        // maybe put interruption here
    }

    uint8_t sz_msg = 0;
    if(head[0] == KEY_WORDS::ReqRepHead[0] &&
       head[1] == KEY_WORDS::ReqRepHead[1] &&
       head[2] == KEY_WORDS::ReqRepHead[2]) {
        sz_msg = head[3];
    } else return -1;

    string = new char[sz_msg + 1];
    socket.readBytes(string, sz_msg);
    string[sz_msg] = 0;
    return strlen(string);
}

socket_type req_t::type()
{
    return ZMQ_REQ;
}
