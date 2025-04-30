// gba.h

#ifndef GBA_H
#define GBA_H

#include "pong.h"

// Hardware registers
extern volatile unsigned short* screen;
extern volatile unsigned long* display_control;
extern volatile unsigned short* palette;
extern volatile unsigned short* front_buffer;
extern volatile unsigned short* back_buffer;
extern volatile unsigned short* buttons;
extern volatile unsigned short* scanline_counter;
extern int next_palette_index;

// Screen dimensions
#define WIDTH 240
#define HEIGHT 160

// Mode and background settings
#define MODE4 0x0004
#define BG2 0x0400
#define SHOW_BACK 0x10

// Button definitions
#define BUTTON_A (1 << 0)
#define BUTTON_B (1 << 1)
#define BUTTON_SELECT (1 << 2)
#define BUTTON_START (1 << 3)
#define BUTTON_RIGHT (1 << 4)
#define BUTTON_LEFT (1 << 5)
#define BUTTON_UP (1 << 6)
#define BUTTON_DOWN (1 << 7)
#define BUTTON_R (1 << 8)
#define BUTTON_L (1 << 9)

// Hardware-related functions
void wait_vblank();
unsigned char button_pressed(unsigned short button);
unsigned char add_color(unsigned char r, unsigned char g, unsigned char b);
void put_pixel(volatile unsigned short *buffer, int row, int col, unsigned char color);
void handle_buttons(struct paddle *p);

#endif
