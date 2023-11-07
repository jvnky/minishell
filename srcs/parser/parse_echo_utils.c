/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_echo_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 22:58:07 by cofoundo          #+#    #+#             */
/*   Updated: 2023/10/26 01:48:45 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_option(t_args *args, int i, int option)
{
	if (option == 0)
	{
		while (args->str[i] && (args->str[i] == ' ' || args->str[i] == '\t'
				|| args->str[i] == '\n' || args->str[i] == '\r'
				|| args->str[i] == '\v' || args->str[i] == '\f'))
			i++;
	}
	if (option == 1)
	{
		while (args->str[i] && (args->str[i] != ' ' && args->str[i] != '\t'
				&& args->str[i] != '\n' && args->str[i] != '\r'
				&& args->str[i] != '\v' && args->str[i] != '\f'))
			i--;
	}
	if (option == 2)
	{
		while (args->str[i] && (args->str[i] == ' ' || args->str[i] == '\t'
				|| args->str[i] == '\n' || args->str[i] == '\r'
				|| args->str[i] == '\v' || args->str[i] == '\f'))
			i--;
	}
	return (i);
}

static int	check_k(t_args *args, int i, int k)
{
	if (args->str[i - 1] == 'n' && (args->str[i] == ' '
			|| args->str[i] == '\t' || args->str[i] == '\n'
			|| args->str[i] == '\r' || args->str[i] == '\v'
			|| args->str[i] == '\f'))
		k++;
	return (k);
}

static int	call_skip_option(t_args *args, int i)
{
	i = skip_option(args, i, 1);
	i = skip_option(args, i, 2);
	return (i);
}

int	parse_echo(t_args *args)
{
	int	i;
	int	k;

	k = 0;
	i = skip_option(args, args->i + 4, 0);
	while (args->str[i] == '-' && args->str[i])
	{
		i++;
		if (args->str[i] == '-')
			break ;
		while (args->str[i] && args->str[i] == 'n')
			i++;
		k = check_k(args, i, k);
		i = skip_option(args, i, 0);
	}
	if (args->str[i] == '-')
	{
		i = call_skip_option(args, i);
		i++;
	}
	i = skip_option(args, i, 1);
	if (k > 0)
		return (i);
	else
		return (0);
}
