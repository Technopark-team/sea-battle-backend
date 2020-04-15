#ifndef PROJECT_SERVER_IPARSER_H
#define PROJECT_SERVER_IPARSER_H

#include <string>

class IParser {
public:
    IParser():  buffer("") {}
    virtual int parse_type(const std::string& request) = 0;
private:
    std::string buffer;
};

#endif //PROJECT_SERVER_IPARSER_H
