#ifndef PROJECT_SERVER_IPARSER_H
#define PROJECT_SERVER_IPARSER_H

#include <string>
#include <sstream>

#include "Data.h"


class IParser {
public:
    IParser():  buffer("") {}
    virtual ~IParser() = default;
    virtual typeMsg parse_type(const std::string& request) = 0;
private:
    std::string buffer;
};

#endif //PROJECT_SERVER_IPARSER_H
