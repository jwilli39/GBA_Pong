// collision.h
// Handles collision detection and responses for ball and paddle interactions.

#ifndef COLLISION_H
#define COLLISION_H

#include "pong.h"

// Wall Collision Checks
int isBall_col_10(struct ball *ball, struct paddle *paddle);
int isBall_col_230(struct ball *ball, struct paddle *paddle);

// User Paddle Collision Handling
void user_paddle_top(struct ball *ball, struct paddle *paddle);
void user_paddle_middle(struct ball *ball, struct paddle *paddle);
void user_paddle_bottom(struct ball *ball, struct paddle *paddle);

// CPU Paddle Collision Handling
void cpu_paddle_top(struct ball *ball, struct paddle *paddle);
void cpu_paddle_middle(struct ball *ball, struct paddle *paddle);
void cpu_paddle_bottom(struct ball *ball, struct paddle *paddle);

// Utility
static int random_delta();

#endif 
