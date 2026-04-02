/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tniambi- <tniambi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 00:05:17 by tniambi-          #+#    #+#             */
/*   Updated: 2025/09/09 12:47:35 by tniambi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

static int	check_echo_flag(char **args)
{
	if (args[1] && ft_strncmp(args[1], "-n", 2) == 0)
		return (1);
	return (0);
}

static void	print_echo_args(char **args, int start_index)
{
	int	i;

	i = start_index;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
}

int	ft_echo(t_command *cmd)
{
	int		no_newline;
	int		start_index;
	char	**args;

	args = cmd->args;
	no_newline = check_echo_flag(args);
	start_index = 1;
	if (no_newline)
		start_index = 2;
	print_echo_args(args, start_index);
	if (!no_newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
