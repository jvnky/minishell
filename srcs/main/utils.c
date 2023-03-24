/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:07:02 by cofoundo          #+#    #+#             */
/*   Updated: 2023/02/25 01:42:38 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && i < n && s1[i] && s2[i])
		i++;
	if (i == n && n)
		i -= 1;
	return (n ? ((unsigned char)s1[i]) - ((unsigned char)s2[i]) : 0);
}

int ft_strlen(char *str)
{
    int i;
    
    i = -1;
    while (str[++i])
        ;
    return (i);
}

void    free_args(t_args *args)
{
    free(args->str);
}

void    free_data(t_data *data)
{
    int i;
    int j;
    
    i = -1;
    while (data->parse[++i])
    {
        j = -1;
        while(data->parse[i][++j])
            free(data->parse[i][j]);
        free(data->parse[i]);
    }
    free(data->parse[i]);
}

void    free_all(t_args *args, t_data *data)
{
    free_args(args);
    free_data(data);
}