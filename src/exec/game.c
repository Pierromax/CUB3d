/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:47:39 by cviegas           #+#    #+#             */
/*   Updated: 2025/01/23 17:11:24 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	exit_game(t_cub *c)
{
	clean_exit(c, "Cross Button Pressed, exited successfully", 0);
	return (0);
}

void	clean_exit(t_cub *cub, char *msg, int exit_code)
{
	if (exit_code == 0)
		psucc(msg);
	else
		perr(msg);
	free_all(cub);
	exit(exit_code);
}

void	free_all(t_cub *cub)
{
	free(cub->ea);
	free(cub->so);
	free(cub->no);
	free(cub->we);
	p_freeimg(&cub->mlx.screen, &cub->mlx);
	p_freeimg(&cub->textures[0], &cub->mlx);
	p_freeimg(&cub->textures[1], &cub->mlx);
	p_freeimg(&cub->textures[2], &cub->mlx);
	p_freeimg(&cub->textures[3], &cub->mlx);
	clean_2dtab(cub->map);
	if (cub->mlx.win)
		mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
	if (cub->mlx.mlx)
	{
		mlx_destroy_display(cub->mlx.mlx);
		free(cub->mlx.mlx);
	}
}

int	update(t_cub *c)
{
	if (is_pressed(XK_Escape, c))
		clean_exit(c, "Escape Key Pressed, exited successfully", 0);
	handle_movements(c);
	draw_ceil_and_floor(c);
	dda(c);
	mlx_put_image_to_window(c->mlx.mlx, c->mlx.win, c->mlx.screen.img, 0, 0);
	return (0);
}
