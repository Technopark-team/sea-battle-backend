#include <iostream>
#include "EngineServer.h"

int main() {
    EngineServer eng("127.0.0.1", 2000);
    eng.run();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}