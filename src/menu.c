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

menu_item* new_menu_item(char* title, char* indicator) {
    
    menu_item* result = calloc(1, sizeof(menu_item));
    
    if (result == NULL) {
    }
    
    result->title = title;
    result->indicator = indicator;
    
    return result;
}

menu_tab* new_menu_tab(char* title, uint8_t item_count, ...) {
    
    uint8_t i;
    va_list arguments;
    menu_tab* result = calloc(1, sizeof(menu_tab));
    
    if (result == NULL) {
    }
    
    result->title = title;
    result->item_count = item_count;
    
    va_start(arguments, item_count);
    
    for (i = 0; i < item_count; i++) {
        result->items[i] = va_arg(arguments, menu_item*);
    }
    
    va_end(arguments);
    
    return result;
    
}

menu* new_menu(uint8_t tab_count, ...) {
    
    uint8_t i;
    va_list arguments;
    menu* result = calloc(1, sizeof(menu));
    
    if (result == NULL) {
    }
    
    va_start(arguments, tab_count);
    
    result->tab_count = tab_count;
    
    for (i = 0; i < tab_count; i++) {
        result->tabs[i] = va_arg(arguments, menu_tab*);
    }
    
    va_end(arguments);
    
    return result;
    
}

void free_menu(menu* source) {
    
    uint8_t i, j;
    
    for (i = 0; i < source->tab_count; i++) {
        for (j = 0; j < source->tabs[i]->item_count; j++) {
            free(source->tabs[i]->items[j]);
        }
        free(source->tabs[i]);
    }
    
    free(source);
    
    return;
    
}

void draw_menu(menu* source, uint8_t selected_tab, uint8_t selected_item) {
    
    uint8_t i;
    uint16_t header_width = LCD_WIDTH / source->tab_count;
    
    gfx_FillScreen(GCOL_BACKGROUND_PRIMARY);
    
    gfx_SetColor(GCOL_HEADER);
    gfx_FillRectangle(0, 0, LCD_WIDTH, HEADER_HEIGHT);
    
    if (source->tab_count > 1) {
        for (i = 0; i < source->tab_count; i++) {
            if (selected_tab == i) {
                gfx_SetTextFGColor(GCOL_SYMBOLIC3);
                gfx_SetColor(GCOL_BACKGROUND_PRIMARY);
                gfx_FillRectangle(i * header_width, 0, header_width, HEADER_HEIGHT);
            } else {
                gfx_SetTextFGColor(GCOL_WHITE);
            }
            gfx_print(source->tabs[i]->title, header_width * i + (header_width - gfx_GetStringWidth(source->tabs[i]->title)) / 2, (HEADER_HEIGHT - FONT_HEIGHT) / 2);
        }
    } else {
        gfx_print(source->tabs[0]->title, (header_width - gfx_GetStringWidth(source->tabs[0]->title)) / 2, (HEADER_HEIGHT - FONT_HEIGHT) / 2);
    }
    
    gfx_SetColor(GCOL_BACKGROUND_SECONDARY);
    
    for (i = 0; i < source->tabs[selected_tab]->item_count; i++) {
        
        if (i % 2 == 1) {
            gfx_FillRectangle(0, (1.5 + i) * HEADER_HEIGHT, LCD_WIDTH, HEADER_HEIGHT);
        }
        
        if (selected_item == i) {
            gfx_SetTextFGColor(GCOL_SYMBOLIC3);
        } else {
            gfx_SetTextFGColor(GCOL_TEXT_PRIMARY);
        }
        
        gfx_SetTextXY(MARGIN, (1.5 + i) * HEADER_HEIGHT + (HEADER_HEIGHT - FONT_HEIGHT) / 2);
        if (i < 10) gfx_PrintInt(i + 1, 0);
        gfx_print_justified(source->tabs[selected_tab]->items[i]->title, JUST_LEFT, 1.5 * MARGIN, JUST_NULL, 0);
        gfx_print_justified(source->tabs[selected_tab]->items[i]->indicator, JUST_RIGHT, 0, JUST_NULL, 0);
        
    }
    
    return;
    
}

uint8_t handle_menu(menu* source, uint8_t* selected_tab, uint8_t* selected_item) {
    
    sk_key_t key;
    
    while (true) {
        
        draw_menu(source, *selected_tab, *selected_item);
        key = wait_for_any_keyup();
        
        switch (key) {
            case sk_Enter:
                return RETS_SUCCESS;
            case sk_Clear:
                return RETS_ERROR;
            case sk_Add:
                return RETS_CHANGED;
            case sk_Up:
                if (*selected_item > 0) (*selected_item)--;
                break;
            case sk_Down:
                if (*selected_item < source->tabs[*selected_tab]->item_count - 1) (*selected_item)++;
                break;
            case sk_Left:
                if (*selected_tab > 0) (*selected_tab)--;
                *selected_item = 0;
                break;
            case sk_Right:
                if (*selected_tab < source->tab_count - 1) (*selected_tab)++;
                *selected_item = 0;
                break;
            case sk_Yequ:
                if (source->tab_count > 0) {
                    *selected_tab = 0;
                    *selected_item = 0;
                }
                break;
            case sk_Window:
                if (source->tab_count > 1) {
                    *selected_tab = 1;
                    *selected_item = 0;
                }
                break;
            case sk_Zoom:
                if (source->tab_count > 2) {
                    *selected_tab = 2;
                    *selected_item = 0;
                }
                break;
            case sk_Trace:
                if (source->tab_count > 3) {
                    *selected_tab = 3;
                    *selected_item = 0;
                }
                break;
            case sk_Graph:
                if (source->tab_count > 4) {
                    *selected_tab = 4;
                    *selected_item = 0;
                }
                break;
            case sk_1:
                if (source->tabs[*selected_tab]->item_count > 0) {
                    *selected_item = 0;
                    return RETS_SUCCESS;
                }
            case sk_2:
                if (source->tabs[*selected_tab]->item_count > 1) {
                    *selected_item = 1;
                    return RETS_SUCCESS;
                }
            case sk_3:
                if (source->tabs[*selected_tab]->item_count > 2) {
                    *selected_item = 2;
                    return RETS_SUCCESS;
                }
            case sk_4:
                if (source->tabs[*selected_tab]->item_count > 3) {
                    *selected_item = 3;
                    return RETS_SUCCESS;
                }
            case sk_5:
                if (source->tabs[*selected_tab]->item_count > 4) {
                    *selected_item = 4;
                    return RETS_SUCCESS;
                }
            case sk_6:
                if (source->tabs[*selected_tab]->item_count > 5) {
                    *selected_item = 5;
                    return RETS_SUCCESS;
                }
            case sk_7:
                if (source->tabs[*selected_tab]->item_count > 6) {
                    *selected_item = 6;
                    return RETS_SUCCESS;
                }
            case sk_8:
                if (source->tabs[*selected_tab]->item_count > 7) {
                    *selected_item = 7;
                    return RETS_SUCCESS;
                }
            case sk_9:
                if (source->tabs[*selected_tab]->item_count > 8) {
                    *selected_item = 8;
                    return RETS_SUCCESS;
                }
            default: break;
        }
        
    }
    
}

char* draw_handle_function_menu(uint8_t tab) {
    
    bool running = true;
    uint8_t selected_tab = tab;
    uint8_t selected_item = 0;
    char* result = calloc(10, sizeof(char));
    
    menu* menu_data = new_menu(4,
                               new_menu_tab("Algebra", 4,
                                            new_menu_item("simplify()", ""),
                                            new_menu_item("solve()", ""),
                                            new_menu_item("Factors()", ""),
                                            new_menu_item("Value()", "")),
                               new_menu_tab("Analysis", 5,
                                            new_menu_item("Derivative()", ""),
                                            new_menu_item("Integral()", ""),
                                            new_menu_item("Tangent()", ""),
                                            new_menu_item("Normal()", ""),
                                            new_menu_item("Angle()", "")),
                               new_menu_tab("Vector", 6,
                                            new_menu_item("VectorMagnitude()", ""),
                                            new_menu_item("VectorNormalized()", ""),
                                            new_menu_item("VectorAngle()", ""),
                                            new_menu_item("VectorDotProduct()", ""),
                                            new_menu_item("VectorCrossProduct()", ""),
                                            new_menu_item("VectorTripleProduct()", "")),
                               new_menu_tab("Misc", 6,
                                            new_menu_item("abs()", ""),
                                            new_menu_item("ln()", ""),
                                            new_menu_item("log()", ""),
                                            new_menu_item("sin(), cos(), tan()", ""),
                                            new_menu_item("arcsin(), arccos(), acrtan()", ""),
                                            new_menu_item("approximate()", ""),
                                            new_menu_item("List()", "")));
    
    memset(result, 0, 10);
    
    while (running) {
        switch (handle_menu(menu_data, &selected_tab, &selected_item)) {
                
            case RETS_SUCCESS:
                
                if (selected_tab == 0) {
                    switch (selected_item) {
                        case 0: strcpy(result, "simplify("); break;
                        case 1: strcpy(result, "solve("); break;
                        case 2: strcpy(result, "Fac("); break;
                        case 3: strcpy(result, "Val("); break;
                    }
                } else if (selected_tab == 1) {
                    switch (selected_item) {
                        case 0: strcpy(result, "Deriv("); break;
                        case 1: strcpy(result, "Int("); break;
                        case 2: strcpy(result, "Tang("); break;
                        case 3: strcpy(result, "Norm("); break;
                        case 4: strcpy(result, "Ang("); break;
                    }
                } else if (selected_tab == 2) {
                    switch (selected_item) {
                        case 0: strcpy(result, "VMag("); break;
                        case 1: strcpy(result, "VNormed("); break;
                        case 2: strcpy(result, "VAng("); break;
                        case 3: strcpy(result, "VDotP("); break;
                        case 4: strcpy(result, "VCrossP("); break;
                        case 5: strcpy(result, "VTripleP("); break;
                    }
                } else if (selected_tab == 3) {
                    switch (selected_item) {
                        case 0: strcpy(result, "abs("); break;
                        case 1: strcpy(result, "ln("); break;
                        case 2: strcpy(result, "log("); break;
                        case 3: strcpy(result, "sin("); break;
                        case 4: strcpy(result, "arcsin("); break;
                        case 5: strcpy(result, "approx("); break;
                        case 6: strcpy(result, "Ls("); break;
                    }
                }
                
                running = false;
                break;
                
            case RETS_CHANGED:
                break;
                
            case RETS_ERROR:
                running = false;
                break;
                
        }
    }
    
    free_menu(menu_data);
    
    return result;
    
}

char* draw_handle_history_menu(history* last_queries, uint8_t tab) {
    
    uint8_t i;
    uint8_t selected_tab = tab;
    uint8_t selected_item = 0;
    char* result = NULL;
    
    bool running = true;
    
    menu* menu_data = new_menu(2,
                               new_menu_tab("Queries", 0),
                               new_menu_tab("Results", 0));
    
    for (i = 0; i < last_queries->item_count; i++) {
        menu_data->tabs[0]->items[i] = new_menu_item(last_queries->items[i]->input, "");
        menu_data->tabs[1]->items[i] = new_menu_item(last_queries->items[i]->output, "");
    }
    
    menu_data->tabs[0]->item_count = last_queries->item_count;
    menu_data->tabs[1]->item_count = last_queries->item_count;
    
    while (running) {
        switch (handle_menu(menu_data, &selected_tab, &selected_item)) {
                
            case RETS_SUCCESS:
                if (selected_tab == 0) {
                    result = calloc(strlen(last_queries->items[selected_item]->input) + 1, sizeof(char));
                    memset(result, 0, strlen(last_queries->items[selected_item]->input) + 1);
                    strcpy(result, last_queries->items[selected_item]->input);
                } else {
                    result = calloc(strlen(last_queries->items[selected_item]->output) + 1, sizeof(char));
                    memset(result, 0, strlen(last_queries->items[selected_item]->output) + 1);
                    strcpy(result, last_queries->items[selected_item]->output);
                }
                running = false;
                break;
                
            case RETS_ERROR:
                result = calloc(1, sizeof(char));
                strcpy(result, "");
                running = false;
                break;
                
            case RETS_CHANGED:
                break;
                
        }
    }
    
    free_menu(menu_data);
    
    return result;
    
}

void draw_handle_mode_menu(void) {
    
    uint8_t selected_tab = 0;
    uint8_t selected_item = 0;
    
    bool running = true;
    
    menu* menu_data = new_menu(2,
                               new_menu_tab("About & Help", 2,
                                            new_menu_item("About", ""),
                                            new_menu_item("Terms", "")),
                               new_menu_tab("Settings", 3,
                                            new_menu_item("Dark Mode", (dark_mode) ? "Enabled" : "Disabled"),
                                            /* new_menu_item("Sleep Timer", (sleep_timer) ? "Enabled" : "Disabled"), */
                                            new_menu_item("Use Spaces", (use_spaces) ? "Enabled" : "Disabled"),
                                            new_menu_item("Reset", "")));
    
    while (running) {
        switch (handle_menu(menu_data, &selected_tab, &selected_item)) {
                
            case RETS_SUCCESS:
                
                if (selected_tab == 0) {
                    switch (selected_item) {
                        case 0: about(); break;
                        case 1: about_terms(); break;
                    }
                } else if (selected_tab == 1) {
                    switch (selected_item) {
                        case 0:
                            dark_mode = !dark_mode;
                            set_setting(0, dark_mode);
                            menu_data->tabs[1]->items[0]->indicator = (dark_mode) ? "Enabled" : "Disabled";
                            break;
                        /* case 1:
                            sleep_timer = !sleep_timer;
                            set_setting(1, sleep_timer);
                            menu_data->tabs[1]->items[1]->indicator = (sleep_timer) ? "Enabled" : "Disabled";
                            break; */
                        case 1:
                            use_spaces = !use_spaces;
                            set_setting(2, use_spaces);
                            menu_data->tabs[1]->items[1]->indicator = (use_spaces) ? "Enabled" : "Disabled";
                            break;
                        case 2:
                            ti_Delete("C3_SET");
                            ti_Delete("C3_HIST");
                            running = false;
                            break;
                    }
                }
                
                break;
                
            case RETS_ERROR:
                running = false;
                break;
                
            case RETS_CHANGED:
                break;
                
        }
    }
    
    free_menu(menu_data);
    
    return;
    
}
