/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atran <atran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 07:29:52 by atran             #+#    #+#             */
/*   Updated: 2025/04/13 17:22:49 by atran            ###   ########.fr       */
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
	org_color = org_color + 3;
	color = ft_calloc(10, sizeof(char));
	if (!color)
		return (NULL);
	ft_memcpy(color, "0x", 2);
	i = 2;
	while (i < (8 - (int)ft_strlen(org_color)))
	{
		if (!color[i])
			color[i] = '0';
		i++;
	}
	ft_memcpy(&color[i], org_color, ft_strlen(org_color));
	if (!color[8])
		ft_memcpy(&color[8], "FF", 2);
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
