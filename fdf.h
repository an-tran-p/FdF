/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atran <atran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:04:47 by atran             #+#    #+#             */
/*   Updated: 2025/02/17 14:52:32 by atran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "Libft/libft.h"
# include "MLX42/include//MLX42/MLX42.h"
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

int		ft_printf(const char *str, ...);
char	*get_next_line(int fd);

#endif
