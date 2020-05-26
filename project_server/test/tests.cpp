#include "gmock/gmock.h"

#include "EngineServer.h"
#include "SessionManager.h"
#include "IParser.h"
#include "IEngine.h"
#include "IUser.h"
#include "IGameEngine.h"

using ::testing::InSequence;

class MockClientSocket: public ClientSocket {
public:
    MockClientSocket(int socket, bool option = false): ClientSocket(socket, option){}
    MOCK_METHOD(int, Recieve, (std::string& msg));
    MOCK_METHOD(int, SendMsg, (const std::string& msg));
};

class MockUser: public User {
public:
    MockUser(std::shared_ptr<ClientSocket> sock): User(sock){}
};


TEST(GameTest, InsertMap) {
    std::shared_ptr<IGameEngine> GameEngine = std::make_shared<IGameEngine>();

    std::string coordinates = "0 0 0 3\n3 3 3 3\n4 0 5 0\n9 0 9 1\n6 3 6 3\n3 5 3 5\n8 4 8 4\n0 9 2 9\n5 6 6 6\n9 7 9 9\n";
    std::string coordinates2 = "0 0 0 3\n3 3 3 3\n4 1 5 1\n9 0 9 1\n2 6 2 6\n0 5 0 5\n8 4 8 4\n0 9 2 9\n5 6 6 6\n9 6 9 8\n";
    std::stringstream stream(coordinates);
    std::stringstream stream2(coordinates2);
    Map map;
    Map map2;

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

    for (int i = 0; i < 10; i++) {
        size_t x_s = 0;
        size_t y_s = 0;
        stream2 >> x_s >> y_s;
        size_t x_e = 0;
        size_t y_e = 0;
        stream2 >> x_e >> y_e;
        Ship ship(x_s, y_s, x_e, y_e);
        map2.ships.insert({i, ship});
    }

    EXPECT_TRUE(GameEngine->InsertMap(1, map));
    EXPECT_TRUE(GameEngine->InsertMap(2, map2));

    GameEngine->SetStep(1);
    std::shared_ptr<GameState> gs = std::make_shared<GameState>();

    std::shared_ptr<GameState> game = GameEngine->UpdateGame(1, {0, 0});
    EXPECT_EQ(1, game->next_step_id_);
    EXPECT_EQ(Result::Hit, game->result_);

    std::shared_ptr<GameState> g = GameEngine->UpdateGame(1, {1, 0});
    EXPECT_EQ(2, g->next_step_id_);
    EXPECT_EQ(Result::Miss, g->result_);

    g = GameEngine->UpdateGame(1, {2, 1});
    EXPECT_EQ(nullptr, g);

    g = GameEngine->UpdateGame(2, {3, 3});
    EXPECT_EQ(2, g->next_step_id_);
    EXPECT_EQ(Result::Kill, g->result_);

    g = GameEngine->UpdateGame(2, {3, 3});
    EXPECT_EQ(1, g->next_step_id_);
    EXPECT_EQ(Result::Miss, g->result_);
}

TEST(SessionManagerTest, CreateJoinSessionTest) {
    std::shared_ptr<ClientSocket> cl = std::make_shared<MockClientSocket>(5);
    std::shared_ptr<ClientSocket> cl1 = std::make_shared<MockClientSocket>(7);
    std::shared_ptr<ClientSocket> cl2 = std::make_shared<MockClientSocket>(6);
    std::shared_ptr<ClientSocket> cl3 = std::make_shared<MockClientSocket>(8);

    UserPtr user = std::make_shared<MockUser>(cl);
    UserPtr user1 = std::make_shared<MockUser>(cl1);
    UserPtr user2 = std::make_shared<MockUser>(cl2);
    UserPtr user3 = std::make_shared<MockUser>(cl3);

    SessionManager session_manager;

    EXPECT_TRUE(session_manager.CreateSession(user));
    EXPECT_EQ(Error::Success, session_manager.AddUserInSession(user2, 1));

    EXPECT_EQ(Error::Full, session_manager.AddUserInSession(user1, 1));
    EXPECT_EQ(Error::NotFound, session_manager.AddUserInSession(user1, 2));

    EXPECT_TRUE(session_manager.CreateSession(user1));
    EXPECT_EQ(Error::UserExist, session_manager.AddUserInSession(user1, 2));

    std::shared_ptr<EraseState> es = std::make_shared<EraseState>();
    EXPECT_EQ(es->winner_id_, session_manager.EraseUser(user, 1)->winner_id_);

    EXPECT_EQ(nullptr, session_manager.EraseUser(user, 3));

    EXPECT_EQ(Error::Success, session_manager.AddUserInSession(user3, 1));
}

TEST(MapTest, InsertPoints) {
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
    GameMap g_map;
    IGameEngine engine;
    std::shared_ptr<GameMap> gm = engine.ValidateMap(map);

    EXPECT_EQ(Result::Hit, gm->InsertPoint({0, 0}));
    EXPECT_EQ(Result::Kill, gm->InsertPoint({3, 3}));
    EXPECT_EQ(Result::Miss, gm->InsertPoint({2, 2}));
    EXPECT_EQ(9, gm->Count());

    EXPECT_EQ(Result::Miss, gm->InsertPoint({0, 0}));
}

TEST(ParserTest, SerializeDeserializeTest) {

}
