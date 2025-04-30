// ball_state.c
// Handles ball collisions with the screen boundaries and updates game scoring.

#include <string.h>
#include "ball_state.h"

/**
 * @brief Checks if the ball has hit the ceiling and updates its state.
 * @param ball Pointer to the ball structure.
 */
void check_ceiling_hit(struct ball *ball) {
    if (ball->y <= 7) {
        ball->speed++;              // Increase speed slightly on ceiling hit
        ball->hitCount++;           // Track total hits for difficulty scaling
        strcpy(ball->current_hit, "ceiling"); // Record the hit type
    }
}

/**
 * @brief Checks if the ball has hit the floor and updates its state.
 * @param ball Pointer to the ball structure.
 */
void check_floor_hit(struct ball *ball) {
    if (ball->y >= 150) {
        ball->speed++;              // Increase speed slightly on floor hit
        ball->hitCount++;           // Track total hits for difficulty scaling
        strcpy(ball->current_hit, "floor"); // Record the hit type
    }
}

/**
 * @brief Checks if the player scored a point and resets the ball if so.
 * @param buffer Pointer to the video buffer (unused here, passed for compatibility).
 * @param ball Pointer to the ball structure.
 * @param game Pointer to the game structure containing scores.
 */
void check_player_point(volatile unsigned short *buffer, struct ball *ball, struct game *game) {
    if (ball->x >= 236) {
        ball->speed = 15;                   // Reset speed for serve
        ball->hitCount = 0;                 // Reset hit count
        ball->direction = 0;                // Set ball direction toward CPU
        strcpy(ball->current_hit, "wait_player_serve"); // Indicate waiting state
        ball->x = 120; ball->y = 15;        // Reset ball position

        // Increment player score; reset if > 9
        if (++game->playerScore > 9) {
            game->playerScore = 0;
            game->cpuScore = 0;
        }
    }
}

/**
 * @brief Checks if the CPU scored a point and resets the ball if so.
 * @param buffer Pointer to the video buffer (unused here, passed for compatibility).
 * @param ball Pointer to the ball structure.
 * @param game Pointer to the game structure containing scores.
 */
void check_cpu_point(volatile unsigned short *buffer, struct ball *ball, struct game *game) {
    if (ball->x <= 2) {
        ball->speed = 15;                   // Reset speed for serve
        ball->hitCount = 0;                 // Reset hit count
        ball->direction = 1;                // Set ball direction toward player
        strcpy(ball->current_hit, "wait_cpu_serve"); // Indicate waiting state
        ball->x = 120; ball->y = 15;        // Reset ball position

        // Increment CPU score; reset if > 9
        if (++game->cpuScore > 9) {
            game->playerScore = 0;
            game->cpuScore = 0;
        }
    }
}
