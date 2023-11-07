/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulatething.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 00:28:28 by ychair            #+#    #+#             */
/*   Updated: 2023/10/26 02:09:04 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int	fdgarbage(t_args *fd, int fdn)
{
	int	*tmp;
	int	i;
	int	k;

	k = 0;
	i = -1;
	while (k == 0 && ++i <= fd->imax)
		if (fdn == fd->fdtab[i])
			k++;
	i = -1;
	if (k == 0)
	{
		fd->imax++;
		tmp = malloc(sizeof(int) * (fd->imax + 1));
		if (!tmp)
			return (0);
		while (++i < fd->imax)
			tmp[i] = fd->fdtab[i];
		tmp[i] = fdn;
		free(fd->fdtab);
		fd->fdtab = tmp;
	}
	return (1);
}

void	fdcloser(t_args *fd)
{
	int	i;

	i = 0;
	while (i <= fd->imax)
	{
		if (fd->fdtab[i] != 0 && fd->fdtab[i] != 1 && fd->fdtab[i] != 2)
		{
			close(fd->fdtab[i]);
			close(fd->fdtab[i]);
		}
		i++;
	}
	free(fd->fdtab);
	fd->fdtab = NULL;
}

char	**writeme(t_node *node, char **args, char **env)
{
	write(2, node->command, ft_strlen(node->command));
	write(2, ": command not found\n", 20);
	free(args);
	return (env);
}

void	nall(t_args *fd)
{
	garbagecollector(fd);
	fd->oin = dup(STDIN_FILENO);
	fd->oout = dup(STDOUT_FILENO);
	garbagecollector(fd);
}

char	**executeast(t_node *node, char **env, t_args *fd, t_data *data)
{
	nall(fd);
	if (!node)
		return (NULL);
	if (node->command[0] == '\"')
	{
		node->command = chekg(node->command);
		node->command = envdol(node->command, env);
	}
	if (node->command[0] != '\'')
		node->command = envdol(node->command, env);
	if (strcmp(node->command, "|") == 0)
		recursivesucks(node, env, data, fd);
	else
	{
		fdgarbage(fd, fd->oin);
		env = executecommand(node, fd, data, env);
	}
	garbagecollector(fd);
	dup2(fd->oin, STDIN_FILENO);
	dup2(fd->oout, STDOUT_FILENO);
	garbagecollector(fd);
	closefor(fd);
	return (env);
}
