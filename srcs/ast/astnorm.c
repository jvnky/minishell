/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astnorm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 01:29:51 by ychair            #+#    #+#             */
/*   Updated: 2023/10/24 01:30:22 by ychair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_node	*createnode(char *command)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->command = command;
	node->numarguments = 0;
	node->arguments = NULL;
	node->ipf = NULL;
	node->opf = NULL;
	node->left = NULL;
	node->right = NULL;
	node->app = 0;
	return (node);
}

void	cleannode(t_node *root)
{
	int	i;

	i = 0;
	if (root == NULL)
		return ;
	if (root->arguments)
	{
		while (root->arguments[i])
		{
			free(root->arguments[i]);
			root->arguments[i] = NULL;
			i++;
		}
		free(root->arguments);
		root->arguments = NULL;
	}
	if (root->command)
	{
		free(root->command);
		root->command = NULL;
	}
	free(root);
	root = NULL;
}

int	setarguments(t_node *node, char **arguments)
{
	int	numarguments;
	int	i;

	i = 0;
	numarguments = 0;
	while (arguments[numarguments] != NULL)
		numarguments++;
	if (numarguments > 0)
	{
		node->arguments = (char **)malloc((numarguments + 1) * sizeof(char *));
		while (i < numarguments)
		{
			node->arguments[i] = truecpy(arguments[i]);
			i++;
		}
		node->arguments[numarguments] = NULL;
		node->numarguments = numarguments;
	}
	return (numarguments);
}

int	checkop(char *command)
{
	if (ft_strcmpa(command, ">") != 0 && ft_strcmpa(command, "<") != 0
		&& ft_strcmpa(command, ">>") != 0 && ft_strcmpa(command, "<<") != 0)
		return (1);
	else
		return (0);
}

int	checkopc(char command)
{
	if (command == '>' || command == '<')
		return (1);
	else
		return (0);
}
