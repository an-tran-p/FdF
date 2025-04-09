/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atran <atran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 07:29:52 by atran             #+#    #+#             */
/*   Updated: 2025/04/09 19:14:20 by atran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*get_color(char *str)
{
	char	*color;
	char	*org_color;
	int		i;

	org_color = ft_strchr(str, ',');
	if (!org_color)
		return (NULL);
	org_color++;
	color = ft_calloc(11, sizeof(char));
	if (!color)
		return (NULL);
	color = ft_memcpy(color, org_color, ft_strlen(org_color));
	i = ft_strlen(org_color) + 1;
	while (i < 10)
	{
		if (!color[i])
			color[i] = '0';
		i++;
	}
	return (color);
}

int	hex_char_to_int(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (0);
}

uint32_t	convert_color(char *str)
{
	int			i;
	uint32_t	color;

	i = 0;
	color = 0;
	str = str + 2;
	while (i < 8)
	{
		color = (color << 4) | hex_char_to_int(str[i]);
		i++;
	}
	return (color);
}

char	*set_color(char *str)
{
	char	*color;

	if (ft_strchr(str, ','))
		color = get_color(str);
	else
		color = ft_strdup("0xFF0000FF");
	if (!color)
		return (NULL);
	return (color);
}

void	get_rgb(uint32_t color, t_point *point)
{
	point->r = (color >> 24) & 0xFF;
	point->g = (color >> 16) & 0xFF;
	point->b = (color >> 8) & 0xFF;
}
