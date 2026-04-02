/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tniambi- <tniambi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:42:49 by aborel            #+#    #+#             */
/*   Updated: 2025/09/09 12:46:59 by tniambi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

void	free_root(t_tree *root)
{
	t_tree	*next;
	t_tree	*cur;

	cur = root;
	while (cur->prev)
		cur = cur->prev;
	while (cur)
	{
		if (cur->arg)
			free(cur->arg);
		if (cur->input)
			free(cur->input);
		if (cur->output)
			free(cur->output);
		if (cur->heredoc)
			delete_heredoc(cur);
		if (cur->fd_in)
			close(cur->fd_in);
		if (cur->fd_out)
			close(cur->fd_out);
		next = cur->next;
		free(cur);
		cur = next;
	}
}

void	close_input(t_tree *node)
{
	close(node->fd_in);
	node->fd_in = 0;
	free(node->input);
}

void	close_output(t_tree *node)
{
	close(node->fd_out);
	node->fd_out = 0;
	free(node->output);
}

void	delete_heredoc(t_tree *node)
{
	if (node->heredoc)
	{
		if (node->fd_in && node->fd_in != STDIN_FILENO)
			close(node->fd_in);
		unlink(node->heredoc);
		free(node->heredoc);
		node->heredoc = NULL;
		node->fd_in = STDIN_FILENO;
	}
}

void	cleanup(t_tree *root, t_command *cmd)
{
	int	i;

	i = 0;
	if (root)
		free_root(root);
	if (cmd)
	{
		while (i < cmd->cmd_count)
		{
			clean_cmd(&cmd[i]);
			i++;
		}
		free(cmd);
	}
}
