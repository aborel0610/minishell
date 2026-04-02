/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec_cont.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborel <aborel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:17:48 by aborel            #+#    #+#             */
/*   Updated: 2025/09/09 13:27:43 by aborel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pre_exec_check(t_tree *root)
{
	if (root->error)
		return (0);
	if (!root->arg)
		return (1);
	if (root->arg[0] == '#')
	{
		g_sig = 0;
		return (0);
	}
	if (!ft_strncmp(root->arg, ":", ft_strlen(root->arg)))
	{
		g_sig = 0;
		return (0);
	}
	return (1);
}

void	build_pipeline(t_command *command, t_tree *root)
{
	t_pipeline	pipeline;

	pipeline.commands = command;
	pipeline.cmd_count = root->pipe + 1 - root->tot_pars_error;
	command->cmd_count = pipeline.cmd_count;
	pipeline.root = root;
	quotes(&pipeline);
	execute_pipeline(&pipeline, root);
}

int	parse_execute(char *line, t_env **env)
{
	t_tree		*root;
	t_command	*command;
	t_command	*tmp;

	if (!line || !*line)
		return (g_sig = 0);
	command = null_command_parse();
	root = NULL;
	root = make_tree(line, env);
	if (!root)
		return (perror("malloc failed"), 1);
	if (pre_exec_check(root))
	{
		expand(root, env);
		tmp = init_commands(&root, env);
		if (tmp)
		{
			free(command);
			command = tmp;
		}
		build_pipeline(command, root);
	}
	cleanup(root, command);
	return (g_sig);
}
