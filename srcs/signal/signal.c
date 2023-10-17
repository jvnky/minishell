/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 03:17:51 by cofoundo          #+#    #+#             */
/*   Updated: 2023/10/17 05:23:25 by ychair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_signals(int sig)
{
	if (sig == 1)
	{

		signal(SIGINT, restore_prompt); // ctrl C

		signal(SIGQUIT, SIG_IGN); // slash
	}

}
void	restore_prompt(int sig)
{
	// g_ret_number = 130;
	// write(1,"\b\b\033[K\n",5);
		write(1, "\n", 1);
	// write(1, "$> ", 3);
        // rl_replace_line("", 0);
		// rl_on_new_line();
        // rl_redisplay();

	(void)sig;
}

void setup_term(void) {
    struct termios t;
    tcgetattr(0, &t);
    t.c_lflag &= ~ECHOCTL;
    tcsetattr(0, TCSANOW, &t);
}
