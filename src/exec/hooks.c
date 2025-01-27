/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:47:34 by cviegas           #+#    #+#             */
/*   Updated: 2025/01/27 18:01:31 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	handle_directions(t_cub *c)
{
	double	old_dir_x;
	double	old_plane_x;

	if (is_pressed(XK_Left, c))
	{
		old_dir_x = c->player.dir[0];
		c->player.dir = (t_v2f){c->player.dir[0] * cos(ROT_SPEED)
			- c->player.dir[1] * sin(ROT_SPEED), old_dir_x * sin(ROT_SPEED)
			+ c->player.dir[1] * cos(ROT_SPEED)};
		old_plane_x = c->player.plane[0];
		c->player.plane = (t_v2f){c->player.plane[0] * cos(ROT_SPEED)
			- c->player.plane[1] * sin(ROT_SPEED), old_plane_x * sin(ROT_SPEED)
			+ c->player.plane[1] * cos(ROT_SPEED)};
	}
	if (is_pressed(XK_Right, c))
	{
		old_dir_x = c->player.dir[0];
		c->player.dir = (t_v2f){c->player.dir[0] * cos(-ROT_SPEED)
			- c->player.dir[1] * sin(-ROT_SPEED), old_dir_x * sin(-ROT_SPEED)
			+ c->player.dir[1] * cos(-ROT_SPEED)};
		old_plane_x = c->player.plane[0];
		c->player.plane = (t_v2f){c->player.plane[0] * cos(-ROT_SPEED)
			- c->player.plane[1] * sin(-ROT_SPEED), old_plane_x
			* sin(-ROT_SPEED) + c->player.plane[1] * cos(-ROT_SPEED)};
	}
}

void	handle_movements(t_cub *c)
{
	t_v2f	new_pos;

	new_pos = c->player.pos;
	if (is_pressed(XK_w, c))
		new_pos = (t_v2f){new_pos[0] + c->player.dir[0] * MOVESPEED, new_pos[1]
			+ c->player.dir[1] * MOVESPEED};
	if (is_pressed(XK_s, c))
		new_pos = (t_v2f){new_pos[0] - c->player.dir[0] * MOVESPEED, new_pos[1]
			- c->player.dir[1] * MOVESPEED};
	if (is_pressed(XK_a, c))
		new_pos = (t_v2f){new_pos[0] - c->player.plane[0] * MOVESPEED,
			new_pos[1] - c->player.plane[1] * MOVESPEED};
	if (is_pressed(XK_d, c))
		new_pos = (t_v2f){new_pos[0] + c->player.plane[0] * MOVESPEED,
			new_pos[1] + c->player.plane[1] * MOVESPEED};
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
	c->player.dir = (t_v2f){c->player.dir[0] * cos(-rot_speed)
		- c->player.dir[1] * sin(-rot_speed), old_dir_x * sin(-rot_speed)
		+ c->player.dir[1] * cos(-rot_speed)};
	old_plane_x = c->player.plane[0];
	c->player.plane = (t_v2f){c->player.plane[0] * cos(-rot_speed)
		- c->player.plane[1] * sin(-rot_speed), old_plane_x * sin(-rot_speed)
		+ c->player.plane[1] * cos(-rot_speed)};
	mlx_mouse_move(c->mlx.mlx, c->mlx.win, c->mlx.screen.size[0] / 2,
		c->mlx.screen.size[1] / 2);
	last_x = c->mlx.screen.size[0] / 2;
	return (0);
}

void	hooks(t_cub *c)
{
	mlx_hook(c->mlx.win, KeyPress, KeyPressMask, k_press, c);
	mlx_hook(c->mlx.win, KeyRelease, KeyReleaseMask, k_release, c);
	mlx_hook(c->mlx.win, DestroyNotify, StructureNotifyMask, exit_game, c);
	if (BONUS)
		mlx_hook(c->mlx.win, MotionNotify, PointerMotionMask, mouse_move, c);
	mlx_loop_hook(c->mlx.mlx, update, c);
}
