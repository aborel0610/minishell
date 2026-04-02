/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_cont.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborel <aborel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:42:42 by aborel            #+#    #+#             */
/*   Updated: 2025/09/17 17:50:53 by aborel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	create_pipes(int pipes[][2], int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			return (-1);
		}
		i++;
	}
	return (0);
}

/*void	close_pipe_child(int pipes[][2], int num_pipes, int cmd_index)
{
	int	j;

	j = 0;
	while (j < num_pipes)
	{
		if (j != cmd_index -1)
			close(pipes[j][0]);
		if (j != cmd_index)
			close(pipes[j][1]);
		j++;
	}
}*/

void	close_all_pipes(int pipes[][2], int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

static void	close_in_child(t_pipeline *pipeline, int i)
{
	int	j;

	j = 0;
	while (j < pipeline->cmd_count)
	{
		if (j != i)
		{
			if (pipeline->commands[j].input != STDIN_FILENO)
				close(pipeline->commands[j].input);
			if (pipeline->commands[j].output != STDOUT_FILENO)
				close(pipeline->commands[j].output);
		}
		j++;
	}
}

void	setup_child_fds(t_pipeline *pipeline, int pipes[][2], int i)
{
	int	input_fd;
	int	output_fd;

	input_fd = get_input_fd(pipeline, pipes, i);
	output_fd = get_output_fd(pipeline, pipes, i);
	if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		if (input_fd != pipeline->commands[i].input)
			close(input_fd);
	}
	if (output_fd != STDOUT_FILENO)
	{
		dup2(output_fd, STDOUT_FILENO);
		if (output_fd != pipeline->commands[i].output)
			close(output_fd);
	}
	close_in_child(pipeline, i);
	close_all_pipes(pipes, pipeline->cmd_count - 1);
}
