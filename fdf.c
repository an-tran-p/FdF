/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atran <atran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:04:17 by atran             #+#    #+#             */
/*   Updated: 2025/04/09 21:18:57 by atran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_point		**grid;
	mlx_t		*mlx;
	mlx_image_t	*image;
	int			zoom;

	zoom = 1;
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
	render_points(grid, zoom);
	render_grid(grid, image);
	mlx_image_to_window(mlx, image, 0, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	ft_free_grid(grid);
}
