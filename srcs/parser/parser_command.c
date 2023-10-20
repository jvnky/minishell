/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 11:58:32 by cofoundo          #+#    #+#             */
/*   Updated: 2023/10/20 05:11:42 by ychair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_command(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array[i]);
	free(array);
	array = NULL;
}

char	**cpy_parse_j(t_data *data, int i)
{
	char	**dst;
	int		j;

	while (data->parse[data->parse_i] && data->parse[data->parse_i][i])
		i++;
	dst = malloc(sizeof(char *) * (i + 2));
	if (!dst)
		return (NULL);
	dst[i + 1] = NULL;
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
	dst[i] = malloc(sizeof(char) * (j + 1));
	if (!dst[i])
		return (0);
	dst[i][j] = '\0';
	j = 0;
	while (str[j])
	{
		dst[i][j] = str[j];
		j++;
	}
	free_command(data->parse[data->parse_i]);
	data->parse[data->parse_i] = dst;
	return (1);
}
