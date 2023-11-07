/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 00:41:52 by cofoundo          #+#    #+#             */
/*   Updated: 2023/10/26 02:04:47 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		write(1, "declare -x ", 11);
		write(1, env[i], ft_strlen(env[i]));
		write(1, "\n", 1);
		g_ret_number = 0;
	}
}

int	check_export(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '=')
		return (0);
	while (str[++i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
			|| str[i] == '\v' || str[i] == '\f')
			return (0);
		if (str[i] == '=')
			return (1);
	}
	return (3);
}

char	**exec_cd(t_node *node, char **env)
{
	if (node->arguments && (node->arguments[0] && !node->arguments[1]))
		env = ft_cd(node->arguments[0], env);
	else if (!node->arguments)
		env = ft_cd(NULL, env);
	else if (node->arguments[0] && node->arguments[1])
	{
		g_ret_number = 1;
		write(2, "minishell: cd: too many arguments\n", 34);
	}
	return (env);
}

char	**rp_export(char **env, char *str)
{
	int	i;
	int	j;

	i = -1;
	while (env[++i])
	{
		j = 0;
		while (str[j] && env[i][j] && str[j] != '=' && str[j] == env[i][j])
			j++;
		if (str[j] == env[i][j] && str[j] == '=')
			break ;
	}
	if (!env[i])
		return (ft_export(env, str));
	else
	{
		free(env[i]);
		env[i] = truecpy(str);
		return (env);
	}
}

char	**exec_export(t_node *node, char **env)
{
	int	i;
	int	check;

	if (node->arguments)
	{
		i = -1;
		while (node->arguments[++i])
		{
			check = check_export(node->arguments[i]);
			if (check == 1)
				env = rp_export(env, node->arguments[i]);
			else if (check == 0)
			{
				g_ret_number = 1;
				write(2, "minishell: export: ", 19);
				write(2, node->arguments[i], ft_strlen(node->arguments[i]));
				write(2, ": not a valid identifier\n", 25);
			}
		}
	}
	else
		print_env(env);
	return (env);
}
