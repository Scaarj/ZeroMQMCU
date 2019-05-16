#include "socket.h"
#include "rep.h"
#include "req.h"
#include "sub.h"
#include "pub.h"

zmq::socket_t::socket_t(socket_type _type)
{
    ptr_socket = nullptr;
    switch (_type) {
    case ZMQ_REP:
        ptr_socket = new rep_t();
        break;
    case ZMQ_REQ:
        ptr_socket = new req_t();
        break;
    case ZMQ_PUB:
        ptr_socket = new pub_t();
        break;
    case ZMQ_SUB:
        ptr_socket = new sub_t();
        break;
    default:
        return;
    }
}

int zmq::socket_t::bind(uint16_t _port)
{
    return ptr_socket->bind(_port);
}

int zmq::socket_t::unbind(uint16_t _port)
{
    return ptr_socket->unbind(_port);
}

int zmq::socket_t::connect(_IPAddress _address, uint16_t _port)
{
    return ptr_socket->connect(_address, _port);
}

int zmq::socket_t::disconnect(_IPAddress _address, uint16_t _port)
{
    return ptr_socket->connect(_address, _port);
}

int zmq::socket_t::send(char *string)
{
    return ptr_socket->send(string);
}

int zmq::socket_t::recv(char *&string)
{
    return ptr_socket->recv(string);
}

int zmq::socket_t::close()
{
    return ptr_socket->close();
}

int zmq::socket_t::setsockopt(option_type _opt, const char *_optval, size_t _optvallen)
{
    ptr_socket->setsockopt(_opt, _optval, _optvallen);
    return 0;
}

void zmq::free_msg(char *&string)
{
    delete [] string;
}
