#ifndef SEABATTLE_UI_INTERFACE_H
#define SEABATTLE_UI_INTERFACE_H

#include <cstddef>
#include <string>

namespace seabattle {
namespace client {
namespace view {

class IUserInput {
 public:
    virtual ~IUserInput() = default;

 private:
    virtual size_t ReadCommand(config::UserCommand &user_command) = 0;
};

}
}
}

#endif  // SEABATTLE_UI_INTERFACE_H
