/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 08:48:52 by cofoundo          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/10/05 04:27:51 by ychair           ###   ########.fr       */
=======
/*   Updated: 2023/08/09 01:44:22 by ychair           ###   ########.fr       */
>>>>>>> 26f2e0fef931109ebf20856787daf6b93424e742
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD
// char    **env;

=======
>>>>>>> 26f2e0fef931109ebf20856787daf6b93424e742
int init_history(t_history  *history)
{
    history->str = malloc(sizeof(char*) * 1);
    if (!history->str)
        return (0);
    history->str[0] = '\0';
    history->i = 0;
    return (1);
}

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

int init_struct(t_args *args, t_data *data, t_history *history)
{
    if (init_args(args) == 0)
        return (0);
    if (init_data(data) == 0)
        return (0);
    if (init_history(history) == 0)
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


void freeAST(Node* root) {
    if (root == NULL)
        return;

    freeAST(root->left);
    freeAST(root->right);
    free(root);
}

void printAST(Node* root) {
    if (root == NULL) {
        return;
    }

    printf("Command: %s\n", root->command);

    if (root->numArguments > 0) {
        printf("Arguments: ");
        for (int i = 0; i < root->numArguments; i++) {
           printf(" i == %d    %s ", i,root->arguments[i]);
        }
        printf("\n");
    }
     if (root->inputFile != NULL) {
        printf("Input File: %s  ", root->inputFile);
         if(root->app == 1)
            printf("  app1\n");
        else if (root->app == 2)
            printf("  app2\n");
        else
            printf("\n");
    }

    if (root->outputFile != NULL) {
        printf("Output File: %s ", root->outputFile);
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
<<<<<<< HEAD

static char **cpy_env(char **env)
{
    int i;
    int j;
    char    **dst;
    
    i = -1;
    while (env[++i])
        ;
    dst = malloc(sizeof(char*) * (i + 1));
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
    return (dst);
}

int main(int ac, char **av, char **enve)
=======
int main(int ac, char **av, char **env)
>>>>>>> 26f2e0fef931109ebf20856787daf6b93424e742
{
    t_args  args;
    t_data  data;
    t_history   history;
    size_t  n;
	Node* root;
<<<<<<< HEAD
    char    **env;
=======

>>>>>>> 26f2e0fef931109ebf20856787daf6b93424e742

    
    /*utiliser isatty pour lire la commande balancer en param pour faire des shells en profondeur
    comme le shell*/
    /*modifier shlvl*/
    (void)ac;
    (void)av;
    env = cpy_env(enve);
    while (1)
    {
        
        // printf("OUT = %d  IN = %d\n",stdout,stdin);
        n = 1;
        if (init_struct(&args, &data, &history) == 0)
        {
            write(0, "Error during struct init.\n", 26);
            return (0);
        }
        write(1, "$> ", 3);
        
        getline(&args.str, &n, stdin);
<<<<<<< HEAD
        // printf("stdin = %d taillestr = %d  lol = %d , args == %s\n",fileno(stdin),ft_strlen(args.str),lol,args.str);
=======
>>>>>>> 26f2e0fef931109ebf20856787daf6b93424e742
        ft_parse(&args, &data, &history);
//		printf("!!! %c\n",*data.parse[1][0]);
        int i = 0;
        int j;
        while(data.parse[i])
        {
            j = 0;
            while(data.parse[i][j])
            {
                // printf("%s\n",data.parse[i][j]);
                // printf("i : %i j : %i\n", i, j);
                j++;
            }
            i++;
        }

        // strcmp strdup TO MAKE

        // ft_env(env,1);
        root = buildast(data.parse,i);
        printAST(root);
<<<<<<< HEAD
        if(root){
           env = executeAST(root,STDIN_FILENO,STDOUT_FILENO,env);  
        }
        else
            puts("FUCK");
        free_all(&args, &data);
        freeAST(root);
    }
=======
        executeAST(root,STDIN_FILENO,STDOUT_FILENO);

        free_all(&args, &data);
        freeAST(root);
    }
	
>>>>>>> 26f2e0fef931109ebf20856787daf6b93424e742
    free_all(&args, &data);
    return (0);
}

