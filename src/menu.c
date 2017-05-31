#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "menu.h"

menu_item_t EMPTY_MENU_ITEM = {
    .type = MENU_ITEM_EMPTY,
};

void menu_move_up(menu_t *menu) {
    if (menu->cursor <= 0) {
        return;
    }

    int i = menu->cursor - 1;
    while (i >= 0) {
        if ((menu->items[i]->type == MENU_ITEM_EMPTY) ||
            (menu->items[i]->type == MENU_ITEM_TEXT)) {
            i--;
        } else {
            menu->cursor = i;
            return;
        }
    }
}


void menu_move_down(menu_t *menu) {
    if (menu->cursor >= menu->num_item - 1) {
        return;
    }

    int i = menu->cursor + 1;
    while (i < menu->num_item) {
        if ((menu->items[i]->type == MENU_ITEM_EMPTY) ||
            (menu->items[i]->type == MENU_ITEM_TEXT)) {
            i++;
        } else {
            menu->cursor = i;
            return;
        }
    }
}


void menu_switch_left(menu_t *menu) {
    if (menu->items[menu->cursor]->type == MENU_ITEM_SELECT) {
        menu->items[menu->cursor]->choice =
            (menu->items[menu->cursor]->choice - 1 +
             (menu->items[menu->cursor]->num_choices)) % (menu->items[menu->cursor]->num_choices);
    }
}


void menu_switch_right(menu_t *menu) {
    if (menu->items[menu->cursor]->type == MENU_ITEM_SELECT) {
        menu->items[menu->cursor]->choice =
            (menu->items[menu->cursor]->choice + 1) %
            (menu->items[menu->cursor]->num_choices);
    }
}


bool menu_enter(menu_t *menu) {
    return menu->items[menu->cursor]->type == MENU_ITEM_BUTTON;
}


bool menu_click(menu_t *menu, int i) {
    bool stop = false;

    if ((i < menu->num_item) &&
        (i >= 0) &&
        (menu->items[i]->type != MENU_ITEM_EMPTY) &&
        (menu->items[i]->type != MENU_ITEM_TEXT)) {
        menu->cursor = i;
        switch (menu->items[menu->cursor]->type) {
        case MENU_ITEM_SELECT:
            menu_switch_right(menu);
            break;

        case MENU_ITEM_BUTTON:
            stop = menu_enter(menu);
            break;

        default:
            break;
        }
    }
    return stop;
}
