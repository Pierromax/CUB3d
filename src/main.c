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

void	put_pixel(t_cub *c, int x, int y, t_col color)
{
	if (x >= 0 && x < c->mlx.screen.size[0] && y >= 0
		&& y < c->mlx.screen.size[1])
		c->mlx.screen.pixels[y * c->mlx.screen.size[0] + x] = color;
}

void	draw_ceil_and_floor(t_cub *c)
{
	int	x;
	int	y;

	y = 0;
	while (y < c->mlx.screen.size[1] / 2)
	{
		x = 0;
		while (x < c->mlx.screen.size[0])
		{
			put_pixel(c, x, y, c->draw.ceil);
			x++;
		}
		y++;
	}
	while (y < c->mlx.screen.size[1])
	{
		x = 0;
		while (x < c->mlx.screen.size[0])
		{
			put_pixel(c, x, y, c->draw.floor);
			x++;
		}
		y++;
	}
}

void	dda(t_cub *c)
{
	int		x;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	t_col	color;

	for (x = 0; x < c->mlx.screen.size[0]; x++)
	{
		cameraX = 2 * x / (double)c->mlx.screen.size[0] - 1;
		rayDirX = c->player.dir[0] + c->player.plane[0] * cameraX;
		rayDirY = c->player.dir[1] + c->player.plane[1] * cameraX;
		mapX = (int)c->player.pos[0];
		mapY = (int)c->player.pos[1];
		deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		hit = 0;
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (c->player.pos[0] - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - c->player.pos[0]) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (c->player.pos[1] - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - c->player.pos[1]) * deltaDistY;
		}
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (c->map[mapX][mapY] == '1')
			{
				hit = 1;
			}
		}
		if (side == 0)
			perpWallDist = (mapX - c->player.pos[0] + (1 - stepX) / 2)
				/ rayDirX;
		else
			perpWallDist = (mapY - c->player.pos[1] + (1 - stepY) / 2)
				/ rayDirY;
		lineHeight = (int)(c->mlx.screen.size[1] / perpWallDist);
		drawStart = -lineHeight / 2 + c->mlx.screen.size[1] / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + c->mlx.screen.size[1] / 2;
		if (drawEnd >= c->mlx.screen.size[1])
			drawEnd = c->mlx.screen.size[1] - 1;
		if (side == 1)
			color = rgb_to_col(0, 0, 255); // Blue for y-side walls
		else
			color = rgb_to_col(0, 255, 0); // Green for x-side walls
		for (int y = drawStart; y < drawEnd; y++)
			put_pixel(c, x, y, color);
	}
}

void	handle_movements(t_cub *c)
{
	if (is_pressed(XK_w, c))
	{
		if (c->map[(int)(c->player.pos[0] + c->player.dir[0]
				* 0.1)][(int)c->player.pos[1]] == '0')
			c->player.pos[0] += c->player.dir[0] * 0.1;
		if (c->map[(int)c->player.pos[0]][(int)(c->player.pos[1]
				+ c->player.dir[1] * 0.1)] == '0')
			c->player.pos[1] += c->player.dir[1] * 0.1;
	}
	if (is_pressed(XK_s, c))
	{
		if (c->map[(int)(c->player.pos[0] - c->player.dir[0]
				* 0.1)][(int)c->player.pos[1]] == '0')
			c->player.pos[0] -= c->player.dir[0] * 0.1;
		if (c->map[(int)c->player.pos[0]][(int)(c->player.pos[1]
				- c->player.dir[1] * 0.1)] == '0')
			c->player.pos[1] -= c->player.dir[1] * 0.1;
	}
	if (is_pressed(XK_a, c))
	{
		if (c->map[(int)(c->player.pos[0] - c->player.plane[0]
				* 0.1)][(int)c->player.pos[1]] == '0')
			c->player.pos[0] -= c->player.plane[0] * 0.1;
		if (c->map[(int)c->player.pos[0]][(int)(c->player.pos[1]
				- c->player.plane[1] * 0.1)] == '0')
			c->player.pos[1] -= c->player.plane[1] * 0.1;
	}
	if (is_pressed(XK_d, c))
	{
		if (c->map[(int)(c->player.pos[0] + c->player.plane[0]
				* 0.1)][(int)c->player.pos[1]] == '0')
			c->player.pos[0] += c->player.plane[0] * 0.1;
		if (c->map[(int)c->player.pos[0]][(int)(c->player.pos[1]
				+ c->player.plane[1] * 0.1)] == '0')
			c->player.pos[1] += c->player.plane[1] * 0.1;
	}
}

int	mouse_move(int x, int y, t_cub *c)
{
	static int	last_x = -1;
	double		rot_speed;
	double		oldDirX;
	double		oldPlaneX;

	(void)y;
	if (last_x == -1)
		last_x = x;
	rot_speed = (x - last_x) * 0.005;
	last_x = x;
	oldDirX = c->player.dir[0];
	c->player.dir[0] = c->player.dir[0] * cos(-rot_speed) - c->player.dir[1]
		* sin(-rot_speed);
	c->player.dir[1] = oldDirX * sin(-rot_speed) + c->player.dir[1]
		* cos(-rot_speed);
	oldPlaneX = c->player.plane[0];
	c->player.plane[0] = c->player.plane[0] * cos(-rot_speed)
		- c->player.plane[1] * sin(-rot_speed);
	c->player.plane[1] = oldPlaneX * sin(-rot_speed) + c->player.plane[1]
		* cos(-rot_speed);
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
	cub->player.dir = (t_v2f){-1, 0};     // Initial direction
	cub->player.plane = (t_v2f){0, 0.66}; // Camera plane
	cub->player.pos = (t_v2f){cub->player_x, cub->player_y};
}

int	main(int ac, char **av)
{
	t_cub cub;

	ft_bzero(&cub, sizeof(t_cub));
	if (parsing(&cub, ac, av) == -1)
		return (free_all(&cub), 1);

	init_cub(&cub);
	hooks(&cub);
	mlx_loop(cub.mlx.mlx);
	clean_exit(&cub, "Opti3D exited successfully", 0);
	return (0);
}