/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_and_create_map.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atran <atran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:51:02 by atran             #+#    #+#             */
/*   Updated: 2025/02/18 17:35:56 by atran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	file_exist_or_empty(char *file)
{
	int		fd;
	char	c;
	char	*ending;

	ending = ft_strnstr(file, ".fdf", ft_strlen(file));
	if (!ending || *(ending + 4))
	{
		ft_printf("Input file need to be .fdf\n");
		return (-1);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("%s: %s\n", strerror(errno), file);
		return (-1);
	}
	if (read(fd, &c, 1) == 0)
	{
		ft_printf("File is empty\n");
		return (-1);
	}
	close(fd);
	return (0);
}

int	count_line(char *file)
{
	int		fd;
	int		line;
	char	c;
	char	prev;

	fd = open(file, O_RDONLY);
	line = 0;
	while (read(fd, &c, 1))
	{
		prev = c;
		if (c == '\n')
			line++;
	}
	if (prev != '\n')
	{
		ft_printf("Invalid map without new line in end of file\n");
		return (-1);
		close(fd);
	}
	close(fd);
	return (line);
}

int	check_line_length(char ***map)
{
	int	length;
	int	i;
	int	j;

	length = 0;
	while (map[0][length])
		length++;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j != length)
			return (-1);
		i++;
	}
	return (length);
}

void	pop_map(char *file, int line_no, char ***map)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	while (line && i < line_no)
	{
		map[i] = ft_split(line, ' ');
		if (!map[i])
		{
			ft_free_2D_strarr(map);
			ft_free_str(&line);
			return ;
		}
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
}

char	***create_map(char *file)
{
	int		line_no;
	char	***map;

	line_no = count_line(file);
	if (line_no < 0)
		return (NULL);
	map = malloc((line_no + 1) * sizeof(char **));
	if (!map)
		return (NULL);
	pop_map(file, line_no, map);
	if (!map)
		return (NULL);
	map[line_no] = NULL;
	if (check_line_length(map) < 0)
	{
		ft_printf("Invalid map with unequal length\n");
		ft_free_2D_strarr(map);
		return (NULL);
	}
	return (map);
}
