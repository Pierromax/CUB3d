/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:52:55 by ple-guya          #+#    #+#             */
/*   Updated: 2024/11/22 16:25:14 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	is_identifier(char *line)
{
	if (!ft_strncmp(line, "SO ", 3))
		return (SO);
	if (!ft_strncmp(line, "SE ", 3))
		return (SE);
	if (!ft_strncmp(line, "NO ", 3))
		return (NO);
	if (!ft_strncmp(line, "NE ", 3))
		return (NE);
	if (!ft_strncmp(line, "C ", 2))
		return (C);
	if (!ft_strncmp(line, "F ", 2))
		return (F);
	if (!check_is_map(line))
		return (map_wall);
	return (0);
}

int	count_words(char *s)
{
	int	word;
	int	new_word;

	word = 0;
	new_word = 0;
	while (*s && *s != '\n')
	{
		if (*s != ' ' && new_word == 0)
		{
			new_word = 1;
			word++;
		}
		if (*s == ' ' && new_word == 1)
			new_word = 0;
		s++;
	}
	return (word);
}

char	*check_file_name(char *file, char *extension)
{
	int		i;
	char	*file_cpy;

	i = 0;
	file_cpy = file;
	file_cpy = ft_strrchr(file_cpy, '.');
	if (ft_strcmp(file_cpy, extension))
		return (NULL);
	return (file);
}

