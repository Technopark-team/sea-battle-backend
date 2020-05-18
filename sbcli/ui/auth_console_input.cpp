#include "auth_console_input.h"
#include <ncurses.h>

namespace seabattle {
namespace client {
namespace ui {

AuthConsoleInput::AuthConsoleInput() {}

// TODO: консольный ввод меню/выход

size_t AuthConsoleInput::ReadCommand(config::UserCommand& user_command) {
//    user_command.command = config::MENU_COMMAND;
    // TODO: https://code-live.ru/post/ncurses-input-output/
    const char items[4][5] = {
        "Auth",
        "Rega",
        "Menu",
        "Exit"
    };

    initscr();

    unsigned choice = 0; //Выбор пользователя
    unsigned exit = 0;

    curs_set(0); //"Убиваем" курсор
    //Включаем режим удобной работы с функциональными клавишами, другими словами KEY_UP и KEY_DOWN без этого не работали бы
    keypad(stdscr, true);

    while ( !exit )
    {
         clear();
        for ( unsigned i = 0; i < 4; i++ ) //Проходим по всем элементам меню
        {
            if ( i == choice ) //Если текущий элемент совпадает с выбором пользователя
                addch('>'); //Выводим указатель
            else
                addch(' '); //Иначе выводим " ", для равновесия

            printw("%s\n", items[i]);
        }

        //Получаем нажатие пользователя
        switch ( getch() )
        {
            case KEY_UP:
                if ( choice ) //Если возможно, переводим указатель вверх
                    choice--;
                break;
            case KEY_DOWN:
                if ( choice != 3 ) //Если возможно, переводим указатель вниз
                    choice++;
                break;
            case KEY_LEFT:
                exit = 1;
                break;
        }
    }

    endwin();

    switch (choice) {
        case 0:
            user_command.command = config::SIGNIN_COMMAND; // SIGNIN
            break;
        case 1:
            user_command.command = config::SIGNUP_COMMAND; // SIGNUP
            break;
        case 2:
            user_command.command = config::MENU_COMMAND; // MENU
            break;
        case 3:
            user_command.command = config::EXIT_COMMAND; // EXIT
            break;
    }

    return 0;
}

size_t AuthConsoleInput::ReadAuthData(utils::data::AuthData& auth_data) {
    auth_data.login = "log";
    auth_data.password = "pas";
    return 0;
}
}  // namespace ui
}  // namespace client
}  // namespace seabattle
