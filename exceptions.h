#pragma once

#include <stdexcept>

namespace mgo {

class XtardaGeneralException: public std::runtime_error
{
public:
    explicit XtardaGeneralException( const std::string& message )
    : std::runtime_error(message)
    {}
};

class XtardaFileException: public std::runtime_error
{
public:
    explicit XtardaFileException( const std::string& message )
    : std::runtime_error(message)
    {}
};

} // namespace mgo