/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tniambi- <tniambi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:46:38 by tniambi-          #+#    #+#             */
/*   Updated: 2025/09/09 13:05:59 by tniambi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

char	*ft_strndup(char *s, int delim)
{
	int		i;
	char	*new;

	i = 0;
	if (!s || delim <= 0)
		return (NULL);
	new = malloc(sizeof(char) * (delim + 1));
	if (!new)
		return (NULL);
	while (i < delim && s[i])
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

t_env	*find_var(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0
			&& ft_strlen(env->key) == ft_strlen(key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

t_env	*update_existing(t_env *existing, char *value)
{
	free(existing->value);
	existing->value = ft_strdup(value);
	return (existing);
}

int	check_export(t_env *env)
{
	t_env	*sorted;
	int		result;

	sorted = sort_env_list(env);
	result = print_env_list(sorted);
	if (sorted)
		free_env_list(sorted);
	return (result);
}
