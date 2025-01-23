/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:09:40 by cviegas           #+#    #+#             */
/*   Updated: 2025/01/23 16:12:46 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	calculate_ray_direction(t_cub *c, int x, t_dda *dda)
{
	double	camera_x;

	camera_x = 2 * x / (double)c->mlx.screen.size[0] - 1;
	dda->ray_dir[0] = c->player.dir[0] + c->player.plane[0] * camera_x;
	dda->ray_dir[1] = c->player.dir[1] + c->player.plane[1] * camera_x;
}

void	initialize_dda(t_cub *c, t_dda *dda, t_v2i *step)
{
	int	i;

	i = -1;
	dda->map_pos = (t_v2i){c->player.pos[0], c->player.pos[1]};
	while (++i <= 1)
	{
		if (dda->ray_dir[i] == 0)
			dda->delta_dist[i] = 1e30;
		else
			dda->delta_dist[i] = fabs(1 / dda->ray_dir[i]);
		if (dda->ray_dir[i] < 0)
		{
			(*step)[i] = -1;
			dda->side_dist[i] = (c->player.pos[i] - dda->map_pos[i])
				* dda->delta_dist[i];
		}
		else
		{
			(*step)[i] = 1;
			dda->side_dist[i] = (dda->map_pos[i] + 1.0 - c->player.pos[i])
				* dda->delta_dist[i];
		}
	}
}

void	perform_dda(t_cub *c, t_dda *dda, t_v2i step, bool *side)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (dda->side_dist[0] < dda->side_dist[1])
		{
			dda->side_dist[0] += dda->delta_dist[0];
			dda->map_pos[0] += step[0];
			dda->side = 0;
		}
		else
		{
			dda->side_dist[1] += dda->delta_dist[1];
			dda->map_pos[1] += step[1];
			dda->side = 1;
		}
		if (c->map[dda->map_pos[0]][dda->map_pos[1]] == '1')
			hit = 1;
	}
	*side = dda->side;
}

void	calculate_wall_distance(t_cub *c, t_dda *dda, t_v2i step, bool side)
{
	if (!side)
		dda->perp_wall_dist = (dda->map_pos[0] - c->player.pos[0] + (1
					- step[0]) / 2) / dda->ray_dir[0];
	else
		dda->perp_wall_dist = (dda->map_pos[1] - c->player.pos[1] + (1
					- step[1]) / 2) / dda->ray_dir[1];
}

void	calculate_draw_limits(t_cub *c, t_dda *dda)
{
	dda->line_height = (int)(c->mlx.screen.size[1] / dda->perp_wall_dist);
	dda->draw_start = -dda->line_height / 2 + c->mlx.screen.size[1] / 2;
	if (dda->draw_start < 0)
		dda->draw_start = 0;
	dda->draw_end = dda->line_height / 2 + c->mlx.screen.size[1] / 2;
	if (dda->draw_end >= c->mlx.screen.size[1])
		dda->draw_end = c->mlx.screen.size[1] - 1;
}
