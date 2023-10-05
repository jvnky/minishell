/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:59:33 by cofoundo          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/08/28 22:45:49 by cofoundo         ###   ########.fr       */
=======
/*   Updated: 2023/06/22 01:45:34 by cofoundo         ###   ########.fr       */
>>>>>>> 26f2e0fef931109ebf20856787daf6b93424e742
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD
static char	**add_history_utils(t_history *history, int i)
{
	int		j;
	char	**dst;

	while (history->str[++i])
		;
	dst = malloc(sizeof(char *) * (i + 2));
	if (!dst)
		return (NULL);
	dst[i + 1] = '\0';
	i = -1;
	while (history->str[++i])
	{
		j = -1;
		while (history->str[i][++j])
			;
		dst[i] = malloc(sizeof(char) * (j + 1));
		if (!dst[i])
			return (NULL);
		dst[i][j] = '\0';
		j = -1;
		while (history->str[i][++j])
			dst[i][j] = history->str[i][j];
	}
	return (dst);
}

int	add_history(t_args *args, t_history *history)
{
	int		i;
	int		j;
	char	**dst;

	dst = add_history_utils(history, -1);
	if (!dst)
		return (0);
	i = -1;
	while (history->str[++i])
		;
	j = -1;
	while (args->str[++j])
		;
	dst[i] = malloc(sizeof(char) * (j + 1));
	if (!dst[i])
		return (0);
	dst[i][j] = '\0';
	j = -1;
	while (args->str[++j])
		dst[i][j] = args->str[j];
	free_history(history);
	history->str = dst;
	return (1);
}
=======
static char **add_history_utils(t_history *history)
{
    int i;
    int j;
    char    **dst;
    
    i = -1;
    while (history->str[++i])
        ;
    dst = malloc(sizeof(char *) * (i + 2));
    if (!dst)
        return (NULL);
    dst[i + 1] = '\0';
    i = -1;
    while (history->str[++i])
    {
        j = -1;
        while (history->str[i][++j])
            ;
        dst[i] = malloc(sizeof(char) * (j + 1));
        if (!dst[i])
            return (NULL);
        dst[i][j] = '\0';
        j = -1;
        while (history->str[i][++j])
            dst[i][j] = history->str[i][j];
    }
    return (dst);
}

int add_history(t_args *args, t_history *history)
{
    int i;
    int j;
    char    **dst;
    
    dst = add_history_utils(history);
    if (!dst)
        return (0);
    i = -1;
    while (history->str[++i])
        ;
    j = -1;
    while (args->str[++j])
        ;
    dst[i] = malloc(sizeof(char) * (j + 1));
    if (!dst[i])
        return (0);
    dst[i][j] = '\0';
    j = -1;
    while (args->str[++j])
        dst[i][j] = args->str[j];
    free_history(history);
    history->str = dst;
    return (1);
}

/*int add_history(t_args *args, t_history *history)
{
    int i;
    int j;
    char    **dst;
    
    i = -1;
    while (history->str[++i])
        ;
    dst = malloc(sizeof(char *) * (i + 2));
    if (!dst)
        return (0);
    dst[i + 1] = '\0';
    i = -1;
    while (history->str[++i])
    {
        j = -1;
        while (history->str[i][++j])
            ;
        dst[i] = malloc(sizeof(char) * (j + 1))
        if (!dst[i])
            return (0);
        dst[i][j] = '\0';
        j = -1;
        while (history->str[i][++j])
            dst[i][j] = history->str[i][j];
    }
    j = -1;
    while (args->str[++j])
        ;
    dst[i] = malloc(sizeof(char) * (j + 1));
    if (!dst[i])
        return (0);
    dst[i][j] = '\0';
    j = -1;
    while (args->str[++j])
        dst[i][j] = args->str[j];
    free_history(history);
    history->str = dst;
    return (1);
}*/
>>>>>>> 26f2e0fef931109ebf20856787daf6b93424e742
