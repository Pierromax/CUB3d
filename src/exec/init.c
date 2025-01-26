/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:47:34 by cviegas           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/01/26 13:03:12 by ple-guya         ###   ########.fr       */
=======
/*   Updated: 2025/01/26 13:00:57 by cviegas          ###   ########.fr       */
>>>>>>> refs/remotes/origin/main
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_img	init_square(t_cub *cub, char *path)
{
	t_img	image;
	int		width;
	int		height;
	int		trash[2];

	image.img = mlx_xpm_file_to_image(cub->mlx.mlx, path, &width, &height);
	if (!image.img)
		clean_exit(cub, "Image init failed", 1);
	if (width < height)
		height = width;
	else
		width = height;
	if (width > 2000)
		clean_exit(cub, "Image too big, < 2000px", 1);
	image.size = (t_v2i){width, height};
	image.address = mlx_get_data_addr(image.img, &trash[0], &trash[1],
			&trash[2]);
	image.pixels = (t_col *)image.address;
	return (image);
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
	cub->player.plane = (t_v2f){0, 0.66};
	cub->textures[0] = init_square(cub, cub->no);
	cub->textures[1] = init_square(cub, cub->so);
	cub->textures[2] = init_square(cub, cub->we);
	cub->textures[3] = init_square(cub, cub->ea);
}
