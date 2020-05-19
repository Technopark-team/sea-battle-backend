#include "Parser.h"

std::shared_ptr<Request> Parser::Deserialize(const std::string& request) {
    std::shared_ptr<Request> rq = std::make_shared<Request>();
    msgpack::object_handle oh = msgpack::unpack(request.data(), request.size());
    msgpack::object obj = oh.get();
    obj.convert(*rq);
    return rq;
}

void Parser::Serialize(std::shared_ptr<Response> rp, std::string& response) {
    std::stringstream stream;
    msgpack::pack(stream, *rp);
    response = stream.str();
}
