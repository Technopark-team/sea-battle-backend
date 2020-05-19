#ifndef PROJECT_SERVER_PARSER_H
#define PROJECT_SERVER_PARSER_H

#include "IParser.h"
#include "Session.h"

class Parser : public IParser {
public:
    Parser():IParser(){}
    std::shared_ptr<Request> Deserialize(const std::string& request) override;
    void Serialize(std::shared_ptr<Response> rp, std::string& response) override;
};

#endif //PROJECT_SERVER_PARSER_H
