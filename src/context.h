#ifndef CONTEXT_H
#define CONTEXT_H
#include "socket_base.h"
#include "singleton.h"

#define PIN_INTERRUPT 2

namespace zmq {
    class context_t {
    public:
        context_t() {}
        void interruptStatus();
        void init();
    private:
        static void ethernet_ISR();
    };
}

#endif // CONTEXT_H
