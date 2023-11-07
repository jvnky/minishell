/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 08:48:52 by cofoundo          #+#    #+#             */
/*   Updated: 2023/10/25 01:44:25 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_ret_number;

static char	**change_shlvl(char **env)
{
	int		i;
	int		j;
	char	*dst;
	char	*str;

	i = env_value(env, "SHLVL");
	j = -1;
	while (env[i][++j])
		;
	str = malloc(sizeof(char) * (j - 5));
	if (!str)
		return (NULL);
	str[j - 6] = '\0';
	while ((j - 7) >= 0)
	{
		str[j - 7] = env[i][j - 1];
		j--;
	}
	str = ft_atoa(str);
	dst = ft_strjoin("SHLVL=", str);
	env = reset_env(dst, env_value(env, "SHLVL"), env);
	free(dst);
	free(str);
	return (env);
}

static char	**cpy_env(char **env, int i)
{
	int		j;
	char	**dst;

	while (env[++i])
		;
	dst = malloc(sizeof(char *) * (i + 1));
	if (!dst)
		return (NULL);
	dst[i] = '\0';
	i = -1;
	while (env[++i])
	{
		j = -1;
		while (env[i][++j])
			;
		dst[i] = malloc(sizeof(char) * (j + 1));
		if (!dst[i])
			return (NULL);
		dst[i][j] = '\0';
		while (--j >= 0)
			dst[i][j] = env[i][j];
	}
	dst = change_shlvl(dst);
	return (dst);
}

char	**init_env(char **enve, char **env)
{
	if (enve && !env)
	{
		env = cpy_env(enve, -1);
		if (!env)
			return (NULL);
	}
	return (env);
}

char	**launch_ast(char **env, t_args *args, t_data *data)
{
	t_node	*root;
	t_num	num;

	num.lent = data->parse_i + 1;
	initnum(&num);
	if (args->str[0] && data->parse[0] && data->parse[0][0][0] != '|')
	{
		root = buildast(data->parse, &num);
		if (root)
			env = executeast(root, env, args, data);
		freeast(root);
	}
	if (args->str[0])
		add_history(args->str);
	return (env);
}

int	main(int ac, char **av, char **enve)
{
	t_args	args;
	t_data	data;
	char	**env;

	(void)ac;
	(void)av;
	env = setup(enve);
	while (1)
	{
		if (!env)
			return (-1);
		if (init_struct(&args, &data) == 0)
			return (0);
		args.str = readline("$>");
		if (!args.str)
			return (contrl_d(&args, env));
		if (ft_parse(&args, &data) == 1 && args.str)
			env = launch_ast(env, &args, &data);
		free_all(&args, &data);
		fdcloser(&args);
	}
	free_all(&args, &data);
	return (0);
}
