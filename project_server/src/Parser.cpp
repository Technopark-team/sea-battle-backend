#include "Parser.h"


typeMsg Parser::parse_type(const std::string& request) {

    Request rq;
    msgpack::object_handle oh = msgpack::unpack(request.data(), request.size());
    msgpack::object obj = oh.get();
    obj.convert(rq);

    typeMsg type = rq.type_;

    if (type == typeMsg::CreateSession) {
        std::cout << rq.data_.login_ << " " << rq.data_.password_ << std::endl;
        return typeMsg::CreateSession;
    } else if (type == typeMsg::JoinSession) {
        return typeMsg::JoinSession;
    }
    return typeMsg::CreateUser;
}

std::string Parser::parseCreateUser(const std::string& message) {

    std::string str = "1";
    return str;
}

int Parser::parseCreateSession(const std::string& message) {
    return 1;
}

int Parser::parseJoinSession(const std::string& message) {
    std::istringstream is(message);
    std::string type;
    is >> type;
    int id = 0;
    is >> id;
    return id;
}

Map Parser::parseStartGame(const std::string& message) {


    return Map();
}

Point Parser::parseUpdateGame(const std::string& message) {

    return Point();
}

