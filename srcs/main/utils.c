/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:07:02 by cofoundo          #+#    #+#             */
/*   Updated: 2023/10/19 04:44:48 by ychair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && i < n && s1[i] && s2[i])
		i++;
	if (i == n && n)
		i -= 1;
	if (n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	else
		return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

void	free_args(t_args *args)
{
	if(args->str != NULL)
		free(args->str);
	args->str = NULL;

}

void	free_data(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->parse[++i])
	{
		j = -1;
		while (data->parse[i][++j])
			free(data->parse[i][j]);
		free(data->parse[i]);
		data->parse[i] = NULL;
	}
	if (data->parse[data->parse_i])
		free(data->parse[data->parse_i]);
	//free(data->parse[i]);
	free(data->parse);
	data->parse = NULL;
}

void	free_all(t_args *args, t_data *data)
{
	free_args(args);
	free_data(data);
}
