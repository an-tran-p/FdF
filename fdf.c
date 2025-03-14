/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atran <atran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:04:17 by atran             #+#    #+#             */
/*   Updated: 2025/03/07 17:54:00 by atran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
				/ 2, grid[i][j].color);
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

	/* int			i;
	int			j; */
	/* i = 0; */
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
	mlx_image_to_window(mlx, image, 0, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	/* while (grid[i])
	{
		j = 0;
		while (grid[i][j].color)
		{
			ft_printf(" // %d, %s, %d, %d", grid[i][j].value, grid[i][j].color,
				grid[i][j].x, grid[i][j].y);
			j++;
		}
		ft_printf("\n");
		i++;
	} */
	ft_free_grid(grid);
}
