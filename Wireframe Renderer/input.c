//
//  input.c
//  Wireframe Renderer
//
//  Created by Teghjyot Singh on 11/11/2025.
//

#include "input.h"

//	TODO: A more intuitive method with modifier keys
int key_handler(int keycode, void *param)
{
	t_data *d = (t_data *)param;

	if (keycode == kVK_ANSI_W) d->state.model.rotate.x -= 0.05f;
	if (keycode == kVK_ANSI_S) d->state.model.rotate.x += 0.05f;
	if (keycode == kVK_ANSI_A) d->state.model.rotate.y -= 0.05f;
	if (keycode == kVK_ANSI_D) d->state.model.rotate.y += 0.05f;
	if (keycode == kVK_ANSI_Q) d->state.model.rotate.z -= 0.05f;
	if (keycode == kVK_ANSI_E) d->state.model.rotate.z += 0.05f;
	
	if (keycode == kVK_ANSI_1) d->state.camera.target.x -= 0.05f;
	if (keycode == kVK_ANSI_2) d->state.camera.target.x += 0.05f;
	if (keycode == kVK_ANSI_3) d->state.camera.target.y -= 0.05f;
	if (keycode == kVK_ANSI_4) d->state.camera.target.y += 0.05f;
	if (keycode == kVK_ANSI_5) d->state.camera.target.z -= 0.05f;
	if (keycode == kVK_ANSI_6) d->state.camera.target.z += 0.05f;
	
	if (keycode == kVK_ANSI_Z) d->state.camera.eye.x -= 0.05f;
	if (keycode == kVK_ANSI_X) d->state.camera.eye.x += 0.05f;
	if (keycode == kVK_ANSI_C) d->state.camera.eye.y -= 0.05f;
	if (keycode == kVK_ANSI_V) d->state.camera.eye.y += 0.05f;
	if (keycode == kVK_ANSI_B) d->state.camera.eye.z -= 0.05f;
	if (keycode == kVK_ANSI_N) d->state.camera.eye.z += 0.05f;
	
	if (keycode == kVK_LeftArrow) d->state.model.translate.x -= 5.00f;
	if (keycode == kVK_RightArrow) d->state.model.translate.x += 5.00f;
	if (keycode == kVK_UpArrow) d->state.model.translate.y -= 5.00f;
	if (keycode == kVK_DownArrow) d->state.model.translate.y += 5.00f;
	if (keycode == kVK_ANSI_Period) d->state.model.translate.z -= 5.00f;
	if (keycode == kVK_ANSI_Comma) d->state.model.translate.z += 5.00f;
	
	if (keycode == kVK_ANSI_1) d->state.model.scale.y -= 0.05f;
	if (keycode == kVK_ANSI_2) d->state.model.scale.y += 0.05f;
	if (keycode == kVK_ANSI_3) d->state.model.scale.x -= 0.05f;
	if (keycode == kVK_ANSI_4) d->state.model.scale.x += 0.05f;
	if (keycode == kVK_ANSI_Minus) d->state.model.scale.z -= 0.05f;
	if (keycode == kVK_ANSI_Equal) d->state.model.scale.z += 0.05f;

	return 0;
}

int mouse_handler(int button, int x, int y, void *param)
{
	t_data	*d;

	d = (t_data *)param;
	if (button == 4)
	{
		d->state.model.scale.x += 0.05;
		d->state.model.scale.y += 0.05;
	}
	else if (button == 5)
	{
		d->state.model.scale.x -= 0.05;
		d->state.model.scale.y -= 0.05;
	}
	return 0;
}
