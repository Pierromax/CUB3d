/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:20:01 by ple-guya          #+#    #+#             */
/*   Updated: 2024/11/14 19:23:34 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub.h"

static int	get_xpm_file(t_cub *cub, char *line, int id)
{
	char	*file;

	if (count_words(line) != 1)
		return (print_error("INVALID ARG FOUND IN .cub FILE", line));
	file = ft_strtrim(line, " \n");
	if (id == SO)
		return (get_xpm_fd(file, &cub->so , &cub->so_fd));
	if (id == SE)
		return (get_xpm_fd(file, &cub->se, &cub->se_fd));
	if (id == NO)
		return (get_xpm_fd(file, &cub->no, &cub->no_fd));
	if (id == NE)
		return (get_xpm_fd(file, &cub->ne, &cub->ne_fd));
	return (0);
}

static int	get_color(t_cub *cub, char *line, t_color *room, int id)
{
	if (!check_color_line(line, " ,"))
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
	int		i;
	int		id;
	t_color	f;
	t_color	c;

	i = 0;
	if (!line)
		return (0);
	while (line[i] == ' ')
		i++;
	if (!line[i])
		return (0);
	id = is_identifier(line + i);
	if (id == SO || id == SE || id == NO || id == NE)
		return (get_xpm_file(cub, line + i + 3, id));
	if (id == C)
		return (get_color(cub, line + i + 2, &c, id));
	if (id == F)
		return (get_color(cub, line + i + 2, &f, id));
	if (id == map_wall)
		return (map_wall);
	return (0);
}

int	file_digger(t_cub *cub)
{
	char	*line;
	int		identifier;

	line = get_next_line(cub->cub_fd);
	while (line)
	{
		if (!line)
			return (1); 
		identifier = get_info(cub, line);
		if (identifier == map_wall)
			break ;
		if (identifier == -1)
			return (free(line), 1);
		free(line);
		line = get_next_line(cub->cub_fd);
	}
	cub->map = get_map(cub, line);
	free(line);
	return (0);
}

int	init(t_cub *cub, int ac, char **av)
{
	if (!cub)
		return(print_error("MALLOC HAS BEEN CRAMPTED", NULL));
	if (ac != 2)
		return(print_error("INVALID ARG NUMBER", NULL));
	cub->file_name = check_file_name(av[1], ".cub");
	if (!cub->file_name)
		return(print_error("map.cub file needed", NULL));
	cub->cub_fd = open(cub->file_name, O_RDONLY);
	if (cub->cub_fd == -1)
		return (print_error("can't access or don't exist", cub->file_name));
	if (file_digger(cub) == -1)
		return (1);
	return(0);
}