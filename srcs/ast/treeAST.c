/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treeAST.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 00:37:03 by ychair            #+#    #+#             */
/*   Updated: 2023/10/25 23:27:02 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"

int	astsixone(t_num *num, char ***commands)
{
	if (commands[num->i + 1]
		&& commands[num->i + 1][0][0] == '>')
	{
		if (!astfor(num, commands))
			return (0);
		asttwo(commands, num);
		return (1);
	}
	if (commands[num->i + 1] && commands[num->i + 1][0][0] == '<')
	{
		if (!astthree(num, commands))
			return (0);
		asttwo(commands, num);
		return (1);
	}
	return (-1);
}

int	astsix(t_num *num, char ***commands)
{
	num->newnode = createnode(num->command);
	if (!num->newnode)
		return (0);
	if (checkop(num->newnode->command))
	{
		if ((num->i == 0) || (num->i > 0 && commands[num->i][num->j - 1] != NULL
			&& checkopc(commands[num->i][num->j - 1][0]) == 0))
			if ((num->i == 0 && num->j == 0) || num->i > 0)
					num->current = num->newnode;
		if (num->i == num->lent - 1 && num->i > 0 && num->prev)
				num->prev->right = num->current;
		astone(commands, num);
		num->checkr = astsixone(num, commands);
		if (num->checkr == 0)
			return (0);
		if (num->checkr == 1)
			return (1);
	}
	return (2);
}

t_node	*normsix(t_num *num)
{
	if (!num->root && num->current)
		num->root = num->current;
	return (num->root);
}

void	specialcase(char ***commands, t_num *num)
{
	if (commands[0][0][0] == '>' || commands[0][0][0] == '<')
	{
		num->command = truecpy(commands[0][0]);
		num->current = createnode(num->command);
		if (commands[0][0][0] == '>')
			num->current->opf = commands[0][1];
		if (commands[0][0][0] == '<')
			num->current->ipf = commands[0][1];
		if (commands[0][0][1] == '>')
			num->current->app = 1;
		if (commands[0][0][1] == '<')
			num->current->app = 2;
		num->i = 0;
	}
}

t_node	*buildast(char ***commands, t_num *num)
{
	specialcase(commands, num);
	while (++num->i < num->lent)
	{
		num->j = 0;
		while (commands[num->i][num->j])
		{
			num->command = truecpy(commands[num->i][num->j]);
			if (ft_strcmpa(num->command, "|") == 0)
			{
				if (astfive(num) == 0)
					return (NULL);
			}
			else
			{
				num->checkr = astsix(num, commands);
				if (num->checkr == 0)
					return (NULL);
				if (num->checkr == 1)
					break ;
			}
			if (commands[num->i][num->j])
				num->j++;
		}
	}
	return (normsix(num));
}
