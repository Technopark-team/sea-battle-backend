#ifndef PROJECT_SERVER_PARSER_H
#define PROJECT_SERVER_PARSER_H


#include "IParser.h"

class Parser : public IParser {
public:
    Parser():IParser(){}
    typeMsg parse_type(const std::string& request) override;

};

#endif //PROJECT_SERVER_PARSER_H
