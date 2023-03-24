/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 08:48:52 by cofoundo          #+#    #+#             */
/*   Updated: 2023/03/24 02:43:23 by ychair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int init_args(t_args *args)
{
    args->str = malloc(sizeof(char) * 1);
    if (!args->str)
        return (0);
    args->str[0] = '\0';
    args->i = 0;
    return (1);
}

int init_data(t_data *data)
{
    data->parse = malloc(sizeof(char**) * 2);
    if (!data->parse)
        return (0);
    data->cmd = malloc(sizeof(char) * 1);
    if (!data->cmd)
        return (0);
    data->parse[0] = '\0';
    data->parse[1] = '\0';
    data->parse_i = 0;
    data->parse_j = 0;
    data->parse_k = 0;
    return (1);
}

int init_struct(t_args *args, t_data *data)
{
    if (init_args(args) == 0)
        return (0);
    if (init_data(data) == 0)
        return (0);
    return (1);
}

int	lentab(char ***data)
{
	int i;

	i = 0;
	while (data[i])
	{
		i++;
	}
	//printf("lem = %d\n",i);
	return (i);
}

void traverseAST(ast_node* root) {
    if (root == NULL) {
        return;
    }
    printf("%s ", root->value);

    traverseAST(root->left);
    traverseAST(root->right);
}

void in_order_traversal(ast_node *root) {
    if (root != NULL) {
        in_order_traversal(root->left);
        printf("%u ", root->type);
		if (root->cmd->args != NULL)
			 printf("%s ", root->cmd->args[0]);
        in_order_traversal(root->right);
    }
}

void post_order_traversal(ast_node *root) {
    if (root != NULL) {
        post_order_traversal(root->left);
        post_order_traversal(root->right);
        printf("%s ", root->value);
    }
}

int main(int ac, char **av, char **env)
{
    t_args  args;
    t_data  data;
    size_t  n;
	ast_node* root;


    /*utiliser isatty pour lire la commande balancer en param pour faire des shells en profondeur
    comme le shell*/
    /*alors tu vas recup env parce ca contient toute les variable d environnement et du coup ez en fait*/
    (void)ac;
    (void)av;
    (void)env;
    while (1)
    {
        n = 1;
        if (init_struct(&args, &data) == 0)
        {
            write(0, "Error during struct init.\n", 26);
            return (0);
        }
        write(1, "$> ", 3);
        getline(&args.str, &n, stdin);
        ft_parse(&args, &data);
		//printf("!!! %c\n",*data.parse[1][0]);
        // int i = 0;
        // int j;
        // while(data.parse[i])
        // {
        //     j = 0;
        //     while(data.parse[i][j])
        //     {
        //         printf("%s\n",data.parse[i][j]);
        //         printf("i : %i j : %i\n", i, j);
        //         j++;
        //     }
        //     i++;
        // }
		int lent = lentab(data.parse);

		root = buildAST(data.parse,lent,root);

		runrun(root,STDIN_FILENO,STDOUT_FILENO);

		printf("Pre-order traversal:\n");
    	traverseAST(root);
        printf("\n");
        printf("in-order traversal:\n");
        in_order_traversal(root);
    	printf("\n");
        printf("post-order traversal:\n");
        post_order_traversal(root);
        printf("\n");

        free_all(&args, &data);
    }
    //free_all(&args, &data);
    return (0);
}

