#include "gmock/gmock.h"

#include "EngineServer.h"
#include "SessionManager.h"
#include "IParser.h"
#include "IEngine.h"
#include "IUser.h"
#include "IGameEngine.h"

using ::testing::InSequence;

int mockFunction(const std::string& str, std::shared_ptr<User>) {
    return 0;
}


/*class MockUser: public User {
public:
    MockUser(int sock): User(std::move(nick), sock){}
    MOCK_METHOD(void, write, (const std::string& message), (override));
    MOCK_METHOD(void, recieve_message, (std::string message), (override));
};*/

class MockClientSocket: public ClientSocket {
public:
    MockClientSocket(int socket, bool option = false): ClientSocket(socket, option){}
    MOCK_METHOD(int, receive, (std::string& msg));
    MOCK_METHOD(int, send_msg, (const std::string& msg));
};

/*class MockSession: public Session {
public:
    MockSession(UserPtr user, size_t id): Session(user, id) {}
    MOCK_METHOD(int, update, ());
    MOCK_METHOD(int, update_game_state, ());
    MOCK_METHOD(int, recieve_from_player, (std::string message));
    MOCK_METHOD(int, notify_users, ());
};*/


/*class MockSessionManager: public SessionManager {
public:
    MockSessionManager(): SessionManager() {}
    MOCK_METHOD(bool, create_session,(UserPtr user, size_t id));
    MOCK_METHOD(int, update_with_user_id, (size_t user_id, std::string message));
    MOCK_METHOD(int, update_sessions,());
    MOCK_METHOD(int, delete_session,());
    MOCK_METHOD(bool, add_user_in_session, (size_t session_id, UserPtr user));
};*/


TEST(GameTest, InsertMap) {
    IGameEngine GameEngine;
    std::string coordinates = "0 0 0 3\n3 3 3 3\n4 0 5 0\n9 0 9 1\n6 3 6 3\n3 5 3 5\n8 4 8 4\n0 9 2 9\n5 6 6 6\n9 7 9 9\n";
    std::stringstream stream(coordinates);
    Map map;

    for (int i = 0; i < 10; i++) {
        size_t x_s = 0;
        size_t y_s = 0;
        stream >> x_s >> y_s;
        size_t x_e = 0;
        size_t y_e = 0;
        stream >> x_e >> y_e;
        Ship ship(x_s, y_s, x_e, y_e);
        map.ships.insert({i, ship});
    }
    EXPECT_TRUE(GameEngine.insertMap(1, map));
}

TEST(SessionManagerTest, CreateSessionTest) {
    std::shared_ptr<ClientSocket> cl = std::make_shared<MockClientSocket>(5);

    //UserPtr user = std::make_shared<User>(cl);
    SessionManager session_manager;

    //EXPECT_TRUE(session_manager.create_session(user));
}

/*TEST(SessionManagerTest, AddInSessionTest) {
    SessionManager session_manager;

    UserPtr user1 = std::make_shared<MockUser>("nick", 1);

    session_manager.create_session(user1, 1);

    EXPECT_EQ(session_manager.add_user_in_session(user1, 1), error::UserExist);
    UserPtr user2 = std::make_shared<MockUser>("nick2", 2);
    EXPECT_TRUE(session_manager.add_user_in_session(user2, 1));
}


TEST(EngineServerTest, CreateActionTest) {
    UserPtr user1 = std::make_shared<MockUser>("nick", 1);
    std::shared_ptr<MockSessionManager> session_manager = std::make_shared<MockSessionManager>();
    EXPECT_CALL(*session_manager, create_session(user1, 1)).Times(1);

    EngineServer server("127.0.0.1", 5555);
    std::string message = "type:create";
    EXPECT_EQ(CreateSession, server.switch_action(message, user1));
}

TEST(EngineServerTest, JoinActionTest) {
    UserPtr user1 = std::make_shared<MockUser>("nick", 1);
    SessionManager sessionManager;

    EXPECT_CALL(sessionManager, add_user_in_session(user1, 1)).Times(1);

    EngineServer server("127.0.0.1", 5555);
    std::string message = "type:join";
    EXPECT_EQ(typeMsg::JoinSession, server.switch_action(message, user1));
}

TEST(EngineServerTest, UpdateActionTest) {
    UserPtr user1 = std::make_shared<MockUser>("nick", 1);
    std::shared_ptr<MockSessionManager> session_manager = std::make_shared<MockSessionManager>();
    std::string message = "type:update";

    EXPECT_CALL(*session_manager, update_with_user_id(user1->get_id(), message)).Times(1);

    EngineServer server("127.0.0.1", 5555);

    EXPECT_EQ(UpdateGame, server.switch_action(message, user1));
}

TEST(EngineTest, EngineEventTest) {
    UserPtr user1 = std::make_shared<MockUser>("nick", 1);
    UserPtr user2 = std::make_shared<MockUser>("nick1", 2);
    UserPtr user3 = std::make_shared<MockUser>("nick1", 3);
    std::vector<UserPtr>all_users = {user1, user2, user3};
    std::vector<UserPtr>users_with_events;
    Engine engine;

    EXPECT_EQ(3, engine.get_users_with_events(users_with_events, all_users));

    EXPECT_THAT(all_users, users_with_events);
}

TEST(SessionTest, NotifyTest) {
    std::shared_ptr<MockUser> user1 = std::make_shared<MockUser>("nick", 1);
    std::shared_ptr<MockUser> user2 = std::make_shared<MockUser>("nick1", 2);
    EXPECT_CALL(*user1, write("message")).Times(1);
    EXPECT_CALL(*user2, write("message")).Times(1);
    
    Session session(user1, 1);
    ASSERT_TRUE(session.add_user_in_session(user2));
    
    EXPECT_EQ(2, session.notifyUsers());
}*/
