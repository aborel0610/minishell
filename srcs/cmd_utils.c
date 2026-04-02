/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tniambi- <tniambi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:00:45 by tniambi-          #+#    #+#             */
/*   Updated: 2025/09/09 12:47:10 by tniambi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

void	set_command_fds(t_command *cmd, t_tree *node)
{
	if (!node || (node->fd_in) == 0)
		cmd->input = STDIN_FILENO;
	else
		cmd->input = node->fd_in;
	if (!node || (node->fd_out) == 0)
		cmd->output = STDOUT_FILENO;
	else
		cmd->output = node->fd_out;
}

int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count] != NULL)
		count++;
	return (count);
}

t_command	null_command(void)
{
	t_command	cmd;

	cmd.args = NULL;
	cmd.path = NULL;
	cmd.pathnames = NULL;
	cmd.argc = 0;
	cmd.input = STDIN_FILENO;
	cmd.output = STDOUT_FILENO;
	cmd.env = NULL;
	cmd.cmd_count = 0;
	return (cmd);
}
