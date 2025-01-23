/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:09:21 by cviegas           #+#    #+#             */
/*   Updated: 2025/01/23 16:09:21 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	print_error(char *error, char *file)
{
	if (file)
		ft_putstr_fd(file, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(error, STDERR);
	ft_putchar_fd('\n', STDERR);
	return (FAIL);
}

void	clean_exit(t_cub *cub, char *msg, int exit_code)
{
	free_all(cub);
	if (msg)
		ft_putstr_fd(msg, STDERR);
	exit(exit_code);
}
