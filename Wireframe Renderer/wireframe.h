//
//  wireframe.h
//  Wireframe Renderer
//
//  Created by Teghjyot Singh on 8/11/2025.
//

#ifndef wireframe_h
#define wireframe_h

#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <libc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_point
{
	int x;
	int y;
	int z;
	unsigned int color;
}	t_point;

typedef struct s_map
{
	int width;
	int height;
	int	default_color;
	t_point **points;
} t_map;

typedef struct s_map_parser
{
	FILE	*fp;		// file pointer
	t_map	*map;
	char	*line;		// line buffer
	size_t	cap;		// capacity
	ssize_t nread;		// bytes read
	int		width;		// map width detected
	int		height;		// map height detected
}	t_map_parser;

typedef struct s_vec3
{
	float x;
	float y;
	float z;
}	t_vec3;

typedef struct s_data
{
	t_map	*map;
}	t_data;

int		verify_input(int argc, const char *argv[], t_map **map);
int		create_points(const char *argv[], t_map **map);
void	print_map(t_map *map);

#endif /* wireframe_h */
