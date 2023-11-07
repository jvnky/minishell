/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:37:14 by ychair            #+#    #+#             */
/*   Updated: 2023/10/26 02:10:44 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "minishell.h"

char	**ft_split(char const *s, char c);
char	**ft_splitpath(char *s, char c);

char	*change_dollar(char *src, int i, char *env);
char	*chekg(char *src);
char	*chekgo(char *src, char *tabsign);
char	*envdol(char *src, char **env);
char	*find_env(char *src, int i, char **env);
char	*ft_alloca(char const *s, char c);
char	*ft_strdup(char *src, int x);
char	*ft_stricpy(char *dst, char *src, int i);
char	*new_src(char **dst, int i, char *srcs);
char	*nospace(char *src, char **env, int i);
char	*set_dst(char *tabsign, char **dst, int i, char **env);
char	*set_tabsign(char *dst, char *tabsign);
char	*truecpy(char *src);
char	*word_dup(char *str, int start, int finish);

int		astfive(t_num *num);
int		astfor(t_num *num, char ***commands);
void	astone(char ***commands, t_num *num);
int		astthree(t_num *num, char ***commands);
void	asttwo(char ***commands, t_num *num);
int		checkbuilt(t_node *node);
int		count_words(char *str, char c);
int		fdgarbage(t_args *fd, int fdn);
int		ft_count(char const *s, char c);
int		ft_strcmpa(char *s1, char *s2);
int		ft_strlcpy(char *dst, char *src);

void	fdcloser(t_args *fd);
void	free_array(char **array);

void	free_splith_head(char *path, char **path_split);
char	*set_path_i(char *path_split, char *cmd);
char	*set_cmd(char **cmd);
char	*set_road(char **path_split, char *path, int i);
char	*get_absolute_path(char **cmd, char **env, int i);
void	write_line(char **env, char *line, int fd);
void	ft_heredocs(t_node *node, char **env, int fd);
char	**argumentsexec(t_node *node);
void	ipf(t_node *node, t_args *fd);
void	fdtin(t_args *fd);
void	freeone(char *line, int fd);
void	opf(t_args *fd, t_node *node);
void	fdtout(t_args *fd);
void	sndchild(char *bins, t_args *fd, t_data *data);
void	mychild(t_args *fd, t_data *data, char **env, char **args);
char	**family(t_args *fd, t_data *data, char **env, char **args);
char	**dad(pid_t pids, char **env);
void	garbagecollector(t_args *fd);
void	closefor(t_args *fd);
void	recursivesucks(t_node *node, char **env, t_data *data, t_args *fd);
t_node	*createnode(char *command);
void	cleannode(t_node *root);
int		setarguments(t_node *node, char **arguments);
int		checkop(char *command);
int		checkopc(char command);
char	**execbuiltin(t_node *node, char **env, t_args *fd, t_data *data);
void	specialcase(char ***commands, t_num *num);
int		check_numeric(char *str);
int		ft_atoi(char *str);
void	ft_exit(t_node *node, char **env, t_args *fd, t_data *data);
int		check_numeric(char *str);
char	**exec_export(t_node *node, char **env);
char	**exec_cd(t_node *node, char **env);
int		check_export(char *str);
char	**executecommand(t_node *node, t_args *fd, t_data *data, char **env);
char	**writeme(t_node *node, char **args, char **env);
#endif
