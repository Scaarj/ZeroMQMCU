#include "sub.h"
#include "zeromqcommand.h"
#include "Ethernet/utility/socket.h"

sub_t::sub_t()
{

}

int sub_t::connect(const _IPAddress &_address, const uint16_t &_port)
{
    // Safe socket to list and try connect
    ZeroMQClient *ptr_zmq_socket = new ZeroMQClient(_address, _port);
    list_socket.append(ptr_zmq_socket);

    int ret = 0;
    ret = connect(ptr_zmq_socket);
    return ret;
}

int sub_t::authorize(ZeroMQClient *&ptr_zmq_socket)
{
    my_list<zmq::options_t*>::iterator it;
    while(ptr_zmq_socket->state() != statement::authorized) {
        switch (ptr_zmq_socket->state()) {
        case statement::not_authorized:
            ptr_zmq_socket->sendGreetings();
        case statement::greetings_send:
            ptr_zmq_socket->recvGreetings();
        case statement::greetings_recv:
            ptr_zmq_socket->sendHandshake();
        case statement::handshake_send:
            ptr_zmq_socket->recvHandshake();
        case statement::handshake_recv:
            ptr_zmq_socket->sendProperties(type());
        case statement::property_send:
            ptr_zmq_socket->recvProperties();
        case statement::property_recv:
            ptr_zmq_socket->setState(statement::subscribing);
        case statement::authorized:
            it = list_option.begin();
            while(it != list_option.end()) {
                subscribe(ptr_zmq_socket, (*it)->type(), (*it)->optval(), (*it)->optvallen());
                it++;
            }

            ptr_zmq_socket->setState(statement::authorized);
            return 0;
        default:
            return -1;
            break;
        }
    }

    return 0;
}

int sub_t::connect(ZeroMQClient *&ptr_zmq_socket)
{
    if(!ptr_zmq_socket->connect(ptr_zmq_socket->address(), ptr_zmq_socket->destport())) {
        return -1;
    }

    return authorize(ptr_zmq_socket);
}

int sub_t::disconnect(const _IPAddress &_address, const uint16_t &_port)
{

}

// After using this function use delete [] for free memory!!!
int sub_t::recv(char *&string)
{
    check_sockets();

    my_list<ZeroMQClient*>::iterator it = list_socket.begin();
    ZeroMQClient *client = *it;

    while(1) {
        client = *it;

        if(client->available() && client->state() == statement::authorized) {
            break;
        } else {
            ++it;
            if(it == list_socket.end()) {
                check_sockets();
                it = list_socket.begin();
            }
        }
    }

    //PORTD |= B10000000;
    int sz_full = client->recv_sub(string);
    //PORTD |= B10000000;

    return sz_full;
}

int sub_t::setsockopt(option_type _opt, const char *_optval, uint8_t _optvallen)
{
    zmq::options_t temp_option(_opt, _optval, _optvallen);
    my_list<zmq::options_t*>::iterator it_option = list_option.begin();

    if(_opt == option_type::ZMQ_SUBSCRIBE) {
        while(it_option != list_option.end()) {
            if(*(*it_option) == temp_option) {
                break;
            }
            it_option++;
        }

        // Add subscribe to container, if itsn't exist
        if(it_option == list_option.end()) {
            zmq::options_t *ptr_option = new zmq::options_t(_opt, _optval, _optvallen);
            list_option.append(ptr_option);
        }
    } else if(_opt == option_type::ZMQ_UNSUBSCRIBE) {
        while(it_option != list_option.end()) {
            // if subscribe message for unsubscribing is founded - delete it from list
            if(*(*it_option) == temp_option) {
                delete *it_option;
                list_option.erase(it_option);
                break;
            } else {
                it_option++;
            }
        }
    }

    my_list<ZeroMQClient*>::iterator it = list_socket.begin();
    while(it != list_socket.end()) {
        if((*it)->connected()) {
            ZeroMQClient *&&client = *it;
            subscribe(client, _opt, _optval, _optvallen);
        }
        ++it;
    }

    return 0;
}

int sub_t::close()
{
    for(size_t i = 0; i < list_socket.size(); ++i) {
        list_socket.at(i)->stop();
    }

    list_socket.clear();
    return list_socket.size();
}

void sub_t::check_sockets()
{
    ZeroMQClient *client = nullptr;
    my_list<ZeroMQClient*>::iterator it = list_socket.begin();

    while(it != list_socket.end()) {
        client = *it;
        if(!client->connected()) {
            client->stop();
            client->setState(statement::not_authorized);
            connect(client);
        }
        ++it;
    }
}

socket_type sub_t::type()
{
    return ZMQ_SUB;
}

my_list<ZeroMQClient *> &sub_t::socket_list()
{
    return list_socket;
}

int sub_t::subscribe(ZeroMQClient *&socket, const option_type &_opt,
                     const char *_optval, uint8_t _optvallen)
{
    if(_opt != ZMQ_SUBSCRIBE && _opt != ZMQ_UNSUBSCRIBE)
        return -1;

    // size of subscribe option with head
    size_t full_size = 3 + _optvallen;
    uint8_t subscribe_msg[full_size];
    subscribe_msg[0] = 0x00;
    subscribe_msg[1] = _optvallen + 1;

    if(_opt == ZMQ_SUBSCRIBE)
        subscribe_msg[2] = 0x01;
    else if(_opt == ZMQ_UNSUBSCRIBE)
        subscribe_msg[2] = 0x00;

    uint8_t *ptr = (subscribe_msg + 3);
    memcpy(ptr, _optval, _optvallen);
    socket->write(subscribe_msg, full_size);
    return 0;
}
