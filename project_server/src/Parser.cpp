#include "Parser.h"


typeMsg Parser::parse_type(const std::string &request) {
    return typeMsg::CreateSession;
}

std::string Parser::parseCreateUser(const std::string& message) {

    std::string str = "1";
    return str;
}

int Parser::parseCreateSession(const std::string& message) {
    return 1;
}

int Parser::parseJoinSession(const std::string& message) {
    return 1;
}

Map Parser::parseStartGame(const std::string &message) {



    return Map();
}

Point Parser::parseUpdateGame(const std::string &message) {



    return Point();
}

