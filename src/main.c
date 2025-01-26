/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:27:49 by cviegas           #+#    #+#             */
/*   Updated: 2025/01/26 16:01:53 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main(int ac, char **av)
{
	t_cub	cub;

	ft_bzero(&cub, sizeof(t_cub));
	if (parsing(&cub, ac, av) == -1)
		return (free_all(&cub), 1);
	init_cub(&cub);
	if (BONUS)
		mlx_mouse_hide(cub.mlx.mlx, cub.mlx.win);
	hooks(&cub);
	mlx_loop(cub.mlx.mlx);
	clean_exit(&cub, "Opti3D exited successfully", 0);
	return (0);
}
