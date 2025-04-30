// layout.c
// Functions for setting up and drawing the game's borders and center net.

#include "layout.h"
#include "gba.h"     

/**
 * @brief Initializes the layout structure with default positions, sizes, and colors for the net and all borders.
 * @param layout Pointer to the layout structure to set up.
 */
void setLayout(struct layout *layout)
{
    // Net
    layout->nx = 120;
    layout->ny = 0;
    layout->nsize = 160;
    layout->ncolor = add_color(11, 11, 11);

    // Left border
    layout->lx = 0;
    layout->ly = 0;
    layout->lsize = 160;
    layout->lcolor = add_color(31, 31, 31);

    // Right border
    layout->rx = 230;
    layout->ry = 0;
    layout->rsize = 160;
    layout->rcolor = add_color(31, 31, 31);

    // Top border
    layout->tx = 0;
    layout->ty = 0;
    layout->tsize = 240;
    layout->tcolor = add_color(31, 31, 31);

    // Bottom border
    layout->bx = 0;
    layout->by = 155;
    layout->bsize = 240;
    layout->bcolor = add_color(31, 31, 31);
}

/**
 * @brief Draws a filled rectangle at the given position.
 * @param buffer Pointer to the video buffer.
 * @param x Starting x coordinate.
 * @param y Starting y coordinate.
 * @param width Width of the rectangle.
 * @param height Height of the rectangle.
 * @param color Color to draw.
 */
static void draw_rect(volatile unsigned short *buffer, int x, int y, int width, int height, unsigned short color)
{
    for (short row = y; row < y + height; row++)
    {
        for (short col = x; col < x + width; col++)
        {
            put_pixel(buffer, row, col, color);
        }
    }
}

/**
 * @brief Draws all borders and the center net using the layout structure.
 * @param buffer Pointer to the video buffer.
 * @param layout Pointer to the layout structure containing all positions, sizes, and colors.
 */
void drawBorders(volatile unsigned short *buffer, struct layout *layout)
{
    // Draw dashed vertical net (every other row)
    for (short row = layout->ny; row < layout->ny + layout->nsize; row += 2)
    {
        for (short col = layout->nx; col < layout->nx + 2; col++)
        {
            put_pixel(buffer, row, col, layout->ncolor);
        }
    }

    // Draw borders using the general-purpose draw_rect function
    draw_rect(buffer, layout->lx, layout->ly, 10, layout->lsize, layout->lcolor);       // Left
    draw_rect(buffer, layout->rx, layout->ry, 10, layout->rsize, layout->rcolor);       // Right
    draw_rect(buffer, layout->tx, layout->ty, layout->tsize, 5, layout->tcolor);        // Top
    draw_rect(buffer, layout->bx, layout->by, layout->bsize, 5, layout->bcolor);        // Bottom
}
