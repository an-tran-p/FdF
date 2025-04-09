/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atran <atran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:30:11 by atran             #+#    #+#             */
/*   Updated: 2025/04/09 20:32:59 by atran            ###   ########.fr       */
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
	(*line).step_r = (float)(a.r - b.r) / (*line).steps;
	(*line).step_g = (float)(a.g - b.g) / (*line).steps;
	(*line).step_b = (float)(a.b - b.b) / (*line).steps;
	(*line).cur_r = a.r;
	(*line).cur_g = a.g;
	(*line).cur_b = a.b;
}

void	check_err(t_line *line, t_point *temp)
{
	int	e2;

	e2 = (*line).err * 2;
	if (e2 > -(*line).dy)
	{
		(*line).err -= (*line).dy;
		(*temp).x += (*line).sx;
	}
	if (e2 < (*line).dx)
	{
		(*line).err += (*line).dx;
		(*temp).y += (*line).sy;
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
		check_err(&line, &temp);
		line.cur_r += line.step_r;
		line.cur_g += line.step_g;
		line.cur_b += line.step_b;
	}
}
