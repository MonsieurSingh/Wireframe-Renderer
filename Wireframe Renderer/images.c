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

// internal registry tracker
typedef struct s_image_entry
{
	t_image	*image;
	int		offset_x;
	int		offset_y;
	int		in_use;
}	t_image_entry;

static t_image_entry	*g_images = NULL;
static size_t			g_capacity = 0;

static int ensure_capacity(size_t needed)
{
	if (needed <= g_capacity)
		return EXIT_FAILURE;
	size_t new_cap = g_capacity ? g_capacity : 1;
	while (new_cap < needed)
		new_cap *= 2;
	t_image_entry *new_arr =
		(t_image_entry *)realloc(g_images, new_cap * sizeof(t_image_entry));
	if (!new_arr)
		return -1;
	if (new_cap > g_capacity)
		memset(new_arr + g_capacity, 0,
				(new_cap - g_capacity) * sizeof(t_image_entry));
	g_images = new_arr;
	g_capacity = new_cap;
	return EXIT_SUCCESS;
}

void images_init(t_data *d, size_t initial_capacity)
{
	(void)d;
	if (g_images)
		return;
	if (initial_capacity == 0)
		initial_capacity = 4;
	g_images = (t_image_entry *)calloc(initial_capacity, sizeof(t_image_entry));
	if (!g_images)
	{
		g_capacity = 0;
		return;
	}
	g_capacity = initial_capacity;
}

//	registers and creates an image at the given enum id
//	existing images for the given id will be destroyed and replaced

t_image *images_add(t_data *d, t_image_id id, int width, int height,
					int offset_x, int offset_y)
{
	t_image *img;

	if (!d || !d->minilibx || !d->minilibx->mlx)
		return NULL;
	if (ensure_capacity((size_t)id + 1))
		return NULL;
	if (g_images[id].in_use && g_images[id].image)
	{
		if (g_images[id].image->img)
			mlx_destroy_image(d->minilibx->mlx, g_images[id].image->img);
		free(g_images[id].image);
		g_images[id].image = NULL;
		g_images[id].in_use = 0;
	}
	img = (t_image *)malloc(sizeof(t_image));
	if (!img)
		return NULL;
	img->img = mlx_new_image(d->minilibx->mlx, width, height);
	if (!img->img)
	{
		free(img);
		return NULL;
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
								  &img->line_length, &img->endian);
	img->width = width;
	img->height = height;
	g_images[id].image = img;
	g_images[id].offset_x = offset_x;
	g_images[id].offset_y = offset_y;
	g_images[id].in_use = 1;
	return img;
}

t_image *images_get(t_image_id id)
{
	if (!g_images || id >= (t_image_id)g_capacity)
		return NULL;
	if (!g_images[id].in_use)
		return NULL;
	return g_images[id].image;
}

void images_draw_all(const t_data *d)
{
	if (!d || !d->minilibx || !d->minilibx->mlx || !d->minilibx->mlx_win || !g_images)
		return;
	for (size_t i = 0; i < g_capacity; ++i) {
		if (g_images[i].in_use && g_images[i].image && g_images[i].image->img) {
			mlx_put_image_to_window(d->minilibx->mlx, d->minilibx->mlx_win, g_images[i].image->img,
									g_images[i].offset_x, g_images[i].offset_y);
		}
	}
}

void images_free(t_data *d)
{
	if (!g_images)
		return;
	for (size_t i = 0; i < g_capacity; ++i) {
		if (g_images[i].in_use && g_images[i].image) {
			if (d && d->minilibx && d->minilibx->mlx && g_images[i].image->img) {
				mlx_destroy_image(d->minilibx->mlx, g_images[i].image->img);
			}
			free(g_images[i].image);
			g_images[i].image = NULL;
			g_images[i].in_use = 0;
		}
	}
	free(g_images);
	g_images = NULL;
	g_capacity = 0;
}
