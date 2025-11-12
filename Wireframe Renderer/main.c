//
//  main.c
//  Wireframe Renderer
//
//  Created by Teghjyot Singh on 8/11/2025.
//

#include "wireframe.h"
#include "images.h"
#include "input.h"

void init(t_data *data)
{
	data->minilibx = (t_mlx *)malloc(sizeof(t_mlx));
	data->minilibx->mlx = mlx_init();
	if (data->minilibx->mlx == NULL)
		exit(EXIT_FAILURE);
	data->minilibx->mlx_win = mlx_new_window(data->minilibx->mlx,
											 1000, 1000, "Wireframe Renderer");
	image_init(data);
	image_add(data, 600, 600);
	data->state.model = (t_model){{ 10, 10, 0 }, { 0, 0, 0 }, { 1, 1, 1 }};
	data->state.camera = (t_camera){{ 0.0f, 0.0f, 5.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }};
}

int main(int argc, const char * argv[])
{
	t_data data;

	bzero(&data, sizeof(t_data));
	if (verify_input(argc, argv, &data.map))
		return (EXIT_FAILURE);
	if (create_points(argv, &data.map))
		return EXIT_FAILURE;
	print_map(data.map);
	init(&data);
	mlx_hook(data.minilibx->mlx_win, 17, 0, exit_handler, &data);
	mlx_loop_hook(data.minilibx->mlx, loop_handler, &data);
	mlx_hook(data.minilibx->mlx_win, 2, 1L << 0, (int (*)(void *))key_handler, &data);
	mlx_hook(data.minilibx->mlx_win, 4, 1L << 2, (int (*)(void *))mouse_handler, &data);
	mlx_loop(data.minilibx->mlx);
	mlx_do_sync(data.minilibx->mlx);
	free_points(data.map);
	return (EXIT_SUCCESS);
}
