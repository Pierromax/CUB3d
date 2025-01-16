/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:27:49 by cviegas           #+#    #+#             */
/*   Updated: 2025/01/16 17:33:19 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_col	rgb_to_col(int red, int green, int blue)
{
	t_col	color;

	color.r = red;
	color.g = green;
	color.b = blue;
	color.a = 0xFF;
	return (color);
}

void	put_pixel(t_cub *c, t_v2i pos, t_col color)
{
	if (pos[0] >= 0 && pos[0] < c->mlx.screen.size[0] && pos[1] >= 0
		&& pos[1] < c->mlx.screen.size[1])
		c->mlx.screen.pixels[pos[1] * c->mlx.screen.size[0] + pos[0]] = color;
}

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

void	perform_dda(t_cub *c, t_dda *dda, t_v2i step, int *side)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (dda->side_dist[0] < dda->side_dist[1])
		{
			dda->side_dist[0] += dda->delta_dist[0];
			dda->map_pos[0] += step[0];
			*side = 0;
		}
		else
		{
			dda->side_dist[1] += dda->delta_dist[1];
			dda->map_pos[1] += step[1];
			*side = 1;
		}
		if (c->map[dda->map_pos[0]][dda->map_pos[1]] == '1')
			hit = 1;
	}
}

void	calculate_wall_distance(t_cub *c, t_dda *dda, t_v2i step, int side)
{
	if (side == 0)
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

void	draw_vertical_line(t_cub *c, int x, t_dda *dda, t_col color)
{
	t_v2i	pos;

	pos[0] = x;
	pos[1] = dda->draw_start;
	while (pos[1] < dda->draw_end)
	{
		put_pixel(c, pos, color);
		pos[1]++;
	}
}

void	dda(t_cub *c)
{
	int		x;
	t_dda	dda;
	t_v2i	step;
	int		side;
	t_col	color;

	x = 0;
	while (x < c->mlx.screen.size[0])
	{
		calculate_ray_direction(c, x, &dda);
		initialize_dda(c, &dda, &step);
		perform_dda(c, &dda, step, &side);
		calculate_wall_distance(c, &dda, step, side);
		calculate_draw_limits(c, &dda);
		if (side == 1)
			color = rgb_to_col(0, 0, 255);
		else
			color = rgb_to_col(0, 255, 0);
		draw_vertical_line(c, x, &dda, color);
		x++;
	}
}

#define MOVESPEED 0.1

void	handle_movements(t_cub *c)
{
	t_v2f	new_pos;

	new_pos = c->player.pos;
	if (is_pressed(XK_w, c))
		new_pos = (t_v2f){c->player.pos[0] + c->player.dir[0] * MOVESPEED,
			c->player.pos[1] + c->player.dir[1] * MOVESPEED};
	if (is_pressed(XK_s, c))
		new_pos = (t_v2f){c->player.pos[0] - c->player.dir[0] * MOVESPEED,
			c->player.pos[1] - c->player.dir[1] * MOVESPEED};
	if (is_pressed(XK_a, c))
		new_pos = (t_v2f){c->player.pos[0] - c->player.plane[0] * MOVESPEED,
			c->player.pos[1] - c->player.plane[1] * MOVESPEED};
	if (is_pressed(XK_d, c))
		new_pos = (t_v2f){c->player.pos[0] + c->player.plane[0] * MOVESPEED,
			c->player.pos[1] + c->player.plane[1] * MOVESPEED};
	if (c->map[(int)new_pos[0]][(int)c->player.pos[1]] != '1')
		c->player.pos[0] = new_pos[0];
	if (c->map[(int)c->player.pos[0]][(int)new_pos[1]] != '1')
		c->player.pos[1] = new_pos[1];
}

int	mouse_move(int x, int y, t_cub *c)
{
	static int	last_x = -1;
	double		rot_speed;
	double		old_dir_x;
	double		old_plane_x;

	(void)y;
	if (last_x == -1)
		last_x = x;
	rot_speed = (x - last_x) * 0.005;
	last_x = x;
	old_dir_x = c->player.dir[0];
	c->player.dir[0] = c->player.dir[0] * cos(-rot_speed) - c->player.dir[1]
		* sin(-rot_speed);
	c->player.dir[1] = old_dir_x * sin(-rot_speed) + c->player.dir[1]
		* cos(-rot_speed);
	old_plane_x = c->player.plane[0];
	c->player.plane[0] = c->player.plane[0] * cos(-rot_speed)
		- c->player.plane[1] * sin(-rot_speed);
	c->player.plane[1] = old_plane_x * sin(-rot_speed) + c->player.plane[1]
		* cos(-rot_speed);
	mlx_mouse_move(c->mlx.mlx, c->mlx.win, c->mlx.screen.size[0] / 2,
		c->mlx.screen.size[1] / 2);
	last_x = c->mlx.screen.size[0] / 2;
	return (0);
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

int	exit_game(t_cub *c)
{
	clean_exit(c, "Cross Button Pressed, exited successfully", 0);
	return (0);
}

void	hooks(t_cub *c)
{
	mlx_hook(c->mlx.win, KeyPress, KeyPressMask, k_press, c);
	mlx_hook(c->mlx.win, KeyRelease, KeyReleaseMask, k_release, c);
	mlx_hook(c->mlx.win, DestroyNotify, StructureNotifyMask, exit_game, c);
	mlx_hook(c->mlx.win, MotionNotify, PointerMotionMask, mouse_move, c);
	mlx_loop_hook(c->mlx.mlx, update, c);
}

void	p_freeimg(t_img *img, t_mlx *mlx)
{
	if (img->img)
	{
		mlx_destroy_image(mlx->mlx, img->img);
		img->img = NULL;
	}
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

t_img	init_screen(t_cub *cub)
{
	t_img	image;
	int		trash[2];

	image.img = mlx_new_image(cub->mlx.mlx, 1920, 1080);
	if (!image.img)
		clean_exit(cub, "Image init failed", 1);
	image.size = (t_v2i){1920, 1080};
	image.address = mlx_get_data_addr(image.img, &trash[0], &trash[1],
			&trash[2]);
	image.pixels = (t_col *)image.address;
	return (image);
}

void	free_all(t_cub *cub)
{
	free(cub->se);
	free(cub->so);
	free(cub->no);
	free(cub->ne);
	p_freeimg(&cub->mlx.screen, &cub->mlx);
	clean_2dtab(cub->map);
	if (cub->mlx.win)
		mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
	if (cub->mlx.mlx)
	{
		mlx_destroy_display(cub->mlx.mlx);
		free(cub->mlx.mlx);
	}
}

void	init_cub(t_cub *cub)
{
	cub->draw.ceil = rgb_to_col(cub->ceiling->blu, cub->ceiling->grn,
			cub->ceiling->red);
	cub->draw.floor = rgb_to_col(cub->floor->blu, cub->floor->grn,
			cub->floor->red);
	cub->mlx.mlx = mlx_init();
	if (!cub->mlx.mlx)
		clean_exit(cub, "Mlx init failed", 1);
	cub->mlx.win = mlx_new_window(cub->mlx.mlx, 1920, 1080, "Opti3D");
	if (!cub->mlx.win)
		clean_exit(cub, "Mlx Window creation failed", 1);
	cub->mlx.screen = init_screen(cub);
	cub->player.dir = (t_v2f){-1, 0};
	cub->player.plane = (t_v2f){0, 0.66};
}

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
