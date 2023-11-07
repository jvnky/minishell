/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 01:48:27 by cofoundo          #+#    #+#             */
/*   Updated: 2023/10/25 23:48:45 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "structure.h"
# include "minishell.h"

char	**cd_home(char **env, char *path);
char	**cd_minus(char **env, char *path);
char	**cd_root(char **env, char *path, char *new_path);
char	**ft_cd(char *str, char **env);
char	**ft_export(char **env, char *str);
char	**launch_cd_option(char **env, char *path, int i);
char	**reset_env(char *buff, int i, char **env);
char	**ft_unset(char *args, char **env);

char	*cd_option_utils(char **env, char *path, char *str);
char	*ft_strcpy(char *dst, char *src);

int		actual_path(char *str, char **env);
int		env_value(char **env, char *str);
int		ft_echo(char *str, int option, int fd);
int		ft_env(char **env, int fd);
int		ft_pwd(void);
int		recup_patch(char *str, char *buff, char **env);
int		ft_strcompr(char *s1, char *s2);

void	free_env(char **env);
char	**cd_utils(char **env, char *path);
int		check_cd_option(char *str);
#endif
