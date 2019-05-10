#ifndef SUB_H
#define SUB_H
#include "socket_base.h"
#include "list.h"

class sub_t : public socket_base_t
{
public:
    sub_t();
    ~sub_t();
private:
    virtual int connect(const _IPAddress &_address, const uint16_t &_port) override;
    virtual int connect(ZeroMQClient *&_socket);
    virtual int disconnect(const _IPAddress &_address, const uint16_t &_port) override;
    virtual int recv(char *&string) override;
    virtual int setsockopt(option_type _opt, const char *_optval, uint8_t _optvallen) override;
    virtual int close() override;
    virtual socket_type type() override;

    int subscribe(ZeroMQClient *&socket, const option_type &_opt,
                  const char *_optval, uint8_t _optvallen);
    void check_sockets();
    int authorize(ZeroMQClient *&ptr_zmq_socket);
private:
    my_list<ZeroMQClient*> list_socket;
};

#endif // SUB_H
