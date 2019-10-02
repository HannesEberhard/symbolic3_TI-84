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

#include "includes.h"

bool dark_mode = false;

void gfx_init(void) {
    
    gfx_palette[GCOL_NULL] = gfx_RGBTo1555(0, 0, 0);
    gfx_palette[GCOL_BLACK] = gfx_RGBTo1555(0, 0, 0);
    gfx_palette[GCOL_WHITE] = gfx_RGBTo1555(255, 255, 255);
    gfx_palette[GCOL_YELLOW] = gfx_RGBTo1555(255, 172, 38);
    gfx_palette[GCOL_GREEN] = gfx_RGBTo1555(210, 239, 86);
    gfx_palette[GCOL_BLUE] = gfx_RGBTo1555(77, 187, 255);
    gfx_palette[GCOL_SYMBOLIC3] = gfx_RGBTo1555(255, 38, 88);
    gfx_palette[GCOL_SYMBOLIC4] = gfx_RGBTo1555(40, 43, 64);
    
    if (dark_mode == false) {
        gfx_palette[GCOL_BACKGROUND_PRIMARY] = gfx_RGBTo1555(255, 255, 255);
        gfx_palette[GCOL_BACKGROUND_SECONDARY] = gfx_RGBTo1555(240, 240, 240);
        gfx_palette[GCOL_TEXT_PRIMARY] = gfx_RGBTo1555(0, 0, 0);
        gfx_palette[GCOL_TEXT_SECONDARY] = gfx_RGBTo1555(180, 180, 180);
        gfx_palette[GCOL_BORDER] = gfx_RGBTo1555(0, 0, 0);
        gfx_palette[GCOL_HEADER] = gfx_RGBTo1555(255, 38, 88);
        gfx_palette[100 + GCOL_BACKGROUND_PRIMARY] = gfx_RGBTo1555(45, 45, 45);
        gfx_palette[100 + GCOL_BACKGROUND_SECONDARY] = gfx_RGBTo1555(0, 0, 0);
        gfx_palette[100 + GCOL_TEXT_PRIMARY] = gfx_RGBTo1555(245, 245, 245);
        gfx_palette[100 + GCOL_TEXT_SECONDARY] = gfx_RGBTo1555(155, 155, 155);
        gfx_palette[100 + GCOL_BORDER] = gfx_RGBTo1555(70, 70, 70);
        gfx_palette[100 + GCOL_HEADER] = gfx_RGBTo1555(0, 0, 0);
    } else {
        gfx_palette[GCOL_BACKGROUND_PRIMARY] = gfx_RGBTo1555(45, 45, 45);
        gfx_palette[GCOL_BACKGROUND_SECONDARY] = gfx_RGBTo1555(0, 0, 0);
        gfx_palette[GCOL_TEXT_PRIMARY] = gfx_RGBTo1555(245, 245, 245);
        gfx_palette[GCOL_TEXT_SECONDARY] = gfx_RGBTo1555(155, 155, 155);
        gfx_palette[GCOL_BORDER] = gfx_RGBTo1555(70, 70, 70);
        gfx_palette[GCOL_HEADER] = gfx_RGBTo1555(0, 0, 0);
        gfx_palette[100 + GCOL_BACKGROUND_PRIMARY] = gfx_RGBTo1555(255, 255, 255);
        gfx_palette[100 + GCOL_BACKGROUND_SECONDARY] = gfx_RGBTo1555(240, 240, 240);
        gfx_palette[100 + GCOL_TEXT_PRIMARY] = gfx_RGBTo1555(0, 0, 0);
        gfx_palette[100 + GCOL_TEXT_SECONDARY] = gfx_RGBTo1555(180, 180, 180);
        gfx_palette[100 + GCOL_BORDER] = gfx_RGBTo1555(0, 0, 0);
        gfx_palette[100 + GCOL_HEADER] = gfx_RGBTo1555(255, 38, 88);
    }
    
    gfx_SetColor(GCOL_BACKGROUND_PRIMARY);
    
    gfx_SetTextConfig(gfx_text_clip);
    gfx_SetTextFGColor(GCOL_TEXT_PRIMARY);
    gfx_SetTextXY(MARGIN, MARGIN);
    
    gfx_FillScreen(GCOL_BACKGROUND_PRIMARY);
    
}

void gfx_print(const char* string, uint16_t x, uint16_t y) {
    gfx_SetTextXY(x, y);
    gfx_PrintString(string);
    gfx_SetTextXY(gfx_GetTextX() + gfx_GetStringWidth(string), y);
}

void gfx_print_justified(const char* string, justification x_justification, uint16_t x_offset, justification y_justification, uint16_t y_offset) {
    
    uint16_t x;
    uint16_t y;
    
    switch (x_justification) {
        case JUST_CENTER:
            x = (LCD_WIDTH - gfx_GetStringWidth(string)) / 2; break;
        case JUST_LEFT:
            x = MARGIN; break;
        case JUST_RIGHT:
            x = LCD_WIDTH - MARGIN - gfx_GetStringWidth(string); break;
        case JUST_NULL:
            x = 0;
        default:
            x = gfx_GetTextX() - x_offset; break;
    }
    
    x += x_offset;
    
    switch (y_justification) {
        case JUST_CENTER:
            y = (LCD_HEIGHT - FONT_HEIGHT) / 2; break;
        case JUST_TOP:
            y = MARGIN; break;
        case JUST_BOTTOM:
            y = LCD_HEIGHT - MARGIN - FONT_HEIGHT; break;
        case JUST_NULL:
            y = 0;
        default:
            y = gfx_GetTextY() - y_offset; break;
    }
    
    y += y_offset;
    
    gfx_SetTextXY(x, y);
    gfx_PrintString(string);
    
}

void gfx_print_line(const char* string, justification x_justification) {
    gfx_print_justified(string, x_justification, 0, JUST_NULL, 0);
    gfx_SetTextXY(MARGIN, gfx_GetTextY() + LINE_HEIGHT + FONT_HEIGHT);
}

void gfx_print_box(const char* string, uint16_t width, uint8_t line_height) {
    
    int i;
    int x = gfx_GetTextX();
    int y = gfx_GetTextY();
    int relative_x = 0;
    int relative_y = 0;
    int word_width = 0;
    char word_buffer[40];
    uint8_t word_buffer_position;
    
    if (width == 0) width = LCD_WIDTH - x - MARGIN;
    
    for (i = 0; string[i] != '\0'; i++) {
        
        word_buffer_position = 0;
        
        if (string[i] == '\\') {
            relative_x = width;
            i++;
        }
        
        for ( ; string[i] != ' ' && string[i] != '\0'; i++) {
            word_buffer[word_buffer_position] = string[i];
            word_buffer_position++;
        }
        
        word_buffer[word_buffer_position] = ' ';
        word_buffer[word_buffer_position + 1] = '\0';
        
        word_width = gfx_GetStringWidth(word_buffer);
        
        if (word_width > width - relative_x) {
            relative_x = 0;
            relative_y += FONT_HEIGHT + line_height;
        }
        
        gfx_print(word_buffer, relative_x + x, relative_y + y);
        relative_x += word_width;
        
        if (string[i] == '\0') break;
        
    }
    
    gfx_SetTextXY(relative_x + x, relative_y + y);
    
}

void print_character_wise(const char* string) {
    
    uint16_t i;
    
    for (i = 0; string[i] != '\0'; i++) {
        if (gfx_GetTextX() + gfx_GetCharWidth(string[i]) < LCD_WIDTH - MARGIN) {
            gfx_PrintChar(string[i]);
        } else {
            gfx_SetTextXY(MARGIN, gfx_GetTextY() + FONT_HEIGHT + LINE_HEIGHT);
            gfx_PrintChar(string[i]);
        }
    }
    
}

void draw_header(const char* left, const char* center, const char* right) {
    
    int8_t y_offset = (dark_mode) ? -5 : -3;
    
    gfx_SetColor(GCOL_HEADER);
    gfx_FillRectangle(0, 0, LCD_WIDTH, HEADER_HEIGHT);
    
    gfx_SetTextFGColor(GCOL_WHITE);
    
    if (left != NULL) {
        gfx_print_justified(left, JUST_LEFT, 0, JUST_TOP, y_offset);
    }
    
    if (center != NULL) {
        gfx_print_justified(center, JUST_CENTER, 0, JUST_TOP, y_offset);
    }
    
    if (right != NULL) {
        gfx_print_justified(right, JUST_RIGHT, 0, JUST_TOP, y_offset);
    }
    
}
