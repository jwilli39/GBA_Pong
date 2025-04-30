// layout.h
// Defines the layout structure and functions for drawing the game's net and borders.

#ifndef LAYOUT_H
#define LAYOUT_H

#include "pong.h"   // For struct layout
#include "gba.h"    // For put_pixel and GBA types

// Layout structure for the game's net and screen borders
struct layout {
    // Net in the center of the screen
    unsigned short nx, ny, nsize;
    unsigned char ncolor;

    // Left border
    unsigned short lx, ly, lsize;
    unsigned char lcolor;

    // Right border
    unsigned short rx, ry, rsize;
    unsigned char rcolor;

    // Top border
    unsigned short tx, ty, tsize;
    unsigned char tcolor;

    // Bottom border
    unsigned short bx, by, bsize;
    unsigned char bcolor;
};

// Initializes the layout structure with default positions, sizes, and colors.
void setLayout(struct layout *layout);

 // Brief Draws all borders and the center net using the layout configuration.
void drawBorders(volatile unsigned short *buffer, struct layout *layout);

#endif
