#include "Parser.h"
#include <iostream>

typeMsg Parser::parse_type(const std::string& request) {
    std::istringstream is(request);
    std::string type;
    is >> type;
    if (type == "cs") {
        return typeMsg::CreateSession;
    } else if (type == "js") {
        return typeMsg::JoinSession;
    }

    return typeMsg::CreateUser;
}

std::string Parser::parseCreateUser(const std::string& message) {

    std::string str = "1";
    return str;
}

int Parser::parseCreateSession(const std::string& message) {

    std::istringstream is(message);
    std::string type;
    is >> type;
    int id = 0;
    is >> id;

    return id;
}

int Parser::parseJoinSession(const std::string& message) {
    std::istringstream is(message);
    std::string type;
    is >> type;
    int id = 0;
    is >> id;
    std::cout << id << std::endl;
    return id;
}

Map Parser::parseStartGame(const std::string &message) {



    return Map();
}

Point Parser::parseUpdateGame(const std::string &message) {



    return Point();
}

