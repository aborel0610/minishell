/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborel <aborel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 03:20:48 by tniambi-          #+#    #+#             */
/*   Updated: 2025/09/09 13:27:16 by aborel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_single_command(t_command *cmd)
{
	if (!cmd)
		return ;
	cmd->args = NULL;
	cmd->path = NULL;
	cmd->pathnames = NULL;
	cmd->argc = 0;
	cmd->input = STDIN_FILENO;
	cmd->output = STDOUT_FILENO;
	cmd->env = NULL;
	cmd->cmd_count = 0;
}

static t_command	*allocate_and_init_commands(int nb_count)
{
	t_command	*commands;
	int			i;

	commands = (t_command *)malloc(sizeof(t_command) * nb_count);
	if (!commands)
		return (NULL);
	i = 0;
	while (i < nb_count)
	{
		init_single_command(&commands[i]);
		i++;
	}
	return (commands);
}

static int	fill_command_array(t_command *commands, t_tree *root, t_env **env)
{
	t_tree	*cur_tree;
	char	**split;
	int		cmd_index;

	cmd_index = 0;
	cur_tree = root;
	while (cur_tree && cmd_index < root->pipe + 1)
	{
		if (cur_tree->arg == NULL || cur_tree->parsing_error)
		{
			cur_tree = cur_tree->next;
			continue ;
		}
		split = modified_split(cur_tree->arg, ' ');
		if (!split)
			return (-1);
		commands[cmd_index] = create_command(split, env, cur_tree);
		cur_tree = cur_tree->next;
		cmd_index++;
	}
	return (0);
}

t_command	*init_commands(t_tree **root, t_env **env)
{
	t_command	*commands;
	int			nb_count;

	nb_count = (*root)->pipe + 1;
	commands = allocate_and_init_commands(nb_count);
	if (!commands)
		return (NULL);
	if (fill_command_array(commands, *root, env) == -1)
	{
		free(commands);
		return (NULL);
	}
	return (commands);
}

t_command	*null_command_parse(void)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->path = NULL;
	cmd->pathnames = NULL;
	cmd->argc = 0;
	cmd->input = STDIN_FILENO;
	cmd->output = STDOUT_FILENO;
	cmd->env = NULL;
	cmd->cmd_count = 0;
	return (cmd);
}
