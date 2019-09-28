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

void press_clear_to_exit(void) {
    gfx_print_justified("Press [CLEAR] to exit", JUST_LEFT, 0, JUST_BOTTOM, 0);
    wait_for_keyup(sk_Clear);
}

void setup(void) {
    
    dark_mode = get_setting(0);
    sleep_timer = get_setting(1);
    use_spaces = get_setting(2);
    
    return;
    
}

return_status terms(void) {
    
    gfx_FillScreen(GCOL_BACKGROUND_PRIMARY);
    
    gfx_SetTextFGColor(GCOL_SYMBOLIC3);
    gfx_SetTextXY(MARGIN, 20);
    gfx_print_line("smybolic3", JUST_LEFT);
    gfx_SetTextFGColor(GCOL_TEXT_SECONDARY);
    gfx_print_line(VERSION_STRING, JUST_LEFT);
    gfx_SetTextXY(MARGIN, gfx_GetTextY() + 7);
    gfx_SetTextFGColor(GCOL_TEXT_PRIMARY);
    gfx_print_line("Copyright (c) 2019 Hannes Eberhard", JUST_LEFT);
    gfx_SetTextXY(MARGIN, gfx_GetTextY() + 7);
    gfx_print_box("Press [ENTER] to accept the following terms or [CLEAR] to quit.", 0, LINE_HEIGHT - 2);
    gfx_SetTextXY(MARGIN, gfx_GetTextY() + FONT_HEIGHT + LINE_HEIGHT + 7);
    gfx_print_box("THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.", 0, LINE_HEIGHT - 2);
    
    while (true) {
        switch (wait_for_any_keyup()) {
            case sk_Enter: return RETS_SUCCESS;
            case sk_Clear: return RETS_ERROR;
        }
    }
    
    return RETS_SUCCESS;
    
}

void about(void) {
    
    gfx_FillScreen(GCOL_BACKGROUND_PRIMARY);
    
    gfx_SetTextFGColor(GCOL_SYMBOLIC3);
    gfx_SetTextXY(MARGIN, 20);
    gfx_print_line("smybolic3", JUST_LEFT);
    gfx_SetTextFGColor(GCOL_TEXT_SECONDARY);
    gfx_print_line(VERSION_STRING, JUST_LEFT);
    gfx_SetTextXY(MARGIN, gfx_GetTextY() + 7);
    gfx_SetTextFGColor(GCOL_TEXT_PRIMARY);
    gfx_print_line("Copyright  (c)  2019  Hannes  Eberhard", JUST_LEFT);
    gfx_SetTextXY(MARGIN, gfx_GetTextY() + 20);
    gfx_print_line("Help  &  contact:", JUST_LEFT);
    gfx_print_line("symbolic-3.web.app", JUST_LEFT);
    gfx_SetTextXY(MARGIN, gfx_GetTextY() + 25);
    gfx_print_box("The use of the 'CE-Programming  Toolchain'  (github.com/CE-Programming/toolchain), licensed  under the LGPL-3.0 license, is hereby acknowledged.", 0, LINE_HEIGHT);
    
    press_clear_to_exit();
    
    return;
    
}

void about_terms(void) {
    
    gfx_FillScreen(GCOL_BACKGROUND_PRIMARY);
    
    gfx_SetTextFGColor(GCOL_TEXT_PRIMARY);
    gfx_SetTextXY(MARGIN, 20);
    gfx_print_box("You've accepted the following terms:", 0, LINE_HEIGHT);
    gfx_SetTextXY(MARGIN, gfx_GetTextY() + FONT_HEIGHT + LINE_HEIGHT + 7);
    gfx_print_box("THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.", 0, LINE_HEIGHT);
    
    press_clear_to_exit();
    
    return;
    
}
