/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: ychair <ychair@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 22:47:09 by cofoundo          #+#    #+#             */
/*   Updated: 2023/09/05 05:08:21 by ychair           ###   ########.fr       */
=======
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 22:47:09 by cofoundo          #+#    #+#             */
/*   Updated: 2023/06/22 01:19:01 by cofoundo         ###   ########.fr       */
>>>>>>> 26f2e0fef931109ebf20856787daf6b93424e742
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pwd(void)
{
    char *path;
<<<<<<< HEAD
    // puts("FUCK\n");
    path = getcwd(NULL, 0);
    // printf("PATH = %s\n",path);
=======
    
    path = getcwd(NULL, 0);
>>>>>>> 26f2e0fef931109ebf20856787daf6b93424e742
    if (!path)
        return (1);
    else
        printf("%s\n", path);
    return (0);
}