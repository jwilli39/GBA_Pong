// render.c
// Handles all drawing-related functions including rendering paddles, the ball, and screen updates.

#include "render.h"
#include "gba.h"

/**
 * @brief Draws both the player and CPU paddles onto the screen.
 * @param buffer Pointer to the video buffer where pixels are drawn.
 * @param p Pointer to the paddle structure containing paddle properties.
 */
void draw_paddle(volatile unsigned short *buffer, struct paddle *p) {
    short row, col;

    // Draw the player paddle
    for (row = p->y; row < (p->y + p->size); row++) {
        for (col = p->x; col < (p->x + 2); col++) {
            put_pixel(buffer, row, col, p->color);
        }
    }

    // Draw the CPU paddle
    for (row = p->y2; row < (p->y2 + p->size2); row++) {
        for (col = p->x2; col < (p->x2 + 2); col++) {
            put_pixel(buffer, row, col, p->color2);
        }
    }
}

/**
 * @brief Draws the ball onto the screen based on its current position and size.
 * @param buffer Pointer to the video buffer where pixels are drawn.
 * @param b Pointer to the ball structure containing ball properties.
 */
void draw_ball(volatile unsigned short *buffer, struct ball *b) {
    short row, col;
    for (row = b->y; row < (b->y + b->size); row++) {
        for (col = b->x; col < (b->x + b->size); col++) {
            put_pixel(buffer, row, col, b->color);
        }
    }
}

/**
 * @brief Clears the area around the paddles and ball by redrawing the background color.
 * @param buffer Pointer to the video buffer where pixels are drawn.
 * @param color Background color to fill cleared areas with.
 * @param p Pointer to the paddle structure containing paddle positions and sizes.
 * @param b Pointer to the ball structure containing ball position and size.
 */
void update_screen(volatile unsigned short *buffer, unsigned short color, struct paddle *p, struct ball *b) {
    short row, col;

    // Clear area around the player paddle
    for (row = p->y - 10; row < (p->y + p->size + 10); row++) {
        for (col = p->x - 10; col < (p->x + p->size + 10); col++) {
            put_pixel(buffer, row, col, color); // Draw background color to erase old paddle
        }
    }

    // Clear area around the CPU paddle
    for (row = p->y2 - 10; row < (p->y2 + p->size2 + 10); row++) {
        for (col = p->x2 - 10; col < (p->x2 + p->size2 + 10); col++) {
            put_pixel(buffer, row, col, color); // Draw background color to erase old CPU paddle
        }
    }

    // Clear area around the ball
    for (row = b->y - 10; row < (b->y + b->size + 10); row++) {
        for (col = b->x - 10; col < (b->x + b->size + 10); col++) {
            put_pixel(buffer, row, col, color); // Draw background color to erase old ball position
        }
    }
}

/**
 * @brief Fills the entire screen with a single background color.
 * @param buffer Pointer to the video buffer where pixels are drawn.
 * @param color Color to fill the screen with.
 */
void clear_screen(volatile unsigned short *buffer, unsigned short color) {
    unsigned short row, col;

    for (row = 0; row < HEIGHT; row++) {
        for (col = 0; col < WIDTH; col++) {
            put_pixel(buffer, row, col, color);
        }
    }
}

/**
 * @brief Switches between the front and back video buffers to update the screen smoothly.
 * @param buffer Pointer to the current active video buffer.
 * @return Pointer to the newly active buffer after flipping.
 */
volatile unsigned short *flip_buffers(volatile unsigned short *buffer) {
    // If the current buffer is the front buffer
    if (buffer == front_buffer) {
        *display_control &= ~SHOW_BACK; // Set to display the front buffer
        return back_buffer;                             // Start drawing to the back buffer
    } else {
        *display_control |= SHOW_BACK;  // Set to display the back buffer
        return front_buffer;                          // Start drawing to the front buffer
    }
}
