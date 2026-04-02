/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborel <aborel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:46:27 by aborel            #+#    #+#             */
/*   Updated: 2025/09/17 18:01:42 by aborel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expanded_string(char *s, char *word, int l)
{
	int		len_key;
	int		len_value;
	int		len_total;
	char	*new_s;
	int		len;

	len_total = ft_strlen(s);
	len_value = ft_strlen(word);
	if (!word)
		len_value = 1;
	len_key = get_keylen(&s[l + 1]) + 1;
	len = len_total - len_key + len_value + 1;
	new_s = (char *)malloc(len * sizeof(char));
	if (!new_s)
		return (NULL);
	if (!word)
		new_s = copy_string(s, "", new_s, l);
	else
		new_s = copy_string(s, word, new_s, l);
	return (new_s);
}

char	*expanded_word(char *s, t_env **env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = *env;
	if (s[0] == '?')
		return (ft_itoa(g_sig));
	while (s[i] && !is_whitespace(s[i]) && s[i] != '\'' && s[i] != '"')
		i++;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, s, i))
		{
			if (tmp->key[i] == 0)
				return (tmp->value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*expansion(char *s, t_env **env, int i)
{
	char	*new_s;
	char	*word;

	word = expanded_word(&s[i + 1], env);
	new_s = expanded_string(s, word, i);
	if (s[i + 1] == '?')
		free(word);
	new_s = expand_arg(new_s, env);
	free(s);
	return (new_s);
}

char	*expand_arg(char *s, t_env **env)
{
	int		i;
	int		d_quote;
	int		s_quote;

	d_quote = 0;
	s_quote = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '"' && !s_quote)
			d_quote = !d_quote;
		if (s[i] == '\'' && !d_quote)
		{
			s_quote = !s_quote;
		}
		if (s[i] == '$' && !s_quote
			&& (s[i + 1] && !is_whitespace(s[i + 1]) && s[i + 1] != '"'))
			s = expansion(s, env, i);
		else
			i++;
	}
	return (s);
}

t_tree	*expand(t_tree *root, t_env **env)
{
	t_tree	*node;

	node = root;
	while (node)
	{
		if (node->arg)
			node->arg = expand_arg(node->arg, env);
		node = node->next;
	}
	return (root);
}
