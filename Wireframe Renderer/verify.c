//
//  verify.c
//  Wireframe Renderer
//
//  Created by Teghjyot Singh on 8/11/2025.
//

#include "wireframe.h"

static int	init_map_parser(t_map_parser *parser, FILE *fp, t_map *map)
{
	if (!parser || !fp || !map)
		return EXIT_FAILURE;
	parser->fp = fp;
	parser->map = map;
	parser->line = NULL;
	parser->cap = 0;
	parser->nread = 0;
	map->width = -1;
	map->height = 0;
	map->default_color = 0x00FFFFFF;
	return EXIT_SUCCESS;
}

static int	count_tokens_ws(const char *s)
{
	int	count;
	int	in_token;

	count = 0;
	in_token = 0;
	if (s == NULL)
		return 0;
	for (const char *p = s; *p; ++p)
	{
		if (isspace((unsigned char)*p))
			in_token = 0;
		else if (!in_token)
		{
			in_token = 1;
			++count;
		}
	}
	return count;
}

static int	skip_blank_lines(char *line, ssize_t nread)
{
	int only_ws;		// only whitespace

	only_ws = 1;
	for (ssize_t i = 0; i < nread; ++i)
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n' &&
			line[i] != '\r' && line[i] != '\v' && line[i] != '\f')
		{
			only_ws = 0;
			break;
		}
	}
	return (only_ws);
}

static int	process_map_lines(t_map_parser *parser)
{
	parser->line = NULL;
	parser->cap = 0;
	while ((parser->nread =
			getline(&parser->line, &parser->cap, parser->fp)) != -1)
	{
		if (skip_blank_lines(parser->line, parser->nread))
			continue;
		int tokens = count_tokens_ws(parser->line);
		if (tokens == 0)
			continue;
		if (parser->map->width == -1)
			parser->map->width = tokens;
		else if (tokens != parser->map->width)
		{
			free(parser->line);
			return EXIT_FAILURE; // non-rectangular map
		}
		parser->map->height++;
		free(parser->line);
		parser->line = NULL;
	}
	if (parser->map->width <= 0 || parser->map->height <= 0)
		return EXIT_FAILURE;
	free(parser->line);
	parser->line = NULL;
	parser->cap = 0;
	return EXIT_SUCCESS;
}

static int	check_map(FILE *fp, t_map *map)
{
	t_map_parser	parser;

	if (init_map_parser(&parser, fp, map) == EXIT_FAILURE)
		return EXIT_FAILURE;
	if (process_map_lines(&parser))
	{
		free(parser.line);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int verify_input(int argc, const char *argv[], t_map **map)
{
	const char	*path;		// file path
	FILE		*fp;		// file pointer

	if (argc != 2 || argv == NULL || argv[1] == NULL)
	{
		fprintf(stderr, "usage: ./fdf <filename>\n");
		return EXIT_FAILURE;
	}
	path = argv[1];
	fp = fopen(path, "r");
	if (fp == NULL)
	{
		fprintf(stderr, "%s: %s\n", path, strerror(errno));
		return EXIT_FAILURE;
	}
	*map = (t_map *)malloc(sizeof(t_map));
	if (check_map(fp, *map))
	{
		fclose(fp);
		return EXIT_FAILURE;
	}
	return (EXIT_SUCCESS);
}
