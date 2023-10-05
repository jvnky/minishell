/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 01:48:27 by cofoundo          #+#    #+#             */
/*   Updated: 2023/09/07 00:21:45 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "structure.h"
# include "minishell.h"

char	*ft_strcpy(char *dst, char *src);
int		actual_path(char *str, char **env);
int		env_value(char **env, char *str);
int		ft_cd(char *str, char **env);
int		ft_echo(char *str, int option, int fd);
int		ft_env(char **env, int fd);
int		ft_pwd(void);
char	**ft_unset(char *args, char **env);
int		new_path(char *path, int i, char **env);
int		recup_patch(char *str, char *buff, char **env);
int		reset_env(char *buff, int i, char **env);
int     ft_export(char **env, char *str);
#endif
