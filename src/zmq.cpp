#include "zmq.h"

int compare_msg(const uint8_t *_msg1, const uint8_t *_msg2, size_t _sz)
{
    for(size_t i = 0; i < _sz; ++i) {
        if(_msg1[i] > _msg2[i])
            return -1;
        else if(_msg1[i] < _msg2[i])
            return 1;
    }

    return 0;
}

