#ifndef PUB_H
#define PUB_H
#include "socket_base.h"
#include "map.h"

class pub_t : public socket_base_t, public EthernetServer
{
public:
    pub_t();
    uint8_t get_socks() const;
protected:
    virtual int bind(const uint16_t &_port) override;
    virtual int unbind(const uint16_t &_port) override;
    virtual int send(char *string) override;

    my_list<ZeroMQClient *> &socket_list();
    virtual socket_type type() override;
private:
    uint16_t m_port;
    my_map<char*, uint8_t>  *map_subscribes;
    my_list<ZeroMQClient*>  list_socket;

    void check_sockets();
    void check_message();
    int form_message(char *&string);

    void drop_message(ZeroMQClient *&ptr_zmq_socket);
    void subscribe(ZeroMQClient *&ptr_zmq_socket);
    void unsubscribe_all(ZeroMQClient *ptr_zmq_socket);

    int authorize(ZeroMQClient *&ptr_zmq_socket);
};

#endif // PUB_H
