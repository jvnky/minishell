/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulatething.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 00:28:28 by ychair            #+#    #+#             */
/*   Updated: 2023/10/17 17:31:28 by ychair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../include/minishell.h"
#include "../../include/env.h"

static	int		ft_count(char const *s, char c)
{
	int	i;
	int j;

	j = 0;
	i = 0;
	if (s[0] != c)
		j++;
	while (s[i])
	{
		while (s[i] == c && s[i])
		{
			i++;
			if (s[i] != c && s[i])
			{
				j++;
				while (s[i] != c && s[i])
					i++;
			}
		}
		if (s[i])
			i++;
	}
	if (s[i - 1] == c)
		j++;
	return (j);
}

static	char	*ft_alloc(char const *s, char c)
{
	char	*dst;
	int		i;

	i = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i] && s[i] != c)
		i++;
	if (!(dst = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	dst[i] = '\0';
	i -= 1;
	while (i >= 0)
	{
		dst[i] = s[i];
		i--;
	}
	return (dst);
}

static	char	**ft_end(char **dst, int j)
{
	if (!(dst[j] = malloc(sizeof(char))))
		return (NULL);
	dst[j] = NULL;
	return (dst);
}

char			**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**dst;

	if (s)
	{
		i = 0;
		j = -1;
		if (!(dst = malloc(sizeof(char*) * (ft_count(s, c) + 1))))
			return (NULL);
		while (s[i])
		{
			dst[++j] = ft_alloc(&s[i], c);
			k = -1;
			while (s[i] && dst[j][++k] && s[i] == dst[j][k])
				i++;
		}
		printf("ok\n");
		return (ft_end(dst, ++j));
	}
	return (NULL);
}
////////// abso path downm ,

int	count_words(char *str, char c)
{
	int i;
	int trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

char	*word_dup(char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char		**ft_splitpath(char *s, char c)
{
	int	i;
	int	j;
	int		index;
	char	**split;

	if (!s || !(split = malloc((count_words(s, c) + 1) * sizeof(char *))))
		return (0);
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = word_dup(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}

static void	free_array(char **array)
{
    int i;

    i = 0;
	while (array[i]) {
		free(array[i]);
		array[i] = NULL;
        i++;
	}
	free(array);
	array = NULL;
}

char *truecpy(char *src)
{
    int i;
    char *dst;
    i = ft_strlen(src);

    dst = malloc(sizeof(char) * i + 1);
    if(!dst)
    {
        return (NULL);
    }
    i = -1;
	while(src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}



char	*ft_stricpy(char *dst, char *src,int i)
{
	int j;
	// i--;
	j = 0;
	while (dst[j])
	{
			dst[j] = src[i];
			i++;
			j++;
	}
	return (dst);
}

char	*ft_strdup(char *src, int x)
{
	char	*new;
	int		i;
	// int		size;

	// size = 0;
	// while (src[size])
	// 	++size;
	// printf("SRC = %s\n",src);
	if (!(new = malloc(sizeof(char) * (x+1))))
		return (NULL);
	i = 0;
	while (i < x)
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char *lolilo(char *srcs, char *envu)
{
	char **sp;
	int i;
	int j;
	char *home;

	i =0;
	sp = ft_split(srcs,' ');
	while(sp[i])
		{
			// printf("SP = %s\n",sp[i]);
			j = 0;
			while(sp[i][j])
			{
				if(sp[i][j] == '$')
				{
					home = ft_strdup(sp[i],j);
					// printf("home = %s\n",home);
					home = ft_strjoin(home,envu);
					if (!sp[i + 1])
						home = ft_strjoin(home,"\"");
					// printf("hom1e = %s\n",home);
					free(sp[i]);
					sp[i] = home;
				}
				j++;
			}
			i++;
		}
		free(srcs);
		srcs =NULL;
		i = 0;
		while(sp[i])
		{
			// printf("srcccc = %s\n",srcs);
			if(!srcs)
				srcs = sp[i];
			else
				srcs = ft_strjoin(srcs,sp[i]);
			i++;
		}
	return srcs;
}


char *envdol(char *src,char **env)
{
	int i;
	char *dmp;
	int len;
	int j;
	char *envu;

	i = 0;
	len = 0;

	while(src[i])
	{
		if(src[i] == '$')
		{
			j = i+1;
			while (src[j] && src[j] != ' ' && src[j] != '\"')
			{
				j++;
				len++;
			}
			dmp = malloc(sizeof(char)* len + 1);
			dmp[len] = '\0';
			printf("SRCS %s\n",src);
			dmp = ft_stricpy(dmp,src,i+1);
			printf("DMP = %s\n",dmp);
			if(env_value(env, dmp) == -1)
			{
				free(dmp);
				dmp = NULL;
			}
			else
				envu = cd_option_utils(env,envu,dmp);
			printf("envu = %s\n",envu);
			 src = lolilo(src,envu);
			// printf("FINSI %s\n",src);
		}
		// puts("fff");
		i++;
	}
return (src);
}
char *chekg(char *src)
{
    int i;

    char *dst;
    i = 0;

    while(src[i])
    {
        i++;
    }
    dst = malloc(sizeof(char)* i - 1);
    dst[i-2] = '\0';

    while((i-2) > 0)
    {
        dst[i-3] = src[i-2];
        i--;
    }
    // printf("DST = %s\n",dst);
    return (dst);
}

char	*get_absolute_path(char **cmd,char **env)
{

    char *path;
    char	**path_split;
    int i;
    char *road;

    if(cmd[0][0] == '\'' || cmd[0][0] == '\"')
	{
		// envdol(cmd[0],env);
        cmd[0] = chekg(cmd[0]);
	}
	road = NULL;
    path = NULL;
    path = cd_option_utils(env,path,"PATH");

    if(!path)
        return(NULL);


    path_split = ft_splitpath(path, ':');
    i = 0;
    while(path_split[i])
    {
        road=ft_strjoin(path_split[i],"/");
        free(path_split[i]);
        path_split[i]=ft_strjoin(road,cmd[0]);
        free(road);

        if(!path_split[i])
        {
            free(path);
            free_array(path_split);
            return NULL;
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
    return NULL;
}



int checkbuilt(Node *node)
{
    if(strcmp(node->command,"echo") == 0)
        return (1);
    if(strcmp(node->command,"echo -n") == 0)
        return (8);
    if(strcmp(node->command,"cd") == 0)
        return (2);
    if(strcmp(node->command,"pwd") == 0)
        return (3);
    if(strcmp(node->command,"export") == 0)
        return (4);
    if(strcmp(node->command,"unset") == 0)
        return (5);
    if(strcmp(node->command,"env") == 0)
        return (6);
    if(strcmp(node->command,"exit") == 0)
        return (7);
    return (0);
}

char **execbuiltin(Node *node,int checkbuiltin,char **env,t_args *fd,t_data *data)
{
    int i;

    i = 0;
    // (void)node;
    if(checkbuiltin == 1 || checkbuiltin == 8 )
    {
        while(node->arguments[i])
        {
            if (i > 0)
                write(1, " ", 1);
            if(node->arguments[i][0] == '\'' || node->arguments[i][0] == '\"')
            {
				if(node->arguments[i][0] == '\"')
					node->arguments[i] = envdol(node->arguments[i],env);
                node->arguments[i] = chekg(node->arguments[i]);
            }
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
        exit(0);
    }

  return (env);
}

int ft_strlcpy(char *dst, char *src)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (src[count] != '\0')
		++count;
	while (src[i] != '\0' && i != count-1)
	{
		dst[i] = src[i];
		i++;
	}
	if (count > 0)
		dst[i] = '\0';
	return (count);
}

void     ft_heredocs(Node *node)
{

    int fd;
    if (node == NULL) {
        return ;
    }

    // Open a temporary file to redirect input
    fd = open(".temp_input_file", O_TRUNC | O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        perror("Failed to open temporary file");
        return;
    }

    // Redirect standard input to the temporary file

    //   printf("Heredoc FD: %d , INPUTEFILE = %s\n", node->stdn, node->inputFile);
    char *line = NULL;
    // if (!line)
    //     puts("FUCKKKKLINE");
    size_t len = 0;

        run_signals(1);
        while (1) {
            write(1, "> ", 3);
            getline(&line, &len,  stdin);
            // printf("Heredoc content: %s, len = %d  delimiter = %s\n", line,ft_strlen(line),node->inputFile);
            write(fd,line,ft_strlen(line));

            if (strncmp(line, node->inputFile,ft_strlen(line)-1) == 0) {
                break; // Stop reading at the delimiter
            }
        }


    free(line); // Free allocated memory
    close(fd);

}


char	**executeCommand(Node *node, t_args *fd, t_data * data, char **env)
{
	int		file_fd;
	int		checkbuiltin;
	int		status;
	pid_t	pids;
	char	**args;
	char	*bins;

	args = (char**)malloc((node->numArguments + 2) * sizeof(char*));
	args[0] = node->command;
	for (int i = 0; i < node->numArguments; i++) {
		args[i + 1] = node->arguments[i];
	}
	args[node->numArguments + 1] = NULL;

	if (node->inputFile && node->app ==2)
		ft_heredocs(node);
	if (node->inputFile)
	{
		if(node->app == 2)
			node->inputFile = ".temp_input_file";
		file_fd = open(node->inputFile, O_RDONLY);
		dup2(file_fd, STDIN_FILENO);
		close(file_fd);
	}
	 if (fd->tin != STDIN_FILENO)
	{
		dup2(fd->tin, STDIN_FILENO);
		close(fd->tin);
	}
	if (node->outputFile != NULL)
	{
		if(node->app == 1)
			file_fd = open(node->outputFile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			file_fd = open(node->outputFile, O_WRONLY | O_CREAT , 0644);
		dup2(file_fd, STDOUT_FILENO);
		close(file_fd);
	}
	else if (fd->tout != STDOUT_FILENO)
	{
		dup2(fd->tout, STDOUT_FILENO);
		close(fd->tout);
	}
	checkbuiltin = checkbuilt(node);
	if(checkbuiltin)
		env = execbuiltin(node,checkbuiltin,env,fd,data);
	else
	{
		pids = fork();
		run_signals(1);
		if (pids == -1)
		{
			perror("Fork failed");
			exit(1);
		}
		else if (pids == 0)
		{
			// printf("!! fdin=%d fdout=%d command=%s\n",fd->tin,fd->tout,node->command);
			if (access(args[0], F_OK) != 0)
			{
				bins = get_absolute_path(args,env);
				execve(bins,args,NULL);
				free(bins);
			}
			else{
				execve(args[0],args,NULL);
				exit(1);
			}
		}
		else
			waitpid(pids, &status, 0); // Wait for the specific child process
	}

	free(args);
	return (env);
}

char	**executeAST(Node* node, char** env, t_args *fd, t_data *data)
{
	int	pipe_fds[2];
	int	original_stdin;
	int	original_stdout;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	if (!node)
		return(NULL);
	if (strcmp(node->command, "|") == 0)
	{
		if (pipe(pipe_fds) == -1)
		{
			perror("Pipe creation failed");
			exit(1);
		}
		fd->tout= pipe_fds[1];
		executeAST(node->left, env,fd,data);
		close(pipe_fds[1]);
		dup2(pipe_fds[0], fd->tin);
		close(pipe_fds[0]);
		executeAST(node->right, env,fd,data);
	}
	else
	{
		// printf("fdin=%d fdout=%d command=%s\n",fd->tin,fd->tout,node->command);
		env = executeCommand(node, fd,data, env);
	}
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
	return (env);
}
