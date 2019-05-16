#include "zeromqclient.h"
#include "Ethernet/utility/socket.h"
#include "Ethernet/utility/w5500.h"

void ZeroMQClient::recvGreetings()
{
    uint8_t msg[SZ_GREETINGS];
    uint8_t sz = readBytes(msg, SZ_GREETINGS);
    if(sz == SZ_GREETINGS)
        m_state = statement::greetings_recv;
    else m_state = statement::bad_statement;
}

void ZeroMQClient::recvHandshake()
{
    uint8_t msg[SZ_HANDSHAKE];
    uint8_t sz = readBytes(msg, SZ_HANDSHAKE);
    if(sz == SZ_HANDSHAKE)
        m_state = statement::handshake_recv;
    else m_state = statement::bad_statement;
}

void ZeroMQClient::recvProperties()
{
    uint8_t msg[SZ_PROPERTIES];
    uint8_t sz = readBytes(msg, SZ_PROPERTIES);
    if(sz == SZ_PROPERTIES)
        m_state = statement::property_recv;
    else m_state = statement::bad_statement;
}

void ZeroMQClient::sendGreetings()
{
    uint8_t sz = send(KEY_WORDS::GREETINGS, sizeof(KEY_WORDS::GREETINGS));
    if(sz == sizeof(KEY_WORDS::GREETINGS))
        m_state = statement::greetings_send;
    else m_state = statement::bad_statement;
}

void ZeroMQClient::sendHandshake()
{
    uint8_t sz = send(KEY_WORDS::HANDSHAKE, sizeof(KEY_WORDS::HANDSHAKE));
    if(sz == sizeof(KEY_WORDS::HANDSHAKE))
        m_state = statement::handshake_send;
    else m_state = statement::bad_statement;
}

void ZeroMQClient::sendProperties(const socket_type& type)
{
    uint8_t *prop_msg;
    uint8_t sz_prop;
    ZeroMQCommand::properties(prop_msg, sz_prop, type);
    uint8_t sz = send(prop_msg, sz_prop);
    delete [] prop_msg;
    if(sz == SZ_PROPERTIES) {
        m_state = statement::property_send;
    } else m_state = statement::bad_statement;
}

statement ZeroMQClient::state() const
{
    return m_state;
}

void ZeroMQClient::setState(const statement &state)
{
    m_state = state;
}
/*
// This function recive all available data in socket
int ZeroMQClient::recv_all(uint8_t *&message)
{
    // Check how much data is available
    int16_t ret = w5500.getRXReceivedSize(_sock);

    if ( ret == 0 )
    {
        // No data available.
        uint8_t status = w5500.readSnSR(_sock);
        if ( status == SnSR::LISTEN || status == SnSR::CLOSED || status == SnSR::CLOSE_WAIT )
        {
            // The remote end has closed its side of the connection, so this is the eof state
            ret = 0;
        }
        else
        {
            // The connection is still up, but there's no data waiting to be read
            ret = -1;
        }
    }

    if ( ret > 2 )
    {
        message = new uint8_t[ret];
        w5500.recv_data_processing(_sock, message, ret);
        w5500.execCmdSn(_sock, Sock_RECV);
    }

    return ret;
}*/

// Recieved a one publisher message from Rx buffer
int ZeroMQClient::recv_sub(char *&message)
{
    // Check how much data is available
    int16_t recv = w5500.getRXReceivedSize(_sock);
    uint16_t ptr = w5500.readSnRX_RD(_sock);

    uint8_t sz_msg = 0;

    // Incomming publisher message size should be at atleast 2 bytes
    if(recv > 2) {
        uint8_t head[2];
        w5500.read_data(_sock, ptr, head, 2);
        ptr += 2;

        sz_msg = head[1];
        message = new char[sz_msg + 1];
        w5500.read_data(_sock, ptr, (uint8_t*)message, sz_msg);
        ptr += sz_msg;

        message[sz_msg] = 0;

        w5500.writeSnRX_RD(_sock, ptr);
        w5500.execCmdSn(_sock, Sock_RECV);
    }

    return sz_msg;
}

int ZeroMQClient::send_pub(uint8_t *message, uint16_t len)
{
    if (_sock == MAX_SOCK_NUM) {
        return 0;
    }

    uint8_t status=0;
    uint16_t ret=0;
    uint16_t freesize=0;

    if (len > w5500.SSIZE)
        ret = w5500.SSIZE; // check size not to exceed MAX size.
    else
        ret = len;

    // if freebuf is available, start.
    do
    {
        freesize = w5500.getTXFreeSize(_sock);
        status = w5500.readSnSR(_sock);
        if ((status != SnSR::ESTABLISHED) && (status != SnSR::CLOSE_WAIT))
        {
            ret = 0;
            break;
        }
    }
    while (freesize < ret);

    w5500.write_data_pub(_sock, message, ret);
    w5500.execCmdSn(_sock, Sock_SEND);

    /* +2008.01 bj */
    while ( (w5500.readSnIR(_sock) & SnIR::SEND_OK) != SnIR::SEND_OK )
    {
        /* m2008.01 [bj] : reduce code */
        if ( w5500.readSnSR(_sock) == SnSR::CLOSED )
        {
            close(_sock);
            return 0;
        }
    }
    /* +2008.01 bj */
    w5500.writeSnIR(_sock, SnIR::SEND_OK);
    return ret;
}

int ZeroMQClient::send(uint8_t *message, uint16_t len)
{
    if (_sock == MAX_SOCK_NUM) {
        return 0;
    }

    uint8_t status=0;
    uint16_t ret=0;
    uint16_t freesize=0;

    if (len > w5500.SSIZE)
        ret = w5500.SSIZE; // check size not to exceed MAX size.
    else
        ret = len;

    // if freebuf is available, start.
    do
    {
        freesize = w5500.getTXFreeSize(_sock);
        status = w5500.readSnSR(_sock);
        if ((status != SnSR::ESTABLISHED) && (status != SnSR::CLOSE_WAIT))
        {
            ret = 0;
            break;
        }
    }
    while (freesize < ret);

    // copy data
    w5500.send_data_processing(_sock, message, ret);
    w5500.execCmdSn(_sock, Sock_SEND);

    /* +2008.01 bj */
    while ( (w5500.readSnIR(_sock) & SnIR::SEND_OK) != SnIR::SEND_OK )
    {
        /* m2008.01 [bj] : reduce code */
        if ( w5500.readSnSR(_sock) == SnSR::CLOSED )
        {
            close(_sock);
            return 0;
        }
    }
    /* +2008.01 bj */
    w5500.writeSnIR(_sock, SnIR::SEND_OK);
    return ret;
}
