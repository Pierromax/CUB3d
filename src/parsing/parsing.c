/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:55:19 by ple-guya          #+#    #+#             */
/*   Updated: 2025/01/26 13:12:57 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	get_xpm_file(t_cub *cub, char *line, int id)
{
	char	*file;

	if (id == SO && cub->so)
		return (print_error("ARG REPEAT", "SO"));
	if (id == WE && cub->we)
		return (print_error("ARG REPEAT", "WE"));
	if (id == EA && cub->ea)
		return (print_error("ARG REPEAT", "EA"));
	if (id == NO && cub->no)
		return (print_error("ARG REPEAT", "NO"));
	if (count_words(line) != 1)
		return (print_error("INVALID ARG FOUND IN .cub FILE", line));
	file = ft_strtrim(line, " \n");
	if (id == SO)
		return (get_xpm_fd(file, &cub->so, &cub->so_fd));
	if (id == WE)
		return (get_xpm_fd(file, &cub->we, &cub->we_fd));
	if (id == NO)
		return (get_xpm_fd(file, &cub->no, &cub->no_fd));
	if (id == EA)
		return (get_xpm_fd(file, &cub->ea, &cub->ea_fd));
	return (0);
}

static int	get_color(t_cub *cub, char *line, t_color *room, int id)
{
	if (id == C && room->color == 42)
		return (print_error("ARG REPEAT", "C"));
	if (id == F && room->color == 42)
		return (print_error("ARG REPEAT", "F"));
	if (check_color_line(line))
		return (print_error("INVALID PARAMETER FOUND", line));
	init_color(room, line);
	if (room->red < 0 || room->red > 255)
		return (print_error("color out of range (between 0 and 255)", NULL));
	if (room->grn < 0 || room->grn > 255)
		return (print_error("color out of range (between 0 and 255)", NULL));
	if (room->blu < 0 || room->blu > 255)
		return (print_error("color out of range (between 0 and 255)", NULL));
	if (id == C)
		cub->ceiling = room;
	if (id == F)
		cub->floor = room;
	return (0);
}

static int	get_info(t_cub *cub, char *line)
{
	int	i;
	int	id;

	i = 0;
	if (!line || line[i] == '\n')
		return (0);
	while (line[i] == ' ')
		i++;
	if (!line[i])
		return (0);
	id = is_identifier(line + i);
	if (id == SO || id == WE || id == NO || id == EA)
		return (get_xpm_file(cub, line + i + 3, id));
	if (id == C)
		return (get_color(cub, line + i + 2, cub->ceiling, id));
	if (id == F)
		return (get_color(cub, line + i + 2, cub->floor, id));
	if (id == MAP_WALL)
		return (MAP_WALL);
	return (id);
}

int	file_digger(t_cub *cub)
{
	char	*line;
	int		identifier;

	line = get_next_line(cub->cub_fd);
	while (line)
	{
		if (!line)
			return (-1);
		identifier = get_info(cub, line);
		if (identifier == MAP_WALL)
			break ;
		if (identifier == 0)
			return (free(line), -1);
		free(line);
		line = get_next_line(cub->cub_fd);
	}
	if (init_map(cub, line))
		return (-1);
	if (check_valid_map(cub))
		return (-1);
	return (0);
}

int	parsing(t_cub *cub, int ac, char **av)
{
	t_color	f;
	t_color	c;

	c.color = 0;
	f.color = 0;
	cub->ceiling = &c;
	cub->floor = &f;
	cub->no = NULL;
	cub->we = NULL;
	cub->ea = NULL;
	cub->so = NULL;
	cub->map = NULL;
	if (ac != 2)
		return (print_error("INVALID ARG NUMBER", NULL));
	cub->file_name = check_file_name(av[1], ".cub");
	if (!cub->file_name)
		return (print_error("map.cub file needed", NULL));
	cub->cub_fd = open(cub->file_name, O_RDONLY);
	if (cub->cub_fd == -1)
		return (print_error("can't access or don't exist", cub->file_name));
	if (file_digger(cub) == -1)
		return (-1);
	return (0);
}
