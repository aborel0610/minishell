/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tniambi- <tniambi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:54:45 by tniambi-          #+#    #+#             */
/*   Updated: 2025/09/15 14:39:38 by tniambi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_redirection_fds_parent(t_pipeline *pipeline)
{
	int	i;

	i = 0;
	while (i < pipeline->cmd_count)
	{
		if (pipeline->commands[i].input != STDIN_FILENO)
		{
			close(pipeline->commands[i].input);
			pipeline->commands[i].input = STDIN_FILENO;
		}
		if (pipeline->commands[i].output != STDOUT_FILENO)
		{
			close(pipeline->commands[i].output);
			pipeline->commands[i].output = STDOUT_FILENO;
		}
		i++;
	}
}

int	wait_for_children(pid_t *pids, int cmd_count)
{
	int	i;
	int	status;
	int	last_status;

	signal(SIGINT, handler_child);
	i = 0;
	while (i < cmd_count)
	{
		if (pids[i] > 0)
		{
			waitpid(pids[i], &status, 0);
			if (i == cmd_count - 1)
			{
				if (WIFEXITED(status))
					last_status = WEXITSTATUS(status);
				else if (WIFSIGNALED(status))
					last_status = 128 + WTERMSIG(status);
				else
					last_status = 1;
			}
		}
		i++;
	}
	g_sig = last_status;
	return (last_status);
}

int	get_input_fd(t_pipeline *pipeline, int pipes[][2], int i)
{
	if (pipeline->commands[i].input != STDIN_FILENO)
		return (pipeline->commands[i].input);
	else if (i > 0)
		return (pipes[i - 1][0]);
	else
		return (STDIN_FILENO);
}

int	get_output_fd(t_pipeline *pipeline, int pipes[][2], int i)
{
	if (pipeline->commands[i].output != STDOUT_FILENO)
		return (pipeline->commands[i].output);
	else if (i < pipeline->cmd_count - 1)
		return (pipes[i][1]);
	else
		return (STDOUT_FILENO);
}

void	redirect_fd(int fd, int target_fd)
{
	if (fd != target_fd && fd >= 0)
	{
		if (dup2(fd, target_fd) == -1)
		{
			perror("dup2 failed");
			return ;
		}
		close(fd);
	}
}
