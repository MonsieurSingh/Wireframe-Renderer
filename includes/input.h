//
//  input.h
//  Wireframe Renderer
//
//  Created by Teghjyot Singh on 11/11/2025.
//

#ifndef input_h
#define input_h

#include "wireframe.h"
#include <Carbon/Carbon.h>

int key_handler(int keycode, void *param);
int mouse_handler(int button, int x, int y, void *param);

#endif /* input_h */
