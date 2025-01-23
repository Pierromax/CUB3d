/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:09:17 by cviegas           #+#    #+#             */
/*   Updated: 2025/01/23 16:09:25 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_ceil_and_floor(t_cub *c)
{
	t_v2i	pos;

	pos[1] = 0;
	while (pos[1] < c->mlx.screen.size[1] / 2)
	{
		pos[0] = 0;
		while (pos[0] < c->mlx.screen.size[0])
		{
			put_pixel(c, pos, c->draw.ceil);
			pos[0]++;
		}
		pos[1]++;
	}
	while (pos[1] < c->mlx.screen.size[1])
	{
		pos[0] = 0;
		while (pos[0] < c->mlx.screen.size[0])
		{
			put_pixel(c, pos, c->draw.floor);
			pos[0]++;
		}
		pos[1]++;
	}
}
