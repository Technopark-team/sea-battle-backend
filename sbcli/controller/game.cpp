#include "game.h"

namespace seabattle {
namespace client {
namespace controller {

GameController::GameController(std::shared_ptr<network::TCPClient>& network_client)
    : game_model_(new model::GameModel(network_client)),
      game_console_interface_(new view::GameConsoleInput()) {}

size_t GameController::Action(std::shared_ptr<config::ControllerSignal>& controller_signal) {
    /*
     * вызов авторизации с зашитыми даныыми
     * сохранение поуученного идентификатора в модель
     * вызов createsession для этого идентификатора
     *
     * запусттть другую консоль
     * вызов авторизации с другими зашитыми даныыми
     * сохранение нвоого полученного идентификатора в модель
     * вызов joinsession для этого идентификатора оользоаателя (!!!)
     * сервер должен включить гго к первому
     *
     * для второго идентификатора вызов creategame
     * для первого вызов creategame
     *
     * 1 конструктор моедии
     * 2 дефолтные значения updategame
     * 3 подумать над тестированием последовательности выше
     *
     */

    config::UserCommand command = std::move(controller_signal->command);
    config::Controller signal = std::move(controller_signal->signal);
    controller_signal->Clean();

    utils::data::TestMap player_map;
    config::UserCommandId exit;
    game_model_->SetUserId(controller_signal->user_id);

//    std::cout << "create or join " << std::endl;
//    //    CREATE or JOIN
    if (command.command == config::UserCommandId::MULTI_COMMAND_START) {
//        std::cout << "CreateSession" << std::endl;
        game_model_->CreateSession();
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    } else {
//        std::cout << "JoinSession" << std::endl;
        game_model_->JoinSession();
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }

    int user_id;
    game_model_->GetUserId(user_id);
    int session_id;
    game_model_->GetSessionId(session_id);

    std::cout << "=== Need Read Game" << std::endl;

    game_console_interface_->ReadMap(player_map, exit);
    std::cout << "=== Read Map" << std::endl;

    game_model_->SetUserMap(player_map);

    std::cout << "=== Need Start Game" << std::endl;

    game_model_->StartGame();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));


//    std::cout << "StartGame, user_id: " << user_id << std::endl;
//    std::cout << "StartGame, session_id: " << session_id << std::endl;
    //

//    int wait;
//    std::cout << "wait ";
//    std::cin >> wait;



//    game_model_->UpdateGame();
//    std::cout << "UpdateGame" << std::endl;
//    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    //
    utils::data::TestPoint enemy_point;
    utils::data::TestGameState game_state;
    utils::data::TestEraseState erase_state;
    //    game_model_->GetEnemyCurrentStep(enemy_point);
        game_model_->GetGameState(game_state);
    //

    utils::data::TestPoint player_point;
    config::UserCommandId map_exit;
    config::UserCommandId end_game;

    game_console_interface_->ReadMap(player_map, map_exit);
    //    game_console_interface_->ReadStep(player_point, step_exit);

    std::cout << "=== StartedGame" << std::endl;

    do {
        std::cout << "=== Started do-while" << std::endl;

        while ((game_state.next_step_id_ != user_id) && (!game_state.end_game_)) {
            std::cout << "=== Update enemy" << std::endl;
            game_model_->UpdateGame();
            game_model_->GetGameState(game_state);
            game_model_->GetEnemyCurrentStep(enemy_point);
            game_model_->GetEraseState(erase_state);
            game_console_interface_->WriteEnemyState(enemy_point, game_state, erase_state);
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }
        std::cout << "=== Update need ReadStep" << std::endl;

        game_console_interface_->ReadStep(player_point, end_game);

        std::cout << "=== Update made ReadStep, need update" << std::endl;

        game_model_->SetCurrentStep(player_point);
        game_model_->UpdateGame();
        std::cout << "=== Update Game user1" << std::endl;

//        std::cout << "enemy's step: " << enemy_point.x_ << ", " << enemy_point.y_ << std::endl;
//        std::cout << "enemy's step status: " << static_cast<int>(game_state.result_)
//                  << ", end: " << game_state.end_game_ << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    } while (!game_state.end_game_);

    //    size_t command = -1;
    //    game_console_interface_->Run(command);

    controller_signal->signal = config::Controller::NONE;
    return 0;
}
}  // namespace controller
}  // namespace client
}  // namespace seabattle