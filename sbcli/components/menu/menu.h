#ifndef SEABATTLE_SBCLI_COMPONENTS_MENU_MENU_H_
#define SEABATTLE_SBCLI_COMPONENTS_MENU_MENU_H_

#include <ncurses.h>
#include <locale.h>

namespace seabattle {
namespace client {
namespace component {

template <class ItemsT, class HelpT>
class MainMenu {
 public:
    MainMenu() = default;
    ~MainMenu() = default;

    size_t Render(size_t &res_choice);

 private:
    size_t Draw_(size_t item);

    ItemsT menu_items_;
    HelpT help_items_;
};

template <class ItemsT, class HelpT>
size_t MainMenu<ItemsT, HelpT>::Draw_(size_t item) {
    clear();
    addstr(menu_items_.menu_name);
    for (int c = 0; c < menu_items_.len; c++) {
        if (c == item) attron(A_REVERSE); /* highlight selection */
        mvaddstr(3 + (c * 2), 20, menu_items_.items[c]);
        attroff(A_REVERSE); /* remove highlight */
    }
    mvaddstr(17, 25, help_items_.help_message);
    refresh();
    return 0;
}

template <class ItemsT, class HelpT>
size_t MainMenu<ItemsT, HelpT>::Render(size_t &res_choice) {
    setlocale(LC_ALL, "");

    int key, menuitem;

    menuitem = 0;

    initscr();

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
    endwin();

    res_choice = menuitem;

    return 0;
}

}  // namespace component
}  // namespace client
}  // namespace seabattle

#endif  // SEABATTLE_SBCLI_COMPONENTS_MENU_MENU_H_
