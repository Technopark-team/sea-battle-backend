#ifndef SEABATTLE_SBCLI_COMPONENTS_AUTH_AUTH_H_
#define SEABATTLE_SBCLI_COMPONENTS_AUTH_AUTH_H_

#include <ncurses.h>
#include <memory>

namespace seabattle {
namespace client {
namespace component {

template <class ItemsT, class HelpT>
class AuthMenu {
 public:
    AuthMenu() = default;
    ~AuthMenu() = default;

    size_t Render(size_t &res_choice);
    size_t ReadAuthData(char* login_, int log_len, char* pass, int pass_len);

 private:
    size_t Draw_(size_t item);

    ItemsT menu_items_;
    HelpT help_items_;
};

template <class ItemsT, class HelpT>
size_t AuthMenu<ItemsT, HelpT>::Draw_(size_t item) {
    clear();
    addstr(menu_items_.menu_name);
    for (int c = 0; c < menu_items_.len; c++) {
        if (c == item) attron(A_REVERSE); /* highlight selection */
        mvaddstr(20 + (c * 2), 50, menu_items_.items[c]);
        attroff(A_REVERSE); /* remove highlight */
    }
    mvaddstr(43, 17, help_items_.help_message);
    refresh();
    return 0;
}

template <class ItemsT, class HelpT>
size_t AuthMenu<ItemsT, HelpT>::Render(size_t &res_choice) {
    int key, menuitem;

    menuitem = 0;


    Draw_(menuitem);
    keypad(stdscr, TRUE);
    noecho(); /* Disable echo */
    while (key != '\n') {
        key = getch();
        switch (key) {
            case KEY_DOWN:
                menuitem++;
                if (menuitem > menu_items_.len - 1) menuitem = 0;
                break;
            case KEY_UP:
                menuitem--;
                if (menuitem < 0) menuitem = menu_items_.len - 1;
                break;
            default:
                break;
        }
        Draw_(menuitem);
    };

    echo();

    res_choice = menuitem;

    return 0;
}

template <class ItemsT, class HelpT>
size_t AuthMenu<ItemsT, HelpT>::ReadAuthData(char* login_, int log_len, char* pass, int pass_len) {

    initscr();
    clear();
//    mvprintw(3, 10, "Логин: ");
    mvprintw(3, 10, "Login: ");
    refresh();
    getnstr(login_, log_len);
//    mvprintw(5, 10, "Пароль: ");
    mvprintw(5, 10, "Password: ");
    refresh();
    noecho();
    getnstr(pass, pass_len);

    endwin();
    return 0;
}

}  // namespace component
}  // namespace client
}  // namespace seabattle

#endif  // SEABATTLE_SBCLI_COMPONENTS_AUTH_AUTH_H_
