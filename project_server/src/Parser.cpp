#include "Parser.h"

std::shared_ptr<DataRequest> Parser::Deserialize(const std::string& request) {
    std::shared_ptr<DataRequest> rq = std::make_shared<DataRequest>();
    msgpack::object_handle oh = msgpack::unpack(request.data(), request.size());
    msgpack::object obj = oh.get();
    obj.convert(*rq);
    return rq;
}

void Parser::Serialize(std::shared_ptr<DataResponse> rp, std::string& response) {
    std::stringstream stream;
    msgpack::pack(stream, *rp);
    response = stream.str();
}
