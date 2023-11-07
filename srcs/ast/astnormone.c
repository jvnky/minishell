/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astnormone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 01:31:33 by ychair            #+#    #+#             */
/*   Updated: 2023/10/24 04:31:17 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	astone(char ***commands, t_num *num)
{
	if (commands[num->i][num->j + 1] && checkop(commands[num->i][num->j + 1]))
	{
		num->j += setarguments(num->current, &(commands[num->i][num->j + 1]));
		if (num->i > 0)
			num->j++;
	}
}

void	asttwo(char ***commands, t_num *num)
{
	if (commands[num->i + 1][0][1] == '>')
		num->current->app = 1;
	if (commands[num->i + 1] && commands[num->i + 1][0][0] == '<'
		&& commands[num->i + 1][0][1] == '<')
			num->current->app = 2;
	num->i++;
	if (num->i == num->lent - 1 && num->i > 0 && num->prev)
		num->prev->right = num->current;
	num->j = 0;
}

int	astthree(t_num *num, char ***commands)
{
	num->current->ipf = commands[num->i + 1][1];
	if (!num->current->ipf)
	{
		cleannode(num->newnode);
		return (0);
	}
	return (1);
}

int	astfor(t_num *num, char ***commands)
{
	num->current->opf = commands[num->i + 1][1];
	if (!num->current->opf)
	{
		cleannode(num->newnode);
		return (0);
	}
	return (1);
}

int	astfive(t_num *num)
{
	num->operatornode = createnode(num->command);
	if (!num->operatornode)
		return (0);
	if (num->root == NULL)
	{
		num->operatornode->left = num->current;
		num->prev = num->operatornode;
		num->root = num->operatornode;
	}
	else
	{
		num->operatornode->left = num->current;
		num->prev->right = num->operatornode;
	}
	num->prev = num->operatornode;
	return (1);
}
