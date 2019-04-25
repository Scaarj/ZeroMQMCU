#include "utility/w5500.h"
#include "utility/socket.h"

extern "C" {
#include "string.h"
}
#include "Ethernet2.h"
#include "EthernetClient.h"
#include "EthernetServer.h"

uint16_t EthernetClient::_srcport = 1024;

EthernetClient::EthernetClient() : _sock(MAX_SOCK_NUM) {
}

EthernetClient::EthernetClient(uint8_t sock) : _sock(sock) {
}

int EthernetClient::connect(_IPAddress ip, uint16_t port) {
    _address = ip;
    _destport = port;
    if (_sock != MAX_SOCK_NUM)
        return 0;

    for (int i = 0; i < MAX_SOCK_NUM; i++) {
        uint8_t s = w5500.readSnSR(i);
        if (s == SnSR::CLOSED || s == SnSR::FIN_WAIT || s == SnSR::CLOSE_WAIT) {
            _sock = i;
            break;
        }
    }

    if (_sock == MAX_SOCK_NUM)
        return 0;

    _srcport++;
    if (_srcport == 0) _srcport = 1024;
    socket(_sock, SnMR::TCP, _srcport, 0);

    if (!::connect(_sock, _rawIPAddress(_address), _destport)) {
        _sock = MAX_SOCK_NUM;
        return 0;
    }

    while (status() != SnSR::ESTABLISHED) {
        delay(1);
        if (status() == SnSR::CLOSED) {
            _sock = MAX_SOCK_NUM;
            return 0;
        }
    }

    return 1;
}

size_t EthernetClient::write(uint8_t b) {
    return write(&b, 1);
}

size_t EthernetClient::write(const uint8_t *buf, size_t size) {
    if (_sock == MAX_SOCK_NUM) {
        return 0;
    }
    if (!send(_sock, buf, size)) {
        return 0;
    }
    return size;
}

int EthernetClient::available() {
    if (_sock != MAX_SOCK_NUM)
        return w5500.getRXReceivedSize(_sock);
    return 0;
}

int EthernetClient::read() {
    uint8_t b;
    if ( recv(_sock, &b, 1) > 0 )
    {
        // recv worked
        return b;
    }
    else
    {
        // No data available
        return -1;
    }
}

int EthernetClient::read(uint8_t *buf, size_t size) {
    return recv(_sock, buf, size);
}

int EthernetClient::peek() {
    uint8_t b;
    // Unlike recv, peek doesn't check to see if there's any data available, so we must
    if (!available())
        return -1;
    ::peek(_sock, &b);
    return b;
}

void EthernetClient::flush() {
    ::flush(_sock);
}

void EthernetClient::stop() {
    if (_sock == MAX_SOCK_NUM)
        return;

    // attempt to close the connection gracefully (send a FIN to other side)
    disconnect(_sock);
    unsigned long start = millis();

    // wait a second for the connection to close
    while (status() != SnSR::CLOSED && millis() - start < 1000)
        delay(1);

    // if it hasn't closed, close it forcefully
    if (status() != SnSR::CLOSED)
        close(_sock);

    EthernetClass::_server_port[_sock] = 0;
    _sock = MAX_SOCK_NUM;
}

uint8_t EthernetClient::connected() {
    if (_sock == MAX_SOCK_NUM) return 0;

    uint8_t s = status();
    return !(s == SnSR::LISTEN || s == SnSR::CLOSED || s == SnSR::FIN_WAIT ||
             (s == SnSR::CLOSE_WAIT && !available()));
}

uint8_t EthernetClient::status() {
    if (_sock == MAX_SOCK_NUM) return SnSR::CLOSED;
    return w5500.readSnSR(_sock);
}

// the next function allows us to use the client returned by
// EthernetServer::available() as the condition in an if-statement.

EthernetClient::operator bool() {
    return _sock != MAX_SOCK_NUM;
}

bool EthernetClient::operator==(const EthernetClient& rhs) {
    return _sock == rhs._sock && _sock != MAX_SOCK_NUM && rhs._sock != MAX_SOCK_NUM;
}

size_t EthernetClient::readBytes(char *buffer, size_t length)
{
    size_t count = 0;
    while (count < length) {
        int c = timedRead();
        if (c < 0) break;
        *buffer++ = (char)c;
        count++;
    }
    return count;
}

uint16_t EthernetClient::destport() const
{
    return _destport;
}

int EthernetClient::timedRead()
{
    int c;
    unsigned long _startMillis = millis();
    do {
        c = read();
        if (c >= 0) return c;
    } while(millis() - _startMillis < 1000);
    return -1;     // -1 indicates timeout
}

uint8_t EthernetClient::sock() const
{
    return _sock;
}

_IPAddress EthernetClient::address() const
{
    return _address;
}
