//
//  ui.c
//  Wireframe Renderer
//
//  Created by Teghjyot Singh on 11/11/2025.
//

#include "ui.h"
#include <stdio.h>
#include <stdlib.h>

static void put_info(t_mlx *minilibx, t_transform *xform, int dx, int dy)
{
	//TODO
}

void	put_ui(t_data *data)
{
	
	put_info(data->minilibx, &data->xform, 10, 10);
}
