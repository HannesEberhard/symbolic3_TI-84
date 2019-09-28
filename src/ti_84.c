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

bool sleep_timer = false;

sk_key_t wait_for_any_keydown(void) {
    sk_key_t key;
    while (!(key = os_GetCSC()));
    return key;
}

void wait_for_keydown(sk_key_t key) {
    while (os_GetCSC() != key);
    return;
}

void wait_for_any_key_release(void) {
    while (os_GetCSC());
    return;
}

sk_key_t wait_for_any_keyup(void) {
    sk_key_t key;
    while (!(key = os_GetCSC()));
    wait_for_any_key_release();
    return key;
}

void wait_for_keyup(sk_key_t key) {
    while (os_GetCSC() != key);
    wait_for_any_key_release();
    return;
}

void set_setting(uint8_t position, bool value) {
    
    ti_var_t var;
    settings data;
    
    uint8_t bit = (value) ? 1 : 0;
    
    ti_CloseAll();
    
    var = ti_Open("C3_SET", "r");
    ti_Read(&data, sizeof(settings), 1, var);
    ti_CloseAll();
    
    data.data = (data.data & ~(1 << position)) | (bit << position);
    
    var = ti_Open("C3_SET", "w");
    ti_Write(&data, sizeof(settings), 1, var);
    gfx_End();
    ti_SetArchiveStatus(true, var);
    gfx_Begin();
    gfx_init();
    ti_CloseAll();
    
    return;
    
}

bool get_setting(uint8_t position) {
    
    ti_var_t var;
    settings data;
    
    var = ti_Open("C3_SET", "r");
    ti_Read(&data, sizeof(settings), 1, var);
    ti_CloseAll();
    
    if ((data.data & (1 << position)) == 0) {
        return false;
    } else {
        return true;
    }
    
}
