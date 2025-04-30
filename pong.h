// pong.h

#ifndef PONG_H
#define PONG_H

// Ball structure
struct ball {
    unsigned short x, y, size, direction, speed, hitCount;
    unsigned char color;
    char current_hit[50];
};

// Paddle structure
struct paddle {
    unsigned short x, y, size;
    unsigned char color;
    unsigned short x2, y2, size2;
    unsigned char color2;
};

// Game structure
struct game {
    unsigned int playerScore, cpuScore;
};

// Function prototype for starting the game
void play_pong();

#endif
