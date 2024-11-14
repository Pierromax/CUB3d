/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_identifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:55:02 by ple-guya          #+#    #+#             */
/*   Updated: 2024/11/14 19:23:40 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub.h"

int	check_color_line(char *line, char *set)
{
	int	i;
	int	j;
	int	virg_count;

	virg_count = 0;
	i = 0;
	while (line[i] || line[i] != '\n')
	{
		j = 0;
		if (line[i] == ',')
			virg_count++;
		while (set[j])
		{
			if (line[i] == set[j])
				break ;
			j++;
		}
		if (ft_isdigit(line[i]) && line[i] != set[j])
			return (1);
		i++;
	}
	if (virg_count != 2)
		return (1);
	return (0);
}

char	*simplify_color_line(char *line)
{
	char	*color;
	int		i;
	int		j;

	i = 0;
	j = 0;
	color = NULL;
	while (line[i])
	{
		if (line[i] != ' ')
			color[j++] = line[i++];
		else
			i++;
	}
	return (color);
}

void	init_color(t_color *room, char *line )
{
	char	**color;

	color = ft_split(line, ',');
	room->red = ft_atoi(color[0]);
	room->grn = ft_atoi(color[1]);
	room->blu = ft_atoi(color[2]);
	clean_2dtab(color);
}

int	get_xpm_fd(char *file, char **path, int *fd)
{
	*path = check_file_name(file, ".xpm");
	if (path == NULL)
		return (print_error(".xpm file needed", *path));
	*fd = open(*path, O_RDONLY);
	if (*fd == -1)
		return (print_error("file don't exist or can't access", *path));
	return (0);
}
