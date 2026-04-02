/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tniambi- <tniambi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:24:04 by tniambi-          #+#    #+#             */
/*   Updated: 2025/09/08 13:25:11 by tniambi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

int	is_basic_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "env", 3) == 0 && cmd[3] == '\0')
		return (1);
	if (ft_strncmp(cmd, "pwd", 3) == 0 && cmd[3] == '\0')
		return (1);
	if (ft_strncmp(cmd, "echo", 4) == 0 && cmd[4] == '\0')
		return (1);
	if (ft_strncmp(cmd, "cd", 2) == 0 && cmd[2] == '\0')
		return (1);
	return (0);
}

int	is_advanced_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "unset", 5) == 0 && cmd[5] == '\0')
		return (1);
	if (ft_strncmp(cmd, "exit", 4) == 0 && cmd[4] == '\0')
		return (1);
	if (ft_strncmp(cmd, "export", 6) == 0 && cmd[6] == '\0')
		return (1);
	return (0);
}

int	is_builtin(char **argv)
{
	if (!argv || !argv[0])
		return (0);
	if (is_basic_builtin(argv[0]))
		return (1);
	if (is_advanced_builtin(argv[0]))
		return (1);
	return (0);
}

void	setup_builtin_fds(t_command *cmd, int *saved_stdin,
			int *saved_stdout)
{
	if (cmd->input != STDIN_FILENO)
	{
		*saved_stdin = dup(STDIN_FILENO);
		dup2(cmd->input, STDIN_FILENO);
	}
	if (cmd->output != STDOUT_FILENO)
	{
		*saved_stdout = dup(STDOUT_FILENO);
		dup2(cmd->output, STDOUT_FILENO);
	}
}

void	restore_builtin_fds(int saved_stdin, int saved_stdout)
{
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}
