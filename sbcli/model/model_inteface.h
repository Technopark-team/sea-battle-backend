#ifndef SEA_BATTLE_BACKEND_MODEL_INTEFACE_H
#define SEA_BATTLE_BACKEND_MODEL_INTEFACE_H

#include <cstddef>
#include <string>

namespace seabattle {
namespace client {
namespace model {

// TODO: переписать интерфейс
class IModel {
 public:
    virtual ~IModel() = default;

    virtual size_t CreateUser() { return 0; };
    virtual size_t CreateSession() { return 0; };
    virtual size_t UpdateGame() { return 0; };
    virtual size_t JoinSession() { return 0; };
    virtual size_t StartGame() { return 0; };
    virtual size_t Enter() { return 0; };
    virtual size_t EndGame() { return 0; };


 private:
    virtual size_t GeneralCallback_(std::stringstream& response) = 0;
};

}  // namespace model
}  // namespace client
}  // namespace seabattle

#endif  // SEA_BATTLE_BACKEND_MODEL_INTEFACE_H
