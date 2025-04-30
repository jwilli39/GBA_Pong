// render.h

#ifndef RENDER_H
#define RENDER_H

#include "pong.h"

// Drawing functions
void draw_paddle(volatile unsigned short *buffer, struct paddle *p);
void draw_ball(volatile unsigned short *buffer, struct ball *b);

// Screen handling functions
void update_screen(volatile unsigned short *buffer, unsigned short color, struct paddle *p, struct ball *b);
void clear_screen(volatile unsigned short *buffer, unsigned short color);
volatile unsigned short *flip_buffers(volatile unsigned short *buffer);

#endif
