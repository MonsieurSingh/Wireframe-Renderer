//
//  main.c
//  Wireframe Renderer
//
//  Created by Teghjyot Singh on 8/11/2025.
//

#include "wireframe.h"
#include "images.h"

void init(t_data *data)
{
	data->minilibx = (t_mlx *)malloc(sizeof(t_mlx));
	data->minilibx->mlx = mlx_init();
	if (data->minilibx->mlx == NULL)
		exit(EXIT_FAILURE);
	data->minilibx->mlx_win = mlx_new_window(data->minilibx->mlx,
											 1000, 1000, "Wireframe Renderer");
	images_init(data, 2);
	images_add(data, IMG_MAIN, 600, 600, 200, 200);
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
	mlx_loop(data.minilibx->mlx);
	free_points(data.map);
	images_free(&data);
	return (EXIT_SUCCESS);
}
