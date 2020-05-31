#include "game.h"
#include <iostream>

namespace seabattle {
namespace client {
namespace component {

GameMenu::GameMenu() {
    // все корабли имеют статус - не установлены (false)
    for (int c = 0; c < menu.len; c++) {
        set_ships.insert({c, false});
    }
}

size_t GameMenu::GetMap(utils::data::TestMap &player_map, config::UserCommandId &exit) {
    // количество установленных кораблей
    int set_ship_counter = 0;
    // код нажатой клавиши
    int key;
    // текущий тип корабля
    int menuitem = 0;

    // рисуем начальное поле и начальные списки
    InitStaticFields();

    // пока пользователь не отказался от ввода и пока не введено 10 кораблей
    while ((exit != config::UserCommandId::QUITMAP_COMMAND) && (set_ship_counter < 10)) {
        key = getch();
        switch (key) {
            case KEY_DOWN:
                // берем следующий пункт меню
                menuitem++;
                // обрабатываем переполнение
                if (menuitem > menu.len - 1) menuitem = 0;
                // проверяем на на то, был ли установлен
                while (set_ships.at(menuitem)) {
                    // ищем не установленный
                    menuitem++;
                    // обрабатываем переполнение
                    if (menuitem > menu.len - 1) menuitem = 0;
                }
                // выделяем следующий не высталенный корабль
                Draw_(menuitem);
                break;
            case KEY_UP:
                // аналогично
                menuitem--;
                if (menuitem < 0) menuitem = menu.len - 1;
                while (set_ships.at(menuitem)) {
                    menuitem--;
                    if (menuitem < 0) menuitem = menu.len - 1;
                }
                Draw_(menuitem);
                break;
            case 'q':
            case 27:
                exit = config::UserCommandId::QUITMAP_COMMAND;
                break;
            case '\n':
            case ' ':
                config::UserCommandId cell_exit = config::UserCommandId::DEFAULT_COMMAND;
                utils::data::TestPoint start;
                utils::data::TestPoint end;

                // корабль ранее не был установлен
                if (!set_ships.at(menuitem)) {
                    SetShip(menuitem, start, end, cell_exit);
                    // если не выход из клетки
                    if (cell_exit == config::UserCommandId::READYCELL_COMMAND) {
                        seabattle::utils::data::TestShip point;
                        // сохраняем корабль в карту
                        point.start_ = std::move(start);
                        point.end_ = std::move(end);
                        player_map.ships.insert({menuitem, point});
                        // фиксируем корабль для избежания повторной установки
                        set_ships.at(menuitem) = true;
                        // считаем поставленные корабли
                        set_ship_counter++;
                    }
                }
                break;
        }
    };
    return 0;
}

// просто ищем корабль, который нужно выделить
size_t GameMenu::Draw_(size_t item) {
    // 4
    init_pair(1, COLOR_MAGENTA, COLOR_WHITE);
    // 3
    init_pair(2, COLOR_YELLOW, COLOR_WHITE);
    // 2
    init_pair(3, COLOR_GREEN, COLOR_WHITE);
    // 1
    init_pair(4, COLOR_BLACK, COLOR_WHITE);

    for (int c = 0; c < menu.len; c++) {
        if (c == item) attron(A_REVERSE); /* highlight selection */
        if (c == 0) attron(COLOR_PAIR(1));
        if (c >= 1 && c <= 2) attron(COLOR_PAIR(2));
        if (c >= 3 && c <= 5) attron(COLOR_PAIR(3));
        if (c >= 6 && c <= 9) attron(COLOR_PAIR(4));
        mvaddstr(29 + c, 16, menu.name[c]);
        attroff(A_REVERSE | COLOR_PAIR(1) | COLOR_PAIR(2) | COLOR_PAIR(3) |
                COLOR_PAIR(4)); /* remove highlight */
        mvaddstr(29 + c, 86, menu.name[c]);
        mvaddstr(29 + c, 77, block::Delimiter().name);
    }

    refresh();
    return 0;
}

size_t GameMenu::SetShip(size_t item, utils::data::TestPoint &start, utils::data::TestPoint &end,
                         config::UserCommandId &cell_exit) {
    // затираем прошлую клетку при переходе
    char empty_char[5] = "    ";
    // начальные координаты (относительный 0,0)
    int x = 19;
    int y = 7;

    int key;

    keypad(stdscr, TRUE);
    curs_set(0);
    noecho(); /* Disable echo */

    // 4
    init_pair(7, COLOR_MAGENTA, COLOR_CYAN);
    // 3
    init_pair(8, COLOR_YELLOW, COLOR_CYAN);
    // 2
    init_pair(9, COLOR_GREEN, COLOR_CYAN);
    // 1
    init_pair(10, COLOR_BLACK, COLOR_CYAN);
    // background
    init_pair(5, COLOR_BLACK, COLOR_CYAN);
    // Cursor color
    init_pair(6, COLOR_RED, COLOR_CYAN);

    MakeBaseColor(item, x, y);

    // выбор начальной точки установки
    while (cell_exit != config::UserCommandId::QUITCELL_COMMAND &&
           cell_exit != config::UserCommandId::READYCELL_COMMAND) {
        YesNo check = YesNo::DEFAULT;

        key = getch();

        switch (key) {
            case 27:
            case 'q':
                IsEmptyCell(x, y, check);
                if (check == YesNo::YES) {
                    attron(COLOR_PAIR(5));
                    mvaddstr(y, x, empty_char);
                    attroff(COLOR_PAIR(5));
                }
                cell_exit = config::UserCommandId::QUITCELL_COMMAND;
                break;
            case ' ':
            case '\n': {
                config::UserCommandId cell_direction_exit = config::UserCommandId::DEFAULT_COMMAND;
                TransformCoordinates(x, y, start);
                SetShipDirection(item, x, y, end, cell_direction_exit);
                if (cell_direction_exit == config::UserCommandId::READYCELL_COMMAND) {
                    InsertCell(start, end);
                    cell_exit = config::UserCommandId::READYCELL_COMMAND;
                }

                break;
            }
            case KEY_UP: {
                utils::data::TestPoint check_point;
                TransformCoordinates(x, y, check_point);
                IsEmptyCell(check_point.x_, check_point.y_, check);
                if (check == YesNo::YES) {
                    attron(COLOR_PAIR(5));
                    mvaddstr(y, x, empty_char);
                    attroff(COLOR_PAIR(5));
                }
                IsPlayerUPEdge(y - 2, check);
                if (check == YesNo::NO) y -= 2;
                MakeBaseColor(item, x, y);
                break;
            }
            case KEY_DOWN: {
                utils::data::TestPoint check_point;
                TransformCoordinates(x, y, check_point);
                IsEmptyCell(check_point.x_, check_point.y_, check);
                if (check == YesNo::YES) {
                    attron(COLOR_PAIR(5));
                    mvaddstr(y, x, empty_char);
                    attroff(COLOR_PAIR(5));
                }
                IsPlayerDOWNEdge(y + 2, check);
                if (check == YesNo::NO) y += 2;
                MakeBaseColor(item, x, y);
                break;
            }
            case KEY_LEFT: {
                utils::data::TestPoint check_point;
                TransformCoordinates(x, y, check_point);
                IsEmptyCell(check_point.x_, check_point.y_, check);
                if (check == YesNo::YES) {
                    attron(COLOR_PAIR(5));
                    mvaddstr(y, x, empty_char);
                    attroff(COLOR_PAIR(5));
                }
                IsPlayerLEFTEdge(x - 5, check);
                if (check == YesNo::NO) x -= 5;
                MakeBaseColor(item, x, y);
                break;
            }
            case KEY_RIGHT: {
                utils::data::TestPoint check_point;
                TransformCoordinates(x, y, check_point);
                IsEmptyCell(check_point.x_, check_point.y_, check);
                if (check == YesNo::YES) {
                    attron(COLOR_PAIR(5));
                    mvaddstr(y, x, empty_char);
                    attroff(COLOR_PAIR(5));
                }
                IsPlayerRIGHTEdge(x + 5, check);
                if (check == YesNo::NO) x += 5;
                MakeBaseColor(item, x, y);
                break;
            }
        }

        refresh();
    }
    attroff(COLOR_PAIR(7) | COLOR_PAIR(8) | COLOR_PAIR(9) | COLOR_PAIR(10));
}

size_t GameMenu::MakeBaseColor(int item, int x, int y) {
    if (item == 0) attron(COLOR_PAIR(7));
    if (item >= 1 && item <= 2) attron(COLOR_PAIR(8));
    if (item >= 3 && item <= 5) attron(COLOR_PAIR(9));
    if (item >= 6 && item <= 9) attron(COLOR_PAIR(10));
    mvaddstr(y, x, block::ShipElement().base);
}

size_t GameMenu::SetShipDirection(size_t item, int x, int y, utils::data::TestPoint &end,
                                  config::UserCommandId &cell_direction_exit) {
    // отрисовка корабля относительно выбранной точки
    int key;

    while (cell_direction_exit != config::UserCommandId::QUITCELL_COMMAND &&
           cell_direction_exit != config::UserCommandId::READYCELL_COMMAND) {
        YesNo check = YesNo::DEFAULT;
        key = getch();

        switch (key) {
            case 'q':
            case 27:
                cell_direction_exit = config::UserCommandId::QUITCELL_COMMAND;
                break;
            case KEY_UP:
                switch (item) {
                    case 0:
                        IsPlayerUPEdge(y - 6, check);
                        if (check == YesNo::NO) {
                            mvaddstr(y, x, block::ShipElement().base);
                            mvaddstr(y - 2, x, block::ShipElement().base);
                            mvaddstr(y - 4, x, block::ShipElement().base);
                            mvaddstr(y - 6, x, block::ShipElement().base);
                            TransformCoordinates(x, y - 6, end);
                            cell_direction_exit = config::UserCommandId::READYCELL_COMMAND;
                        }
                        break;
                    case 1:
                    case 2:
                        IsPlayerUPEdge(y - 4, check);
                        if (check == YesNo::NO) {
                            mvaddstr(y, x, block::ShipElement().base);
                            mvaddstr(y - 2, x, block::ShipElement().base);
                            mvaddstr(y - 4, x, block::ShipElement().base);
                            TransformCoordinates(x, y - 4, end);
                            cell_direction_exit = config::UserCommandId::READYCELL_COMMAND;
                        }
                        break;
                    case 3:
                    case 4:
                    case 5:
                        IsPlayerUPEdge(y - 2, check);
                        if (check == YesNo::NO) {
                            mvaddstr(y, x, block::ShipElement().base);
                            mvaddstr(y - 2, x, block::ShipElement().base);
                            TransformCoordinates(x, y - 2, end);
                            cell_direction_exit = config::UserCommandId::READYCELL_COMMAND;
                        }
                        break;
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                        mvaddstr(y, x, block::ShipElement().base);
                        TransformCoordinates(x, y, end);
                        cell_direction_exit = config::UserCommandId::READYCELL_COMMAND;
                        break;
                }
                break;
            case KEY_DOWN:
                switch (item) {
                    case 0:
                        IsPlayerDOWNEdge(y + 6, check);
                        if (check == YesNo::NO) {
                            mvaddstr(y, x, block::ShipElement().base);
                            mvaddstr(y + 2, x, block::ShipElement().base);
                            mvaddstr(y + 4, x, block::ShipElement().base);
                            mvaddstr(y + 6, x, block::ShipElement().base);
                            TransformCoordinates(x, y + 6, end);
                            cell_direction_exit = config::UserCommandId::READYCELL_COMMAND;
                        }
                        break;
                    case 1:
                    case 2:
                        IsPlayerDOWNEdge(y + 4, check);
                        if (check == YesNo::NO) {
                            mvaddstr(y, x, block::ShipElement().base);
                            mvaddstr(y + 2, x, block::ShipElement().base);
                            mvaddstr(y + 4, x, block::ShipElement().base);
                            TransformCoordinates(x, y + 4, end);
                            cell_direction_exit = config::UserCommandId::READYCELL_COMMAND;
                        }
                        break;
                    case 3:
                    case 4:
                    case 5:
                        IsPlayerDOWNEdge(y + 2, check);
                        if (check == YesNo::NO) {
                            mvaddstr(y, x, block::ShipElement().base);
                            mvaddstr(y + 2, x, block::ShipElement().base);
                            TransformCoordinates(x, y + 2, end);
                            cell_direction_exit = config::UserCommandId::READYCELL_COMMAND;
                        }
                        break;
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                        mvaddstr(y, x, block::ShipElement().base);
                        TransformCoordinates(x, y, end);
                        cell_direction_exit = config::UserCommandId::READYCELL_COMMAND;
                        break;
                }
                break;
            case KEY_LEFT:
                switch (item) {
                    case 0:
                        IsPlayerLEFTEdge(x - 15, check);
                        if (check == YesNo::NO) {
                            mvaddstr(y, x, block::ShipElement().base);
                            mvaddstr(y, x - 5, block::ShipElement().base);
                            mvaddstr(y, x - 10, block::ShipElement().base);
                            mvaddstr(y, x - 15, block::ShipElement().base);
                            TransformCoordinates(x - 15, y, end);
                            cell_direction_exit = config::UserCommandId::READYCELL_COMMAND;
                        }
                        break;
                    case 1:
                    case 2:
                        IsPlayerLEFTEdge(x - 10, check);
                        if (check == YesNo::NO) {
                            mvaddstr(y, x, block::ShipElement().base);
                            mvaddstr(y, x - 5, block::ShipElement().base);
                            mvaddstr(y, x - 10, block::ShipElement().base);
                            TransformCoordinates(x - 10, y, end);
                            cell_direction_exit = config::UserCommandId::READYCELL_COMMAND;
                        }
                        break;
                    case 3:
                    case 4:
                    case 5:
                        IsPlayerLEFTEdge(x - 5, check);
                        if (check == YesNo::NO) {
                            mvaddstr(y, x, block::ShipElement().base);
                            mvaddstr(y, x - 5, block::ShipElement().base);
                            TransformCoordinates(x - 5, y, end);
                            cell_direction_exit = config::UserCommandId::READYCELL_COMMAND;
                        }
                        break;
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                        mvaddstr(y, x, block::ShipElement().base);
                        TransformCoordinates(x, y, end);
                        cell_direction_exit = config::UserCommandId::READYCELL_COMMAND;
                        break;
                }
                break;
            case KEY_RIGHT:
                switch (item) {
                    case 0:
                        IsPlayerRIGHTEdge(x + 15, check);
                        if (check == YesNo::NO) {
                            mvaddstr(y, x, block::ShipElement().base);
                            mvaddstr(y, x + 5, block::ShipElement().base);
                            mvaddstr(y, x + 10, block::ShipElement().base);
                            mvaddstr(y, x + 15, block::ShipElement().base);
                            TransformCoordinates(x + 15, y, end);
                            cell_direction_exit = config::UserCommandId::READYCELL_COMMAND;
                        }
                        break;
                    case 1:
                    case 2:
                        IsPlayerRIGHTEdge(x + 10, check);
                        if (check == YesNo::NO) {
                            mvaddstr(y, x, block::ShipElement().base);
                            mvaddstr(y, x + 5, block::ShipElement().base);
                            mvaddstr(y, x + 10, block::ShipElement().base);
                            TransformCoordinates(x + 10, y, end);
                            cell_direction_exit = config::UserCommandId::READYCELL_COMMAND;
                        }
                        break;
                    case 3:
                    case 4:
                    case 5:
                        IsPlayerRIGHTEdge(x + 5, check);
                        if (check == YesNo::NO) {
                            mvaddstr(y, x, block::ShipElement().base);
                            mvaddstr(y, x + 5, block::ShipElement().base);
                            TransformCoordinates(x + 5, y, end);
                            cell_direction_exit = config::UserCommandId::READYCELL_COMMAND;
                        }
                        break;
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                        mvaddstr(y, x, block::ShipElement().base);
                        TransformCoordinates(x, y, end);
                        cell_direction_exit = config::UserCommandId::READYCELL_COMMAND;
                        break;
                }
                break;
        }
    }
    refresh();
}

size_t GameMenu::InitStaticFields() {
    // очищаем предыдущий экран
    clear();

    keypad(stdscr, TRUE);
    noecho();

    // Field background color
    init_pair(5, COLOR_BLACK, COLOR_CYAN);

    // задаем статическое поле без списка кораблей
    mvaddstr(4, 41, block::UserFieldName().name);
    mvaddstr(4, 108, block::EnemyFieldName().name);
    mvaddstr(4, 77, block::Delimiter().name);
    for (int c = 0; c < block::Field().len; c++) {
        attron(COLOR_PAIR(5));
        mvaddstr(5 + c, 16, block::Field().field[c]);
        mvaddstr(5 + c, 86, block::Field().field[c]);
        attroff(COLOR_PAIR(5));
        mvaddstr(5 + c, 77, block::Delimiter().name);
    }

    mvaddstr(27, 77, block::Delimiter().name);
    mvaddstr(28, 77, block::Delimiter().name);

    mvaddstr(28, 16, block::UserListName().name);
    mvaddstr(28, 86, block::EnemyListName().name);

    // начальный выбор корабля
    Draw_(0);

    // отображаем в консоли
    refresh();
}

/*
 * X = 19 Y = 7
 *
 * X
 * 0  1  2  3  4  5  6  7  8  9
 * 19 24 29 34 39 44 49 54 59 64
 *
 * Y
 * 0  1  2  3  4  5  6  7  8  9
 * 7  9  11 13 15 17 19 21 23 25
 *
 */
size_t GameMenu::TransformCoordinates(int x, int y, utils::data::TestPoint &point) {
    switch (x) {
        case 19:
            point.x_ = 0;
            break;
        case 24:
            point.x_ = 1;
            break;
        case 29:
            point.x_ = 2;
            break;
        case 34:
            point.x_ = 3;
            break;
        case 39:
            point.x_ = 4;
            break;
        case 44:
            point.x_ = 5;
            break;
        case 49:
            point.x_ = 6;
            break;
        case 54:
            point.x_ = 7;
            break;
        case 59:
            point.x_ = 8;
            break;
        case 64:
            point.x_ = 9;
            break;
    }

    switch (y) {
        case 7:
            point.y_ = 0;
            break;
        case 9:
            point.y_ = 1;
            break;
        case 11:
            point.y_ = 2;
            break;
        case 13:
            point.y_ = 3;
            break;
        case 15:
            point.y_ = 4;
            break;
        case 17:
            point.y_ = 5;
            break;
        case 19:
            point.y_ = 6;
            break;
        case 21:
            point.y_ = 7;
            break;
        case 23:
            point.y_ = 8;
            break;
        case 25:
            point.y_ = 9;
            break;
    }

    return 0;
}

size_t GameMenu::IsPlayerUPEdge(int y, YesNo &check) {
    if (y >= 7) {
        check = YesNo::NO;
    } else {
        check = YesNo::YES;
    }
}

size_t GameMenu::IsPlayerDOWNEdge(int y, YesNo &check) {
    if (y <= 25) {
        check = YesNo::NO;
    } else {
        check = YesNo::YES;
    }
}

size_t GameMenu::IsPlayerLEFTEdge(int x, YesNo &check) {
    if (x >= 19) {
        check = YesNo::NO;
    } else {
        check = YesNo::YES;
    }
}

size_t GameMenu::IsPlayerRIGHTEdge(int x, YesNo &check) {
    if (x <= 64) {
        check = YesNo::NO;
    } else {
        check = YesNo::YES;
    }
}

size_t GameMenu::InsertCell(utils::data::TestPoint &start, utils::data::TestPoint &end) {
    if (start.x_ == end.x_) {
        for (int iter = start.y_; iter <= end.y_; iter++) {
            std::pair<int, int> test_pair = std::make_pair(start.x_, iter);
            nonempty_cells.push_back(test_pair);
        }
    }
    if (start.y_ == end.y_) {
        for (int iter = start.x_; iter <= end.x_; iter++) {
            std::pair<int, int> test_pair = std::make_pair(iter, start.y_);
            nonempty_cells.push_back(test_pair);
        }
    }
}

size_t GameMenu::IsEmptyCell(int x, int y, YesNo &check) {
    auto test_pair = std::make_pair(x, y);
    if (std::find(nonempty_cells.begin(), nonempty_cells.end(), test_pair) !=
        nonempty_cells.end()) {
        check = YesNo::NO;
    } else {
        check = YesNo::YES;
    }
}

//=================================================================================================

size_t GameMenu::GetStep(utils::data::TestPoint &player_step, config::UserCommandId &exit) {
    // затираем прошлую клетку при переходе
    char empty_char[5] = "    ";
    // начальные координаты (относительный 0,0)
    int x = 89;
    int y = 7;

    int key;

    keypad(stdscr, TRUE);
    curs_set(0);
    noecho(); /* Disable echo */

    init_pair(6, COLOR_RED, COLOR_CYAN);
    attron(COLOR_PAIR(6));
    mvaddstr(y, x, block::ShipElement().base);

    // выбор начальной точки установки
    while (exit != config::UserCommandId::QUITCELL_COMMAND &&
           exit != config::UserCommandId::READYCELL_COMMAND) {
        YesNo check = YesNo::DEFAULT;

        key = getch();

        switch (key) {
            case 27:
            case 'q':
                mvaddstr(y, x, empty_char);
                exit = config::UserCommandId::QUITCELL_COMMAND;
                break;
            case ' ':
            case '\n':
                TransformCoordinates(x, y, player_step);
                exit = config::UserCommandId::READYCELL_COMMAND;
                break;
            case KEY_UP:
                attron(COLOR_PAIR(5));
                mvaddstr(y, x, empty_char);
                attroff(COLOR_PAIR(5));
                IsOpponentUPEdge(y - 2, check);
                if (check == YesNo::NO) y -= 2;
                attron(COLOR_PAIR(6));
                mvaddstr(y, x, block::ShipElement().base);
                break;
            case KEY_DOWN:
                attron(COLOR_PAIR(5));
                mvaddstr(y, x, empty_char);
                attroff(COLOR_PAIR(5));
                IsOpponentDOWNEdge(y + 2, check);
                if (check == YesNo::NO) y += 2;
                attron(COLOR_PAIR(6));
                mvaddstr(y, x, block::ShipElement().base);
                break;
            case KEY_LEFT:
                attron(COLOR_PAIR(5));
                mvaddstr(y, x, empty_char);
                attroff(COLOR_PAIR(5));
                IsOpponentLEFTEdge(x - 5, check);
                if (check == YesNo::NO) x -= 5;
                attron(COLOR_PAIR(6));
                mvaddstr(y, x, block::ShipElement().base);
                break;
            case KEY_RIGHT:
                attron(COLOR_PAIR(5));
                mvaddstr(y, x, empty_char);
                attroff(COLOR_PAIR(5));
                IsOpponentRIGHTEdge(x + 5, check);
                if (check == YesNo::NO) x += 5;
                attron(COLOR_PAIR(6));
                mvaddstr(y, x, block::ShipElement().base);
                break;
        }

        refresh();
    }
    attroff(COLOR_PAIR(6));
}

size_t GameMenu::IsOpponentUPEdge(int y, YesNo &check) {
    if (y >= 7) {
        check = YesNo::NO;
    } else {
        check = YesNo::YES;
    }
}

size_t GameMenu::IsOpponentDOWNEdge(int y, YesNo &check) {
    if (y <= 25) {
        check = YesNo::NO;
    } else {
        check = YesNo::YES;
    }
}

size_t GameMenu::IsOpponentLEFTEdge(int x, YesNo &check) {
    if (x >= 89) {
        check = YesNo::NO;
    } else {
        check = YesNo::YES;
    }
}

size_t GameMenu::IsOpponentRIGHTEdge(int x, YesNo &check) {
    if (x <= 134) {
        check = YesNo::NO;
    } else {
        check = YesNo::YES;
    }
}

}  // namespace component
}  // namespace client
}