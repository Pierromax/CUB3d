/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_identifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:55:02 by ple-guya          #+#    #+#             */
/*   Updated: 2025/01/26 13:19:01 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	is_set(int c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (0);
		i++;
	}
	return (1);
}

int	check_color_line(char *l)
{
	int	virg_count;
	int	digit_count;
	int	new_nb;

	new_nb = 0;
	virg_count = 0;
	digit_count = 0;
	while (*l && *l != '\n' && (!is_set(*l, " ,") || ft_isdigit(*l)))
	{
		if (*l == ' ' || *l == ',')
		{
			if (*l == ',')
				virg_count++;
			new_nb = 0;
		}
		if (ft_isdigit(*l) && new_nb == 0)
		{
			new_nb = 1;
			digit_count++;
		}
		l++;
	}
	if (virg_count != 2 || digit_count != 3)
		return (1);
	return (0);
}

void	init_color(t_color *room, char *line)
{
	char	**color;

	room->color = 42;
	color = ft_split(line, ',');
	room->red = ft_atoi(color[0]);
	room->grn = ft_atoi(color[1]);
	room->blu = ft_atoi(color[2]);
	clean_2dtab(color);
}

int	get_xpm_fd(char *file, char **path, int *fd)
{
	if (*path)
		free(*path);
	*path = check_file_name(file, ".xpm");
	if (path == NULL)
		return (print_error(".xpm file needed", *path));
	*fd = open(*path, O_RDONLY);
	if (*fd == -1)
		return (free(file), print_error("file don't exist or can't access",
				*path));
	return (0);
}
