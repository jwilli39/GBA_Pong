// collision.c
// Implements ball and paddle collision detection and response logic.

#include <string.h>
#include <stdlib.h>

#include "collision.h"

/**
 * @brief Generates a small random vertical offset for ball movement after collision.
 * @return A random integer between 6 and 8.
 */
static int random_delta() {
    // Return a random value: 6, 7, or 8
    return 6 + (rand() % 3);
}

/**
 * @brief Checks if the ball has collided with the left wall (x = 10).
 * @param ball Pointer to the ball structure.
 * @param paddle Pointer to the paddle structure.
 * @return 1 if collision occurred, 0 otherwise.
 */
int isBall_col_10(struct ball *ball, struct paddle *paddle) {
    short bx = ball->x;       // Ball's x position
    short px = paddle->x;     // Paddle's x position (user)

    // Check if the ball's x matches the left wall (column 10) within 2 pixels tolerance
    return (bx == px || bx == px + 1 || bx == px + 2);
}

/**
 * @brief Checks if the ball has collided with the right wall (x = 230).
 * @param ball Pointer to the ball structure.
 * @param paddle Pointer to the paddle structure.
 * @return 1 if collision occurred, 0 otherwise.
 */
int isBall_col_230(struct ball *ball, struct paddle *paddle) {
    short bx = ball->x;        // Ball's x position
    short px = paddle->x2 - 2; // Adjusted CPU paddle x position

    // Check if the ball's x matches the right wall (column 230) within 2 pixels tolerance
    return (bx == px || bx == px - 1 || bx == px - 2);
}

/**
 * @brief Handles collision with the top section of the user paddle.
 * @param ball Pointer to the ball structure.
 * @param paddle Pointer to the paddle structure.
 */
void user_paddle_top(struct ball *ball, struct paddle *paddle) {
    short by = ball->y, py = paddle->y;

    // Check if the ball hits the top part of the user paddle
    if (by >= py && by <= py + 4) {
        strcpy(ball->current_hit, "upRight"); // Update ball's last hit direction
        ball->direction = 1;                  // Set ball direction to right
        ball->hitCount++;                     // Increment total hit count
        ball->speed += random_delta();        // Slightly increase ball speed

        // Cap ball speed at a maximum of 8
        if (ball->speed > 8) ball->speed = 8;

        // Bounce ball up and right
        ball->x += 4;
        ball->y -= 4;
    }
}

/**
 * @brief Handles collision with the middle section of the user paddle.
 * @param ball Pointer to the ball structure.
 * @param paddle Pointer to the paddle structure.
 */
void user_paddle_middle(struct ball *ball, struct paddle *paddle) {
    short by = ball->y, py = paddle->y;

    // Check if the ball hits the middle part of the user paddle
    if (by == py + 5 || by == py + 6) {
        strcpy(ball->current_hit, "right");   // Update ball's last hit direction
        ball->direction = 1;                  // Set ball direction to straight right
        ball->hitCount++;                     // Increment total hit count
        ball->speed += random_delta();        // Slightly increase ball speed

        // Cap ball speed at a maximum of 8
        if (ball->speed > 8) ball->speed = 8;

        // Push ball horizontally to the right
        ball->x += 6;
    }
}

/**
 * @brief Handles collision with the bottom section of the user paddle.
 * @param ball Pointer to the ball structure.
 * @param paddle Pointer to the paddle structure.
 */
void user_paddle_bottom(struct ball *ball, struct paddle *paddle) {
    short by = ball->y, py = paddle->y;

    // Check if the ball hits the bottom part of the user paddle
    if (by >= py + 7 && by <= py + 11) {
        strcpy(ball->current_hit, "downRight"); // Update ball's last hit direction
        ball->direction = 1;                    // Set ball direction to right
        ball->hitCount++;                       // Increment total hit count
        ball->speed += random_delta();          // Slightly increase ball speed

        // Cap ball speed at a maximum of 8
        if (ball->speed > 8) ball->speed = 8;

        // Bounce ball down and right
        ball->x += 4;
        ball->y += 4;
    }
}

/**
 * @brief Handles collision with the top section of the CPU paddle.
 * @param ball Pointer to the ball structure.
 * @param paddle Pointer to the paddle structure.
 */
void cpu_paddle_top(struct ball *ball, struct paddle *paddle) {
    short by = ball->y, py = paddle->y2;

    // Check if the ball hits the top part of the CPU paddle
    if (by >= py && by <= py + 4) {
        strcpy(ball->current_hit, "upLeft"); // Update ball's last hit direction
        ball->direction = 0;                 // Set ball direction to left
        ball->hitCount++;                    // Increment total hit count
        ball->speed += random_delta();       // Slightly increase ball speed

        // Cap ball speed at a maximum of 8
        if (ball->speed > 8) ball->speed = 8;

        // Bounce ball up and left
        ball->x -= 4;
        ball->y -= 4;
    }
}

/**
 * @brief Handles collision with the middle section of the CPU paddle.
 * @param ball Pointer to the ball structure.
 * @param paddle Pointer to the paddle structure.
 */
void cpu_paddle_middle(struct ball *ball, struct paddle *paddle) {
    short by = ball->y, py = paddle->y2;

    // Check if the ball hits the middle part of the CPU paddle
    if (by == py + 5 || by == py + 6) {
        strcpy(ball->current_hit, "left");   // Update ball's last hit direction
        ball->direction = 0;                 // Set ball direction to straight left
        ball->hitCount++;                    // Increment total hit count
        ball->speed += random_delta();       // Slightly increase ball speed

        // Cap ball speed at a maximum of 8
        if (ball->speed > 8) ball->speed = 8;

        // Push ball horizontally to the left
        ball->x -= 6;
    }
}

/**
 * @brief Handles collision with the bottom section of the CPU paddle.
 * @param ball Pointer to the ball structure.
 * @param paddle Pointer to the paddle structure.
 */
void cpu_paddle_bottom(struct ball *ball, struct paddle *paddle) {
    short by = ball->y, py = paddle->y2;

    // Check if the ball hits the bottom part of the CPU paddle
    if (by >= py + 7 && by <= py + 11) {
        strcpy(ball->current_hit, "downLeft"); // Update ball's last hit direction
        ball->direction = 0;                   // Set ball direction to left
        ball->hitCount++;                      // Increment total hit count
        ball->speed += random_delta();         // Slightly increase ball speed

        // Cap ball speed at a maximum of 8
        if (ball->speed > 8) ball->speed = 8;

        // Bounce ball down and left
        ball->x -= 4;
        ball->y += 4;
    }
}
