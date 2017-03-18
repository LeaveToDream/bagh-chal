#ifndef __GAME_H__
#define __GAME_H__

#include "models.h"

typedef struct {
    board_t       board;
    player_turn_t turn;
    int           num_goats_to_put;
    int           num_eaten_goats;
} game_t;

game_t *game_new();
void game_free(game_t *g);

// game_reset resets the game.
void game_reset();

// game_get_possible_from_selections updates the `pos` structure with the
// valid from positions.
void game_get_possible_from_selections(game_t *g, possible_positions_t *pos);

// game_get_possible_from_selections updates the `pos` structure with the
// valid to positions given a from position.
void game_get_possible_to_selections(game_t *g, position_t from_pos,
                                     possible_positions_t *pos);

// game_do_mvt does the given movement for the current player if valid.
// Returns 0 if the movement is not feasible. 1 otherwhise.
int game_do_mvt(game_t *g, mvt_t *mvt);

// game_is_done returns 0 if the game is still on. 1 if the game is done.
int game_is_done(game_t *g);

#endif