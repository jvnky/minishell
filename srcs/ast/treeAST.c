/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treeAST.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 00:37:03 by ychair            #+#    #+#             */
/*   Updated: 2023/10/20 06:06:05 by ychair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"

t_node	*createnode(char *command)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->command = truecpy(command);
	node->numarguments = 0;
	node->arguments = NULL;
	node->ipf = NULL;
	node->opf = NULL;
	node->left = NULL;
	node->right = NULL;
	node->app = 0;
	return (node);
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
	if (strcmp(command, ">") != 0 && strcmp(command, "<") != 0
		&& strcmp(command, ">>") != 0 && strcmp(command, "<<") != 0)
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

t_node	*buildast(char ***commands, int lent)
{
	t_node	*root;
	t_node	*current;
	t_node	*prev;
	t_node	*newnode;
	t_node	*operatornode;
	int		i;
	int		j;
	char	*command;/*trop de variable*/

	root = NULL;
	current = NULL;
	prev = NULL;
	i = 0;
	while (i < lent)
	{
		j = 0;
		while (commands[i][j])
		{
			command = truecpy(commands[i][j]);
			if (strcmp(command, "|") == 0)
			{
				operatornode = createnode(command);
				if (!operatornode)
					return (NULL);
				free(command);
				if (root == NULL)
				{
					operatornode->left = current;
					prev = operatornode;
					root = operatornode;
				}
				else
				{
					operatornode->left = current;
					prev->right = operatornode;
				}
				prev = operatornode;
			}
			else
			{
				newnode = createnode(command);
				free(command);
				if (checkop(newnode->command))
				{
					if ((i == 0) || (i > 0 && commands[i][j - 1] != NULL
						&& checkopc(commands[i][j - 1][0]) == 0))
					{
						if ((i == 0 && j == 0) || i > 0)
								current = newnode;
					}
					if (i == lent - 1 && i > 0 && prev)
						prev->right = current;
					if (commands[i][j + 1] && (commands[i][j + 1][0] == '-'
						|| checkop(commands[i][j + 1])))
					{
						j += setarguments(current, &(commands[i][j + 1]));
						if (i > 0)
							j++;
					}
					if ((commands[i + 1] && commands[i + 1][0][0] == '>')
							|| (commands[i][j + 1]
							&& commands[i][j + 1][0] == '>'))
					{
						current->opf = truecpy(commands[i + 1][1]);
						if (commands[i + 1][0][1] == '>')
							current->app = 1;
					}
					if ((commands[i + 1] && commands[i + 1][0][0] == '<')
							|| (commands[i][j + 1]
							&& commands[i][j + 1][0] == '<'))
							current->ipf = truecpy(commands[i + 1][1]);
					if (commands[i + 1] && commands[i + 1][0][0] == '<'
							&& commands[i + 1][0][1] == '<')
					{
						current->app = 2;
						// current = astheredocs(commands, lent, i, j);
						if (!root && current)
							root = current;
						if (prev)
							prev->right = current;
						return (root);
					}
				}
			}
			j++;
		}
		i++;
	}
	if (!root && current)
		root = current;
	return (root);
}

t_node	*astheredocs(char ***commands, int lent, int i, int j)
{
	t_node	*root;
	t_node	*current;
	t_node	*prev;
	t_node	*operatornode;
	t_node	*newnode;
	char	*command;

	root = NULL;
	current = NULL;
	prev = NULL;
	while (i < lent)
	{
		while (commands[i][j])
		{
			command = truecpy(commands[i][j]);
			if (strcmp(command, "|") == 0)
			{
				operatornode = createnode(command);
				if (!root)
				{
					operatornode->left = current;
					prev = operatornode;
					root = operatornode;
				}
				else
				{
					operatornode->left = current;
					prev->right = operatornode;
				}
				prev = operatornode;
			}
			else
			{
				newnode = createnode(command);
				if (checkop(newnode->command))
				{
					if ((i == 0) || (i > 0 && commands[i][j - 1]
						&& checkopc(commands[i][j - 1][0]) == 0))
					{
						if ((i == 0 && j == 0) || i > 0)
							current = newnode;
					}
					if (i == lent - 1 && i > 0 && prev)
						prev->right = current;
					printf("ALLO %s\n",commands[i][j+1]);
					if (!commands[i][j + 1] && (commands[i][j + 1][0] == '-'
						|| checkop(commands[i][j + 1])))
					{
						while (commands[i][j + 1]
							&& checkop(commands[i][j + 1]))
						{
							setarguments(current, &(commands[i][j + 1]));
							j++;
						}
					}
					if (commands[i + 1] && commands[i + 1][0][0] == '>')
						current->opf = truecpy(commands[i + 1][1]);
					if (commands[i + 1]
						&& commands[i + 1][0][0] == '>'
						&& commands[i + 1][0][1] == '>')
						current->app = 1;
					if (commands[i + 1] && commands[i + 1][0][0] == '<')
						current->ipf = truecpy(commands[i + 1][1]);
					if (commands[i + 1]
						&& commands[i + 1][0][0] == '<'
						&& commands[i + 1][0][1] == '<')
						current->app = 2;
				}
			}
		j++;
		}
	i++;
	j = 0;
	}
	if (!root && current)
		root = current;
	return (root);
}
