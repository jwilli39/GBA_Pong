// ball_logic.h
// Handles ball movement and direction logic for the Pong game.

#ifndef BALL_LOGIC_H
#define BALL_LOGIC_H

#include "pong.h"

// Updates the ball's position and checks for collisions or scoring
void move_ball(volatile unsigned short *buffer, struct ball *ball, struct paddle *paddle, struct game *game);

// Sets the ball's velocity and direction based on the last hit
void ball_direction(struct ball *ball, const char *current_Hit);

#endif
