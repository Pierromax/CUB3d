/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:52:27 by ple-guya          #+#    #+#             */
/*   Updated: 2024/11/26 23:42:53 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "libft.h"
# include <sys/stat.h>
# include <fcntl.h>

# define SO 1
# define SE 2
# define NO 3
# define NE 4
# define C 5
# define F 6
# define map_wall 7

typedef struct s_color
{
	int		color;
	int		red;
	int		grn;
	int		blu;
}	t_color;

typedef struct s_cub
{
	char	*so;
	char	*no;
	char	*se;
	char	*ne;
	int		player_flag;
	int		map_flag;
	int		so_fd;
	int		no_fd;
	int		se_fd;
	int		ne_fd;
	int		cub_fd;
	int		player_x;
	int		player_y;
	t_color	*ceiling;
	t_color	*floor;
	char	*file_name;
	char	**map;
}	t_cub;

/*******************************/
/*       INITIALISATION       */
/*******************************/

int		parsing(t_cub *cub, int ac, char **av);
int		init_map(t_cub *cub, char *line);
int		get_xpm_fd(char *file, char **path, int *fd);
void	init_color(t_color *room, char *line);
int		check_valid_map(t_cub *cub);

/*******************************/
/*            UTILS            */
/*******************************/

int		count_words(char *s);
int		check_color_line(char *line);
char	*check_file_name(char *file, char *extension);
int		is_identifier(char *line);
char	*simplify_color_line(char *line);
int		is_set(int c, char *set);
char	**ft_tabdup(char **tab);

//map
int		check_one_block(t_cub *cub, char *map);
int		init_start_point(t_cub *cub);
int		check_is_map(char *line);
int		flood_fill(char **map, int x, int y, char wall);

//error
int		print_error(char *error, char *file);
int		check_identifier(t_cub *cub, char *first_line);


#endif