/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:38:01 by cviegas           #+#    #+#             */
/*   Updated: 2025/01/27 17:49:31 by cviegas          ###   ########.fr       */
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

# ifndef BONUS
#  define BONUS 0
# endif
# define SO 1
# define WE 2
# define NO 3
# define EA 4
# define C 5
# define F 6
# define MAP_WALL 7
# define RDM_ARG 8
# define MOVESPEED 0.1
# define ROT_SPEED 0.04

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

typedef struct s_dda
{
	t_v2f				ray_dir;
	t_v2i				map_pos;
	t_v2f				side_dist;
	t_v2f				delta_dist;
	double				perp_wall_dist;
	int					line_height;
	int					draw_start;
	int					draw_end;
	double				side_x;
	int					side;
}						t_dda;

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
	char				*we;
	char				*ea;
	int					player_flag;
	int					map_flag;
	int					so_fd;
	int					no_fd;
	int					ea_fd;
	int					we_fd;
	int					cub_fd;
	int					player_x;
	int					player_y;
	char				*file_name;
	t_img				textures[4];
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
char					*addspace(char *line);

// map
int						check_one_block(t_cub *cub, char *map);
int						init_start_point(t_cub *cub);
int						check_is_map(char *line);
int						flood_fill(char **map, int x, int y, char wall);

// error
int						print_error(char *error, char *file);
int						check_identifier(t_cub *cub, char *first_line);

/* FUNCTIONS */
void					calculate_wall_distance(t_cub *c, t_dda *dda,
							t_v2i step, bool side);
void					perform_dda(t_cub *c, t_dda *dda, t_v2i step,
							bool *side);
void					draw_vertical_line(t_cub *c, int x, t_dda *dda,
							t_img texture);
void					init_cub(t_cub *cub);
t_col					rgb_to_col(int red, int green, int blue);
void					put_pixel(t_cub *c, t_v2i pos, t_col color);
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

void					calculate_ray_direction(t_cub *c, int x, t_dda *dda);
void					initialize_dda(t_cub *c, t_dda *dda, t_v2i *step);
void					calculate_draw_limits(t_cub *c, t_dda *dda);

void					dda(t_cub *c);
void					draw_ceil_and_floor(t_cub *c);

void					handle_directions(t_cub *c);
void					handle_movements(t_cub *c);
int						mouse_move(int x, int y, t_cub *c);
void					hooks(t_cub *c);

void					p_freeimg(t_img *img, t_mlx *mlx);
t_img					init_screen(t_cub *cub);
t_img					init_square(t_cub *cub, char *path);

int						exit_game(t_cub *c);
int						update(t_cub *c);

#endif