/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:51:56 by cofoundo          #+#    #+#             */
/*   Updated: 2023/10/15 15:26:35 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*ft_zero(long x)
{
	char	*tabe;

	if (x == 0)
	{
		tabe = malloc(sizeof(char) * 2);
		if (!tabe)
			return (NULL);
		tabe[0] = '0';
		tabe[1] = '\0';
		return (tabe);
	}
	return (NULL);
}

static	int	ft_fact(long x)
{
	long	j;
	int		i;

	j = x;
	i = 0;
	while (j != 0)
	{
		j /= 10;
		i++;
	}
	return (i);
}

static	char	*ft_alloc(int i, int n)
{
	char	*dst;

	dst = malloc(sizeof(char) * (i + 1));
	if (!dst)
		return (NULL);
	dst[i] = '\0';
	if (n < 0)
		dst[0] = '-';
	return (dst);
}

char	*ft_itoa(int n)
{
	char	*dst;
	int		i;
	long	x;

	x = n;
	i = ft_fact(x);
	if (!ft_zero(x))
	{
		if (x < 0)
		{
			i++;
			x *= -1;
		}
		dst = ft_alloc(i, n);
		if (!dst)
			return (NULL);
		while (x)
		{
			i--;
			dst[i] = x % 10 + '0';
			x /= 10;
		}
		return (dst);
	}
	return (ft_zero(x));
}

char	*ft_atoa(char *str)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	j = 1;
	n = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[++i - 1] == '-')
			j *= -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + str[i] - '0';
		i++;
	}
	n *= j;
	n += 1;
	free(str);
	str = ft_itoa(n);
	return (str);
}
