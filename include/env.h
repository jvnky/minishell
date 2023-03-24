/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 01:48:27 by cofoundo          #+#    #+#             */
/*   Updated: 2023/03/12 00:15:35 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

#include "structure.h"

char    *ft_strcpy(char *dst, char *src);
int actual_path(char *str, char **env);
int env_value(char *str, char **env);
int ft_cd(char *str, char **env);
int ft_echo(char *str, int option, int fd);
int ft_env(char *str, char **env, int fd);
int ft_pwd(void);
int ft_unset(char *args, char **env);
int new_path(char *path, int i, char **env);
int recup_patch(char *str, char *buff, char **env);
int reset_env(char *buff, int i, char **env);
#endif