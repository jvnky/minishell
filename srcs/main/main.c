/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 08:48:52 by cofoundo          #+#    #+#             */
/*   Updated: 2023/10/22 04:41:16 by ychair           ###   ########.fr       */
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
void printAST(t_node* root) {
    if (root == NULL) {
        return;
    }

    printf("Command: %s\n", root->command);

    if (root->numarguments > 0) {
        printf("Arguments: ");
        for (int i = 0; i < root->numarguments; i++) {
           printf(" i == %d    %s ", i,root->arguments[i]);
        }
        printf("\n");
    }
     if (root->ipf != NULL) {
        printf("Input File: %s  ", root->ipf);
         if(root->app == 1)
            printf("  app1\n");
        else if (root->app == 2)
            printf("  app2\n");
        else
            printf("\n");
    }

    if (root->opf != NULL) {
        printf("Output File: %s ", root->opf);
        if(root->app == 1)
            printf("  app1\n");
        else if (root->app == 2)
            printf("  app2\n");
        else
            printf("\n");
    }
   // printf("Left Node:\n");
     printAST(root->left);

    //printf("Right Node:\n");
    printAST(root->right);
}


void	launch_ast(char **env, t_args *args, t_data *data)
{
	t_node	*root;
	t_num	num;
	// args->oin = dup(STDIN_FILENO);
	// args->oout = dup(STDOUT_FILENO);
	num.i = 0;
	// num->j = 0;
	if (args->str[0])
	{
		add_history(args->str);

		int i = 0;
		while(data->parse[i])
		{
			int j = 0;
			while(data->parse[i][j])
			{
				printf("%s  i = %d j = %d\n",data->parse[i][j],i,j);
				j++;
			}
			i++;
		}

		root = buildast(data->parse, data->parse_i + 1, &num);
		printAST(root);
		if (root)
			env = executeast(root, env, args, data);

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
			close(args.tout);
			close(args.tin);
			fdcloser(&args);
			free_array(env);
			// free_all(&args, &data);
			return (0);
		}
		if (ft_parse(&args, &data) == 1 && args.str)
			launch_ast(env, &args, &data);
		free_all(&args, &data);
		fdcloser(&args);
	}
	free_all(&args, &data);
	return (0);
}
