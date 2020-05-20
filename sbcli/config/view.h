#ifndef SEABATTLE_SBCLI_CONFIG_VIEW_H_
#define SEABATTLE_SBCLI_CONFIG_VIEW_H_

#include <string>

namespace seabattle {
namespace client {
namespace config {

struct HelpMainMenu {
    const char *help_message = "Используй стрелки для навигации, а клавишу ENTER для выбора";
};

struct HelpAuthMenu {
    const char *help_message = "Используй стрелки для навигации, а клавишу ENTER для выбора";
};

struct MenuExistUser {
    const char *menu_name = "Главное меню";
    const char *hello_message = "Привет, ";
    const int len = 5;
    const char items[5][100] = {
        "Одиночная игра", "Загрузить игру", "Многопользовательская игра", "Выход из аккаунта",
            "Закрыть игру"
    };
};

struct MenuNonExistUser {
    const char *menu_name = "Главное меню";
    const char *hello_message = "Здравствуй, игрок! Укажи, кто ты!";
    const int len = 3;
    const char items[3][100] { "Авторизация", "Регистрация", "Закрыть игру" };
};

struct AuthExistUser {
    const char *menu_name = "Меню авторизации";
    const int len = 2;
    const char items[2][100] = { "Выход", "А меню" };
};

struct AuthNonExistUser {
    const char *menu_name = "Меню авторизации";
    const int len = 2;
    const char items[2][100] = { "Ввод данных", "В меню" };
};

}  // namespace view
}  // namespace client
}  // namespace seabattle

#endif  // SEABATTLE_SBCLI_CONFIG_VIEW_H_
