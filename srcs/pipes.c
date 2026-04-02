/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tniambi- <tniambi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 08:16:32 by tniambi-          #+#    #+#             */
/*   Updated: 2025/09/15 13:51:02 by tniambi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

void	execute_command(t_command *cmd, t_tree *root)
{
	change_fds(cmd->input, cmd->output);
	if (is_builtin(cmd->args) == 1)
	{
		g_sig = launch_builtin(cmd, root);
		free_env_list(*cmd->env);
		cleanup(root, cmd);
		exit(g_sig);
	}
	else if (execve(cmd->path, cmd->args, cmd->pathnames) == -1)
	{
		perror("execution");
		g_sig = 1;
		exit(g_sig);
	}
}

int	execute_single_command(t_command *cmd, t_tree *root)
{
	pid_t	pid;
	int		status;

	if (!cmd->path && !is_builtin(cmd->args))
		return (g_sig);
	if (is_builtin(cmd->args))
	{
		g_sig = launch_builtin(cmd, root);
		return (g_sig);
	}
	signals_child_mode();
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
		execute_command(cmd, root);
	reset_signals(0);
	waitpid(pid, &status, 0);
	reset_signals(1);
	handle_exit_command(cmd, root);
	set_exit_status(status);
	return (g_sig);
}

static int	fork_single_command(t_pipeline *pipeline, int pipes[][2],
							pid_t *pids, int i)
{
	t_tree	*root;

	root = pipeline->root;
	if (pipeline->commands[i].path || is_builtin(pipeline->commands[i].args))
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (perror("fork"), -1);
		if (pids[i] == 0)
		{
			setup_child_fds(pipeline, pipes, i);
			execute_command(&pipeline->commands[i], root);
			exit(g_sig);
		}
	}
	return (0);
}

int	fork_and_exec(t_pipeline *pipeline, int pipes[][2],
					pid_t *pids)
{
	int	i;

	i = 0;
	while (i < pipeline->cmd_count)
	{
		signals_child_mode();
		if (fork_single_command(pipeline, pipes, pids, i) == -1)
			return (-1);
		i++;
	}
	close_redirection_fds_parent(pipeline);
	return (0);
}

int	execute_pipeline(t_pipeline *pipeline, t_tree *root)
{
	int		num_pipes;
	int		pipes[1024][2];
	pid_t	pids[1024];

	if (!pipeline || pipeline->cmd_count == 0)
		return (-1);
	if (pipeline->cmd_count == 1)
		return (execute_single_command(&pipeline->commands[0], root));
	num_pipes = pipeline->cmd_count - 1;
	if (create_pipes(pipes, num_pipes) == -1)
		return (-1);
	if (fork_and_exec(pipeline, pipes, pids) == -1)
		return (-1);
	close_all_pipes(pipes, num_pipes);
	return (wait_for_children(pids, pipeline->cmd_count));
}
