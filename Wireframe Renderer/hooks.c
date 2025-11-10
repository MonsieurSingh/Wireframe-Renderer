//
//  hooks.c
//  Wireframe Renderer
//
//  Created by Teghjyot Singh on 9/11/2025.
//

#include "wireframe.h"

int loop_handler(void *param)
{
	t_data *data;
	
	data = (t_data *)param;
	render(data);
	return (EXIT_SUCCESS);
}

int exit_handler(void *param)
{
	exit(EXIT_SUCCESS);
}
