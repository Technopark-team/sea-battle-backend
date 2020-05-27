#ifndef SEABATTLE_SBCLI_CONFIG_VIEW_H_
#define SEABATTLE_SBCLI_CONFIG_VIEW_H_

#include <string>

namespace seabattle {
namespace client {
namespace config {

struct HelpMainMenu {
//    const char *help_message = "Используй стрелки для навигации, а клавишу ENTER для выбора";
    const char *help_message = "Use narrows for navigation, press ENTER to select";
};

struct HelpAuthMenu {
    const char *help_message = "Use narrows for navigation, press ENTER to select";
//    const char *help_message = "Используй стрелки для навигации, а клавишу ENTER для выбора";
};

struct MenuExistUser {
//    const char *menu_name = "Главное меню";
//    const char *hello_message = "Привет, ";
    const char *menu_name = "Main menu";
    const char *hello_message = "Hi, ";const int len = 2;
//    const int len = 5;
    const char items[2][100] = {"Multiplayer", "Exit"};
//    const char items[2][100] = {"Многопользовательская игра", "Закрыть игру"};
//    const char items[5][100] = {"Одиночная игра", "Загрузить игру", "Многопользовательская игра",
//                                "Выход из аккаунта", "Закрыть игру"};
};

struct MenuNonExistUser {
//    const char *menu_name = "Главное меню";
//    const char *hello_message = "Здравствуй, игрок! Укажи, кто ты!";
    const char *menu_name = "Main menu";
    const char *hello_message = "Hi! Tell me, who you are!";
    const int len = 3;
//    const char items[3][100]{"Авторизация", "Регистрация", "Закрыть игру"};
    const char items[3][100]{"Sign in", "Sign up", "Exit"};
};

struct AuthExistUser {
//    const char *menu_name = "Меню авторизации";
    const char *menu_name = "Authorization menu";
    const int len = 2;
//    const char items[2][100] = {"Выход", "В меню"};
    const char items[2][100] = {"Exit the game", "Exit to Main menu"};
};

struct AuthNonExistUser {
//    const char *menu_name = "Меню авторизации";
    const char *menu_name = "Authorization menu";
    const int len = 2;
//    const char items[2][100] = {"Ввод данных", "В меню"};
    const char items[2][100] = {"Input data", "Exit to Main menu"};
};

struct GameExitHelp {
    const int len = 2;
//    const char items[2][100] = {"Для выхода в меню нажмите Q", "Для завершения игры нажмите Q"};
    const char items[2][100] = {"Press Q to exit to Main menu", "Press Q to exit the game"};
};

struct GameMoveHelp {
    const int len = 3;
//    const char items[3][10000] = {
//        "Для выбора корабля из списка используйте клавиши ВВЕРХ/ВНИЗ/ПРОБЕЛ",
//        "Для выбора клетки для установки корабля используйте клавиши "
//        "ВВЕРХ/ВНИЗ/ВЛЕВО/ВПРАВО/ПРОБЕЛ или ESC для возвращения к выбору корабля из списка",
//        "Для выбора положения корабля на поле используйте клавиши ВВЕРХ/ВНИЗ/ВЛЕВО/ВПРАВО/ПРОБЕЛ "
//        "или ESC для возвращения к выбору корабля из списка"};
    const char items[3][10000] = {
        "Press UP/DOWN/SPACE to choose ship in list ",
        "In order to choose cells to set ship press "
        "UP/DOWN/LEFT/RIGHT/SPACE or ESC to return to select a ship from the list",
        "To select the position of the ship on the field press  UP/DOWN/LEFT/RIGHT/SPACE "
        "or ESC to return to select a ship from the list"};
};

}  // namespace config
}  // namespace client
}  // namespace seabattle

#endif  // SEABATTLE_SBCLI_CONFIG_VIEW_H_
