//
//  free.c
//  Wireframe Renderer
//
//  Created by Teghjyot Singh on 8/11/2025.
//

#include "wireframe.h"

//	TODO: Add functions to destroy and kill processes
static void free_points_rows(t_map *map)
{
	if (!map || !map->points)
		return;
	for (int i = 0; i < map->height; ++i)
	{
		free(map->points[i]);
		map->points[i] = NULL;
	}
	free(map->points);
	map->points = NULL;
}

void free_points(t_map *map)
{
	if (!map)
		return;
	free_points_rows(map);
	map->width = 0;
	map->height = 0;
}
