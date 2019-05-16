#include "rep.h"

rep_t::rep_t()
{

}

int rep_t::bind(const uint16_t &_port)
{
    return 0;
}

int rep_t::unbind(const uint16_t &_port)
{

}

int rep_t::send(char *string)
{
    return 0;
}

int rep_t::recv(char *&string)
{
    return 0;
}

socket_type rep_t::type()
{
    return ZMQ_REP;
}

my_list<ZeroMQClient *> &rep_t::socket_list()
{
    return list_socket;
}
