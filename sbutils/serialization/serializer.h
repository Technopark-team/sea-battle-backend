#ifndef SEA_BATTLE_BACKEND_SERIALIZER_H
#define SEA_BATTLE_BACKEND_SERIALIZER_H

#include <memory>
#include <sstream>
#include "sbutils/data/data.h"

namespace seabattle {
namespace utils {
namespace serializer {

template <class T>
class Serializer {
 public:
    explicit Serializer();
    ~Serializer() = default;

    static std::shared_ptr<std::stringstream> Serialize(T& data);

    static std::shared_ptr<T> Deserialize(std::stringstream& stream, size_t bytes);
};

template <class T>
Serializer<T>::Serializer() {}

template <class T>
std::shared_ptr<std::stringstream> Serializer<T>::Serialize(T& data) {
    std::shared_ptr<std::stringstream> ss = std::make_shared<std::stringstream>();
    msgpack::pack(*ss, data);
    return ss;
}

template <class T>
std::shared_ptr<T> Serializer<T>::Deserialize(std::stringstream& stream, size_t bytes) {
    std::shared_ptr<T> data = std::make_shared<T>();
    msgpack::object_handle oh = msgpack::unpack(stream.str().data(), bytes);
    msgpack::object obj = oh.get();
    obj.convert(*data);
    return data;
}

}  // namespace serializer
}  // namespace utils
}  // namespace seabattle

#endif  // SEA_BATTLE_BACKEND_SERIALIZER_H
