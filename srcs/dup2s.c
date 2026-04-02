/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2s.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborel <aborel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:29:55 by aborel            #+#    #+#             */
/*   Updated: 2025/09/17 17:49:57 by aborel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	change_fds(int input_fd, int output_fd)
{
	if (input_fd != STDIN_FILENO)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 input fail");
			exit(EXIT_FAILURE);
		}
		close(input_fd);
	}
	if (output_fd != STDOUT_FILENO)
	{
		if (dup2(output_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 output fail");
			exit(EXIT_FAILURE);
		}
		close(output_fd);
	}
	return ;
}

void	check_quotes(char c, int *quotes)
{
	if (c == '\'')
		quotes[0] *= -1;
	if (c == '"')
		quotes[1] *= -1;
}

void	handle_exit_command(t_command *cmd, t_tree *root)
{
	if (!ft_strncmp(cmd->args[0], "exit", 5))
	{
		free_env_list(*cmd->env);
		cleanup(root, cmd);
		exit(g_sig);
	}
}
