/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atran <atran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:04:17 by atran             #+#    #+#             */
/*   Updated: 2025/04/13 16:10:43 by atran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_input(mlx_key_data_t keydata, void *param)
{
	t_window	*window;

	window = (t_window *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(window->mlx);
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
	{
		if ((window->org_height + window->org_width - window->min_value)
			* (window->zoom + 1) * 0.5 < HEIGHT / 2 && window->org_width
			* (window->zoom + 1) < WIDTH / 2)
			window->zoom++;
	}
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
	{
		if (window->zoom > 1)
			window->zoom--;
	}
	if (window->image)
		mlx_delete_image(window->mlx, window->image);
	window->image = mlx_new_image(window->mlx, WIDTH, HEIGHT);
	if (!window->image)
		return ;
	render_points(window->grid, window);
	render_grid(window->grid, window->image);
	mlx_image_to_window(window->mlx, window->image, 0, 0);
}

void	run_window(t_point **grid)
{
	t_window	window;

	window.zoom = 1;
	window.grid = grid;
	window.mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!window.mlx)
		return ;
	window.image = mlx_new_image(window.mlx, WIDTH, HEIGHT);
	if (!window.image)
		return ;
	render_points(grid, &window);
	render_grid(grid, window.image);
	mlx_image_to_window(window.mlx, window.image, 0, 0);
	mlx_key_hook(window.mlx, handle_input, &window);
	mlx_loop(window.mlx);
	mlx_terminate(window.mlx);
}

int	main(int argc, char **argv)
{
	t_point	**grid;

	if (argc != 2)
		return (0);
	if (file_exist_or_empty(argv[1]) < 0)
		return (0);
	grid = create_grid(argv[1]);
	if (!grid)
		return (0);
	run_window(grid);
	ft_free_grid(grid);
}
