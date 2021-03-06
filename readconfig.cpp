#include "readconfig.h"
#include "boost/algorithm/string.hpp"

#include <cstddef>
#include <fstream>

namespace mgo {
namespace config {

Reader::Reader( const std::string& cfgfile )
{
    // Open the config file
    std::ifstream ifs;
    ifs.open( cfgfile.c_str(), std::ios::in );
    if ( !ifs )
    {
        throw std::runtime_error( "Could not open " + cfgfile );
    }
    std::string line;
    std::size_t n;
    while ( getline( ifs, line ) )
    {
        boost::trim( line );
        if ( line != "" && line[ 0 ] != '#' )
        {
            n = line.find( "=" );
            if ( n > 0 )
            {
                std::string key = line.substr( 0, n );
                boost::trim( key );
                boost::to_upper( key );
                std::string value = line.substr( n + 1 );
                boost::trim( value );
                m_map[ key ] = value;
            }
        }
    }
    ifs.close();
}

std::string Reader::read(
    const std::string& key,
    const std::string& defaultValue
    ) const
{
    std::string upperKey = key;
    std::string value;
    boost::trim( upperKey );
    boost::to_upper( upperKey );
    auto it = m_map.find( upperKey );
    if ( it == m_map.end() )
    {
        value = defaultValue;
    }
    else
    {
        value = it->second;
        if ( value.empty() )
            value = defaultValue;
    }
    // Finally - if the value contains the string ${...} then we
    // should substitute its contents for another variable from the
    // config file.
    std::size_t pos;
    while ( ( pos = value.find( "${" ) ) != std::string::npos )
    {
        std::size_t endPos = value.find( "}", pos );
        if ( endPos == std::string::npos )
        {
            break; // no terminating brace so return string as is
        }
        std::string key = value.substr( pos + 2, ( endPos - pos ) - 2 );
        value = value.substr( 0, pos ) + read( key, "" ) +
                value.substr( endPos + 1 );
    }
    return value;
}

unsigned long Reader::readLong(
    const std::string& key,
    const unsigned long defaultValue
    ) const
{
    return std::stoul( read( key, std::to_string( defaultValue ) ) );
}

unsigned long Reader::readLong(
    const std::string& key,
    const std::string& defaultValue
    ) const
{
    return std::stoul( read( key, defaultValue ) );
}

std::string Reader::operator[]( const std::string& key ) const
{
    return read( key );
}

bool Reader::readBool(
    const std::string& key,
    const bool defaultBoolValue
    ) const
{
    std::string defaultValue;
    if ( defaultBoolValue == true )
    {
        defaultValue = "Y";
    }
    else
    {
        defaultValue = "N";
    }
    std::string value = read( key, defaultValue );
    boost::to_upper( value );
    if ( value[ 0 ] == 'Y' || value[ 0 ] == 'T' )
    {
        return true;
    }
    else
    {
        return false;
    }
}

float Reader::readFloat(
    const std::string & key,
    const float defaultValue
    ) const
{
    try
    {
        return std::stof( read( key, std::to_string( defaultValue ) ) );
    }
    catch( ... )
    {
        return defaultValue;
    }
}

} // namespace config
} // namespace mgo
