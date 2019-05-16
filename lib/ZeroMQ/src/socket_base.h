#ifndef SOCKET_BASE_H
#define SOCKET_BASE_H
#include "zmq.h"
#include "options.h"
#include "zeromqclient.h"

class socket_base_t
{
public:
    socket_base_t();
public:
    virtual int bind(const uint16_t &_port);
    virtual int unbind(const uint16_t &_port);

    virtual int connect(const _IPAddress &_address, const uint16_t &_port);
    virtual int disconnect(const _IPAddress &_address, const uint16_t &_port);

    virtual int connect(ZeroMQClient *&_socket);
    virtual int disconnect(ZeroMQClient *&_socket);
    virtual int recv(ZeroMQClient *&_socket);

    virtual int send(char *string);
    virtual int recv(char *&string);

    virtual int setsockopt(option_type _opt, const char *_optval, uint8_t _optvallen);
    virtual int close();

    virtual my_list<ZeroMQClient*> &socket_list();
    virtual socket_type type();

    _IPAddress address() const;
    uint16_t port() const;
protected:
    my_list<zmq::options_t*> list_option;
};

#endif // SOCKET_BASE_H
