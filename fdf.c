/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atran <atran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:04:17 by atran             #+#    #+#             */
/*   Updated: 2025/02/18 17:33:50 by atran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* void	ft_print_map(char ***map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			ft_printf("%s", map[i][j]);
	}
} */

int	main(int argc, char **argv)
{
	t_point	**grid;
	int		i;
	int		j;

	i = 0;
	if (argc != 2)
		return (0);
	if (file_exist_or_empty(argv[1]) < 0)
		return (0);
	grid = create_grid(argv[1]);
	if (!grid)
		return (0);
	while (grid[i])
	{
		j = 0;
		while (grid[i][j].color)
		{
			ft_printf(" %d, %s", grid[i][j].value, grid[i][j].color);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	ft_free_grid(grid);
}
/*Check input:
- File exist and can be opened.
- Check if file can be read.
- Handle empty file
- File doesn't end with '\n'
- File need to end with .fdf
- Each row need to have same number of value
- Value need to be a valid number (not overflow), and can be turned into number
- file need to have nly number, space, new line and color code.
- */
