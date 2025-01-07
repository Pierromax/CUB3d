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

int	update(t_cub *c)
{
	if (is_pressed(XK_Escape, c))
		clean_exit(c, "Escape Key Pressed, exited successfully", 0);
	draw_ceil_and_floor(c);
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
	cub->player.player_dir = (t_v2f){0, 0};
	cub->player.player_pos = (t_v2f){cub->player_x, cub->player_y};
}

int	main(int ac, char **av)
{
	t_cub cub;

	ft_bzero(&cub, sizeof(t_cub));
	if (parsing(&cub, ac, av) == -1)
		return (free_all(&cub), 1);
	printf("Ceiling color: R=%d, G=%d, B=%d\n", cub.ceiling->red,
		cub.ceiling->grn, cub.ceiling->blu);
	printf("Floor color: R=%d, G=%d, B=%d\n", cub.floor->red, cub.floor->grn,
		cub.floor->blu);
	init_cub(&cub);
	hooks(&cub);
	mlx_loop(cub.mlx.mlx);
	clean_exit(&cub, "Opti3D exited successfully", 0);
	return (0);
}