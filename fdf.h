/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atran <atran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:04:47 by atran             #+#    #+#             */
/*   Updated: 2025/03/07 17:42:36 by atran            ###   ########.fr       */
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

# define WIDTH 800
# define HEIGHT 600

typedef struct s_point
{
	int		value;
	char	*color;
	int		x;
	int		y;
}			t_point;

int			ft_printf(const char *str, ...);
char		*get_next_line(int fd);
int			file_exist_or_empty(char *file);
char		***create_map(char *file);
int			count_line(char *file);
int			check_line_length(char ***map);
void		ft_free_grid(t_point **grid);
t_point		**create_grid(char *file);

#endif
