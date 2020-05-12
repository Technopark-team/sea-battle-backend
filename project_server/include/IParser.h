#ifndef PROJECT_SERVER_IPARSER_H
#define PROJECT_SERVER_IPARSER_H

#include <string>
#include <sstream>

enum class typeMsg {
    CreateSession = 1,
    UpdateGame,
    JoinSession,
    StartGame,
    CreateUser,
    EndGame
};

enum class errorType {
    InvalidType = -1,
    NoType = -2
};

class IParser {
public:
    IParser():  buffer("") {}
    virtual ~IParser() = default;
    virtual typeMsg parse_type(const std::string& request) = 0;
private:
    std::string buffer;
};

#endif //PROJECT_SERVER_IPARSER_H
