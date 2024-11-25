/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:47:19 by ple-guya          #+#    #+#             */
/*   Updated: 2024/11/25 16:30:15 by ple-guya         ###   ########.fr       */
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

int	flood_fill(char **map, int x, int y, char target)
{

	if (!map[y] || !map[y][x] || map[y][x] == target)
		return (0);
	if (flood_fill(map, x + 1, y, target) ||
		flood_fill(map, x - 1, y, target) ||
		flood_fill(map, x, y + 1, target) ||
		flood_fill(map, x, y - 1, target))
		return (0);
	return (1);
}
