/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lovethree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 01:25:04 by ychair            #+#    #+#             */
/*   Updated: 2023/10/25 03:08:52 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

char	**dad(pid_t pids, char **env)
{
	int	status;

	status = 0;
	waitpid(pids, &status, 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) != 0)
		{	
			g_ret_number = 127;
			return (env);
		}
		g_ret_number = 0;
	}
	return (NULL);
}

char	**family(t_args *fd, t_data *data, char **env, char **args)
{
	pid_t	pids;

	fdgarbage(fd, 7);
	if (args[0][0] != '>' && args[0][0] != '<')
	{
		pids = fork();
		run_signals(1);
		if (pids == -1)
		{
			perror("Fork failed");
			exit(1);
		}
		else if (pids == 0)
			mychild(fd, data, env, args);
		else if (dad(pids, env) != NULL)
			return (env);
	}
	return (NULL);
}

void	garbagecollector(t_args *fd)
{
	fdgarbage(fd, fd->oin);
	fdgarbage(fd, fd->oout);
	fdgarbage(fd, fd->tin);
	fdgarbage(fd, fd->tout);
}

void	closefor(t_args *fd)
{
	close(fd->oin);
	close(fd->oout);
	close(fd->tin);
	close(fd->tout);
}

void	recursivesucks(t_node *node, char **env, t_data *data, t_args *fd)
{
	int	pipe_fds[2];

	if (pipe(pipe_fds) == -1)
	{
		perror("Pipe creation failed");
		exit(1);
	}
	fdgarbage(fd, fd->tout);
	fd->tout = pipe_fds[1];
	fdgarbage(fd, fd->tout);
	executeast(node->left, env, fd, data);
	close(pipe_fds[1]);
	close(fd->tin);
	dup2(pipe_fds[0], fd->tin);
	fdgarbage(fd, fd->tin);
	close(pipe_fds[0]);
	executeast(node->right, env, fd, data);
}
