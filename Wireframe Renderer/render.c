//
//  render.c
//  Wireframe Renderer
//
//  Created by Teghjyot Singh on 8/11/2025.
//

#include "render.h"
#include "wireframe.h"

t_vec3 project_point(int i, int j, t_map *map)
{
	t_vec3	v;
	
	v.x = j;
	v.y = i;
	v.z = map->points[i][j].z;
	return v;
}

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char *dst;
	
	if (x >= 0 && x < image->width && y >= 0 && y < image->height)
	{
		dst = image->addr + (y * image->line_length + x *
							 (image->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}
