// ball_state.h
// Functions for checking ball collisions and scoring in the Pong game.

#ifndef BALL_STATE_H
#define BALL_STATE_H

#include "pong.h"

// Wall collision check functions
void check_ceiling_hit(struct ball *ball);
void check_floor_hit(struct ball *ball);

// Scoring check functions
void check_player_point(volatile unsigned short *buffer, struct ball *ball, struct game *game);
void check_cpu_point(volatile unsigned short *buffer, struct ball *ball, struct game *game);

#endif 
