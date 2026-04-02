/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_cont.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborel <aborel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:47:21 by aborel            #+#    #+#             */
/*   Updated: 2025/09/09 13:09:01 by aborel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handler_int(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sig = 130;
}

void	set_exit_status(int status)
{
	if (WIFEXITED(status))
		g_sig = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_sig = 128 + WTERMSIG(status);
	else
		g_sig = 1;
}
