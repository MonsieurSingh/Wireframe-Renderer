//
//  input.c
//  Wireframe Renderer
//
//  Created by Teghjyot Singh on 11/11/2025.
//

#include "input.h"

int key_handler(int keycode, void *param)
{
	t_data	*d;
	t_model		model;
	t_camera	cam;

	d = (t_data *)param;
	model = d->state.model;
	cam = d->state.camera;
	if (keycode == kVK_ANSI_W) model.rotate.x -= 0.05f;
	if (keycode == kVK_ANSI_S) model.rotate.x += 0.05f;
	if (keycode == kVK_ANSI_A) model.rotate.y -= 0.05f;
	if (keycode == kVK_ANSI_D) model.rotate.y += 0.05f;
	if (keycode == kVK_ANSI_Q) model.rotate.z -= 0.05f;
	if (keycode == kVK_ANSI_E) model.rotate.z += 0.05f;

	if (keycode == kVK_ANSI_1) cam.target.x -= 0.05f;
	if (keycode == kVK_ANSI_2) cam.target.x += 0.05f;
	if (keycode == kVK_ANSI_3) cam.target.y -= 0.05f;
	if (keycode == kVK_ANSI_4) cam.target.y += 0.05f;
	if (keycode == kVK_ANSI_5) cam.target.z -= 0.05f;
	if (keycode == kVK_ANSI_6) cam.target.z += 0.05f;
	
	if (keycode == kVK_ANSI_Z) cam.eye.x -= 0.05f;
	if (keycode == kVK_ANSI_X) cam.eye.x += 0.05f;
	if (keycode == kVK_ANSI_C) cam.eye.y -= 0.05f;
	if (keycode == kVK_ANSI_V) cam.eye.y += 0.05f;
	if (keycode == kVK_ANSI_B) cam.eye.z -= 0.05f;
	if (keycode == kVK_ANSI_N) cam.eye.z += 0.05f;

	if (keycode == kVK_LeftArrow) model.translate.x -= 5.00f;
	if (keycode == kVK_RightArrow) model.translate.x += 5.00f;
	if (keycode == kVK_UpArrow) model.translate.y -= 5.00f;
	if (keycode == kVK_DownArrow) model.translate.y += 5.00f;
	if (keycode == kVK_ANSI_Period) model.translate.z -= 5.00f;
	if (keycode == kVK_ANSI_Comma) model.translate.z += 5.00f;
	if (keycode == kVK_ANSI_1) model.scale.y -= 0.05f;
	if (keycode == kVK_ANSI_2) model.scale.y += 0.05f;
	if (keycode == kVK_ANSI_3) model.scale.x -= 0.05f;
	if (keycode == kVK_ANSI_4) model.scale.x += 0.05f;
	if (keycode == kVK_ANSI_Minus) model.scale.z -= 0.05f;
	if (keycode == kVK_ANSI_Equal) model.scale.z += 0.05f;
	return 0;
}

int mouse_handler(int button, int x, int y, void *param)
{
	t_data	*d;
	t_model	model;

	d = (t_data *)param;
	model = d->state.model;
	if (button == 4)
	{
		model.scale.x += 0.05;
		model.scale.y += 0.05;
	}
	else if (button == 5)
	{
		model.scale.x -= 0.05;
		model.scale.y -= 0.05;
	}
	return 0;
}
