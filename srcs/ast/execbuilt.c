/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execbuilt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 02:49:38 by cofoundo          #+#    #+#             */
/*   Updated: 2023/10/26 02:10:06 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static char	**execbuilt_util(t_node *node, char **env)
{
	int	checkbuiltin;
	int	i;

	checkbuiltin = checkbuilt(node);
	if (checkbuiltin == 2)
		env = exec_cd(node, env);
	if (checkbuiltin == 3)
	{
		ft_pwd();
		g_ret_number = 0;
	}
	if (checkbuiltin == 4)
		env = exec_export(node, env);
	if (checkbuiltin == 5)
	{
		if (node->arguments)
		{
			i = -1;
			while (node->arguments[++i])
				env = ft_unset(node->arguments[i], env);
		}
	}
	if (checkbuiltin == 6)
		ft_env(env, 1);
	return (env);
}

static void	exec_echo(t_node *node, char **env, int i)
{
	int	checkbuiltin;

	checkbuiltin = checkbuilt(node);
	while (node->arguments && node->arguments[++i])
	{
		if (i > 0)
			write(1, " ", 1);
		if (node->arguments[i][0] == '\'' || node->arguments[i][0] == '\"')
		{
			if (node->arguments[i][0] == '\"')
			{
				node->arguments[i] = chekg(node->arguments[i]);
				node->arguments[i] = nospace(node->arguments[i], env, -1);
				if (node->arguments[i] != NULL)
					node->arguments[i] = envdol(node->arguments[i], env);
			}
			else
				node->arguments[i] = chekg(node->arguments[i]);
		}
		else
			node->arguments[i] = envdol(node->arguments[i], env);
		if (node->arguments[i])
			ft_echo(node->arguments[i], checkbuiltin, 1);
	}
}

char	**execbuiltin(t_node *node, char **env, t_args *fd, t_data *data)
{
	int	checkbuiltin;

	checkbuiltin = checkbuilt(node);
	if (checkbuiltin == 7)
		ft_exit(node, env, fd, data);
	if (checkbuiltin == 1 || checkbuiltin == 8)
	{
		if (node->arguments && node->arguments[0][0] == '\0')
		{
			free(node->arguments[0]);
			node->arguments[0] = NULL;
		}
		exec_echo(node, env, -1);
		if (checkbuiltin != 8)
			write(1, "\n", 1);
	}
	env = execbuilt_util(node, env);
	return (env);
}
