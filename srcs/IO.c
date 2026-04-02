/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IO.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tniambi- <tniambi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:23:02 by aborel            #+#    #+#             */
/*   Updated: 2025/09/09 12:46:18 by tniambi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

int	output(char *s, t_tree *node, int flag)
{
	int		i;
	int		len;

	i = skipwhite(s);
	if (node->fd_out)
		close_output(node);
	node->output = remove_quotes(next_word(s));
	if (!node->output || node->output[0] == 0)
	{
		error(2, "", node);
		while (s[i] && (s[i] == '>' || s[i] == ' '))
			i++;
		return (i + 2);
	}
	node->fd_out = open(node->output, O_WRONLY | O_CREAT | flag, 0777);
	if (node->fd_out == -1)
		perror("Could not open file");
	len = len_next_word(&s[i]);
	return (i + len + 2);
}

int	input(char *s, t_tree *node)
{
	int		i;
	int		len;

	i = skipwhite(s);
	if (node->fd_in)
		close_input(node);
	if (node->heredoc)
		delete_heredoc(node);
	node->input = remove_quotes(next_word(s));
	if (!node->input || node->input[0] == 0)
	{
		error(2, "", node);
		while (s[i] && (s[i] == '<' || s[i] == ' '))
			i++;
		return (i + 2);
	}
	node->fd_in = open(node->input, O_RDONLY, 0777);
	if (node->fd_in == -1)
		perror("Could not open file");
	node->input = add_quotes(node->input);
	len = len_next_word(&s[i]);
	return (i + len + 2);
}

static int	handle_input_redirections(char *line, int len, t_tree *node,
									t_env **env)
{
	int	original_len;

	original_len = ft_strlen(line);
	if (peek(&line[len], "<<"))
		len += heredoc(&line[len + 2], node, env);
	else if (peek(&line[len], "<"))
	{
		len += input(&line[len + 1], node);
		if (len < original_len && line[len])
			len += redirections(&line[len], node, env);
	}
	return (len);
}

static int	handle_output_redirections(char *line, int len, t_tree *node,
									t_env **env)
{
	int	original_len;

	original_len = ft_strlen(line);
	if (peek(&line[len], ">>"))
	{
		len += output(&line[len + 2], node, 02000);
		if (len < original_len && line[len])
			len += redirections(&line[len], node, env);
	}
	else if (peek(&line[len], ">"))
	{
		len += output(&line[len + 1], node, 01000);
		if (len < original_len && line[len])
			len += redirections(&line[len], node, env);
	}
	return (len);
}

int	redirections(char *line, t_tree *node, t_env **env)
{
	int	len;
	int	original_len;

	if (!line || !*line)
		return (0);
	original_len = ft_strlen(line);
	len = skipwhite(line);
	if (len >= original_len || !line[len])
		return (len);
	if (peek(&line[len], "<<") || peek(&line[len], "<"))
		len = handle_input_redirections(line, len, node, env);
	else if (peek(&line[len], ">>") || peek(&line[len], ">"))
		len = handle_output_redirections(line, len, node, env);
	return (len);
}
