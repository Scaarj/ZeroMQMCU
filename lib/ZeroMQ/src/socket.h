#ifndef SOCKET_H
#define SOCKET_H
#include "socket_base.h"

namespace zmq {

void free_msg(char *&string);

struct option
{
    option() {}
};
    class socket_t
    {
    public:
        socket_t(socket_type _type);
        int bind(uint16_t _port);
        int unbind(uint16_t _port);
        int connect(_IPAddress _address, uint16_t _port);
        int disconnect(_IPAddress _address, uint16_t _port);
        int send(char *string);
        int recv(char *&string);
        int close();
        int setsockopt(option_type _opt, const char *_optval, size_t _optvallen);
        int getsockopt();
        socket_type get_type() const;
    private:
        socket_base_t   *ptr_socket;
    };
}

#endif // SOCKET_H
