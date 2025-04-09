/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_grid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atran <atran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:29:17 by atran             #+#    #+#             */
/*   Updated: 2025/04/09 20:33:07 by atran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	render_points(t_point **grid, mlx_image_t *image, int zoom)
{
	double	radians;
	int		i;
	int		j;

	i = 0;
	radians = 30 * (M_PI / 180);
	while (grid[i])
	{
		j = 0;
		while (grid[i][j].color)
		{
			grid[i][j].x = i * zoom * cos(radians) - j * zoom * cos(radians);
			grid[i][j].y = i * zoom * sin(radians) + j * zoom * sin(radians)
				- grid[i][j].value * 0.2 * zoom;
			mlx_put_pixel(image, grid[i][j].x + WIDTH / 2, grid[i][j].y + HEIGHT
				/ 2, grid[i][j].int_color);
			j++;
		}
		i++;
	}
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
