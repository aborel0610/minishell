/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tniambi- <tniambi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:36:18 by tniambi-          #+#    #+#             */
/*   Updated: 2025/09/15 14:36:11 by tniambi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	parse_heredoc_delimiter(char *s, char **end, t_tree *node)
{
	int	i;

	i = skipwhite(s);
	*end = next_word(s);
	if ((*end)[0] == 0)
	{
		if (g_sig != 2)
			error(2, "newline", node);
		while (s[i] == '<')
			i++;
		return (i);
	}
	return (0);
}

static int	handle_heredoc_line(char *line, char *end, int len, int fd)
{
	if (!line)
		return (1);
	if (g_sig == 130)
	{
		if (line)
			free(line);
		return (1);
	}
	if (ft_strncmp(line, end, len) == 0 && (int)ft_strlen(line) == len)
	{
		free(line);
		return (1);
	}
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
	return (0);
}

static void	process_heredoc_input(int fd, char *end, int len)
{
	char	*line;
	int		original_g_sig;

	original_g_sig = g_sig;
	g_sig = 0;
	signals_heredoc_mode();
	while (1)
	{
		line = readline("> ");
		if (handle_heredoc_line(line, end, len, fd))
		{
			reset_signals(1);
			if (!line)
				g_sig = original_g_sig;
			break ;
		}
	}
}

int	read_heredoc(char *s, int fd, t_tree *node)
{
	int		i;
	char	*end;
	int		len;

	i = parse_heredoc_delimiter(s, &end, node);
	if (end[0] == 0)
		return (i);
	len = ft_strlen(end);
	process_heredoc_input(fd, end, len);
	if (end)
		free(end);
	i = skipwhite(s);
	while (s[i] && is_whitespace(s[i]))
		i++;
	while (s[i] && !is_whitespace(s[i]))
		i++;
	return (i);
}
