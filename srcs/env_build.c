/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tniambi- <tniambi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 06:20:48 by tniambi-          #+#    #+#             */
/*   Updated: 2025/09/09 12:47:47 by tniambi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

static char	*ft_strjoin_env(char *key, char *value)
{
	char	*result;
	int		i;
	int		j;

	if (!key || !value)
		return (NULL);
	result = malloc(strlen(key) + strlen(value) + 2);
	if (!result)
		return (NULL);
	i = -1;
	while (key[++i])
		result[i] = key[i];
	result[i++] = '=';
	j = -1;
	while (value[++j])
		result[i + j] = value[j];
	result[i + j] = '\0';
	return (result);
}

static int	ft_lstsize_env(t_env *env)
{
	if (!env)
		return (0);
	return (1 + ft_lstsize_env(env->next));
}

char	**env_to_array(t_env *env_list)
{
	char	**env_array;
	int		size;
	int		i;
	t_env	*current;

	if (!env_list)
		return (NULL);
	size = ft_lstsize_env(env_list);
	env_array = malloc(sizeof(char *) * (size + 1));
	if (!env_array)
		return (NULL);
	current = env_list;
	i = 0;
	while (current && i < size)
	{
		env_array[i] = ft_strjoin_env(current->key, current->value);
		if (!env_array[i])
			return (free_split(env_array), NULL);
		current = current->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
