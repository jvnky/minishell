/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 04:37:46 by cofoundo          #+#    #+#             */
/*   Updated: 2023/10/24 04:39:25 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**setup(char **enve)
{
	char	**env;

	env = NULL;
	g_ret_number = 0;
	setup_term();
	run_signals(1);
	env = init_env(enve, env);
	return (env);
}

int	contrl_d(t_args *args, char **env)
{
	close(args->tout);
	close(args->tin);
	fdcloser(args);
	free_array(env);
	return (0);
}
