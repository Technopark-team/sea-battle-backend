#ifndef PROJECT_SERVER_PARSER_H
#define PROJECT_SERVER_PARSER_H


#include "IParser.h"
#include "Session.h"

class Parser : public IParser {
public:
    Parser():IParser(){}
    typeMsg parse_type(const std::string& request) override;

    std::string parseCreateUser(const std::string& message);
    int parseCreateSession(const std::string& message);
    int parseJoinSession(const std::string& message);

    Map parseStartGame(const std::string& message);
    Point parseUpdateGame(const std::string& message);
};

#endif //PROJECT_SERVER_PARSER_H
