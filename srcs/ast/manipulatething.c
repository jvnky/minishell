/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulatething.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 00:28:28 by ychair            #+#    #+#             */
/*   Updated: 2023/10/19 03:15:19 by ychair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ast.h"
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../include/minishell.h"
#include "../../include/env.h"


char	*get_absolute_path(char **cmd, char **env)
{
	char	*path;
	char	**path_split;
	int		i;
	char	*road;

	if (cmd[0][0] == '\'' || cmd[0][0] == '\"')
		cmd[0] = chekg(cmd[0]);
	road = NULL;
	path = NULL;
	path = cd_option_utils(env, path, "PATH");

	if (!path)
		return (NULL);


	path_split = ft_splitpath(path, ':');
	i = 0;
	while (path_split[i])
	{
		road = ft_strjoin(path_split[i], "/");
		free(path_split[i]);
		path_split[i] = ft_strjoin(road, cmd[0]);
		free(road);

		if (!path_split[i])
		{
			free(path);
			free_array(path_split);
			return (NULL);
		}
		if (access(path_split[i], F_OK) == 0)
		{
			road = truecpy(path_split[i]);
			free(path);
			free_array(path_split);
			return (road);
		}
		i++;
	}
	free(path);
	free_array(path_split);
	return (NULL);
}




char	**execbuiltin(t_node *node, int checkbuiltin, char **env, t_args *fd, t_data *data)
{
	int		i;

	i = 0;
	if (checkbuiltin == 1 || checkbuiltin == 8 )
	{
		if(node->arguments &&node->arguments[i][0] == '\0')
		{
			free(node->arguments[i]);
			node->arguments[i] = NULL;
		}
		while(node->arguments && node->arguments[i])
		{
			if (i > 0)
				write(1, " ", 1);
			if(node->arguments[i][0] == '\'' || node->arguments[i][0] == '\"')
			{
				if(node->arguments[i][0] == '\"')
				{
					printf("ECHO = %s\n",node->arguments[i]);
					node->arguments[i] = chekg(node->arguments[i]);
					printf("ECHO1 = %s\n",node->arguments[i]);
					if(node->arguments[i] !=NULL)
					{
						node->arguments[i] = envdol(node->arguments[i], env);
					}
				}
				else
				{

					node->arguments[i] = chekg(node->arguments[i]);
				}
			}
			if(node->arguments[i])
				ft_echo(node->arguments[i],checkbuiltin,1);
			i++;
		}
		if (checkbuiltin != 8)
			write(1, "\n", 1);
	}
	if(checkbuiltin == 2)
	{
		/*if ()*/
		if ((node->arguments[0] && !node->arguments[1]))
			ft_cd(node->arguments[0],env);
	}
	if(checkbuiltin == 3)
	{
			ft_pwd();
	}
	if(checkbuiltin == 4)
	{
			ft_export(env, node->arguments[0]);
	}
	if(checkbuiltin == 5)
		{
			env = ft_unset(node->arguments[0], env);

		}
		if(checkbuiltin == 6)
		{
			ft_env(env, 1);

		}
	if(checkbuiltin == 7)
	{
		free_all(fd,data);
		free(node);
		free_array(env);
		exit(0);
	}

	return (env);
}

void     ft_heredocs(t_node *node, char **env)
{

    int fd;
	char *tmp;
	 char *line;
    if (node == NULL) {
        return ;
    }

    // Open a temporary file to redirect input
    fd = open(".temp_input_file", O_TRUNC | O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        perror("Failed to open temporary file");
        return;
    }
	(void)env;
    // Redirect standard input to the temporary file

    //   printf("Heredoc FD: %d , INPUTEFILE = %s\n", node->stdn, node->ipf);
    line = NULL;
    // if (!line)
    //     puts("FUCKKKKLINE");
    // size_t len = 0;

        run_signals(1);
        while (1)
		{
			line = readline(">");
			if(!line)
			{
				break;
			}
			if (strncmp(line, node->ipf,ft_strlen(line)-1) == 0) {
				puts("FINISH");
                break; // Stop reading at the delimiter
            }
			tmp = nospace(line,env);
			tmp = ft_strjoin(tmp,"\n");
			write(fd,tmp,ft_strlen(tmp));
        }
    // free(line); // Free allocated memory
	free(line);
	free(tmp);
    close(fd);
}


char	**executeCommand(t_node *node, t_args *fd, t_data * data, char **env)
{
	int		file_fd;
	int		checkbuiltin;
	int		status;
	pid_t	pids;
	char	**args;
	char	*bins;
	int		i;

	i = 0;
	bins = NULL;
	args = (char **)malloc((node->numarguments + 2) * sizeof(char *));
	if(!args)
		args = NULL;
	args[0] = truecpy(node->command);
	while (i < node->numarguments)
	{
		args[i + 1] = truecpy(node->arguments[i]);
		i++;
	}
	args[node->numarguments + 1] = NULL;

	if (node->ipf && node->app == 2)
		ft_heredocs(node, env);
	if (node->ipf)
	{
		if (node->app == 2)
			node->ipf = ".temp_input_file";
		file_fd = open(node->ipf, O_RDONLY);
		dup2(file_fd, STDIN_FILENO);
		close(file_fd);
	}
	else if (fd->tin != STDIN_FILENO)
	{
		dup2(fd->tin, STDIN_FILENO);
		close(fd->tin);
	}
	if (node->opf != NULL)
	{
		if (node->app == 1)
			file_fd = open(node->opf, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			file_fd = open(node->opf, O_WRONLY | O_CREAT , 0644);
		dup2(file_fd, STDOUT_FILENO);
		close(file_fd);
	}
	else if (fd->tout != STDOUT_FILENO)
	{
		dup2(fd->tout, STDOUT_FILENO);
		close(fd->tout);
	}
	checkbuiltin = checkbuilt(node);
	if (checkbuiltin)
		env = execbuiltin(node, checkbuiltin, env, fd, data);
	else
	{
		pids = fork();
		run_signals(1);
		if (pids == -1)
		{
			perror("Fork failed");
			exit(1);
		}
		else if (pids == 0 && args[0])
		{

			if (access(args[0], F_OK) != 0)
			{
				bins = get_absolute_path(args, env);
				if (!bins)
					bins = args[0];
				if (execve(bins, args, NULL) == -1)
				{
					free(bins);
					free_array(env);
					bins = NULL;
					free_all(fd,data);
					exit(3);
				}
			}
			else
			{
				if (execve(args[0], args, NULL) == -1)
				{
					free_array(env);
					free_all(fd,data);
					exit(5);
				}
			}
			// if(bins)
			free_array(env);
			free(bins);
			free_all(fd,data);
			exit(0);
		}
		else
		{
			waitpid(pids, &status, 0);
			// printf("STATUS %d\n",g_ret_number);
			if (WIFEXITED(status))
			{
				if (WEXITSTATUS(status) == 1)
				{
					g_ret_number = (status / 2) - 1;
					printf("127: command not found\n");
					free_all(fd, data);
					return (env);
				}
			}
		}
	}
	free_array(args);
	return (env);
}

char	**executeast(t_node *node, char **env, t_args *fd, t_data *data)
{
	int	pipe_fds[2];
	int	original_stdin;
	int	original_stdout;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	printf("%s 5\n",node->command);
	node->command = envdol(node->command, env);
	printf("1%s 5\n",node->command);
	// printf("COMMAND %s\n",node->command);
	if (!node)
		return (NULL);
	if (ft_strcmp(node->command, "|") == 0)
	{
		if (pipe(pipe_fds) == -1)
		{
			perror("Pipe creation failed");
			exit(1);
		}
		fd->tout = pipe_fds[1];
		executeast(node->left, env, fd, data);
		close(pipe_fds[1]);
		dup2(pipe_fds[0], fd->tin);
		close(pipe_fds[0]);
		executeast(node->right, env, fd, data);
	}
	else
	{
		env = executeCommand(node, fd, data, env);
	}
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
	return (env);
}
