#include "utils.h"

namespace utils
{
    Rnd::Rnd()
    : m_gen( m_rd() )
    {}

    float Rnd::getFloat( float from, float to )
    {
        std::uniform_real_distribution<> dis( from, to );
        return dis( m_gen ); 
    }

    int Rnd::getInt( int from, int to )
    {
        std::uniform_int_distribution<> dis( from, to );
        return dis( m_gen ); 
    }
}