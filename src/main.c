/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:50:14 by ple-guya          #+#    #+#             */
/*   Updated: 2024/11/25 16:47:32 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	free_all(t_cub cub)
{
	free (cub.se);
	free (cub.so);
	free (cub.no);
	free (cub.ne);
	clean_2dtab(cub.map);
}

int	main(int ac, char **av)
{
	t_cub	cub;

	if (parsing(&cub, ac, av) == -1)
		return (free_all(cub), 1);
	free_all(cub);
	return (0);
}
