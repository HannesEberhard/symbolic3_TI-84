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

#ifndef menu_h
#define menu_h

#include "includes.h"

typedef struct {
    char* title;
    char* indicator;
} menu_item;

typedef struct {
    char* title;
    uint8_t item_count;
    menu_item* items[15];
} menu_tab;

typedef struct {
    uint8_t tab_count;
    menu_tab* tabs[5];
} menu;

menu_item* new_menu_item(char* title, char* indicator);
menu_tab* new_menu_tab(char* title, uint8_t item_count, ...);
menu* new_menu(uint8_t tab_count, ...);
void free_menu(menu* source);
void draw_menu(menu* source, uint8_t selected_tab, uint8_t selected_item);
uint8_t handle_menu(menu* source, uint8_t* selected_tab, uint8_t* selected_item);
char* draw_handle_function_menu(uint8_t tab);
char* draw_handle_history_menu(history* last_queries, uint8_t tab);
void draw_handle_mode_menu(void);

#endif /* menu_h */
