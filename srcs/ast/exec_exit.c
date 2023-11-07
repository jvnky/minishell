/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 00:31:01 by cofoundo          #+#    #+#             */
/*   Updated: 2023/10/26 00:53:41 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_alpha_arg(t_node *node, char **env, t_args *fd, t_data *data)
{
	write(2, "minishell: exit: ", 17);
	write(2, node->arguments[0], ft_strlen(node->arguments[0]));
	write(2, ": numeric argument required\n", 29);
	close(fd->oout);
	close(fd->tin);
	free_all(fd, data);
	freeast(node);
	free_array(env);
	exit(2);
}

static void	exit_num_arg(t_node *node, char **env, t_args *fd, t_data *data)
{
	int	i;

	i = ft_atoi(node->arguments[0]);
	write(1, "exit\n", 5);
	close(fd->oout);
	close(fd->tin);
	free_all(fd, data);
	freeast(node);
	free_array(env);
	exit(i);
}

void	ft_exit(t_node *node, char **env, t_args *fd, t_data *data)
{
	if (node->arguments && node->arguments[0] && node->arguments[1])
	{
		g_ret_number = 1;
		write(2, "minishell: exit: too many arguments\n", 36);
	}
	else if (node->arguments && node->arguments[0])
	{
		if (check_numeric(node->arguments[0]) == 1)
			exit_num_arg(node, env, fd, data);
		else
			exec_alpha_arg(node, env, fd, data);
	}
	else
	{
		write(1, "exit\n", 5);
		close(fd->oout);
		close(fd->tin);
		free_all(fd, data);
		freeast(node);
		free_array(env);
		exit(0);
	}
}

int	ft_atoi(char *str)
{
	int	i;
	int	n;

	i = -1;
	n = 0;
	while (str[++i])
		n = n * 10 + (str[i] - '0');
	return (n);
}

int	check_numeric(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (0);
	return (1);
}
