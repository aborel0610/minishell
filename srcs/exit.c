/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborel <aborel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:34:31 by tniambi-          #+#    #+#             */
/*   Updated: 2025/09/09 11:21:15 by aborel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

static int	check_sign_and_advance(char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

static int	parse_number(char *str, int i, long long *num)
{
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		if (*num > (LLONG_MAX - (str[i] - '0')) / 10)
			return (0);
		*num = *num * 10 + (str[i] - '0');
		i++;
	}
	return (1);
}

static int	is_valid_long_long(char *str, long long *result)
{
	int			i;
	int			sign;
	long long	num;

	if (!str || !str[0])
		return (0);
	i = 0;
	num = 0;
	sign = check_sign_and_advance(str, &i);
	if (!str[i])
		return (0);
	if (!parse_number(str, i, &num))
		return (0);
	*result = num * sign;
	return (1);
}

static void	exit_cleanup(t_command *cmd, t_tree *root, int code)
{
	free_env_list(*cmd->env);
	cleanup(root, cmd);
	g_sig = code;
	exit(code);
}

int	ft_exit(t_command *cmd, t_tree *root)
{
	long long	exit_code;
	char		**args;

	args = cmd->args;
	write(1, "exit\n", 5);
	if (args[1] && args[2])
	{
		write(2, "minishell: exit: too many arguments\n", 37);
		g_sig = 1;
		return (1);
	}
	if (!args[1])
		exit_cleanup(cmd, root, g_sig);
	if (!is_valid_long_long(args[1], &exit_code))
	{
		write(2, "minishell: exit: ", 17);
		write(2, cmd->args[1], ft_strlen(cmd->args[1]));
		write(2, ": numeric argument required\n", 28);
		exit_cleanup(cmd, root, 2);
	}
	exit_cleanup(cmd, root, (int)(exit_code % 256));
	return (0);
}
