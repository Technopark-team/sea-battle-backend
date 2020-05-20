#ifndef SEABATTLE_CONTROLLER_INTERFACE_H
#define SEABATTLE_CONTROLLER_INTERFACE_H

#include <cstddef>
#include <string>
#include "sbcli/config/config.h"

namespace seabattle {
namespace client {
namespace controller {

class IController {
 public:
    virtual ~IController() = default;

 private:
    virtual size_t Action(std::shared_ptr<config::ControllerSignal> &controller_signal) = 0;
};

}  // namespace controller
}  // namespace client
}  // namespace seabattle

#endif  // SEABATTLE_CONTROLLER_INTERFACE_H
