/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tniambi- <tniambi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 07:01:59 by tniambi-          #+#    #+#             */
/*   Updated: 2025/09/09 12:48:38 by tniambi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

static int	exec_basic_builtin(char *bi, t_command *cmd)
{
	if (ft_strncmp(bi, "env", 3) == 0 && bi[3] == '\0')
		return (print_env_list(*cmd->env));
	if (ft_strncmp(bi, "pwd", 3) == 0 && bi[3] == '\0')
		return (ft_pwd());
	if (ft_strncmp(bi, "echo", 4) == 0 && bi[4] == '\0')
		return (ft_echo(cmd));
	if (ft_strncmp(bi, "cd", 2) == 0 && bi[2] == '\0')
		return (ft_cd(cmd->args));
	return (127);
}

static int	exec_advanced_builtin(char *bi, t_command *cmd, t_tree *root)
{
	if (ft_strncmp(bi, "unset", 5) == 0 && bi[5] == '\0')
		return (ft_unset(cmd->args, cmd->env));
	if (ft_strncmp(bi, "exit", 4) == 0 && bi[4] == '\0')
		return (ft_exit(cmd, root));
	if (ft_strncmp(bi, "export", 6) == 0 && bi[6] == '\0')
		return (ft_export(cmd->args, cmd->env));
	return (127);
}

int	execute_builtin(t_command *cmd, t_tree *root)
{
	char	*bi;
	int		result;

	bi = cmd->args[0];
	if (!bi || !bi[0])
		return (1);
	result = exec_basic_builtin(bi, cmd);
	if (result != 127)
		return (result);
	result = exec_advanced_builtin(bi, cmd, root);
	if (result != 127)
		return (result);
	return (127);
}

int	launch_builtin(t_command *cmd, t_tree *root)
{
	int	ret;
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = -1;
	saved_stdout = -1;
	setup_builtin_fds(cmd, &saved_stdin, &saved_stdout);
	ret = execute_builtin(cmd, root);
	restore_builtin_fds(saved_stdin, saved_stdout);
	return (ret);
}
