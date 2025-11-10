//
//  render.c
//  Wireframe Renderer
//
//  Created by Teghjyot Singh on 8/11/2025.
//

#include "render.h"
#include "wireframe.h"
#include "images.h"
#include <math.h>

int interpolateColor(int color1, int color2, float t)
{
	int r1 = (color1 >> 16) & 0xFF;
	int g1 = (color1 >> 8) & 0xFF;
	int b1 = color1 & 0xFF;
	
	int r2 = (color2 >> 16) & 0xFF;
	int g2 = (color2 >> 8) & 0xFF;
	int b2 = color2 & 0xFF;
	
	int r = r1 + (r2 - r1) * t;
	int g = g1 + (g2 - g1) * t;
	int b = b1 + (b2 - b1) * t;
	
	return (r << 16) | (g << 8) | b;
}

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


void plotLine(t_image *image, int x0, int y0, int x1, int y1, int color1, int color2)
{
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = dx + dy, e2;
	
	int total_distance = abs(x1 - x0) + abs(y1 - y0);
	
	while (1)
	{
		float t = (float)(abs(x0 - x1) + abs(y0 - y1)) / total_distance;
		int color = interpolateColor(color1, color2, t);
		my_mlx_pixel_put(image, x0, y0, color);
		if (x0 == x1 && y0 == y1) break;
		
		e2 = 2 * err;
		if (e2 >= dy) { err += dy; x0 += sx; }
		if (e2 <= dx) { err += dx; y0 += sy; }
	}
}

int	render(void *d)
{
	t_data	*data;
	t_image	*img;
	int		scale;

	data = d;
	scale = 20;
	img = images_get(IMG_MAIN);
	for (int y = 0; y < (img->height / scale) - 1; y++) {
		for (int x = 0; x < (img->width / scale) - 1; x++) {
			plotLine(img, x * scale, y * scale, (x + 1) * scale, y * scale, 0x00FFFFFF, 0x00FFFFFF);
			plotLine(img, x * scale, y * scale, (x + 1) * scale, y * scale, 0x00FFFFFF, 0x00FFFFFF);
			plotLine(img, x * scale, y * scale, x * scale, (y + 1) * scale, 0x00FFFFFF, 0x00FFFFFF);
			plotLine(img, x * scale, (y + 1) * scale, (x + 1) * scale, y * scale, 0x00FFFFFF, 0x00FFFFFF);
			if (x + 1 == (img->width / scale) - 1)
				plotLine(img, (x + 1) * scale, y * scale, (x + 1) * scale, (y + 1) * scale, 0x00FFFFFF, 0x00FFFFFF);
			if (y + 1 == (img->height / scale) - 1)
				plotLine(img, x * scale, (y + 1) * scale, (x + 1) * scale, (y + 1) * scale, 0x00FFFFFF, 0x00FFFFFF);
		}
	}
	images_draw_all(data);
	return EXIT_SUCCESS;
}
