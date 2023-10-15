/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 11:58:32 by cofoundo          #+#    #+#             */
/*   Updated: 2023/10/13 02:05:46 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cpy_parse_j(t_data *data, int i)
{
	char	**dst;
	int		j;

	while (data->parse[data->parse_i] && data->parse[data->parse_i][i])
		i++;
	dst = malloc(sizeof(char *) * (i + 2));
	if (!dst)
		return (NULL);
	dst[i + 1] = '\0';
	dst[i] = '\0';
	i = -1;
	while (data->parse[data->parse_i] && data->parse[data->parse_i][++i])
	{
		j = 0;
		while (data->parse[data->parse_i][i][j])
			j++;
		dst[i] = malloc(sizeof(char) * (j + 1));
		if (!dst[i])
			return (NULL);
		dst[i][j] = '\0';
		while (--j >= 0)
			dst[i][j] = data->parse[data->parse_i][i][j];
	}
	return (dst);
}

int	add_command(t_data *data, char *str, int i)
{
	char	**dst;
	int		j;

	j = 0;
	dst = cpy_parse_j(data, 0);
	if (!dst)
		return (0);
	while (dst[i])
		i++;
	while (str[j])
		j++;
	dst[i] = malloc(sizeof(char *) * (j + 1));
	if (!dst[i])
		return (0);
	dst[i][j] = '\0';
	j = 0;
	while (str[j])
	{
		dst[i][j] = str[j];
		j++;
	}
	free(data->parse[data->parse_i]);
	data->parse[data->parse_i] = dst;
	return (1);
}
