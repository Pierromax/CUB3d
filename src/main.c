/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:50:14 by ple-guya          #+#    #+#             */
/*   Updated: 2024/11/14 19:25:24 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main(int ac, char **av)
{
	t_cub cub;
	
	if (init(&cub, ac, av) == -1)
		return (1);
	free(cub.se);
	free(cub.so);
	free(cub.no);
	free(cub.ne);
	return (0);
}
