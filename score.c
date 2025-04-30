// score.c
// Functions related to score display logic and digit rendering on the screen.

#include "pong.h"
#include "score.h"
#include "gba.h"

// 7-segment display bit patterns for digits 0–9.
// Each row maps to a digit (0–9); each column is a segment (0–6).
// Segment layout is assumed to be in the format: {q1, q2, q3, q4, q5, q6, q7}
static const int scorePatterns[10][7] = {
    {1, 1, 1, 1, 1, 0, 1}, // 0
    {0, 1, 0, 1, 0, 0, 0}, // 1
    {0, 1, 1, 0, 1, 1, 1}, // 2
    {0, 1, 0, 1, 1, 1, 1}, // 3
    {1, 1, 0, 1, 0, 1, 0}, // 4
    {1, 0, 0, 1, 1, 1, 1}, // 5
    {1, 0, 1, 1, 1, 1, 1}, // 6
    {0, 1, 0, 1, 1, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 0, 1, 1, 1, 0}  // 9
};

/**
 * @brief Draws a single segment of a 7-segment digit for either the player or CPU score.
 * @param buffer The video buffer where pixels will be drawn.
 * @param s Pointer to the score structure containing segment positions and colors.
 * @param index Index of the segment to draw (0–6).
 * @param isCPU Non-zero if drawing for the CPU score; 0 for player score.
 */
void drawScoreQuadrant(volatile unsigned short *buffer, struct score *s, int index, int isCPU)
{
    short row, col;
    short x, y;                  // Coordinates of the top-left corner of the segment
    unsigned short color;       // Color to draw the segment

    // Choose the correct coordinates and color depending on whether this is for the CPU or the player
    if (isCPU) {
        x = s->ax[index];       // CPU's x-coordinate for this segment
        y = s->ay[index];       // CPU's y-coordinate for this segment
        color = s->color2;      // CPU's color
    } else {
        x = s->x[index];        // Player's x-coordinate for this segment
        y = s->y[index];        // Player's y-coordinate for this segment
        color = s->color;       // Player's color
    }

    // If the index is less than 4, it's a vertical segment
    if (index < 4) {
        // Draw a vertical line by drawing a pixel in each row from y to y + size
        for (row = y; row < y + s->size; row++) {
            put_pixel(buffer, row, x, color);
        }
    } else {
        // Otherwise, it's a horizontal segment
        // Draw a horizontal line by drawing pixels across columns from x to x + size
        for (row = y; row < y + 1; row++) {
            for (col = x; col < x + s->size + 1; col++) {
                put_pixel(buffer, row, col, color);
            }
        }
    }
}

/**
 * @brief Initializes the starting score display settings for both the player and the CPU.
 * @param score Pointer to the score structure to initialize.
 */
void setStartingScore(struct score *score)
{
    score->size = 4;

    // Colors
    score->color = add_color(31, 15, 15);  // user - light red
    score->color2 = add_color(15, 15, 31); // cpu - light blue

    // User coordinates
    score->x[0] = 112; score->y[0] = 15; // q1
    score->x[1] = 116; score->y[1] = 15; // q2
    score->x[2] = 112; score->y[2] = 19; // q3
    score->x[3] = 116; score->y[3] = 19; // q4
    score->x[4] = 112; score->y[4] = 15; // q5
    score->x[5] = 112; score->y[5] = 18; // q6
    score->x[6] = 112; score->y[6] = 22; // q7

    // CPU coordinates
    score->ax[0] = 125; score->ay[0] = 15; // q1
    score->ax[1] = 129; score->ay[1] = 15; // q2
    score->ax[2] = 125; score->ay[2] = 19; // q3
    score->ax[3] = 129; score->ay[3] = 19; // q4
    score->ax[4] = 125; score->ay[4] = 15; // q5
    score->ax[5] = 125; score->ay[5] = 18; // q6
    score->ax[6] = 125; score->ay[6] = 22; // q7
}

/**
 * @brief Updates the visual score display for either the player or the CPU.
 * @param buffer The video buffer to draw to.
 * @param game Pointer to the current game state containing the scores.
 * @param s Pointer to the score structure with segment positions and colors.
 * @param isCPU Flag indicating whether to update the CPU's score (non-zero) or the player's (0).
 */
void updateScore(volatile unsigned short *buffer, struct game *game, struct score *s, int isCPU)
{
    int currentScore;

    // Decide which score to use: CPU or player
    if (isCPU == 1) {
        currentScore = game->cpuScore;
    } else {
        currentScore = game->playerScore;
    }

    // Loop through all 7 segments of the digit
    for (int i = 0; i < 7; i++) {
        // If the segment should be drawn for this number
        if (scorePatterns[currentScore][i]) {
            // Draw that specific segment (quadrant) of the score digit
            drawScoreQuadrant(buffer, s, i, isCPU);
        }
    }
}
