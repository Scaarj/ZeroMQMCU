#ifndef OPTION_H
#define OPTION_H
#include "zmq.h"

enum option_type {
    ZMQ_EMPTY = 0,
    ZMQ_SUBSCRIBE,
    ZMQ_UNSUBSCRIBE
};

namespace zmq {
    class options_t
    {
    public:
        options_t() {}
        ~options_t()
        {
            memset(m_optval, 0, m_optvallen);
            delete [] m_optval;
            m_optval = NULL;
        }
        options_t(option_type _type, const char *_optval, size_t _optvallen);
        bool operator==(const options_t &second) {
            size_t index = 0;

            if(m_optvallen == 0 && second.m_optvallen == 0)
                return true;

            while(index < m_optvallen && index < second.optvallen()) {
                if((m_optval + index) != (second.m_optval + index))
                    return false;
            }
            return true;
        }

        option_type type() const;
        char *optval() const;
        size_t optvallen() const;
    private:
        option_type m_type;
        char *m_optval;
        size_t m_optvallen;
    };
}


#endif // OPTION_H
