#pragma once

#include <string>
#include <map>

namespace mgo {
namespace config {

class Reader{
public:
    Reader(const std::string& sConfigFileName);
    ~Reader(){}
    std::string read(
        const std::string& key,
        const std::string& defaultValue = ""
        ) const;
    unsigned long readLong(
        const std::string& key,
        const unsigned long defaultValue = 0
        ) const;
    unsigned long readLong(
        const std::string& key,
        const std::string& defaultValue = "0"
        ) const;
    bool readBool(
        const std::string& key,
        const bool defaultValue
        ) const;
    float readFloat(
        const std::string& key,
        const float defaultValue
        ) const;

    std::string operator[](const std::string& key) const;
private:
    std::map<std::string, std::string> m_map;
};

} // namespace Config
} // namespace mgo
