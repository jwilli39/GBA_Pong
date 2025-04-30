// score.h

#ifndef SCORE_H
#define SCORE_H

// struct for the score board
struct score
{
    int size;
    unsigned char color;
    unsigned char color2;

    // arrays for x and y coordinates [user]
    int x[7];
    int y[7];

    // arrays for x and y coordinates [cpu]
    int ax[7];
    int ay[7];
};

// Unified starting score function both user and CPU
void setStartingScore(struct score *score);

// Unified score update function for both user and CPU
void updateScore(volatile unsigned short *buffer, struct game *game, struct score *s, int isCPU);

// Unified score drawing function for both user and CPU
void drawScoreQuadrant(volatile unsigned short *buffer, struct score *s, int index, int isCPU);

#endif
