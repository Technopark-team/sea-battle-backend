#ifndef SEABATTLE_SBCLI_COMPONENTS_GAME_GAME_H_
#define SEABATTLE_SBCLI_COMPONENTS_GAME_GAME_H_

#include <ncurses.h>
#include <memory>
#include "sbcli/blocks/field.h"
#include "sbcli/blocks/ships.h"
#include "sbutils/data/test_data.h"

namespace seabattle {
namespace client {
namespace component {

template <class T>
class GameMenu {
 public:
    GameMenu() = default;
    ~GameMenu() = default;

    size_t Render(size_t &res_choice);
    size_t WalkAround();

 private:
    size_t Draw_(size_t item);
    void run();
    void run1(int y, int x);

    T menu;
};

template <class T>
void GameMenu<T>::run() {
    char empty_char[5] = "    ";
    int x = 19, y = 7;

    int in_char;

    bool exit_requested = false;

    curs_set(0);
    noecho(); /* Disable echo */

    // выбор начальной точки установки
    while (1) {
        in_char = getch();

        mvaddstr(y, x, empty_char);

        switch (in_char) {
            case 'q':
                exit_requested = true;
                break;
            case 'z':
                run1(y, x);
                break;
            case KEY_UP:
            case 'w':
                y -= 2;
                break;
            case KEY_DOWN:
            case 's':
                y += 2;
                break;
            case KEY_LEFT:
            case 'a':
                x -= 5;
                break;
            case KEY_RIGHT:
            case 'd':
                x += 5;
                break;
            default:
                break;
        }

        mvaddstr(y, x, block::ShipElement().base);

        if (exit_requested) break;

        refresh();
    }


    getch();
}

template <class T>
void GameMenu<T>::run1(int y, int x) {
    int in_char;
    bool exit_requested = false;

    // отрисовка корабля относительно выбранной точки
    while (1) {
        in_char = getch();

        switch (in_char) {
            case 'q':
                exit_requested = true;
                break;
            case KEY_UP:
            case 'w':
                mvaddstr(y, x, block::ShipElement().base);
                mvaddstr(y - 2, x, block::ShipElement().base);
                mvaddstr(y - 4, x, block::ShipElement().base);
                mvaddstr(y - 6, x, block::ShipElement().base);
                break;
            case KEY_DOWN:
            case 's':
                mvaddstr(y, x, block::ShipElement().base);
                mvaddstr(y + 2, x, block::ShipElement().base);
                mvaddstr(y + 4, x, block::ShipElement().base);
                mvaddstr(y + 6, x, block::ShipElement().base);
                break;
            case KEY_LEFT:
            case 'a':
                mvaddstr(y, x, block::ShipElement().base);
                mvaddstr(y, x - 5, block::ShipElement().base);
                mvaddstr(y, x - 10, block::ShipElement().base);
                mvaddstr(y, x - 15, block::ShipElement().base);
                break;
            case KEY_RIGHT:
            case 'd':
                mvaddstr(y, x, block::ShipElement().base);
                mvaddstr(y, x + 5, block::ShipElement().base);
                mvaddstr(y, x + 10, block::ShipElement().base);
                mvaddstr(y, x + 15, block::ShipElement().base);
                break;
            default:
                break;
        }
        if (exit_requested) break;

        refresh();
    }
}

template <class T>
size_t GameMenu<T>::Draw_(size_t item) {
    clear();

    mvaddstr(4, 41, block::UserFieldName().name);
    mvaddstr(4, 108, block::EnemyFieldName().name);
    mvaddstr(4, 77, block::Delimiter().name);
    for (int c = 0; c < block::Field().len; c++) {
        mvaddstr(5 + c, 16, block::Field().field[c]);
        mvaddstr(5 + c, 86, block::Field().field[c]);
        mvaddstr(5 + c, 77, block::Delimiter().name);
    }

    mvaddstr(27, 77, block::Delimiter().name);
    mvaddstr(28, 77, block::Delimiter().name);

    mvaddstr(28, 16, block::UserListName().name);
    mvaddstr(28, 86, block::EnemyListName().name);
    for (int c = 0; c < menu.len; c++) {
        if (c == item) attron(A_REVERSE); /* highlight selection */
        mvaddstr(29 + c, 16, menu.name[c]);
        attroff(A_REVERSE); /* remove highlight */
        mvaddstr(29 + c, 86, menu.name[c]);
        mvaddstr(29 + c, 77, block::Delimiter().name);
    }

    refresh();
    return 0;
}

template <class T>
size_t GameMenu<T>::Render(size_t &res_choice) {
    int key, menuitem;

    menuitem = 0;
    //выбор корабля
    Draw_(menuitem);
    keypad(stdscr, TRUE);
    noecho(); /* Disable echo */
    while (key != '\n') {
        key = getch();
        switch (key) {
            case KEY_DOWN:
                menuitem++;
                if (menuitem > menu.len - 1) menuitem = 0;
                break;
            case KEY_UP:
                menuitem--;
                if (menuitem < 0) menuitem = menu.len - 1;
                break;
            default:
                break;
        }
        Draw_(menuitem);
    };

    echo();

    res_choice = menuitem;

    run();

    return 0;
}

template <class T>
size_t GameMenu<T>::WalkAround() {
    return 0;
}

}  // namespace component
}  // namespace client
}  // namespace seabattle

#endif  // SEABATTLE_SBCLI_COMPONENTS_GAME_GAME_H_
