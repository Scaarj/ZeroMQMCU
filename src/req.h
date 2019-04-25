#ifndef REQ_H
#define REQ_H
#include "socket_base.h"

class req_t : public socket_base_t
{
public:
    req_t();
    virtual int connect(const _IPAddress &_address, const uint16_t &_port) override;
    virtual int disconnect(const _IPAddress &_address, const uint16_t &_port) override;
    virtual int send(char *string) override;
    virtual int recv(char *&string) override;
    virtual socket_type type() override;
private:
    EthernetClient  socket;
};

#endif // REQ_H
