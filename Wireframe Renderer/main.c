//
//  main.c
//  Wireframe Renderer
//
//  Created by Teghjyot Singh on 8/11/2025.
//

#include "wireframe.h"

int main(int argc, const char * argv[])
{
	t_data data;

	bzero(&data, sizeof(t_data));
	if (verify_input(argc, argv, &data.map))
		return (EXIT_FAILURE);
	if (create_points(argv, &data.map))
		return EXIT_FAILURE;
	print_map(data.map);
	return (EXIT_SUCCESS);
}

t_vec3 project_point(int i, int j, t_map *map)
{
	t_vec3	v;

	v.x = j;
	v.y = i;
	v.z = map->points[i][j].z;
	return v;
}
