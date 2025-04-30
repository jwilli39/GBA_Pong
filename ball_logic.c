// ball_logic.c
// Handles ball movement, direction control, and collision responses during gameplay.

#include <string.h>

#include "ball_logic.h"
#include "gba.h"
#include "collision.h"
#include "ball_state.h"

/**
 * @brief Updates the ball's position and handles collisions, direction, and scoring.
 * @param buffer Pointer to the video buffer.
 * @param ball Pointer to the ball structure.
 * @param paddle Pointer to the paddle structure.
 * @param game Pointer to the game structure.
 */
void move_ball(volatile unsigned short *buffer, struct ball *ball, struct paddle *paddle, struct game *game) {
    // Store a copy of the ball's current hit state
    char current_hit[50];
    strcpy(current_hit, ball->current_hit);

    // Check if the player or CPU scored
    check_cpu_point(buffer, ball, game);
    check_player_point(buffer, ball, game);

    // Adjust the ball's direction based on its last interaction
    ball_direction(ball, current_hit);

    // Check for collisions with the top or bottom screen edges
    check_ceiling_hit(ball);
    check_floor_hit(ball);

    // Handle collision with user paddle (left side)
    if (isBall_col_10(ball, paddle)) {
        user_paddle_top(ball, paddle);
        user_paddle_middle(ball, paddle);
        user_paddle_bottom(ball, paddle);
    }

    // Handle collision with CPU paddle (right side)
    if (isBall_col_230(ball, paddle)) {
        cpu_paddle_top(ball, paddle);
        cpu_paddle_middle(ball, paddle);
        cpu_paddle_bottom(ball, paddle);
    }
}

/**
 * @brief Updates the ball's velocity and position based on its current hit state.
 * @param ball Pointer to the ball structure.
 * @param hit The ball's last hit label used to determine direction.
 */
void ball_direction(struct ball *ball, const char *hit) {
    int bs;

    // Limit movement speed for consistent control (max 3)
    if (ball->speed > 3) {
        bs = 3;
    } else {
        bs = ball->speed;
    }

    // Ball going down and left
    if ((strcmp(hit, "downLeft") == 0) || (strcmp(hit, "ceiling") == 0 && ball->direction == 0)) {
        ball->x -= bs;
        ball->y += bs;

    // Ball going down and right
    } else if ((strcmp(hit, "downRight") == 0) || (strcmp(hit, "ceiling") == 0 && ball->direction == 1)) {
        ball->x += bs;
        ball->y += bs;

    // Ball going up and right
    } else if ((strcmp(hit, "upRight") == 0) || (strcmp(hit, "floor") == 0 && ball->direction == 1)) {
        ball->x += bs;
        ball->y -= bs;

    // Ball going straight right
    } else if (strcmp(hit, "right") == 0) {
        ball->x += bs;

    // Ball going up and left
    } else if ((strcmp(hit, "upLeft") == 0) || (strcmp(hit, "floor") == 0 && ball->direction == 0)) {
        ball->x -= bs;
        ball->y -= bs;

    // Ball going straight left
    } else if (strcmp(hit, "left") == 0) {
        ball->x -= bs;

    // Player is about to serve (ball moves down before serve starts)
    } else if (strcmp(hit, "wait_player_serve") == 0) {
        ball->y += 1;
        if (ball->y == 20) {
            strcpy(ball->current_hit, "player_serve");
        }

    // CPU is about to serve (ball moves down before serve starts)
    } else if (strcmp(hit, "wait_cpu_serve") == 0) {
        ball->y += 1;
        if (ball->y == 20) {
            strcpy(ball->current_hit, "cpu_serve");
        }

    // Ball moves diagonally (left) when served by the player
    } else if (strcmp(hit, "player_serve") == 0) {
        ball->x -= 1;
        ball->y += 1;

    // Ball moves diagonally (right) when served by the CPU
    } else if (strcmp(hit, "cpu_serve") == 0) {
        ball->x += 1;
        ball->y += 1;
    }
}
