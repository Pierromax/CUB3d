/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:52:04 by ple-guya          #+#    #+#             */
/*   Updated: 2024/11/25 16:30:41 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

//check if the map is separated by a space line.
static int check_one_block(t_cub *cub, char *map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i] == '\n')
		{
			if (map[i + 1] == '\n')
			{
				cub->map_flag = 1;
				return(1);
			}
			while ((map[i + 1] == ' ' || map[i + 1] == '\t'))
			{
				if (map[i + 2] == '\n')
				{
					cub->map_flag = 1;
					return(1);
				}
				i++;
			}
		}
		i++;
	}
	return (0);
}

static int	init_start_point(t_cub *cub)
{
	int		i;
	int		j;

	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[j])
		{
			if (!is_set(cub->map[i][j], "SENW"))
			{
				if (cub->player_flag == 0)
				{
					cub->player_x = j;
					cub->player_y = i;
					cub->player_flag = 1;
				}
				else if (cub->player_flag == 1)
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_valid_map(t_cub *cub)
{
	cub->player_flag = 0;
	if (init_start_point(cub))
		return (print_error("its a solo game", "map"));
	if (cub->player_flag == 0)
		return (print_error("where's the og man", "map"));
	// if (flood_fill(cub->map, cub->player_x, cub->player_y, '1'))
	// 	return (print_error("Map not close", NULL));
	return (0);
}

static char	*get_map(t_cub *cub, char *map)
{
	char	*map_tmp;
	char	*line;

	map_tmp = map;
	line = get_next_line(cub->cub_fd);
	while (line)
	{
		if (check_is_map(line))
		{
			print_error("invalid arg found", "map");
			return (free(line), free(map_tmp), NULL);
		}
		map = ft_strjoin(map_tmp, line);
		free(map_tmp);
		free(line);
		if (!map)
			return (print_error("malloc has been Crampted", "map"), NULL);
		map_tmp = map;
		line = get_next_line(cub->cub_fd);
	}
	free(line);
	return (map);
}

int	init_map(t_cub *cub, char *first_line)
{
	char	*map_tmp;
	char	*map;
	int		i;

	i = 0;
	if (check_identifier(cub, first_line)== -1)
		return (1);
	map_tmp = ft_strdup(first_line);
	free(first_line);
	map = get_map(cub, map_tmp);
	if (check_one_block(cub, map))
		return (free(map), print_error("just one block pls man", "map"));
	cub->map = ft_split(map, '\n');
	free(map);
	if (!cub->map)
		return (1);
	return (0);
}
