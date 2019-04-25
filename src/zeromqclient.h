#ifndef ZEROMQSOCKET_H
#define ZEROMQSOCKET_H
#include "Ethernet/EthernetClient.h"
#include "zeromqcommand.h"

enum socket_status {
    LISTEN = 0,
    CONNECTED,
    GREETED,
    HANDSHAKED,
    PROPERTIED,
    AUTHORIZED,
    DISCONNECTED,
    TIMEOUT
};

enum statement {
    not_authorized = 0,
    authorized,
    greetings_send,
    greetings_recv,
    handshake_send,
    handshake_recv,
    property_send,
    property_recv,
    subscribe_send,
    subscribing,
    bad_statement
};

class ZeroMQClient : public EthernetClient {
public:
    ZeroMQClient() : m_state(not_authorized) {}
    ZeroMQClient(const _IPAddress &address, const uint16_t &port) : m_state(not_authorized)
    {
        _address = address;
        _destport = port;
        m_state = not_authorized;
    }
    virtual ~ZeroMQClient() { stop(); }
    ZeroMQClient(EthernetClient client) : EthernetClient(client) {}


    bool operator==(const ZeroMQClient &second) {
        return (sock() == second.sock());
    }

    bool is_authorized() const;
    void authorizing();

    void recvGreetings();
    void recvHandshake();
    void recvProperties();

    void sendGreetings();
    void sendHandshake();
    void sendProperties(const socket_type &type);

    statement state() const;

    void setState(const statement &state);
    //int recv_all(uint8_t *&message);
    int recv_sub(char *&message);
    int send_pub(uint8_t *message, uint16_t len);
    int send(uint8_t *message, uint16_t len);
private:
    ZeroMQClient(const ZeroMQClient&) {}
    statement m_state;
};

#endif // ZEROMQSOCKET_H
