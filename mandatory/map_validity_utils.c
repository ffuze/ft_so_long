/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validity_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:53:33 by adegl-in          #+#    #+#             */
/*   Updated: 2025/03/03 16:00:10 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_strlen_no_newline(char *str)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	return (len);
}

int	is_symmetric(char **map, int height)
{
	int	i;
	int	width;
	int	expected_width;

	if (!map || !map[0])
		return (0);
	expected_width = ft_strlen_no_newline(map[0]);
	i = 0;
	while (i < height)
	{
		width = ft_strlen_no_newline(map[i]);
		if (width != expected_width)
			return (0);
		i++;
	}
	return (1);
}

static int	count_characters(char *str, int *p, int *c, int *e)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'P')
			(*p)++;
		else if (str[i] == 'C')
			(*c)++;
		else if (str[i] == 'E')
			(*e)++;
		else if (str[i] != '1' && str[i] != '0' && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	count_elements(char **map, int height, int *p, int *c, int *e)
{
	int	i;

	i = 0;
	while (i < height)
	{
		if (!count_characters(map[i], p, c, e))
			return (0);
		i++;
	}
	return (1);
}

char	**copy_map(char **map, int height)
{
	int		i;
	char	**map_copy;

	map_copy = malloc(height * sizeof(char *));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		map_copy[i] = ft_strdup(map[i]);
		if (!map_copy[i])
		{
			free_grid(map_copy, i);
			return (NULL);
		}
		i++;
	}
	return (map_copy);
}
