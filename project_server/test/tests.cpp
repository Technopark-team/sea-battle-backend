#include "gmock/gmock.h"

#include "EngineServer.h"
#include "SessionManager.h"
#include "IParser.h"
#include "IEngine.h"
#include "IUser.h"

using ::testing::InSequence;

class MockUser: public User {
public:
    MockUser(std::string nick, int sock): User(std::move(nick), sock){}
    MOCK_METHOD(int, send_message, (std::string message), (override));
    MOCK_METHOD(int, recieve_message, (std::string message), (override));
};

class MockSession: public Session {
public:
    MockSession(UserPtr user, size_t id): Session(user, id) {}
    MOCK_METHOD(int, update, ());
    MOCK_METHOD(int, update_game_state, ());
    MOCK_METHOD(int, recieve_from_player, (std::string message));
    MOCK_METHOD(int, notify_users, ());
};


class MockSessionManager: public SessionManager {
public:
    MockSessionManager(): SessionManager() {}
    MOCK_METHOD(bool, create_session,(UserPtr user, size_t id));
    MOCK_METHOD(int, update_with_user_id, (size_t user_id, std::string message));
    MOCK_METHOD(int, update_sessions,());
    MOCK_METHOD(int, delete_session,());
    MOCK_METHOD(bool, add_user_in_session, (size_t session_id, UserPtr user));
};



TEST(ParserTypeTest, CreateSessionTest) {
    Parser parser;
    EXPECT_EQ(typeMsg::CreateSession, parser.parse_type("type:create"));
}

TEST(ParserTypeTest, JoinSessionTest) {
    Parser parser;
    EXPECT_EQ(typeMsg::JoinSession, parser.parse_type("type:join"));
}

TEST(ParserTypeTest, UpdateGameTest) {
    Parser parser;
    EXPECT_EQ(typeMsg::UpdateGame, parser.parse_type("type:update"));
}

TEST(ParserTypeTest, InvalidTypeTest) {
    Parser parser;
    EXPECT_EQ(typeMsg::InvalidType, parser.parse_type("type:destroy"));
}

TEST(ParserTypeTest, NoTypeTest) {
    Parser parser;
    EXPECT_EQ(typeMsg::NoType, parser.parse_type("tye:join"));
}

TEST(ParserArgumentsTest, GameStateArguments) {

}

TEST(ParserArgumentsTest, InvalidGameStateArguments) {

}

TEST(SessionManagerTest, CreateSessionTest) {
    UserPtr user = std::make_shared<MockUser>("nick", 1);
    SessionManager session_manager;

    EXPECT_TRUE(session_manager.create_session(user, 1));

    EXPECT_FALSE(session_manager.create_session(user, 1));
}

TEST(SessionManagerTest, AddInSessionTest) {
    SessionManager session_manager;

    UserPtr user1 = std::make_shared<MockUser>("nick", 1);

    session_manager.create_session(user1, 1);

    EXPECT_FALSE(session_manager.add_user_in_session(user1, 1));
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
    std::shared_ptr<MockSessionManager> session_manager = std::make_shared<MockSessionManager>();

    EXPECT_CALL(*session_manager, add_user_in_session(1, user1)).Times(1);

    EngineServer server("127.0.0.1", "5555", 1, session_manager);
    std::string message = "type:join";
    EXPECT_EQ(JoinSession, server.switch_action(message, user1));
}

TEST(EngineServerTest, UpdateActionTest) {
    UserPtr user1 = std::make_shared<MockUser>("nick", 1);
    std::shared_ptr<MockSessionManager> session_manager = std::make_shared<MockSessionManager>();
    std::string message = "type:update";

    EXPECT_CALL(*session_manager, update_with_user_id(user1->get_id(), message)).Times(1);

    EngineServer server("127.0.0.1", "5555", 1, session_manager);

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
    EXPECT_CALL(*user1, recieve_message("message")).Times(1);
    EXPECT_CALL(*user2, recieve_message("message")).Times(1);
    
    Session session(user1, 1);
    ASSERT_TRUE(session.add_user_in_session(user2));
    
    EXPECT_EQ(2, session.notify_users());
}