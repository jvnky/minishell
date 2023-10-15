/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 11:59:32 by cofoundo          #+#    #+#             */
/*   Updated: 2023/10/13 14:17:43 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote(t_args *args, t_data *data, char c, int k)
{
	int		i;
	int		j;
	char	*str;

	i = args->i + 1;
	while (ft_cmp(args->str, i, c) == 0)
	{
		i++;
		k++;
	}
	str = malloc(sizeof(char) * (k + 1));
	if (!str)
		return (0);
	str[k] = '\0';
	j = 0;
	while (k-- > 0)
		str[j++] = args->str[args->i++];
	if (add_command(data, str, 0) == 0)
		return (0);
	return (1);
}

int	parse_quote(t_args *args, char c)
{
	int	i;

	i = args->i + 1;
	while (args->str[i] && ft_cmp(args->str, i, c) == 0)
		i++;
	if (!args->str[i])
		return (0);
	return (1);
}
