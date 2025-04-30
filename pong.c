// pong.c
// Main game loop for Pong — handles drawing, input, movement, and core logic.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pong.h"
#include "gba.h"
#include "layout.h"
#include "cpu.h"
#include "render.h"
#include "score.h"
#include "ball_logic.h"
#include "ball_state.h"
#include "collision.h"

/**
 * @brief Main function that keeps the Pong game running by updating the screen, player input, and game logic.
 */
void play_pong() {
    // Set display mode to Mode 4 with Background 2 enabled (used for bitmap graphics)
    *display_control = MODE4 | BG2;

    // Initialize the player and CPU paddles with position, size, and color
    struct paddle p = {40, 80, 11, add_color(31, 0, 0),   // Player paddle (red)
                       200, 80, 11, add_color(0, 0, 31)}; // CPU paddle (blue)

    // Initialize the layout (borders) and score structures
    struct layout layout;
    struct score s;

    // Initialize the ball with starting position, direction, speed, and color (white)
    struct ball b = {120, 10, 1, 0, 4, 0, add_color(31, 31, 31), "downLeft"};

    // Initialize the game score (player and CPU scores start at 0)
    struct game g = {0, 0};

    // Pointer to the front buffer where drawing will happen
    volatile unsigned short *buffer = front_buffer;

    // Set the starting scores to 0
    setStartingScore(&s);

    // Set up the layout of the game field (like walls)
    setLayout(&layout);

    // Define a green color for the background
    unsigned char green = add_color(0, 15, 0);

    // Clear both front and back buffers with green background
    clear_screen(front_buffer, green);
    clear_screen(back_buffer, green);

    // Main game loop - runs forever
    while (1) {
        // Update the screen with current game objects
        update_screen(buffer, green, &p, &b);

        // Draw the player and CPU paddles
        draw_paddle(buffer, &p);

        // Move the CPU paddle to track the ball
        cpu_move(&b, &p, &g);

        // Draw the borders (layout) around the game area
        drawBorders(buffer, &layout);

        // Draw the ball at its current position
        draw_ball(buffer, &b);

        // Move the ball according to its velocity and direction
        move_ball(buffer, &b, &p, &g);

        // Update the player's and CPU's score displays
        updateScore(buffer, &g, &s, 0); // Player 1
        updateScore(buffer, &g, &s, 1); // Player 2 (CPU)

        // Handle button input for the player (move paddle)
        handle_buttons(&p);

        // Wait for vertical blank (screen refresh sync)
        wait_vblank();

        // Swap the front and back buffers for smooth drawing
        buffer = flip_buffers(buffer);
    }
}
