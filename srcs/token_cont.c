/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cont.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborel <aborel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:09:09 by aborel            #+#    #+#             */
/*   Updated: 2025/09/09 14:53:46 by aborel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

t_len_cmd	lencmd(char *s, t_tree *tree, int len, t_env **env)
{
	t_len_cmd	cmd;
	int			new_white;
	int			quote[2];

	cmd.i = 0;
	cmd.redir = 0;
	cmd.white = 0;
	quote[0] = -1;
	quote[1] = -1;
	while (cmd.i < len && s[cmd.i])
	{
		is_quote(s[cmd.i], quote);
		if ((s[cmd.i] == '<' || s[cmd.i] == '>')
			&& (quote[0] < 0 && quote[1] < 0))
			cmd = redir_len(cmd, s, tree, env);
		else if (is_whitespace(s[cmd.i]))
		{
			new_white = skipwhite(&s[cmd.i]) - 1;
			cmd.i += new_white;
			cmd.white += new_white;
		}
		if (cmd.i < len && s[cmd.i])
			cmd.i++;
	}
	return (cmd);
}

int	calculate_actual_size(char *s, int len)
{
	int	i;
	int	size;
	int	quote[2];

	i = 0;
	size = 0;
	quote[0] = -1;
	quote[1] = -1;
	while (i < len && s[i])
	{
		is_quote(s[i], quote);
		if ((s[i] == '<' || s[i] == '>') && (quote[0] < 0 && quote[1] < 0))
			i += skipword(&s[i + 1]) + 2;
		else if (is_whitespace(s[i]))
		{
			size++;
			i += skipwhite(&s[i]);
		}
		else
		{
			size++;
			i++;
		}
	}
	return (size);
}

int	get_type(char *s, t_tree *tree)
{
	if (is_symbol(s[0]))
		tree->type = s[0];
	else
		tree->type = 'a';
	return (0);
}

int	skipword(char *line)
{
	int	i;
	int	quote[2];

	if (!line)
		return (0);
	i = 0;
	quote[0] = -1;
	quote[1] = -1;
	while (line[i] && is_whitespace(line[i]))
		i++;
	while (line[i])
	{
		is_quote(line[i], quote);
		if (is_whitespace(line[i]) && (quote[0] < 0 && quote[1] < 0))
			break ;
		i++;
	}
	return (i);
}

int	skipwhite(char *line)
{
	int	len;

	if (!line)
		return (0);
	len = 0;
	while (line[len] && is_whitespace(line[len]))
		len++;
	return (len);
}
