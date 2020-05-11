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

    virtual size_t PostSignup() { return 0; };
    virtual size_t PostSignin() { return 0; };
    virtual size_t PostGameSingle() { return 0; };
    virtual size_t PostGameMulti() { return 0; };
    virtual size_t PutGameSave() { return 0; };
    virtual size_t GetGameOpen() { return 0; };
    virtual size_t PostGameStep() { return 0; };
    virtual size_t GetGameState() { return 0; };
    virtual size_t PutGameStop() { return 0; };

 private:
    virtual size_t GeneralCallback_(std::string response) = 0;
};

}  // namespace model
}  // namespace client
}  // namespace seabattle

#endif  // SEA_BATTLE_BACKEND_MODEL_INTEFACE_H
