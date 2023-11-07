/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loveone.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 01:21:52 by ychair            #+#    #+#             */
/*   Updated: 2023/10/24 01:57:12 by ychair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	write_line(char **env, char *line, int fd)
{
	char	*tmp;
	char	*dst;

	dst = nospace(line, env, -1);
	tmp = ft_strjoin(dst, "\n");
	write(fd, tmp, ft_strlen(tmp));
	free(dst);
	free(tmp);
	dst = NULL;
	tmp = NULL;
}

void	ft_heredocs(t_node *node, char **env, int fd)
{
	char	*line;

	if (node == NULL)
		return ;
	fd = open(".temp_input_file", O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
	{
		perror("Failed to open temporary file");
		return ;
	}
	line = NULL;
	while (1)
	{
		line = readline(">");
		if (!line)
			break ;
		if (strncmp(line, node->ipf, ft_strlen(line)) == 0 && (line[0] != '\0'))
			break ;
		if (line[0] != '\0')
			write_line(env, line, fd);
		else
			write(fd, "\n", 1);
	}
	freeone(line, fd);
}

char	**argumentsexec(t_node *node)
{
	int		i;
	char	**args;

	i = 0;
	args = (char **)malloc((node->numarguments + 2) * sizeof(char *));
	args[0] = node->command;
	while (i < node->numarguments)
	{
		args[i + 1] = node->arguments[i];
		i++;
	}
	args[node->numarguments + 1] = NULL;
	return (args);
}

void	ipf(t_node *node, t_args *fd)
{
	int		file_fd;

	file_fd = 0;
	if (node->app == 2)
		node->ipf = ".temp_input_file";
	file_fd = open(node->ipf, O_RDONLY);
	close(STDIN_FILENO);
	fdgarbage(fd, file_fd);
	dup2(file_fd, STDIN_FILENO);
	close(file_fd);
}

void	fdtin(t_args *fd)
{
	close(STDIN_FILENO);
	fdgarbage(fd, fd->tin);
	dup2(fd->tin, STDIN_FILENO);
	close(fd->tin);
}
