/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_grid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atran <atran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:29:48 by atran             #+#    #+#             */
/*   Updated: 2025/02/18 17:30:38 by atran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_free_grid(t_point **grid)
{
	int	i;
	int	j;

	if (grid)
	{
		i = 0;
		while (grid[i])
		{
			j = 0;
			while (grid[i][j].color)
			{
				free(grid[i][j].color);
				j++;
			}
			free(grid[i]);
			i++;
		}
		free(grid);
		grid = NULL;
	}
}

t_point	**pop_grid(char ***map, t_point **grid, int line)
{
	int	i;
	int	j;

	i = -1;
	while (++i < line)
	{
		grid[i] = malloc((check_line_length(map) + 1) * sizeof(t_point));
		if (!grid[i])
			return (NULL);
		j = -1;
		while (map[i][++j])
		{
			grid[i][j].value = ft_atoi(map[i][j]);
			if (ft_strchr(map[i][j], ','))
				grid[i][j].color = ft_strdup(ft_strchr(map[i][j], ',') + 1);
			else
				grid[i][j].color = ft_strdup("0xADD8E6");
			if (!grid[i][j].color)
				return (NULL);
		}
		grid[i][j].color = NULL;
	}
	grid[line] = NULL;
	return (grid);
}

t_point	**create_grid(char *file)
{
	char	***map;
	t_point	**grid;
	int		line;

	map = create_map(file);
	if (!map)
		return (NULL);
	line = count_line(file);
	grid = malloc((line + 1) * sizeof(t_point *));
	if (!grid)
	{
		ft_free_2D_strarr(map);
		return (NULL);
	}
	grid = pop_grid(map, grid, line);
	if (!grid)
	{
		ft_free_2D_strarr(map);
		ft_free_grid(grid);
		return (NULL);
	}
	ft_free_2D_strarr(map);
	return (grid);
}
