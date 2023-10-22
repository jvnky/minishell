/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treeAST.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 00:37:03 by ychair            #+#    #+#             */
/*   Updated: 2023/10/22 04:41:57 by ychair           ###   ########.fr       */
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



// void	astone(t_node	*op,t_node	*current,t_node	*prev,t_node	*root)
// {


// 	// return (1);
// }


t_node	*buildast(char ***commands, int lent,t_num *num)
{
	t_node	*root;
	t_node	*current;
	t_node	*prev;
	t_node	*newnode;
	t_node	*operatornode;
	char	*command;/*trop de variable*/

	root = NULL;
	current = NULL;
	prev = NULL;
	command = NULL;
	newnode = NULL;
	while (num->i < lent)
	{
		num->j = 0;
		while (commands[num->i][num->j])
		{

			command = truecpy(commands[num->i][num->j]);
			if (ft_strcmpa(command, "|") == 0)
			{
				operatornode = createnode(command);
				if (!operatornode)
					return (NULL);
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
				if (!newnode)
					return (NULL);
				printf("comm = %s\n",newnode->command);
				if (checkop(newnode->command))
				{
					if ((num->i == 0) || (num->i > 0 && commands[num->i][num->j - 1] != NULL
						&& checkopc(commands[num->i][num->j - 1][0]) == 0))
					{
						if ((num->i == 0 && num->j == 0) || num->i > 0)
								current = newnode;
					}
					// printf("current = %s , i =%d j=%d  LEN = %d  K = %d\n",current->command,num->i,num->j,lent,num->k);
					if (num->i == lent - 1 && num->i > 0 && prev)
							prev->right = current;
					if (commands[num->i][num->j + 1] && (commands[num->i][num->j + 1][0] == '-'
						|| checkop(commands[num->i][num->j + 1])))
					{
						num->j += setarguments(current, &(commands[num->i][num->j + 1]));
						if (num->i > 0)
							num->j++;
					}
					if (commands[num->i + 1] && commands[num->i + 1][0][0] == '>')
					{

						 puts("FFFF");
						current->opf = commands[num->i + 1][1];
						// printf("1FILE = %s\n",current->opf);
						if (!current->opf)
						{
							cleannode(newnode);
							return (NULL);
						}
						// printf("FILE = %s\n",current->opf);
						if (commands[num->i + 1][0][1] == '>')
							current->app = 1;
						 num->i++;
						if (num->i == lent - 1 && num->i > 0 && prev)
							prev->right = current;
						 break;
						// num->j++;
					}
					else if (commands[num->i + 1] && commands[num->i + 1][0][0] == '<')
					{
						current->ipf = commands[num->i + 1][1];
						if (!current->ipf)
						{
							cleannode(newnode);
							return (NULL);
						}
					}
					if (commands[num->i + 1] && commands[num->i + 1][0][0] == '<'
							&& commands[num->i + 1][0][1] == '<')
						{
							current->app = 2;
						}
				}
			}
			num->j++;
		}
		num->i++;
	}

	if (!root && current)
		root = current;
	// cleannode(newnode);
	return (root);
}

