#include "context.h"

void zmq::context_t::interruptStatus()
{
    delay(5);
    Serial.print("SIR: ");
    Serial.println(w5500.readSIR());

    delay(5);
    Serial.print("SIMR: ");
    Serial.println(w5500.readSIMR());

    delay(5);
    Serial.print("SnIR: ");
    for(int i = 0; i < 8; ++i) {
        Serial.print(w5500.readSnIR(i));
        Serial.print("/");
    }
    Serial.println();

    delay(5);
    Serial.print("SnIMR: ");
    for(int i = 0; i < 8; ++i) {
        Serial.print(w5500.readSnIMR(i));
        Serial.print("/");
    }
    Serial.println();
}

void zmq::context_t::init()
{
    uint16_t interval = 255;
    w5500.writeINTLEVEL(interval);
/*
    // Mask for connect interrupts
    for(int i = 0; i < 8; ++i) {
        w5500.writeSnIMR(i, 0x04);
        w5500.writeSnIR(i, 0xFF);
    }

    w5500.writeSIMR(0xFF);

    pinMode(PIN_INTERRUPT, INPUT);
    digitalWrite(PIN_INTERRUPT, HIGH);
    attachInterrupt(0, ethernet_ISR, LOW);*/
}

void zmq::context_t::ethernet_ISR()
{
    uint8_t socket = w5500.readSIR();
    uint8_t socket_index = 0;
    while(!(socket & (1 << socket_index))) {
        socket_index++;
    }

    uint8_t _SnIR = w5500.readSnIR(socket_index);

    uint8_t interrupt_num = 0;
    while(!(_SnIR & (1 << interrupt_num))) {
        interrupt_num++;
    }

    w5500.writeSnIR(socket_index, 1 << interrupt_num);
    /*
    uint8_t socket = w5500.readSIR();
    uint8_t socket_index = 0;
    while(!(socket & (1 << socket_index))) {
        socket_index++;
    }

    uint8_t _SnIR = w5500.readSnIR(socket_index);

    for(int i = 0; i < 8; ++i) {

    }

    uint8_t interrupt_num = 0;
    while(!(_SnIR & (1 << interrupt_num))) {
        interrupt_num++;
    }

    Serial.println(socket_index);


    socket_base_t* ptr_socket = nullptr;
    ZeroMQClient* ptr_zmq_socket = nullptr;
    bool zmq_founded = false;

    for(unsigned int i = 0; i < SOCKET_LIST.size(); ++i) {
        ptr_socket = SOCKET_LIST.at(i);

        if(ptr_socket->type() != socket_type::ZMQ_PUB &&
                ptr_socket->type() != socket_type::ZMQ_REP)
            continue;

        for(unsigned int j = 0; j < ptr_socket->socket_list().size(); ++j) {
            if(ptr_socket->socket_list().at(j)->sock() == socket_index) {
                ptr_zmq_socket = ptr_socket->socket_list().at(j);
                zmq_founded = true;
                break;
            }
        }

        if(zmq_founded)
            break;
    }

    if(ptr_socket == nullptr || ptr_zmq_socket == nullptr) {
        w5500.writeSnIR(socket_index, 1 << interrupt_num);
        return;
    }


    switch (interrupt_num) {
    case 0:
        // Connect pub/rep/sub socket
        ptr_socket->connect(ptr_zmq_socket);
        break;
    case 1:
        // Disconnect pub/rep/sub socket
        ptr_socket->disconnect(ptr_zmq_socket);
        break;
    case 2:
        // Message recieve
        ptr_socket->recv(ptr_zmq_socket);
        break;
    case 3:
        // Connection timeout
        ptr_socket->disconnect(ptr_zmq_socket);
        break;
    case 4:
        // Message send ok (TCP) Not used
        break;
    default:
        // unreachable case
        break;
    }

    w5500.writeSnIR(socket_index, 1 << interrupt_num);*/
}

