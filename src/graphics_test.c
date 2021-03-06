#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "graphics.h"

#define TEST_EVENT_KEY(key_name)                            \
    sprintf(state.msg, "Press %s", # key_name);             \
    graphics.draw_game(context, &state);                    \
    graphics.wait_event_game(context, &event);              \
    if (event.type != EVENT_KEY || event.key != key_name) { \
        sprintf(err_msg, "Expected %s", # key_name);        \
        return false;                                       \
    }                                                       \

#define TEST_EVENT_CH(ch_name)                                      \
    sprintf(state.msg, "Press %c", ch_name);                        \
    graphics.draw_game(context, &state);                            \
    graphics.wait_event_game(context, &event);                      \
    if (event.type != EVENT_KEY) {                                  \
        sprintf(err_msg, "Expected %c", ch_name);                   \
        return false;                                               \
    }                                                               \
    if (event.key != KEY_CH || event.ch != ch_name) {               \
        sprintf(err_msg, "Expected %c, got %c", ch_name, event.ch); \
        return false;                                               \
    }                                                               \

#define TEST_EVENT_MOUSE(pos1, pos2)                                  \
    sprintf(state.msg, "Click on %c (%d,%d)",                         \
            position_get_tag((position_t){pos1, pos2 }), pos1, pos2); \
    graphics.draw_game(context, &state);                              \
    graphics.wait_event_game(context, &event);                        \
    if (event.type != EVENT_POSITION) {                               \
        sprintf(err_msg, "Expected (%d,%d)", pos1, pos2);             \
        return false;                                                 \
    }                                                                 \
    if (event.position.c != pos1 || event.position.r != pos2) {       \
        sprintf(err_msg, "Expected (%d,%d), got (%d,%d)",             \
                pos1, pos2, event.position.c, event.position.r);      \
        return false;                                                 \
    }

#define WAIT_BEFORE_NEXT_TEST()                                  \
    do {                                                         \
        graphics.draw_game(context, &state);                     \
        graphics.wait_event_game(context, &event);               \
        if (event.type == EVENT_QUIT) {                          \
            return true;                                         \
        }                                                        \
    } while (event.type != EVENT_KEY || event.key != KEY_ENTER); \


bool test_graphics(void                 *context,
                   graphics_callbacks_t graphics,
                   char                 *err_msg) {
    game_state_to_draw_t state;
    game_t               game;
    event_t              event;

    state.game = &game;


    game.num_goats_to_put = 20;
    game.num_eaten_goats  = 0;
    game.turn             = GOAT_TURN;
    state.input.from.c    = 2;
    state.input.from.r    = POSITION_NOT_SET;
    state.input.to.c      = POSITION_NOT_SET;
    state.input.to.r      = POSITION_NOT_SET;
    char msg[256] = "";
    state.msg = msg;

    board_t board = { {
                          TIGER_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, TIGER_CELL,
                          EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL,
                          EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL,
                          EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL,
                          TIGER_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, TIGER_CELL
                      } };
    memcpy(&game.board, &board, sizeof(game.board));

    possible_positions_t possible_positions_1 = { {
                                                      0, 1, 1, 1, 0,
                                                      1, 1, 1, 1, 1,
                                                      1, 1, 1, 1, 1,
                                                      1, 1, 1, 1, 1,
                                                      0, 1, 1, 1, 0
                                                  } };
    state.possible_positions = possible_positions_1;

    WAIT_BEFORE_NEXT_TEST();

    game.num_goats_to_put = 19;
    game.num_eaten_goats  = 0;
    game.turn             = TIGER_TURN;
    state.input.from.c    = POSITION_NOT_SET;
    state.input.from.r    = POSITION_NOT_SET;
    state.input.to.c      = POSITION_NOT_SET;
    state.input.to.r      = POSITION_NOT_SET;

    board_t board1 = { {
                           TIGER_CELL, EMPTY_CELL, GOAT_CELL, EMPTY_CELL, TIGER_CELL,
                           EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL,
                           EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL,
                           EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL,
                           TIGER_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, TIGER_CELL
                       } };
    memcpy(&game.board, &board1, sizeof(game.board));

    possible_positions_t possible_positions_2 = { {
                                                      1, 0, 0, 0, 1,
                                                      0, 0, 0, 0, 0,
                                                      0, 0, 0, 0, 0,
                                                      0, 0, 0, 0, 0,
                                                      1, 0, 0, 0, 1
                                                  } };
    state.possible_positions = possible_positions_2;

    WAIT_BEFORE_NEXT_TEST();

    game.num_goats_to_put = 0;
    game.num_eaten_goats  = 0;
    game.turn             = GOAT_TURN;
    state.input.from.c    = 1;
    state.input.from.r    = 3;
    state.input.to.c      = POSITION_NOT_SET;
    state.input.to.r      = POSITION_NOT_SET;

    board_t board2 = { {
                           TIGER_CELL, GOAT_CELL, GOAT_CELL, GOAT_CELL, GOAT_CELL,
                           GOAT_CELL, GOAT_CELL, EMPTY_CELL, TIGER_CELL, GOAT_CELL,
                           GOAT_CELL, EMPTY_CELL, GOAT_CELL, GOAT_CELL, GOAT_CELL,
                           GOAT_CELL, GOAT_CELL, GOAT_CELL, GOAT_CELL, GOAT_CELL,
                           TIGER_CELL, GOAT_CELL, GOAT_CELL, GOAT_CELL, TIGER_CELL
                       } };
    memcpy(&game.board, &board2, sizeof(game.board));

    possible_positions_t possible_positions_3 = { {
                                                      0, 0, 0, 0, 0,
                                                      0, 0, 0, 0, 0,
                                                      0, 1, 0, 0, 0,
                                                      0, 0, 0, 0, 0,
                                                      0, 0, 0, 0, 0
                                                  } };
    state.possible_positions = possible_positions_3;

    WAIT_BEFORE_NEXT_TEST();

    game.num_goats_to_put = 0;
    game.num_eaten_goats  = 4;
    game.turn             = GOAT_TURN;
    state.input.from.c    = 3;
    state.input.from.r    = 2;
    state.input.to.c      = POSITION_NOT_SET;
    state.input.to.r      = POSITION_NOT_SET;

    board_t board3 = { {
                           TIGER_CELL, GOAT_CELL, GOAT_CELL, GOAT_CELL, TIGER_CELL,
                           GOAT_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL,
                           GOAT_CELL, EMPTY_CELL, GOAT_CELL, GOAT_CELL, GOAT_CELL,
                           GOAT_CELL, GOAT_CELL, GOAT_CELL, GOAT_CELL, GOAT_CELL,
                           TIGER_CELL, GOAT_CELL, GOAT_CELL, GOAT_CELL, TIGER_CELL
                       } };
    memcpy(&game.board, &board3, sizeof(game.board));

    possible_positions_t possible_positions_4 = { {
                                                      0, 0, 0, 0, 0,
                                                      0, 0, 0, 1, 0,
                                                      0, 0, 0, 0, 0,
                                                      0, 0, 0, 0, 0,
                                                      0, 0, 0, 0, 0
                                                  } };
    state.possible_positions = possible_positions_4;

    WAIT_BEFORE_NEXT_TEST();

    TEST_EVENT_KEY(KEY_ENTER);
    TEST_EVENT_KEY(KEY_ARROW_UP);
    TEST_EVENT_CH('a');
    TEST_EVENT_CH('4');
    TEST_EVENT_MOUSE(3, 1);
    TEST_EVENT_CH('A');
    TEST_EVENT_MOUSE(0, 0);
    return true;
}
