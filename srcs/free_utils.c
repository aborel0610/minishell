/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborel <aborel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 04:23:58 by tniambi-          #+#    #+#             */
/*   Updated: 2025/09/09 13:17:10 by aborel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_env_list(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		free(env->key);
		free(env->value);
		temp = env;
		env = env->next;
		free(temp);
	}
}

void	free_perror(char *str, char **cmd_arg, char **paths)
{
	perror(str);
	if (cmd_arg != NULL)
		free_split(cmd_arg);
	if (paths != NULL)
		free_split(paths);
}

void	clean_cmd(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->args)
		free_split(cmd->args);
	if (cmd->pathnames)
		free_split(cmd->pathnames);
	if (cmd->path)
		free(cmd->path);
}

void	cleanup_heredocs(t_tree *root)
{
	t_tree	*node;

	node = root;
	while (node)
	{
		if (node->heredoc)
			delete_heredoc(node);
		node = node->next;
	}
}
