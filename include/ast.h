/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:37:14 by ychair            #+#    #+#             */
/*   Updated: 2023/10/21 03:35:19 by ychair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "minishell.h"

char	**ft_split(char const *s, char c);
char	**ft_splitpath(char *s, char c);

char	*change_dollar(char *src, int i, char *env);
char	*chekg(char *src);
char	*envdol(char *src, char **env);
char	*find_env(char *src, int i, char **env);
char	*ft_alloca(char const *s, char c);
char	*ft_strdup(char *src, int x);
char	*ft_stricpy(char *dst, char *src, int i);
char	*new_src(char **dst, int i,char *srcs);
char	*truecpy(char *src);
char	*word_dup(char *str, int start, int finish);

int		checkbuilt(t_node *node);
int		count_words(char *str, char c);
int		ft_count(char const *s, char c);
int		ft_strlcpy(char *dst, char *src);

void	free_array(char **array);


char	*nospace(char *src, char **env);
int		ft_strcmpa(char *s1, char *s2);
void	fdcloser(t_args *fd);
#endif
