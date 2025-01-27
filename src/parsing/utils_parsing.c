/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:52:55 by ple-guya          #+#    #+#             */
/*   Updated: 2025/01/27 18:19:05 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	is_identifier(char *line)
{
	int	len;

	if (!ft_strncmp(line, "SO ", 3))
		return (SO);
	if (!ft_strncmp(line, "WE ", 3))
		return (WE);
	if (!ft_strncmp(line, "NO ", 3))
		return (NO);
	if (!ft_strncmp(line, "EA ", 3))
		return (EA);
	if (!ft_strncmp(line, "C ", 2))
		return (C);
	if (!ft_strncmp(line, "F ", 2))
		return (F);
	if (!check_is_map(line))
		return (MAP_WALL);
	len = ft_strlen(line);
	if (len > 0)
		return (RDM_ARG);
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
	if (!file_cpy)
		return (NULL);
	if (ft_strcmp(file_cpy, extension))
		return (NULL);
	return (file);
}

char	**ft_tabdup(char **tab)
{
	char	**tab_dup;
	int		len;
	int		i;

	if (!tab)
		return (NULL);
	len = ft_tablen(tab);
	i = 0;
	tab_dup = (char **)malloc(sizeof(char *) * (len + 1));
	if (!tab_dup)
		return (NULL);
	while (i < len)
	{
		tab_dup[i] = ft_strdup(tab[i]);
		if (!tab_dup[i])
		{
			clean_2dtab(tab_dup);
			return (NULL);
		}
		i++;
	}
	tab_dup[i] = NULL;
	return (tab_dup);
}

char	*addspace(char *line)
{
	char	*newline;

	free(line);
	newline = (char *)malloc(3);
	if (!newline)
		return (NULL);
	newline[0] = ' ';
	newline[1] = '\n';
	newline[2] = '\0';
	return (newline);
}
