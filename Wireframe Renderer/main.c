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
											 1920, 1200, "Wireframe Renderer");
	images_init(data, 2);
	images_add(data, 0, 1920, 1200, 0, 0);
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
	free_points(data.map);
	init(&data);
	mlx_loop(data.minilibx->mlx);
	images_free(&data);
	return (EXIT_SUCCESS);
}
