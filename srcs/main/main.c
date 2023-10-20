/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 08:48:52 by cofoundo          #+#    #+#             */
/*   Updated: 2023/10/21 00:28:44 by ychair           ###   ########.fr       */
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

static char	**init_env(char **enve, char **env)
{
	if (enve && !env)
	{
		env = cpy_env(enve, -1);
		if (!env)
			return (NULL);
	}
	return (env);
}

void	launch_ast(char **env, t_args *args, t_data *data)
{
	t_node	*root;

	// args->oin = dup(STDIN_FILENO);
	// args->oout = dup(STDOUT_FILENO);
	if (args->str[0])
	{
		add_history(args->str);
		root = buildast(data->parse, data->parse_i + 1);
		if (root)
			env = executeast(root, env, args, data);
		close(args->tin);
		close(args->tout);
		// free_array(env);
		freeast(root); //A PLACE AILLEUR
	}
	return ;
}

int	main(int ac, char **av, char **enve)
{
	t_args	args;
	t_data	data;
	char	**env;

	(void)ac;
	(void)av;
	env = NULL;
	g_ret_number = 0;
	setup_term();
	run_signals(1);
	env = init_env(enve, env);
	while (1)
	{
		if (!env)
			return (-1);
		if (init_struct(&args, &data) == 0)
			return (0);
		rl_outstream = stderr;
		args.str = readline("$>");
		if (!args.str)
		{
			close(args.tin);
			close(args.tout);
			close(args.oin);
			close(args.oout);
			free_array(env);
			return (0);
		}
		if (ft_parse(&args, &data) == 1 && args.str)
			launch_ast(env, &args, &data);
		free_all(&args, &data);
		close(args.tin);
		// close(args.tout);
		close(args.oin);
		close(args.oout);
	}
	free_all(&args, &data);
	return (0);
}
