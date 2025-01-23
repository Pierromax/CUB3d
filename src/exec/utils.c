/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:09:32 by cviegas           #+#    #+#             */
/*   Updated: 2025/01/23 16:09:32 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	p_freeimg(t_img *img, t_mlx *mlx)
{
	if (img->img)
	{
		mlx_destroy_image(mlx->mlx, img->img);
		img->img = NULL;
	}
}

void	put_pixel(t_cub *c, t_v2i pos, t_col color)
{
	if (pos[0] >= 0 && pos[0] < c->mlx.screen.size[0] && pos[1] >= 0
		&& pos[1] < c->mlx.screen.size[1])
		c->mlx.screen.pixels[pos[1] * c->mlx.screen.size[0] + pos[0]] = color;
}

t_col	rgb_to_col(int red, int green, int blue)
{
	t_col	color;

	color.r = red;
	color.g = green;
	color.b = blue;
	color.a = 0;
	return (color);
}
