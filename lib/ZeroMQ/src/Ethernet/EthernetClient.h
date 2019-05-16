#ifndef ethernetclient_h
#define ethernetclient_h
#include "IPAddress.h"

class EthernetClient {

public:
    EthernetClient();
    ~EthernetClient() {}
    EthernetClient(uint8_t sock);
    EthernetClient(_IPAddress address, uint16_t destport) :
        _address(address), _destport(destport) {}

    uint8_t status();
    virtual int connect(_IPAddress ip, uint16_t port);
    virtual size_t write(uint8_t);
    virtual size_t write(const uint8_t *buf, size_t size);
    virtual int available();
    virtual int read();
    virtual int read(uint8_t *buf, size_t size);
    virtual int peek();
    virtual void flush();
    virtual void stop();
    virtual uint8_t connected();
    virtual operator bool();
    virtual bool operator==(const EthernetClient&);
    virtual bool operator!=(const EthernetClient& rhs) { return !this->operator==(rhs); };
    uint8_t* _rawIPAddress(_IPAddress& addr) { return addr.raw_address(); };
    friend class EthernetServer;


    uint8_t sock() const;
    static uint16_t srcport();
    _IPAddress address() const;
    uint16_t destport() const;

    size_t readBytes( char *buffer, size_t length); // read chars from stream into buffer
    size_t readBytes( uint8_t *buffer, size_t length) { return readBytes((char *)buffer, length); }
protected:
    int timedRead();

    _IPAddress  _address;
    uint16_t    _destport;
    static uint16_t _srcport;
    uint8_t _sock;
};

#endif
