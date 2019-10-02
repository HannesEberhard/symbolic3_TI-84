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

sk_key_t key;
char input_buffer_left[INPUT_BUFFER_SIZE];
char input_buffer_right[INPUT_BUFFER_SIZE];
bool second_button_pressed;
bool alpha_button_pressed;
int8_t var1_position;
int8_t var2_position;

history* last_queries;
uint8_t selected_history_item = 0;

history_item* new_history_item(const char* input, const char* output) {
    history_item* result = calloc(1 , sizeof(history_item));
    result->input = calloc(sizeof(input) + 1, sizeof(char));
    result->output = calloc(sizeof(output) + 1, sizeof(char));
    strcpy(result->input, input);
    strcpy(result->output, output);
    return result;
}

void free_history_item(history_item* source) {
    free(source->input);
    free(source->output);
}

void free_history(history* source) {
    
    uint8_t i;
    
    for (i = 0; i < source->item_count; i++) {
        free_history_item(source->items[i]);
    }
    
    free(source);
    
}

void append_new_history_item(history* last_queries, const char* input, const char* output) {
    
    uint8_t i;
    
    if (last_queries->item_count == 10) {
        free_history_item(last_queries->items[9]);
        last_queries->item_count--;
    }

    for (i = last_queries->item_count; i > 0; i--) {
        last_queries->items[i] = last_queries->items[i - 1];
    }
    
    last_queries->items[0] = new_history_item(input, output);
    
    last_queries->item_count++;
    
}

void shift_char(char* a, char* b, int8_t direction) {
    
    char* temp = calloc(INPUT_BUFFER_SIZE, sizeof(char));
    char transfer;
    
    if (direction == 1 && strlen(b) > 0) {
        a[strlen(a) + 1] = '\0';
        a[strlen(a)] = b[0];
        strcpy(b, b + 1);
    } else if (direction == -1 && strlen(a) > 0) {
        transfer = a[strlen(a) - 1];
        a[strlen(a) - 1] = '\0';
        memmove(&b[1], b, strlen(b));
        b[0] = transfer;
    }
    
    free(temp);
    
}

uint8_t get_input(void) {
    
    char* function_menu_result;
    
    switch ((key = wait_for_any_keyup())) {
            
        case sk_Yequ:
            function_menu_result = draw_handle_function_menu(0);
            strcat(input_buffer_left, function_menu_result);
            free(function_menu_result);
            break;
        case sk_Window:
            function_menu_result = draw_handle_function_menu(1);
            strcat(input_buffer_left, function_menu_result);
            free(function_menu_result);
            break;
        case sk_Zoom:
            function_menu_result = draw_handle_function_menu(2);
            strcat(input_buffer_left, function_menu_result);
            free(function_menu_result);
            break;
        case sk_Trace:
            function_menu_result = draw_handle_function_menu(3);
            strcat(input_buffer_left, function_menu_result);
            free(function_menu_result);
            break;
        case sk_Graph: break;
            
        case sk_Up: strcat(input_buffer_left, draw_handle_history_menu(last_queries, 0)); break;
        case sk_Down: strcat(input_buffer_left, draw_handle_history_menu(last_queries, 1)); break;
        case sk_Right: shift_char(input_buffer_left, input_buffer_right, 1); break;
        case sk_Left: shift_char(input_buffer_left, input_buffer_right, -1); break;
            
        case sk_2nd:
            second_button_pressed = !second_button_pressed;
            alpha_button_pressed = false;
            break;
        case sk_Alpha:
            alpha_button_pressed = !alpha_button_pressed;
            second_button_pressed = false;
            break;
            
        case sk_Mode: draw_handle_mode_menu(); break;
        case sk_Del: input_buffer_left[strlen(input_buffer_left) - 1] = '\0'; break;
        case sk_GraphVar:
            if (var1_position != -1) input_buffer_left[strlen(input_buffer_left) - 1] = '\0';
            var1_position = (var1_position + 1) % 6;
            switch (var1_position) {
                case 0: strcat(input_buffer_left, "x"); break;
                case 1: strcat(input_buffer_left, "y"); break;
                case 2: strcat(input_buffer_left, "z"); break;
                case 3: strcat(input_buffer_left, "a"); break;
                case 4: strcat(input_buffer_left, "b"); break;
                case 5: strcat(input_buffer_left, "c"); break;
            }
            break;
        case sk_Stat: strcat(input_buffer_left, "Ls("); break;
            
        case sk_Math:
            if (alpha_button_pressed) {
                strcat(input_buffer_left, "a"); break;
            } else {
                function_menu_result = draw_handle_function_menu(0);
                strcat(input_buffer_left, function_menu_result);
                free(function_menu_result);
            }
            break;
        case sk_Apps: if (alpha_button_pressed) strcat(input_buffer_left, "b"); break;
        case sk_Prgm: if (alpha_button_pressed) strcat(input_buffer_left, "c"); break;
        case sk_Vars:
            if (var2_position != -1) input_buffer_left[strlen(input_buffer_left) - 1] = '\0';
            var2_position = (var2_position + 1) % 6;
            switch (var2_position) {
                case 0: strcat(input_buffer_left, "X"); break;
                case 1: strcat(input_buffer_left, "Y"); break;
                case 2: strcat(input_buffer_left, "Z"); break;
                case 3: strcat(input_buffer_left, "A"); break;
                case 4: strcat(input_buffer_left, "B"); break;
                case 5: strcat(input_buffer_left, "C"); break;
            }
            break;
            
        case sk_Power:
            if (second_button_pressed) {
                strcat(input_buffer_left, "pi");
            } else if (alpha_button_pressed) {
                strcat(input_buffer_left, "h");
            } else {
                strcat(input_buffer_left, "^");
            }
            break;
        case sk_Square:
            if (second_button_pressed) {
                strcat(input_buffer_left, "^(1/2)");
            } else if (alpha_button_pressed) {
                strcat(input_buffer_left, "i");
            } else {
                strcat(input_buffer_left, "^2");
            }
            break;
        case sk_Recip: strcat(input_buffer_left, (alpha_button_pressed) ? "d" : "^(-1)"); break;
            
        case sk_Sin:
            if (second_button_pressed) {
                strcat(input_buffer_left, "arcsin(");
            } else if (alpha_button_pressed) {
                strcat(input_buffer_left, "e");
            } else {
                strcat(input_buffer_left, "sin(");
            }
            break;
        case sk_Cos:
            if (second_button_pressed) {
                strcat(input_buffer_left, "arccos(");
            } else if (alpha_button_pressed) {
                strcat(input_buffer_left, "f");
            } else {
                strcat(input_buffer_left, "cos(");
            }
            break;
        case sk_Tan:
            if (second_button_pressed) {
                strcat(input_buffer_left, "arctan(");
            } else if (alpha_button_pressed) {
                strcat(input_buffer_left, "g");
            } else {
                strcat(input_buffer_left, "tan(");
            }
            break;
            
        case sk_Comma: strcat(input_buffer_left, (alpha_button_pressed) ? "j" : ","); break;
        case sk_LParen: strcat(input_buffer_left, (alpha_button_pressed) ? "k" : "("); break;
        case sk_RParen: strcat(input_buffer_left, (alpha_button_pressed) ? "l" : ")"); break;
            
        case sk_Log:
            if (second_button_pressed) {
                strcat(input_buffer_left, "10^");
            } else if (alpha_button_pressed) {
                strcat(input_buffer_left, "n");
            } else {
                strcat(input_buffer_left, "log(");
            }
            break;
        case sk_Ln:
            if (second_button_pressed) {
                strcat(input_buffer_left, "e^");
            } else if (alpha_button_pressed) {
                strcat(input_buffer_left, "s");
            } else {
                strcat(input_buffer_left, "ln(");
            }
            break;
            
        case sk_Add: strcat(input_buffer_left, "+"); break;
        case sk_Sub: strcat(input_buffer_left, (alpha_button_pressed) ? "w" : "-"); break;
        case sk_Mul: strcat(input_buffer_left, (alpha_button_pressed) ? "r" : "*"); break;
        case sk_Div:
            if (second_button_pressed) {
                strcat(input_buffer_left, "e");
            } else if (alpha_button_pressed) {
                strcat(input_buffer_left, "m");
            } else {
                strcat(input_buffer_left, "/");
            }
            break;
            
        case sk_0: strcat(input_buffer_left, (alpha_button_pressed) ? " " : "0"); break;
        case sk_1: strcat(input_buffer_left, (alpha_button_pressed) ? "y" : "1"); break;
        case sk_2: strcat(input_buffer_left, (alpha_button_pressed) ? "z" : "2"); break;
        case sk_3: strcat(input_buffer_left, "3"); break;
        case sk_4: strcat(input_buffer_left, (alpha_button_pressed) ? "t" : "4"); break;
        case sk_5: strcat(input_buffer_left, (alpha_button_pressed) ? "u" : "5"); break;
        case sk_6: strcat(input_buffer_left, (alpha_button_pressed) ? "v" : "6"); break;
        case sk_7: strcat(input_buffer_left, (alpha_button_pressed) ? "o" : "7"); break;
        case sk_8: strcat(input_buffer_left, (alpha_button_pressed) ? "p" : "8"); break;
        case sk_9: strcat(input_buffer_left, (alpha_button_pressed) ? "q" : "9"); break;
            
        case sk_Chs: strcat(input_buffer_left, "-"); break;
        case sk_DecPnt: strcat(input_buffer_left, (second_button_pressed) ? "i" : "."); break;
            
        case sk_Enter: return RETS_SUCCESS; break;
        case sk_Clear:
            if (strlen(input_buffer_left) == 0 && strlen(input_buffer_right) == 0) {
                return RETS_ERROR;
            } else {
                memset(input_buffer_left, 0, INPUT_BUFFER_SIZE);
                memset(input_buffer_right, 0, INPUT_BUFFER_SIZE);
            }
            break;
        case sk_Store: strcat(input_buffer_left, (alpha_button_pressed) ? "x" : "="); break;
            
    }
    
    if (key != sk_GraphVar) {
        var1_position = -1;
    }
    
    if (key != sk_Vars) {
        var2_position = -1;
    }
    
    if (key != sk_2nd) {
        second_button_pressed = false;
    }
    
    if (key != sk_Alpha) {
        alpha_button_pressed = false;
    }
    
    return RETS_CHANGED;
    
}

uint8_t handle_draw_input(void) {
    
    bool is_running = true;
    char input_buffer[2 * INPUT_BUFFER_SIZE];
    char result[2 * INPUT_BUFFER_SIZE];
    return_status status = RETS_NULL;

    memset(input_buffer_left, 0, INPUT_BUFFER_SIZE);
    memset(input_buffer_right, 0, INPUT_BUFFER_SIZE);
    memset(input_buffer, 0, INPUT_BUFFER_SIZE);

    last_queries = calloc(1, sizeof(history));

    second_button_pressed = false;
    alpha_button_pressed = false;

    var1_position = -1;
    var2_position = -1;

    last_queries->item_count = 0;

    while (is_running) {

        if (status != RETS_NULL) status = get_input();

        gfx_FillScreen(GCOL_BACKGROUND_PRIMARY);
        draw_header("symbolic3", "", "Computer Algebra");

        gfx_SetTextXY(MARGIN, 40);
        gfx_SetTextFGColor(GCOL_TEXT_PRIMARY);
        print_character_wise(input_buffer_left);

        if (second_button_pressed) {
            gfx_SetTextFGColor(GCOL_BLUE);
        } else if (alpha_button_pressed) {
            gfx_SetTextFGColor(GCOL_GREEN);
        } else {
            gfx_SetTextFGColor(GCOL_SYMBOLIC3);
        }

        print_character_wise(" | ");

        gfx_SetTextFGColor(GCOL_TEXT_PRIMARY);
        print_character_wise(input_buffer_right);

        if (status == RETS_SUCCESS && (strlen(input_buffer_left) > 0 || strlen(input_buffer_right) > 0)) {
            
            memset(input_buffer, 0, 2 * INPUT_BUFFER_SIZE);
            strcat(input_buffer, input_buffer_left);
            strcat(input_buffer, input_buffer_right);
            
            memset(result, 0, 2 * INPUT_BUFFER_SIZE);
            
            if (symbolic4(result, input_buffer) == RETS_SUCCESS) {
                gfx_SetTextXY(MARGIN, gfx_GetTextY() + 20);
                gfx_SetTextFGColor(GCOL_SYMBOLIC3);
                print_character_wise(result);
                append_new_history_item(last_queries, input_buffer, result);
            } else {
                gfx_SetTextXY(MARGIN, gfx_GetTextY() + 20);
                gfx_SetTextFGColor(GCOL_TEXT_PRIMARY);
                print_character_wise("ERROR");
            }
            
        } else if (status == RETS_ERROR) {
            is_running = false;
        }

        status = RETS_CHANGED;

    }
    
    return RETS_SUCCESS;
    
}
