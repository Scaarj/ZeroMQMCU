#include "pub.h"
#include "Ethernet/utility/socket.h"

pub_t::pub_t()
{
    map_subscribes = new my_map<char*, uint8_t>;
}

pub_t::~pub_t()
{

}

int pub_t::bind(const uint16_t &_port)
{
    if(list_socket.size() >= MAX_SOCK_NUM)
        return -1;

    m_port = _port;
    EthernetServer::set_port(m_port);
    ZeroMQClient *socket = new ZeroMQClient(begin());
    socket->setState(statement::not_authorized);
    list_socket.append(socket);
    return 0;
}

int pub_t::unbind(const uint16_t &_port)
{

}

int pub_t::send(char *string)
{
    // Check all connection
    check_sockets();

    // Should have atleast 2 socket, for sending message.
    // If there is one socket at the moment, then there are no authorized connections.
    // Because 1 socket just listen port
    if(list_socket.size() <= 1)
        return 0;

    // Check for input message
    check_message();
    // Form publisher message and send to subscribers
    int sz = form_message(string);
    return sz;
}

int pub_t::authorize(ZeroMQClient *&ptr_zmq_socket)
{
    while(ptr_zmq_socket->state() != statement::authorized) {
        switch (ptr_zmq_socket->state()) {
        case statement::not_authorized:
            ptr_zmq_socket->recvGreetings();
        case statement::greetings_recv:
            ptr_zmq_socket->sendGreetings();
        case statement::greetings_send:
            ptr_zmq_socket->recvHandshake();
        case statement::handshake_recv:
            ptr_zmq_socket->sendHandshake();
        case statement::handshake_send:
            ptr_zmq_socket->recvProperties();
        case statement::property_recv:
            ptr_zmq_socket->sendProperties(type());
        case statement::property_send:
            ptr_zmq_socket->setState(statement::authorized);
        case statement::authorized:
        default:
            return -1;
            break;
        }
    }

    return 0;
}

// Subscribe message have next form:
// 0x00/uint8_t full size/0x01 delimiter/ message with size = full size - 1
// Its possible to get several subscribing message in one - in connection
// subscriber send it in one message
void pub_t::subscribe(ZeroMQClient *&ptr_zmq_socket)
{
    while(ptr_zmq_socket->available()) {
        uint8_t head = ptr_zmq_socket->read();
        // If bad head drop the message
        if(head != 0x00) {
            drop_message(ptr_zmq_socket);
            return;
        }

        // sz_full = size of type + size of msg
        uint8_t sz_full = ptr_zmq_socket->read();
        // 0x00 - unsubscribe, 0x01 - subscribe
        uint8_t type_msg = ptr_zmq_socket->read();
        // Subscribe string. Allocate size for string + byte for '\0'
        char *subscribe = new char[sz_full];
        ptr_zmq_socket->readBytes(subscribe, sz_full - 1);

        // If sz_msg equal 1, its mean that this socket subscribing for all message
        // by sending empty string "0x00 0x01 0x01"

        // set end of string null-delimiter
        subscribe[sz_full - 1] = 0;

        // Msg type - 0x00 unsubscribe, 0x01 - subscribe
        if(type_msg == 0x01) {
            uint8_t socket_bit_mask = (1 << ptr_zmq_socket->sock());

            if(map_subscribes->contains(subscribe)) {
                map_subscribes->value(subscribe) |= socket_bit_mask;
                // delete string if already have this string in map container
                delete [] subscribe;
            } else {
                map_subscribes->insert(subscribe, socket_bit_mask);
            }
        } else
            // Unsubscribe
            if(type_msg == 0x00) {
                uint8_t value = map_subscribes->value(subscribe);
                value &= ~(1 << ptr_zmq_socket->sock());

                // If no one subscrided on this message - delete from container
                if(value == 0) {
                    map_subscribes->remove(subscribe);
                }
                delete [] subscribe;
            } else drop_message(ptr_zmq_socket);
    }
}

void pub_t::unsubscribe_all(ZeroMQClient *ptr_zmq_socket)
{
    uint8_t sock_mask = 1 << ptr_zmq_socket->sock();
    // Take inverse of socket mask for attract with socket mask with map.value()
    sock_mask = ~sock_mask;
    my_map<char*, uint8_t> *new_map = new my_map<char*, uint8_t>;

    // In this cycle we passing map_subscribe by deleting root node
    // and insert this node to new map, if statement root()->data != 0 is true,
    // otherwise we delete this node (including string) without adding.
    // After complete passing container, set pointer to new map
    while(map_subscribes->size()) {
        // Check subscribe for existing socket-client after disconnect one
        uint8_t temp_data = (sock_mask & map_subscribes->root()->data);

        // If one or more client subscribed on this subscribe message
        // put this element in new map, if not delete [] string
        if(temp_data != 0) {
            new_map->insert(map_subscribes->root()->key, temp_data);
        } else {
            delete [] map_subscribes->root()->key;
        }
        map_subscribes->remove(map_subscribes->root()->key);
    }

    delete map_subscribes;
    map_subscribes = new_map;

    my_list<ZeroMQClient*>::iterator it = list_socket.begin();
    while(it != list_socket.end()) {
        if(*it == ptr_zmq_socket) {
            list_socket.erase(it);
            delete ptr_zmq_socket;
            break;
        } else it++;
    }

    return 0;
}

socket_type pub_t::type()
{
    return ZMQ_PUB;
}

void pub_t::check_sockets()
{
    // count of listen sockets
    int count = 0;

    my_list<ZeroMQClient*>::iterator it = list_socket.begin();
    while(it != list_socket.end()) {
        ZeroMQClient *client = *it;
        uint8_t _status = client->status();

        if(_status == SnSR::CLOSED || _status == SnSR::FIN_WAIT || _status == SnSR::CLOSE_WAIT) {
            list_socket.erase(it);
            if(client->state() == statement::authorized)
                unsubscribe_all(client);
            client->stop();
            delete client;

            continue;
        } else if(_status == SnSR::LISTEN) {
            count++;

            if(count > 1) {
                list_socket.erase(it);
                if(client->state() == statement::authorized)
                    unsubscribe_all(client);
                client->stop();
                delete client;
                continue;
            }
        }
        ++it;
    }

    if(count == 0)
        this->bind(m_port);
}

void pub_t::check_message()
{
    my_list<ZeroMQClient*>::iterator it = list_socket.begin();
    while(it != list_socket.end()) {
        ZeroMQClient *client = *it;
        if(client->available()) {
            if(client->state() == statement::authorized) {
                subscribe(client);
            } else if(client->state() == statement::not_authorized) {
                authorize(client);
                subscribe(client);
            }
        }
        ++it;
    }
}

int pub_t::form_message(char *string)
{
    size_t sz_subscribe = 0;
    size_t sz_string = strlen(string);
    // Finding space - its end of subscribe-string
    while((int)(*(string + sz_subscribe)) != 32 && sz_subscribe < sz_string) {
        sz_subscribe++;
    }

    char subscribe[sz_subscribe + 1];
    memcpy(subscribe, string, sz_subscribe);
    subscribe[sz_subscribe] = 0;

    // socket mask which subscribed for all message, checking on every message sending
    uint8_t mask_sub_for_all = 0;
    mask_sub_for_all = map_subscribes->value("");
    // socket mask which subscribed on current message
    uint8_t mask_socket = 0;
    mask_socket = map_subscribes->value(subscribe);

    // Union sockets mask, that should recieve a message
    mask_socket |= mask_sub_for_all;
    if(!mask_socket)
        return -1;
    uint8_t sz_msg = 0;

    my_list<ZeroMQClient*>::iterator it = list_socket.begin();
    while(it != list_socket.end()) {
        ZeroMQClient *client = *it;
        uint8_t sock_client = client->sock();

        if(mask_socket & (1 << sock_client)) {
            if(client->state() == statement::authorized) {
                sz_msg = client->send_pub(string, sz_string);
            }
        }
        it++;
    }
    return sz_msg;
}

void pub_t::drop_message(ZeroMQClient *&ptr_zmq_socket)
{
    while(ptr_zmq_socket->available())
        ptr_zmq_socket->read();
}
