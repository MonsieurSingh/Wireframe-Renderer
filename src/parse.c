//
//  parse.c
//  Wireframe Renderer
//
//  Created by Teghjyot Singh on 8/11/2025.
//

#include "wireframe.h"

// tok = "zz,0XTTRRBBGG\0" changes to:
// tok = "zz\00XTTRRBBGG\0" where comma + 1 = "0XTTRRBBGG\0"
static int parse_z_color(char *comma, unsigned int *out_color,
						 int *out_z, const char *tok)
{
	char		*endp;
	long		z;
	const char	*cstr;

	*comma = '\0';
	z = strtoimax(tok, &endp, 10);
	if (endp == tok || *endp != '\0')
		return -1;
	*out_z = (int)z;
	cstr = comma + 1;
	*out_color = (unsigned int)strtoull(cstr, &endp, 16);
	return EXIT_SUCCESS;
}

static int parse_z(int *out_z, const char *tok)
{
	char	*endp;

	endp = NULL;
	long z = strtol(tok, &endp, 10);
	if (endp == tok)
		return -1;
	*out_z = (int)z;
	return EXIT_SUCCESS;
}

// token = "z" or "z,0xTTRRGGBB"
static int split_token(const char *tok, int *out_z, unsigned int *out_color)
{
	char	*comma;

	if (tok == NULL || *tok == '\0')
		return -1;
	comma = strchr(tok, ',');
	if (comma)
		parse_z_color(comma, out_color, out_z, tok);
	else
		parse_z(out_z, tok);
	return EXIT_SUCCESS;
}

static int parse_line(FILE *fp, char *line, t_map **map, int row) {
	int				column;
	char			*cursor;
	char			*tok;
	int				z;
	unsigned int	color;

	cursor = line;
	column = 0;
	while (column < (*map)->width && (tok = strtok(cursor, " \t\n;")) != NULL)
	{
		color = (*map)->default_color;
		if (split_token(tok, &z, &color))
		{
			free(line);
			fclose(fp);
			return EXIT_FAILURE;
		}
		(*map)->points[row][column] =
		(t_point) {.x = column, .y = row, .z = z, .color = color };
		column++;
		cursor = NULL;
	}
	return EXIT_SUCCESS;
}

static int fill_points(FILE *fp, t_map **map)
{
	char	*line;
	size_t	cap;
	ssize_t	nread;
	int		row;

	line = NULL;
	cap = 0;
	row = 0;
	while (row < (*map)->height && (nread = getline(&line, &cap, fp)) != -1)
	{
		if (parse_line(fp, line, map, row))
			return EXIT_FAILURE;
		row++;
	}
	free(line);
	fclose(fp);
	if (row != (*map)->height)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

static int allocate_points(FILE *fp, t_map **map)
{
	(*map)->points = (t_point **)calloc((size_t)(*map)->height, sizeof(t_point *));
	if (!(*map)->points)
	{
		fprintf(stderr, "out of memory\n");
		fclose(fp);
		return EXIT_FAILURE;
	}
	for (int row = 0; row < (*map)->height; ++row)
	{
		(*map)->points[row] = (t_point *)calloc((size_t)(*map)->width, sizeof(t_point));
		if (!(*map)->points[row])
		{
			fprintf(stderr, "out of memory\n");
			fclose(fp);
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}

int create_points(const char *argv[], t_map **map)
{
	const char	*path;
	FILE		*fp;

	if (map == NULL || *map == NULL)
		return EXIT_FAILURE;
	path = argv[1];
	fp = fopen(path, "r");
	if (!fp)
	{
		fprintf(stderr, "%s: %s\n", path, strerror(errno));
		return EXIT_FAILURE;
	}
	if (allocate_points(fp, map))
		return EXIT_FAILURE;
	if (fill_points(fp, map))
		return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

void	print_map(t_map *map)
{
	for (int i = 0; i < map->height; i++)
	{
		for (int j = 0; j < map->width; j++)
		{
			printf("%#010x ", map->points[i][j].color);
		}
		printf("\n");
	}
	for (int i = 0; i < map->height; i++)
	{
		for (int j = 0; j < map->width; j++)
		{
			printf("%3hd", map->points[i][j].z);
		}
		printf("\n");
	}
}
