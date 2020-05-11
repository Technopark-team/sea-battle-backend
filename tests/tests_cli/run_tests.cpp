#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "controller/test_auth_mock.h"

namespace seabattle {
namespace client {
namespace test {

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}  // namespace test
}  // namespace client
}  // namespace seabattle
