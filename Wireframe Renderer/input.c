//
//  input.c
//  Wireframe Renderer
//
//  Created by Teghjyot Singh on 11/11/2025.
//

#include "input.h"

int key_handler(int keycode, void *param)
{
	t_data *d = (t_data *)param;

	if (keycode == kVK_ANSI_W) d->xform.rotate.x -= 0.05f;
	if (keycode == kVK_ANSI_S) d->xform.rotate.x += 0.05f;
	if (keycode == kVK_ANSI_A) d->xform.rotate.y -= 0.05f;
	if (keycode == kVK_ANSI_D) d->xform.rotate.y += 0.05f;
	if (keycode == kVK_ANSI_Q) d->xform.rotate.z -= 0.05f;
	if (keycode == kVK_ANSI_E) d->xform.rotate.z += 0.05f;

	if (keycode == kVK_LeftArrow) d->xform.translate.x -= 5.00f;
	if (keycode == kVK_RightArrow) d->xform.translate.x += 5.00f;
	if (keycode == kVK_UpArrow) d->xform.translate.y -= 5.00f;
	if (keycode == kVK_DownArrow) d->xform.translate.y += 5.00f;
	if (keycode == kVK_ANSI_Period) d->xform.translate.z -= 5.00f;
	if (keycode == kVK_ANSI_Comma) d->xform.translate.z += 5.00f;
	if (keycode == kVK_ANSI_1) d->xform.scale.y -= 0.05f;
	if (keycode == kVK_ANSI_2) d->xform.scale.y += 0.05f;
	if (keycode == kVK_ANSI_3) d->xform.scale.x -= 0.05f;
	if (keycode == kVK_ANSI_4) d->xform.scale.x += 0.05f;
	if (keycode == kVK_ANSI_Minus) d->xform.scale.z -= 0.05f;
	if (keycode == kVK_ANSI_Equal) d->xform.scale.z += 0.05f;
	return 0;
}

int mouse_handler(int button, int x, int y, void *param)
{
	t_data	*d;

	d = (t_data *)param;
	if (button == 4)
	{
		d->xform.scale.x += 0.05;
		d->xform.scale.y += 0.05;
	}
	else if (button == 5)
	{
		d->xform.scale.x -= 0.05;
		d->xform.scale.y -= 0.05;
	}
	return 0;
}
