/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_new_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tniambi- <tniambi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:14:08 by tniambi-          #+#    #+#             */
/*   Updated: 2025/09/08 13:07:38 by tniambi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

static char	*find_separator(char *env)
{
	char	*separator;

	separator = ft_strchr(env, '=');
	return (separator);
}

static t_env	*minimal_env(void)
{
	char	cwd[PATH_MAX];
	t_env	*env_list;

	env_list = NULL;
	if (getcwd(cwd, sizeof(cwd)))
		add_env_var(&env_list, "PWD", cwd);
	add_env_var(&env_list, "SHLVL", "1");
	return (env_list);
}

t_env	*create_env_list(char **env)
{
	t_env	*env_list;
	int		i;
	char	*key;
	char	*value;
	char	*separator;

	if (!env || !*env)
		return (minimal_env());
	env_list = NULL;
	i = 0;
	while (env[i])
	{
		separator = find_separator(env[i]);
		if (!separator)
		{
			i++;
			continue ;
		}
		key = ft_substr(env[i], 0, separator - env[i]);
		value = separator + 1;
		add_env_var(&env_list, key, value);
		free(key);
		i++;
	}
	return (env_list);
}

t_env	*new_env_node(const char *key, const char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	if (!new_node->key || !new_node->value)
	{
		free(new_node->key);
		free(new_node->value);
		free(new_node);
		return (NULL);
	}
	return (new_node);
}

void	add_env_var(t_env **env, const char *key, const char *value)
{
	t_env	*new_node;
	t_env	*current;

	new_node = new_env_node(key, value);
	if (!new_node)
		return ;
	if (*env == NULL)
	{
		*env = new_node;
		return ;
	}
	current = *env;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
}
