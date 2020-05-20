#include "auth_console_input.h"

namespace seabattle {
namespace client {
namespace view {

AuthConsoleInput::AuthConsoleInput() {}

// TODO: консольный ввод меню/выход

size_t AuthConsoleInput::RenderAuth(size_t &command) {
    int key, menuitem;

    menuitem = 0;
    const size_t MENU_MAX = 2;

    initscr();

    DrawMenuAuth(menuitem);
    keypad(stdscr, TRUE);
    noecho(); /* Disable echo */
    do {
        key = getch();
        switch (key) {
            case KEY_DOWN:
                menuitem++;
                if (menuitem > MENU_MAX - 1) menuitem = 0;
                break;
            case KEY_UP:
                menuitem--;
                if (menuitem < 0) menuitem = MENU_MAX - 1;
                break;
            default:
                break;
        }
        DrawMenuAuth(menuitem);
    } while (key != '\n');

    echo(); /* re-enable echo */

    /* At this point, the value of the selected menu is kept in the
       menuitem variable. The program can branch off to whatever subroutine
       is required to carry out that function
    */

    endwin();
    command = menuitem;

    return 0;
}

size_t AuthConsoleInput::DrawMenuAuth(size_t item) {
    setlocale(LC_ALL, "");
    const int MENUMAX = 2;
    int c;
    char mainmenu[] = "Authorization menu";
    char menu[MENUMAX][50] = {"Log out", "Exit to main menu"};

    clear();
    addstr(mainmenu);
    for (c = 0; c < MENUMAX; c++) {
        if (c == item) attron(A_REVERSE); /* highlight selection */
        mvaddstr(3 + (c * 2), 20, menu[c]);
        attroff(A_REVERSE); /* remove highlight */
    }
    mvaddstr(17, 25,
             "Use arrow keys to move; Enter to select:");
    refresh();
    return 0;
}

size_t AuthConsoleInput::DrawMenuNonAuth(size_t item) {
    setlocale(LC_ALL, "");
    const int MENUMAX = 2;
    int c;
    char mainmenu[] = "Authorization menu";
    char menu[MENUMAX][50] = {"Input", "Exit to main menu"};

    clear();
    addstr(mainmenu);
    for (c = 0; c < MENUMAX; c++) {
        if (c == item) attron(A_REVERSE); /* highlight selection */
        mvaddstr(3 + (c * 2), 20, menu[c]);
        attroff(A_REVERSE); /* remove highlight */
    }
    mvaddstr(17, 25,
             "Use arrow keys to move; Enter to select:");
    refresh();
    return 0;
}

size_t AuthConsoleInput::RenderNonAuth(size_t &command) {
    int key, menuitem;

    menuitem = 0;
    const size_t MENU_MAX = 2;

    initscr();

    DrawMenuNonAuth(menuitem);
    keypad(stdscr, TRUE);
    noecho(); /* Disable echo */
    do {
        key = getch();
        switch (key) {
            case KEY_DOWN:
                menuitem++;
                if (menuitem > MENU_MAX - 1) menuitem = 0;
                break;
            case KEY_UP:
                menuitem--;
                if (menuitem < 0) menuitem = MENU_MAX - 1;
                break;
            default:
                break;
        }
        DrawMenuNonAuth(menuitem);
    } while (key != '\n');

    echo(); /* re-enable echo */

    /* At this point, the value of the selected menu is kept in the
       menuitem variable. The program can branch off to whatever subroutine
       is required to carry out that function
    */

    endwin();
    command = menuitem;
    return 0;
}

size_t AuthConsoleInput::ReadAuthData(utils::data::AuthData &auth_data) {
    setlocale(LC_ALL, "");
    char name[46];
    char password[9];

    initscr();
    clear();
    mvprintw(3, 10, "Login: ");
    refresh();
    getnstr(name, 45);
    mvprintw(5, 6, "Password: ");
    refresh();
    noecho();
    getnstr(password, 8);

    endwin();
    auth_data.login.assign(name);
    auth_data.password.assign(password);
    return 0;
}
}  // namespace view
}  // namespace client
}  // namespace seabattle
