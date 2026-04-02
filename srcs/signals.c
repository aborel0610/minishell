/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tniambi- <tniambi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:34:20 by aborel            #+#    #+#             */
/*   Updated: 2025/09/15 14:30:39 by tniambi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handler_child(int signal)
{
	(void)signal;
	write(1, "\n", 1);
}

void	signals_child_mode(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	handler_heredoc(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	g_sig = 130;
}

void	signals_heredoc_mode(void)
{
	signal(SIGINT, handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	reset_signals(int bool)
{
	if (bool)
	{
		signal(SIGINT, handler_int);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, handler_child);
		signal(SIGQUIT, handler_child);
	}
}
