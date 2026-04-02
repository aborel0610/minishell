/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tniambi- <tniambi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:24:20 by aborel            #+#    #+#             */
/*   Updated: 2025/09/09 12:48:25 by tniambi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(int code, char *s, t_tree *node)
{
	g_sig = code;
	if (code == 2)
	{
		write(2, "minishell: syntax error near unexpected token ", 46);
		write(2, s, ft_strlen(s));
		write(2, "\n", 1);
	}
	if (code == 126)
	{
		write(2, "minishell: ", 11);
		write(2, s, ft_strlen(s));
		write(2, ": Is a directory\n", 17);
	}
	node->parsing_error = 1;
	while (node->prev)
		node = node->prev;
	node->tot_pars_error++;
}

void	pipe_error(t_tree *root, t_tree *node)
{
	if (!node->prev || !node->next)
	{
		error(2, "|", node);
		root->error = 2;
		return ;
	}
	else if (node->prev->type == 'a' && node->next->type == 'a')
	{
		root->pipe++;
		if (!node->prev->arg && node->prev->heredoc)
		{
			root->tot_pars_error++;
			node->prev->parsing_error++;
		}
	}
	else
	{
		error(2, "|", node);
		return ;
	}
}

void	arg_error(t_tree *node)
{
	int	i;

	if (node->arg[0] == '/')
	{
		i = 0;
		while (node->arg[i])
		{
			if (node->arg[i] == '/' || is_whitespace(node->arg[i]))
				i++;
			else if (node->arg[i] == '.')
				i++;
			else
				break ;
		}
		if (node->arg[i] == 0 && is_directory(node->arg))
			error(126, node->arg, node);
	}	
}

void	check_pars_errors(t_tree *root)
{
	t_tree	*node;

	node = root;
	while (node)
	{
		if (node->type == '|')
			pipe_error(root, node);
		if (node->type == 'a' && node->arg)
			arg_error(node);
		node = node->next;
	}
}

int	check_command_access(char *path, char *cmd_name)
{
	if (!path)
	{
		write(2, "minishell: ", 11);
		write(2, cmd_name, ft_strlen(cmd_name));
		write(2, ": command not found\n", 20);
		return (127);
	}
	if (access(path, F_OK) == -1)
	{
		write(2, "minishell: ", 11);
		write(2, cmd_name, ft_strlen(cmd_name));
		write(2, ": No such file or directory\n", 28);
		return (127);
	}
	if (access(path, X_OK) == -1)
	{
		write(2, "minishell: ", 11);
		write(2, cmd_name, ft_strlen(cmd_name));
		write(2, ": Permission denied\n", 20);
		return (126);
	}
	return (0);
}
