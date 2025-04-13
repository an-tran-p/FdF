/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_grid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atran <atran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:29:17 by atran             #+#    #+#             */
/*   Updated: 2025/04/13 17:37:36 by atran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	render_points(t_point **grid, t_window *window)
{
	double	radians;
	int		i;
	int		j;

	i = -1;
	window->min_v = grid[0][0].value;
	window->max_v = grid[0][0].value;
	radians = 30 * (M_PI / 180);
	while (grid[++i])
	{
		j = -1;
		while (grid[i][++j].color)
		{
			grid[i][j].x = i * window->zoom * cos(radians) - j * window->zoom
				* cos(radians);
			grid[i][j].y = i * window->zoom * sin(radians) + j * window->zoom
				* sin(radians) - grid[i][j].value * 0.5 * window->zoom;
			if (grid[i][j].value < window->min_v)
				window->min_v = grid[i][j].value;
			if (grid[i][j].value > window->max_v)
				window->max_v = grid[i][j].value;
		}
	}
	window->org_h = i;
	window->org_w = j;
}

void	render_grid(t_point **grid, mlx_image_t *image)
{
	int	i;
	int	j;

	i = 0;
	while (grid[i])
	{
		j = 0;
		while (grid[i][j].color)
		{
			if (grid[i + 1])
				draw_line_gradient(image, grid[i][j], grid[i + 1][j]);
			if (grid[i][j + 1].color)
				draw_line_gradient(image, grid[i][j], grid[i][j + 1]);
			j++;
		}
		i++;
	}
}
