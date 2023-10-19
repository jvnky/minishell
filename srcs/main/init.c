/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:33:31 by cofoundo          #+#    #+#             */
/*   Updated: 2023/10/15 15:33:31 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_args(t_args *args)
{
	args->str = NULL;
	args->i = 0;
	args->tin = dup(STDIN_FILENO);
	args->tout = dup(STDOUT_FILENO);
	return (1);
}

int	init_data(t_data *data)
{
	data->parse = malloc(sizeof(char **));
	if (!data->parse)
		return (0);
	data->parse[0] = '\0';
	data->parse[1] = NULL;
	data->parse_i = 0;
	data->parse_j = 0;
	data->parse_k = 0;
	return (1);
}

int	init_struct(t_args *args, t_data *data)
{
	if (init_args(args) == 0)
	{
		write(0, "Error during struct init.\n", 26);
		return (0);
	}
	if (init_data(data) == 0)
	{
		write(0, "Error during struct init.\n", 26);
		return (0);
	}
	return (1);
}
