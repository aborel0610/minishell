/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tniambi- <tniambi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:56:41 by tniambi-          #+#    #+#             */
/*   Updated: 2025/09/09 12:43:24 by tniambi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborel <aborel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:56:41 by tniambi-          #+#    #+#             */
/*   Updated: 2025/08/26 16:40:23 by aborel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

char	**get_pathnames(char **envp)
{
	char	**pathnames;

	pathnames = NULL;
	while (envp && *envp)
	{
		if (ft_strncmp(*envp, "PATH", 4) == 0)
			break ;
		envp++;
	}
	if (envp && *envp)
		pathnames = ft_split(*envp + 5, ':');
	return (pathnames);
}

static char	*handle_absolute_path(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	perror(cmd);
	g_sig = 127;
	return (NULL);
}

static char	*check_path_directories(char *cmd, char **pathnames)
{
	char	*path;
	char	*full;

	while (*pathnames)
	{
		path = ft_strjoin(*pathnames, "/");
		if (!path)
			return (NULL);
		full = ft_strjoin(path, cmd);
		free(path);
		if (!full)
			return (NULL);
		if (access(full, X_OK) == 0)
			return (full);
		free(full);
		pathnames++;
	}
	return (NULL);
}

char	*get_command_path(char *cmd, char **pathnames)
{
	char	*result;

	if (!cmd || !*cmd)
		return (NULL);
	if (is_builtin(&cmd))
		return (ft_strdup("built-in"));
	if (ft_strchr(cmd, '/'))
		return (handle_absolute_path(cmd));
	if (!pathnames)
		return (NULL);
	result = check_path_directories(cmd, pathnames);
	if (!result)
	{
		g_sig = 127;
		perror(cmd);
	}
	return (result);
}

t_command	create_command(char **args, t_env **env, t_tree *node)
{
	t_command	cmd;
	char		**envp;
	char		**pathnames;

	if (!args || !args[0] || !env || !*env)
		return (null_command());
	cmd.env = env;
	cmd.args = args;
	envp = env_to_array(*env);
	pathnames = get_pathnames(envp);
	cmd.path = get_command_path(args[0], pathnames);
	cmd.pathnames = pathnames;
	set_command_fds(&cmd, node);
	cmd.argc = count_args(args);
	free_split(envp);
	return (cmd);
}
