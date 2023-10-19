/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 22:26:03 by cofoundo          #+#    #+#             */
/*   Updated: 2023/10/19 01:42:17 by ychair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_history(t_history *history)
{
	int	i;

	i = -1;
	while (history->str[++i])
		free(history->str[i]);
	free(history->str);
}

void	free_reset(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->parse[++i])
	{
		j = -1;
		while (data->parse[++j])
			free(data->parse[i][j]);
		free(data->parse[i]);
	}
}

void	free_exit(t_data *data, t_history *history)
{
	int	i;
	int	j;

	i = -1;
	while (data->parse[++i])
	{
		j = -1;
		while (data->parse[++j])
			free(data->parse[i][j]);
		free(data->parse[i]);
	}
	i = -1;
	while (history->str[++i])
		free(history->str[i]);
	return ;
}

void	freeast(t_node *root)
{
	if (root == NULL)
		return ;
	free(root->command);
	freeast(root->left);
	freeast(root->right);
	free(root);
	root = NULL;
}
