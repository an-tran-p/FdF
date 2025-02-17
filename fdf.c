/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atran <atran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:04:17 by atran             #+#    #+#             */
/*   Updated: 2025/02/17 16:29:36 by atran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*read_file(char *file)
{
	int	fd;
	int	line;
	char	c;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("%s: %s\n", strerror(errno), file);
		exit(1);
	}
	while(read(fd,c,1) != NULL)
	close(fd);
}

int	main(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		return (0);
}
/*Check input:
- File exist and can be opened.
- Check if file can be read.
- Handle empty file
- Each row need to have same number of value
- Value need to be a valid number (not overflow), and can be turned into number
- file need to have nly number, space, new line and color code.
- */
