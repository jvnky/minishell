/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 11:51:10 by cofoundo          #+#    #+#             */
/*   Updated: 2023/10/15 23:06:35 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_echo(t_args *args)
{
	int	i;

	i = args->i + 4;
	while (args->str[i] && (args->str[i] == ' ' || args->str[i] == '\t'
			|| args->str[i] == '\n' || args->str[i] == '\r'
			|| args->str[i] == '\v' || args->str[i] == '\f'))
		i++;
	if (args->str[i] == '-' && args->str[i])
	{
		i++;
		while (args->str[i] && args->str[i] == 'n')
			i++;
		if (args->str[i] && (args->str[i] == ' ' || args->str[i] == '\t'
				|| args->str[i] == '\n' || args->str[i] == '\r'
				|| args->str[i] == '\v'
				|| args->str[i] == '\f'))
			return (i);
		else
			return (0);
	}
	return (0);
}

static int	check_echo(t_args *args, t_data *data)
{
	if (parse_echo(args) == 0)
	{
		if (add_command(data, "echo", 0) == 0)
			return (0);
		args->i += 4;
	}
	else
	{
		args->i = parse_echo(args);
		if (add_command(data, "echo -n", 0) == 0)
			return (0);
	}
	return (1);
}

static int	check_env(t_args *args, t_data *data)
{
	if (ft_strcmpr(args, "export") != 0)
	{
		if (add_command(data, "export", 0) == 0)
			return (0);
		args->i += 6;
	}
	else if (ft_strcmpr(args, "unset") != 0)
	{
		if (add_command(data, "unset", 0) == 0)
			return (0);
		args->i += 5;
	}
	else if (ft_strcmpr(args, "env") != 0)
	{
		if (add_command(data, "env", 0) == 0)
			return (0);
		args->i += 3;
	}
	return (1);
}

static int	check_built_in(t_args *args, t_data *data)
{
	if (ft_strcmpr(args, "echo") != 0)
	{
		if (check_echo(args, data) == 0)
			return (0);
	}
	else if (ft_strcmpr(args, "cd") != 0)
	{
		if (add_command(data, "cd", 0) == 0)
			return (0);
		args->i += 2;
	}
	else if (ft_strcmpr(args, "pwd") != 0)
	{
		if (add_command(data, "pwd", 0) == 0)
			return (0);
		args->i += 3;
	}
	return (1);
}

int	parse_built_in(t_args *args, t_data *data)
{
	if (check_built_in(args, data) == 0)
		return (0);
	else if (check_env(args, data) == 0)
		return (0);
	else if (ft_strcmpr(args, "exit") != 0)
	{
		if (add_command(data, "exit", 0) == 0)
			return (0);
		args->i += 4;
	}
	return (1);
}
