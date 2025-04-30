// palette.c
// Handles color management by adding new colors to the palette and tracking palette usage.

#include "gba.h"

// Definitions for the hardware pointers
volatile unsigned short *screen = (volatile unsigned short *)0x6000000;
volatile unsigned long *display_control = (volatile unsigned long *)0x4000000;
volatile unsigned short *palette = (volatile unsigned short *)0x5000000;
volatile unsigned short *front_buffer = (volatile unsigned short *)0x6000000;
volatile unsigned short *back_buffer = (volatile unsigned short *)0x600A000;
volatile unsigned short *buttons = (volatile unsigned short *)0x04000130;
volatile unsigned short *scanline_counter = (volatile unsigned short *)0x4000006;

// Tracks the next available index in the color palette
int next_palette_index = 0;

/**
 * @brief Waits for the start of the vertical blanking period (VBlank).
 */
void wait_vblank() {
    // Wait until scanline reaches 160, signaling the start of VBlank
    while (*scanline_counter < 160) {
    }
}

/**
 * @brief Check if a specific GBA button is currently pressed.
 * @param button The button mask to check (e.g., BUTTON_A, BUTTON_UP, etc.)
 * @return 1 if the button is pressed, 0 if it is not pressed.
 */
unsigned char button_pressed(unsigned short button) {
    // Read the current button state and isolate the specific button bit
    unsigned short pressed = *buttons & button;

    // If the result is 0, the button is pressed
    if (pressed == 0) {
        return 1; // Button is pressed
    } else {
        return 0; // Button is not pressed
    }
}

/**
 * @brief Adds a new RGB color to the palette and returns its index.
 * @param r Red component (0–31).
 * @param g Green component (0–31).
 * @param b Blue component (0–31).
 * @return Index of the newly added color in the palette.
 */
unsigned char add_color(unsigned char r, unsigned char g, unsigned char b) {
    // Convert 5-bit RGB values into a 15-bit RGB color format used by the GBA
    unsigned short color = (b << 10) | (g << 5) | r;

    // Store the color in the next available slot in the palette
    palette[next_palette_index] = color;

    // Move to the next palette index
    next_palette_index++;

    // Return the index of the color that was just added
    return next_palette_index - 1;
}

/**
 * @brief Draws a single pixel onto the screen in Mode 4 (packed pixel format).
 * @param buffer Pointer to the video buffer where pixels are stored.
 * @param row Row position (y-coordinate) of the pixel.
 * @param col Column position (x-coordinate) of the pixel.
 * @param color Color value to set for the pixel (8-bit).
 */
void put_pixel(volatile unsigned short *buffer, int row, int col, unsigned char color) {
    // Calculate the offset in the buffer (2 pixels per 16-bit value, so divide by 2)
    unsigned short offset = (row * WIDTH + col) >> 1;

    // Read the current 16-bit value from the buffer
    unsigned short pixel = buffer[offset];

    // If column is odd, set the high byte; else, set the low byte
    if (col & 1) {
        buffer[offset] = (color << 8) | (pixel & 0x00FF); // Set high 8 bits
    } else {
        buffer[offset] = (pixel & 0xFF00) | color;        // Set low 8 bits
    }
}

/**
 * @brief Handles player input to move the paddle up and down based on button presses.
 * @param p Pointer to the paddle structure to update based on input.
 */
void handle_buttons(struct paddle *p) {
    // Move paddle down if the DOWN button is pressed
    if (button_pressed(BUTTON_DOWN)) {
        p->y += 2; // Move the paddle down by 2 pixels

        // Keep the paddle from going too far down (past bottom edge)
        if (p->y >= 146) {
            p->y -= 2;
        }
    }

    // Move paddle up if the UP button is pressed
    if (button_pressed(BUTTON_UP)) {
        p->y -= 2; // Move the paddle up by 2 pixels

        // Keep the paddle from going too far up (past top edge)
        if (p->y <= 8) {
            p->y += 2; 
        }
    }
}
