/*
 
 Copyright (c) 2019 Hannes Eberhard
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
 */

#ifndef graphics_h
#define graphics_h

#include "includes.h"

#define MARGIN 10
#define HEADER_HEIGHT 20
#define FONT_HEIGHT 8
#define LINE_HEIGHT 5

typedef enum {
    GCOL_NULL,
    GCOL_BACKGROUND_PRIMARY,
    GCOL_BACKGROUND_SECONDARY,
    GCOL_TEXT_PRIMARY,
    GCOL_TEXT_SECONDARY,
    GCOL_BORDER,
    GCOL_HEADER,
    GCOL_BLACK,
    GCOL_WHITE,
    GCOL_YELLOW,
    GCOL_GREEN,
    GCOL_BLUE,
    GCOL_SYMBOLIC3,
    GCOL_SYMBOLIC4
} GFX_COLORS;

typedef enum {
    JUST_NULL,
    JUST_CENTER,
    JUST_TOP,
    JUST_RIGHT,
    JUST_BOTTOM,
    JUST_LEFT
} justification;

extern bool dark_mode;

void gfx_init(void);
void gfx_print(const char* string, uint16_t x, uint16_t y);
void gfx_print_justified(const char* string, justification x_justification, uint16_t x_offset, justification y_justification, uint16_t y_offset);
void gfx_print_line(const char* string, justification x_justification);
void gfx_print_box(const char* string, uint16_t width, uint8_t line_height);
void print_character_wise(const char* string);
void draw_header(const char* left, const char* center, const char* right);

#endif /* graphics_h */
