#include "socket_base.h"

socket_base_t::socket_base_t()
{

}

int socket_base_t::bind(const uint16_t &_port)
{
    return -1;
}

int socket_base_t::unbind(const uint16_t &_port)
{
    return -1;
}

int socket_base_t::connect(const _IPAddress &_address, const uint16_t &_port)
{
    return -1;
}

int socket_base_t::disconnect(const _IPAddress &_address, const uint16_t &_port)
{
    return -1;
}

int socket_base_t::connect(ZeroMQClient *&_socket)
{
    return -1;
}

int socket_base_t::disconnect(ZeroMQClient *&_socket)
{
    return -1;
}

int socket_base_t::recv(ZeroMQClient *&_socket)
{
    return -1;
}

int socket_base_t::send(char *string)
{
    return -1;
}

int socket_base_t::recv(char *&string)
{
    return -1;
}

int socket_base_t::setsockopt(option_type _opt, const char *_optval, uint8_t _optvallen)
{
    return -1;
}

int socket_base_t::close()
{
    return -1;
}

socket_type socket_base_t::type()
{
    return socket_type::ZMQ_UNKNOW;
}
