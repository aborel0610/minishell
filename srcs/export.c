/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tniambi- <tniambi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:54:57 by tniambi-          #+#    #+#             */
/*   Updated: 2025/09/09 12:49:02 by tniambi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"   

static void	insert_sorted(t_env **sort_env, t_env *new_node)
{
	t_env	*temp;

	if (!*sort_env
		|| ft_strncmp(new_node->key, (*sort_env)->key,
			ft_strlen(new_node->key)) < 0)
	{
		new_node->next = *sort_env;
		*sort_env = new_node;
	}
	else
	{
		temp = *sort_env;
		while (temp->next && ft_strncmp(new_node->key, temp->next->key,
				ft_strlen(new_node->key)) > 0)
			temp = temp->next;
		new_node->next = temp->next;
		temp->next = new_node;
	}
}

static t_env	*create_declare_node(t_env *current, char *declare)
{
	char	*temp;
	t_env	*new_node;

	temp = ft_strjoin(declare, current->key);
	new_node = new_env_node(temp, current->value);
	if (temp)
		free(temp);
	return (new_node);
}

t_env	*sort_env_list(t_env *env)
{
	t_env	*sorted;
	t_env	*current;
	t_env	*new_node;
	char	*declare;

	if (!env)
		return (NULL);
	sorted = NULL;
	current = env;
	declare = ft_strdup("declare -x ");
	while (current)
	{
		new_node = create_declare_node(current, declare);
		if (!new_node)
		{
			free(declare);
			free_env_list(sorted);
			return (NULL);
		}
		insert_sorted(&sorted, new_node);
		current = current->next;
	}
	return (free(declare), sorted);
}

static int	process_export_arg(char *arg, t_env **env)
{
	char	*equal_pos;
	char	*key;
	char	*value;
	t_env	*existing;

	equal_pos = mod_strchr(arg, '=');
	if (!equal_pos || equal_pos == arg)
		return (1);
	key = ft_strndup(arg, equal_pos - arg);
	value = ft_strdup(equal_pos + 1);
	if (!key || !value)
	{
		free(key);
		free(value);
		return (0);
	}
	existing = find_var(*env, key);
	if (existing)
		update_existing(existing, value);
	else
		add_env_var(env, key, value);
	free(key);
	free(value);
	return (1);
}

int	ft_export(char **argv, t_env **env)
{
	int	i;

	g_sig = 0;
	if (!argv || !env)
		return (1);
	if (!argv[1])
		return (check_export(*env));
	i = 1;
	while (argv[i])
	{
		process_export_arg(argv[i], env);
		i++;
	}
	return (g_sig);
}
