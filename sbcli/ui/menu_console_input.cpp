#include "menu_console_input.h"

namespace seabattle {
namespace client {
namespace ui {

MenuConsoleInput::MenuConsoleInput() {}

size_t MenuConsoleInput::RenderAuth(size_t &command) {
    int key, menuitem;

    menuitem = 0;
    const size_t MENU_MAX = 5;

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

size_t MenuConsoleInput::DrawMenuAuth(size_t item) {
    const int MENUMAX = 5;
    int c;
    char mainmenu[] = "Main Menu";
    char menu[MENUMAX][21] = {"Single", "Download", "Multiplayer", "Log out", "Exit"};

    clear();
    addstr(mainmenu);
    for (c = 0; c < MENUMAX; c++) {
        if (c == item) attron(A_REVERSE); /* highlight selection */
        mvaddstr(3 + (c * 2), 20, menu[c]);
        attroff(A_REVERSE); /* remove highlight */
    }
    mvaddstr(17, 25, "Use arrow keys to move; Enter to select:");
    refresh();
    return 0;
}

size_t MenuConsoleInput::DrawMenuNonAuth(size_t item) {
    const int MENUMAX = 3;
    int c;
    char mainmenu[] = "Main Menu";
    char menu[MENUMAX][21] = {"Authorization", "Registration", "Exit"};

    clear();
    addstr(mainmenu);
    for (c = 0; c < MENUMAX; c++) {
        if (c == item) attron(A_REVERSE); /* highlight selection */
        mvaddstr(3 + (c * 2), 20, menu[c]);
        attroff(A_REVERSE); /* remove highlight */
    }
    mvaddstr(17, 25, "Use arrow keys to move; Enter to select:");
    refresh();
    return 0;
}

size_t MenuConsoleInput::RenderNonAuth(size_t &command) {
    int key, menuitem;

    menuitem = 0;
    const size_t MENU_MAX = 3;

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

}  // namespace ui
}  // namespace client
}  // namespace seabattle
