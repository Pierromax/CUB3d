/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:22:39 by ple-guya          #+#    #+#             */
/*   Updated: 2024/11/22 16:25:21 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_identifier(t_cub *cub, char *first_line)
{
	if (!cub->no)
		return (free(first_line), print_error("can't find identifier", "NO"));
	if (!cub->ne)
		return (free(first_line), print_error("can't find identifier", "NE"));
	if (!cub->se)
		return (free(first_line), print_error("can't find identifier", "SE"));
	if (!cub->so)
		return (free(first_line), print_error("can't find identifier", "SO"));
	if (!cub->ceiling->color)
		return (free(first_line), print_error("can't find identifier", "C"));
	if (!cub->floor->color)
		return (free(first_line), print_error("can't find identifier", "F"));
	return (0);
}

int	print_error(char *error, char *file)
{
	int	file_len;

	ft_putendl_fd("Error", 2);
	if (file)
	{
		file_len = 0;
		while (file[file_len] && file[file_len] != '\n')
			file_len++;
		write(2, file, file_len);
		ft_putstr_fd(" : ", 2);
	}
	ft_putendl_fd(error, 2);
	return (-1);
}
