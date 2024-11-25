/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:47:19 by ple-guya          #+#    #+#             */
/*   Updated: 2024/11/25 18:26:59 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub.h"

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
	if (x < 0 || y < 0 || !map[y][x] || !map[y])
		return (1);
	if (map[y][x] == wall || map[y][x] == 'v')
		return(0);
	map[y][x] = 'v';
	if (flood_fill(map, x + 1, y, wall) ||
		flood_fill(map, x - 1, y, wall) ||
		flood_fill(map, x, y + 1, wall) ||
		flood_fill(map, x, y - 1, wall))
		return (1);
	return (0);
}
