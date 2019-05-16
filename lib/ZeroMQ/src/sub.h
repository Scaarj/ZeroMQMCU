#ifndef SUB_H
#define SUB_H
#include "socket_base.h"
#include "list.h"

class sub_t : public socket_base_t
{
public:
    sub_t();
    virtual int connect(const _IPAddress &_address, const uint16_t &_port) override;
    virtual int connect(ZeroMQClient *&_socket);
    virtual int disconnect(const _IPAddress &_address, const uint16_t &_port) override;
    virtual int recv(char *&string) override;
    virtual int setsockopt(option_type _opt, const char *_optval, uint8_t _optvallen) override;
    virtual int close() override;
    void check_sockets();
    int authorize(ZeroMQClient *&ptr_zmq_socket);
    virtual socket_type type() override;
    virtual my_list<ZeroMQClient*> &socket_list() override;
private:
    my_list<ZeroMQClient*> list_socket;
    int subscribe(ZeroMQClient *&socket, const option_type &_opt, const char *_optval, uint8_t _optvallen);
};

#endif // SUB_H
