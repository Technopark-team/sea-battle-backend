#ifndef PROJECT_SERVER_PARSER_H
#define PROJECT_SERVER_PARSER_H


#include "IParser.h"
enum type_msg {
    NewPlayer = 1,
    CreateSession,
    UpdateGame,
    JoinSession
};

enum error_type {
    InvalidType = -1,
    NoType = -2
};
class Parser : public IParser {
public:
    Parser():IParser(){}
   int parse_type(const std::string& request) override;
};

#endif //PROJECT_SERVER_PARSER_H
