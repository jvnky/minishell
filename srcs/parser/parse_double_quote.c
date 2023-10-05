/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 11:59:32 by cofoundo          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/09/06 23:08:39 by ychair           ###   ########.fr       */
=======
/*   Updated: 2023/05/27 00:23:09 by cofoundo         ###   ########.fr       */
>>>>>>> 26f2e0fef931109ebf20856787daf6b93424e742
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
	args->i++;
	j = 0;
	while (k-- > 0)
		str[j++] = args->str[args->i++];
	args->i++;
	if (add_command(data, str, 0) == 0)
		return (0);
	return (1);
}

int	parse_quote(t_args *args, char c)
{
	int	i;

	i = args->i + 1;
	while (args->str[i] && ft_cmp(args->str, i, c) != 0)
		i++;
	if (args->str[i])
		return (1);
	return (0);
}
