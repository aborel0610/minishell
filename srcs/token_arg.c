/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tniambi- <tniambi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:50:32 by aborel            #+#    #+#             */
/*   Updated: 2025/09/15 14:39:59 by tniambi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

t_len_cmd	redir_len(t_len_cmd cmd, char *s, t_tree *tree, t_env **env)
{
	int	new_redir;

	new_redir = redirections(&s[cmd.i], tree, env);
	cmd.i += new_redir - 1;
	cmd.redir += new_redir;
	return (cmd);
}

char	*build_word(int len, int i, char *s)
{
	char	*word;

	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (0);
	word[len] = '\0';
	while (--len >= 0)
		word[len] = s[i + len];
	return (word);
}

char	*next_word(char *s)
{
	int		i;
	int		len;
	char	*word;
	int		quote[2];

	if (!s)
		return (NULL);
	quote[0] = -1;
	quote[1] = -1;
	i = 0;
	while (s[i] && is_whitespace(s[i]))
		i++;
	len = 0;
	while (s[i + len])
	{
		is_quote(s[i + len], quote);
		if (is_whitespace(s[i + len]) && (quote[0] < 0 && quote[1] < 0))
			break ;
		len ++;
	}
	word = build_word(len, i, s);
	return (word);
}

int	len_next_word(char *s)
{
	int		i;
	int		len;
	int		quote[2];

	if (!s)
		return (0);
	quote[0] = -1;
	quote[1] = -1;
	i = 0;
	while (s[i] && is_whitespace(s[i]))
		i++;
	len = 0;
	while (s[i + len])
	{
		is_quote(s[i + len], quote);
		if (is_whitespace(s[i + len]) && (quote[0] < 0 && quote[1] < 0))
			break ;
		len ++;
	}
	return (i + len);
}

int	skip_redir(char *s)
{
	int	i;

	i = 1;
	if ((s[0] == '>' && s[1] == '>') || (s[0] == '<' && s[1] == '<'))
		i++;
	i += skipword(&s[i]);
	i += skipwhite(&s[i]);
	return (i);
}
