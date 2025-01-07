/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:52:27 by ple-guya          #+#    #+#             */
/*   Updated: 2025/01/07 17:56:44 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../libft/libft.h"
# include "minilibx/mlx.h"
# include "vec2.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/stat.h>

# define SO 1
# define SE 2
# define NO 3
# define NE 4
# define C 5
# define F 6
# define map_wall 7

# define STDERR STDERR_FILENO
# define FAIL EXIT_FAILURE
# define RED "\033[1;31m"
# define LIL_RED "\033[0;31m"
# define YELLOW "\033[1;33m"
# define GREEN "\033[1;32m"
# define LIL_GREEN "\033[0;32m"
# define RCOLOR "\033[0m"
# define MAX_KEYS 65535

typedef __uint8_t		t_hexa;

typedef struct s_color
{
	int					color;
	int					red;
	int					grn;
	int					blu;
}						t_color;

typedef union u_color	t_col;

union					u_color
{
	__uint32_t			integer;
	struct
	{
		__uint8_t		r;
		__uint8_t		g;
		__uint8_t		b;
		__uint8_t		a;
	};
};

typedef struct s_img
{
	void				*img;
	void				*address;
	t_col				*pixels;
	t_v2i				size;
}						t_img;

typedef struct s_mlx
{
	void				*mlx;
	void				*win;
	t_img				screen;
}						t_mlx;

typedef struct s_player
{
	t_v2f				dir;
	t_v2f				pos;
	t_v2f				plane;

}						t_player;

typedef struct s_draw
{
	t_col				ceil;
	t_col				floor;
}						t_draw;

typedef struct s_cub
{
	t_mlx				mlx;
	char				**map;
	bool				keys[MAX_KEYS];
	t_draw				draw;
	t_player			player;
	t_color				*ceiling;
	t_color				*floor;

	char				*so;
	char				*no;
	char				*se;
	char				*ne;
	int					player_flag;
	int					map_flag;
	int					so_fd;
	int					no_fd;
	int					se_fd;
	int					ne_fd;
	int					cub_fd;
	int					player_x;
	int					player_y;

	char				*file_name;
}						t_cub;

/*******************************/
/*       INITIALISATION       */
/*******************************/

int						parsing(t_cub *cub, int ac, char **av);
int						init_map(t_cub *cub, char *line);
int						get_xpm_fd(char *file, char **path, int *fd);
void					init_color(t_color *room, char *line);
int						check_valid_map(t_cub *cub);

/*******************************/
/*            UTILS            */
/*******************************/

int						count_words(char *s);
int						check_color_line(char *line);
char					*check_file_name(char *file, char *extension);
int						is_identifier(char *line);
char					*simplify_color_line(char *line);
int						is_set(int c, char *set);
char					**ft_tabdup(char **tab);

// map
int						check_one_block(t_cub *cub, char *map);
int						init_start_point(t_cub *cub);
int						check_is_map(char *line);
int						flood_fill(char **map, int x, int y, char wall);

// error
int						print_error(char *error, char *file);
int						check_identifier(t_cub *cub, char *first_line);

/* FUNCTIONS */
void					clean_exit(t_cub *cub, char *msg, int exit_code);
void					psucc(const char *s);
int						m_release(int button, t_cub *c);
int						m_press(int button, t_cub *c);
int						k_release(int keysym, t_cub *c);
int						k_press(int keysym, t_cub *c);
bool					is_pressed(int key, t_cub *c);
void					free_all(t_cub *cub);
void					perr(const char *s);
void					s(void);

#endif