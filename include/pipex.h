/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:45:32 by cofoundo          #+#    #+#             */
/*   Updated: 2021/10/06 19:42:06 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "parser.h"

int		main(int ac, char **av, char **env);
int		ft_strlen(char *s);
char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
void	error(void);
int		child(int *pipe_fd, int *file_fd, char **av, char **path_list);
int		parent(int *pipe_fd, int *file_fd, char **av, char **path_list);
void	error_file(char *str);
char	**all_path(char **env);
int		ft_strcmp(const char *s1, const char *s2);
char	*get_path(char *command, char **path_list);
void	error_read(char *str);
void	free_split(char **str);
int		argument(void);
int		malloc_error(void);
char	*ft_strdup(char *s1);
#endif
