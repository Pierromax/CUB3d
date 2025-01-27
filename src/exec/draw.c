/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:10:08 by cviegas           #+#    #+#             */
/*   Updated: 2025/01/27 17:17:47 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_vertical_line(t_cub *c, int x, t_dda *dda, t_img texture)
{
	t_v2i	pos;
	t_v2i	tex;
	double	step;
	double	tex_pos;

	pos[0] = x;
	tex[0] = (int)(dda->side_x * (double)texture.size[0]);
	if (dda->side == 0 && dda->ray_dir[0] > 0)
		tex[0] = texture.size[0] - tex[0] - 1;
	if (dda->side == 1 && dda->ray_dir[1] < 0)
		tex[0] = texture.size[0] - tex[0] - 1;
	step = 1.0 * texture.size[1] / dda->line_height;
	tex_pos = (dda->draw_start - c->mlx.screen.size[1] / 2 + dda->line_height
			/ 2) * step;
	pos[1] = dda->draw_start;
	while (pos[1] < dda->draw_end)
	{
		tex[1] = (int)tex_pos;
		if (tex[1] >= 0 && tex[1] < texture.size[1])
			put_pixel(c, pos, texture.pixels[texture.size[1] * tex[1]
				+ tex[0]]);
		tex_pos += step;
		pos[1]++;
	}
}

t_img	choose_wall_texture(t_cub *c, t_dda *dda, bool side)
{
	t_img	texture;

	if (side == 1 && dda->ray_dir[1] < 0)
		texture = c->textures[3];
	else if (side == 1 && dda->ray_dir[1] >= 0)
		texture = c->textures[2];
	else if (side == 0 && dda->ray_dir[0] < 0)
		texture = c->textures[1];
	else
		texture = c->textures[0];
	if (!side)
		dda->side_x = c->player.pos[1] + dda->perp_wall_dist * dda->ray_dir[1];
	else
		dda->side_x = c->player.pos[0] + dda->perp_wall_dist * dda->ray_dir[0];
	dda->side_x -= floor(dda->side_x);
	return (texture);
}

void	dda(t_cub *c)
{
	int		x;
	t_dda	dda;
	t_v2i	step;
	bool	side;
	t_img	texture;

	x = 0;
	while (x < c->mlx.screen.size[0])
	{
		calculate_ray_direction(c, x, &dda);
		initialize_dda(c, &dda, &step);
		perform_dda(c, &dda, step, &side);
		calculate_wall_distance(c, &dda, step, side);
		calculate_draw_limits(c, &dda);
		texture = choose_wall_texture(c, &dda, side);
		draw_vertical_line(c, x, &dda, texture);
		x++;
	}
}
