/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 11:53:30 by cofoundo          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/09/05 23:11:28 by cofoundo         ###   ########.fr       */
=======
/*   Updated: 2023/03/31 11:03:41 by cofoundo         ###   ########.fr       */
>>>>>>> 26f2e0fef931109ebf20856787daf6b93424e742
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_until_space(t_args *args)
{
<<<<<<< HEAD
	while (args->str[args->i_max] && (args->str[args->i_max] != ' '
			|| args->str[args->i_max] != '\t'
			|| args->str[args->i_max] != '\n'
			|| args->str[args->i_max] != '\r'
			|| args->str[args->i_max] != '\v'
			|| args->str[args->i_max] != '\f'))
=======
	while (args->str[args->i_max] && (args->str[args->i_max] != ' ' 
				|| args->str[args->i_max] != '\t' 
				|| args->str[args->i_max] != '\n' 
				|| args->str[args->i_max] != '\r' 
				|| args->str[args->i_max] != '\v' 
				|| args->str[args->i_max] != '\f'))
>>>>>>> 26f2e0fef931109ebf20856787daf6b93424e742
		args->i_max++;
	return ;
}

void	skip_white_space(t_args *args)
{
<<<<<<< HEAD
	while (args->str[args->i] && (args->str[args->i] == ' '
			|| args->str[args->i] == '\t'
			|| args->str[args->i] == '\n'
			|| args->str[args->i] == '\r'
			|| args->str[args->i] == '\v'
			|| args->str[args->i] == '\f'))
=======
	while (args->str[args->i] && (args->str[args->i] == ' ' 
				|| args->str[args->i] == '\t' 
				|| args->str[args->i] == '\n' || args->str[args->i] == '\r' 
				|| args->str[args->i] == '\v' 
				|| args->str[args->i] == '\f'))
>>>>>>> 26f2e0fef931109ebf20856787daf6b93424e742
		args->i++;
	return ;
}

int	ft_strcmpr(t_args *args, char *check)
{
	int	i;
	int	j;

	j = 0;
	skip_white_space(args);
	i = args->i;
	while (check[j] && args->str[i] && args->str[i] == check[j])
	{
		i++;
		j++;
	}
	if (!check[j])
		return (j);
	else
		return (0);
}

int	ft_cmp(char *str, int i, char c)
{
	if (str[i] == c)
		return (1);
	return (0);
}

char	*cpy_str(t_data *data, int i, int j)
{
	char	*dst;
	int		k;

	k = 0;
	while (data->parse[i][j][k])
				k++;
	dst = malloc(sizeof(char) * (k + 1));
	if (!dst)
		return (NULL);
	dst[k] = '\0';
	k = 0;
	while (data->parse[i][j][k])
	{
		dst[k] = data->parse[i][j][k];
		k++;
	}
	return (dst);
}
