/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:52:04 by ple-guya          #+#    #+#             */
/*   Updated: 2025/01/26 17:47:11 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	is_closed(char **map)
{
	int		i;
	int		j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_set(map[i][j], "0EWNS"))
				if (flood_fill(map, j, i, '1'))
					return (clean_2dtab(map), 0);
			j++;
		}
		i++;
	}
	clean_2dtab(map);
	return (1);
}

int	check_valid_map(t_cub *cub)
{
	char	**map_cpy;

	cub->player_flag = 0;
	if (init_start_point(cub))
		return (print_error("its a solo game", "map"));
	if (cub->player_flag == 0)
		return (print_error("where's the og man", "map"));
	map_cpy = ft_tabdup(cub->map);
	if (!map_cpy)
		return (print_error("malloc has been crampted", NULL));
	if (!is_closed(map_cpy))
		return (print_error("invalid map", NULL));
	return (0);
}

static void	*get_map(t_cub *cub, char *map)
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
		if (ft_strlen(line) == 1)
			line = addspace(line);
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
	if (first_line == NULL)
		return (print_error("NO MAP FOUND", NULL));
	if (check_identifier(cub, first_line) == -1)
		return (1);
	map_tmp = ft_strdup(first_line);
	if (!map_tmp)
		return (print_error("MALLOC CRAMPTED", NULL));
	free(first_line);
	map = get_map(cub, map_tmp);
	if (!map)
		return (1);
	cub->map = ft_split(map, '\n');
	free(map);
	if (!cub->map)
		return ((s(), 1));
	return (0);
}
