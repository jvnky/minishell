/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 11:59:32 by cofoundo          #+#    #+#             */
/*   Updated: 2023/02/18 01:48:57 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int quote(t_args *args, t_data *data, char c)
{
	int i;
	int k;
	int j;
	char    *str;
	
	i = args->i + 1;
	k = 0;
	while (ft_cmp(args->str, i, c) != 0)
	{
		i++;
		k++;
	}
	str = malloc(sizeof(char) * (k + 3));
	if (!str)
		return (0);
	str[0] = c;
	str[k + 1] = c;
	str[k + 2] = '\0';
	args->i++;
	j = 0;
	while (k > 0)
	{
		str[j] = args->str[args->i];
		k--;
		args->i++;
		j++;
	}
	args->i++;
	if (add_command(data, str) == 0)
		return (0);
	return (1);
}

int parse_quote(t_args *args, char c)
{
	int i;
	
	i = args->i + 1;
	while(args->str[i] && ft_cmp(args->str, i, c) != 0)
		i++;
	if (args->str[i])
		return (1);
	return (0);
}