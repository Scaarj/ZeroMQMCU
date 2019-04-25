#include "options.h"


zmq::options_t::options_t(option_type _type, const char *_optval, size_t _optvallen) :
    m_type(_type), m_optvallen(_optvallen)

{
    unsigned char full_size = m_optvallen + 1;
    m_optval = new char[full_size];
    for(size_t i = 0; i < _optvallen; ++i)
        m_optval[i] = _optval[i];
    m_optval[full_size - 1] = 0;
}

size_t zmq::options_t::optvallen() const
{
    return m_optvallen;
}

char *zmq::options_t::optval() const
{
    return m_optval;
}

option_type zmq::options_t::type() const
{
    return m_type;
}
