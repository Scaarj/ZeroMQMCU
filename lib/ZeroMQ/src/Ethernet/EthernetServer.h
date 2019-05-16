#ifndef ethernetserver_h
#define ethernetserver_h
#include "Print.h"

class EthernetClient;

class EthernetServer : public Print {
private:
    uint16_t _port;
    void accept();
    void _accept(const int &sock);
public:
    EthernetServer() {}
    EthernetServer(uint16_t);
    EthernetClient available();
    EthernetClient available(const int &sock);
    virtual EthernetClient begin();
    virtual EthernetClient begin(const int &sock);
    virtual size_t write(uint8_t);
    virtual size_t write(const uint8_t *buf, size_t size);
    virtual size_t _write(const int &sock, const uint8_t *buf, size_t size);
    using Print::write;
    void set_port(const uint16_t &port);
};

#endif
