/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborel <aborel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 00:10:14 by tniambi-          #+#    #+#             */
/*   Updated: 2025/09/09 12:27:22 by aborel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

//    UNSET
int	is_valid_identifier(const char *s)
{
	int	i;

	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (0);
	i = 1;
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	unset_env_var(const char *key, t_env **env)
{
	t_env	*prev;
	t_env	*curr;

	prev = NULL;
	curr = *env;
	while (curr)
	{
		if (ft_strncmp(curr->key, key, ft_strlen(key)) == 0
			&& ft_strlen(curr->key) == ft_strlen(key))
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return (0);
		}
		prev = curr;
		curr = curr->next;
	}
	return (1);
}

int	ft_unset(char **args, t_env **env)
{
	int	i;
	int	exit_status;

	exit_status = 0;
	i = 1;
	if (!args || !env)
		return (1);
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_putstr_fd("unset: invalid identifier: ", 2);
			ft_putendl_fd(args[i], 2);
			exit_status = 1;
		}
		else
			unset_env_var(args[i], env);
		i++;
	}
	return (exit_status);
}
