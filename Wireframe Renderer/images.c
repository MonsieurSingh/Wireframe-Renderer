//
//  images.c
//  Wireframe Renderer
//
//  Created by Teghjyot Singh on 8/11/2025.
//

#include "images.h"
#include "mlx.h"
#include <stdlib.h>
#include <string.h>

static size_t	g_img_capacity = 4;

void	image_init(t_data *data)
{
	int	i;

	i = 0;
	data->images = (t_image **)malloc(sizeof(t_image *) * (g_img_capacity + 1));
	while (i <= g_img_capacity)
		data->images[i++] = NULL;
}

void	image_add(t_data *data, int width, int height)
{
	int		i;

	i = 0;
	while (i < g_img_capacity && data->images[i])
		i++;
	data->images[i] = (t_image *)malloc(sizeof(t_image));
	data->images[i]->img = mlx_new_image(data->minilibx->mlx, width, height);
	data->images[i]->addr = mlx_get_data_addr(data->images[i]->img,
											  &data->images[i]->bits_per_pixel,
											  &data->images[i]->line_length,
											  &data->images[i]->endian);
	data->images[i]->width = width;
	data->images[i]->height = width;
}

void	image_destroy_all(t_data *data)
{
	int		i;
	
	i = 0;
	while (i < g_img_capacity && data->images[i] != NULL)
	{
		mlx_destroy_image(data->minilibx->mlx, data->images[i]);
		i++;
	}
}
