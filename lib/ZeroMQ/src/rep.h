#ifndef REP_H
#define REP_H
#include "socket_base.h"

class rep_t : public socket_base_t
{
public:
    rep_t();
    virtual int bind(const uint16_t &_port) override;
    virtual int unbind(const uint16_t &_port) override;
    virtual int send(char *string) override;
    virtual int recv(char *&string) override;
    virtual socket_type type() override;
    virtual my_list<ZeroMQClient*> &socket_list() override;
private:
    my_list<ZeroMQClient*>    list_socket;
   // EthernetServer server;
};

#endif // REP_H
