/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atran <atran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:04:17 by atran             #+#    #+#             */
/*   Updated: 2025/03/22 17:30:41 by atran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

uint32_t	create_color(int r, int g, int b)
{
	return (((r & 0xFF) << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | 0xFF);
}

void	set_line(t_line *line, t_point a, t_point b)
{
	(*line).dx = abs(b.x - a.x);
	(*line).dy = abs(b.y - a.y);
	if (a.x < b.x)
		(*line).sx = 1;
	else if (a.x >= b.x)
		(*line).sx = -1;
	if (a.y < b.y)
		(*line).sy = 1;
	else if (a.y >= b.y)
		(*line).sy = -1;
	(*line).err = (*line).dx - (*line).dy;
	if ((*line).dx >= (*line).dy)
		(*line).steps = (*line).dx;
	else if ((*line).dx < (*line).dy)
		(*line).steps = (*line).dy;
	(*line).step_r = (float)((a.r - b.r) / (*line).steps);
	(*line).step_g = (float)((a.g - b.g) / (*line).steps);
	(*line).step_b = (float)((a.b - b.b) / (*line).steps);
	(*line).cur_r = a.r;
	(*line).cur_g = a.g;
	(*line).cur_b = a.b;
}

void	check_err(t_line *line, t_point temp)
{
	int	e2;

	e2 = (*line).err * 2;
	if (e2 > -(*line).dy)
	{
		(*line).err -= (*line).dy;
		temp.x += (*line).sx;
	}
	if (e2 < (*line).dx)
	{
		(*line).err += (*line).dx;
		temp.y += (*line).sy;
	}
}

void	draw_line_gradient(mlx_image_t *image, t_point a, t_point b)
{
	t_line		line;
	uint32_t	color;
	t_point		temp;

	set_line(&line, a, b);
	temp = a;
	while (1)
	{
		color = create_color((int)(line.cur_r), (int)(line.cur_g),
				(int)(line.cur_b));
		mlx_put_pixel(image, temp.x + WIDTH / 2, temp.y + HEIGHT / 2, color);
		if (temp.x == b.x && temp.y == b.y)
			break ;
		check_err(&line, temp);
		line.cur_r += line.step_r;
		line.cur_g += line.step_g;
		line.cur_b += line.step_b;
	}
}

void	render_points(t_point **grid, mlx_image_t *image)
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
			grid[i][j].x = i * cos(radians) - j * cos(radians);
			grid[i][j].y = i * sin(radians) + j * sin(radians)
				- grid[i][j].value;
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

int	main(int argc, char **argv)
{
	t_point		**grid;
	mlx_t		*mlx;
	mlx_image_t	*image;

	if (argc != 2)
		return (0);
	if (file_exist_or_empty(argv[1]) < 0)
		return (0);
	grid = create_grid(argv[1]);
	if (!grid)
		return (0);
	mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!mlx)
		return (0);
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	render_points(grid, image);
	render_grid(grid, image);
	mlx_image_to_window(mlx, image, 0, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	ft_free_grid(grid);
}
