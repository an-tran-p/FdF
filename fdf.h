/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atran <atran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:04:47 by atran             #+#    #+#             */
/*   Updated: 2025/03/22 16:48:40 by atran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "Libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <unistd.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_point
{
	int			value;
	char		*color;
	uint32_t	int_color;
	int			r;
	int			g;
	int			b;
	int			x;
	int			y;
}				t_point;

typedef struct s_line
{
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			steps;
	float		step_r;
	float		step_g;
	float		step_b;
	float		cur_r;
	float		cur_g;
	float		cur_b;
}				t_line;

int				ft_printf(const char *str, ...);
char			*get_next_line(int fd);
int				file_exist_or_empty(char *file);
char			***create_map(char *file);
int				count_line(char *file);
int				check_line_length(char ***map);
void			ft_free_grid(t_point **grid);
t_point			**create_grid(char *file);
uint32_t		convert_color(char *str);
char			*get_color(char *str);
char			*set_color(char *str);
void			get_rgb(uint32_t color, t_point point);

#endif
