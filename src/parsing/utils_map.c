/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:47:19 by ple-guya          #+#    #+#             */
/*   Updated: 2025/01/16 17:37:22 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_one_block(t_cub *cub, char *map)
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
				return (1);
			}
			while ((map[i + 1] == ' ' || map[i + 1] == '\t'))
			{
				if (map[i + 2] == '\n')
				{
					cub->map_flag = 1;
					return (1);
				}
				i++;
			}
		}
		i++;
	}
	return (0);
}

static void	set_player_infos(t_cub *cub, int i, int j)
{
	cub->player.pos = (t_v2f){j, i};
	cub->player_flag = 1;
	if (cub->map[i][j] == 'N')
		cub->player.dir = (t_v2f){-1, 0};
	else if (cub->map[i][j] == 'S')
		cub->player.dir = (t_v2f){1, 0};
	else if (cub->map[i][j] == 'E')
		cub->player.dir = (t_v2f){0, 1};
	else if (cub->map[i][j] == 'W')
		cub->player.dir = (t_v2f){0, -1};
}

int	init_start_point(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (!is_set(cub->map[i][j], "SENW"))
			{
				if (cub->player_flag == 0)
					set_player_infos(cub, i, j);
				else if (cub->player_flag == 1)
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_is_map(char *line)
{
	char	*set;
	int		i;
	int		j;

	set = " 10WSEN\n\t";
	i = 0;
	while (line[i])
	{
		j = 0;
		if (is_set(line[i], set))
			return (1);
		i++;
	}
	return (0);
}

int	flood_fill(char **map, int x, int y, char wall)
{
	if (x < 0 || y < 0 || !map[y][x] || !map[y] || map[y][x] == ' ')
		return (1);
	if (map[y][x] == wall || map[y][x] == 'v')
		return (0);
	map[y][x] = 'v';
	if (flood_fill(map, x + 1, y, wall) || flood_fill(map, x - 1, y, wall)
		|| flood_fill(map, x, y + 1, wall) || flood_fill(map, x, y - 1, wall))
		return (1);
	return (0);
}
