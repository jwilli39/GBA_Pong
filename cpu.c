// cpu.c
// Handles CPU paddle movement logic based on the ball's position.
// Adjusts speed slightly as the game progresses to increase difficulty.

#include "cpu.h"

/**
 * @brief Moves the CPU paddle to track the ball's position.
 * @param b Pointer to the ball structure containing ball position and hit count.
 * @param p Pointer to the paddle structure containing paddle position.
 * @param g Pointer to the game structure.
 */
void cpu_move(struct ball *b, struct paddle *p, struct game *g) {
    int speed = 3;        // Default CPU paddle speed
    int count = b->hitCount; // Number of times the ball has been hit

    // Increase CPU speed slightly after many hits
    if (count > 11) {
        speed = 2;
    }

    int b_row = b->y;   // Ball's current vertical position
    int p_row = p->y2;  // CPU paddle's current vertical position

    // If the ball is below the CPU paddle, move paddle down
    if (b_row > p_row + 5) {
        p->y2 += speed;
        // Prevent the paddle from moving below the bottom boundary
        if (p->y2 >= 146) {
            p->y2 -= speed;
        }
    }

    // If the ball is above the CPU paddle, move paddle up
    if (b_row < p_row + 5) {
        p->y2 -= speed;
        // Prevent the paddle from moving above the top boundary
        if (p->y2 <= 8) {
            p->y2 += speed;
        }
    }
}
