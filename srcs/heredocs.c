/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tniambi- <tniambi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:15:16 by aborel            #+#    #+#             */
/*   Updated: 2025/09/15 13:45:40 by tniambi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*continue_prompting(char *line, char *end, int len, int fd)
{
	while (line && (ft_strncmp(line, end, len) || (int)ft_strlen(line) != len))
	{
		write(fd, line, ft_strlen(line));
		free(line);
		line = readline("> ");
		write(fd, "\n", 1);
	}
	return (line);
}

int	ft_lseek(int fd, char *file)
{
	close(fd);
	fd = open(file, O_RDWR, 0600);
	return (fd);
}

int	create_tmp(t_tree *node, t_env **env)
{
	int		fd;
	int		i;
	char	*name;
	char	*dir;

	i = -1;
	dir = expanded_word("TMP", env);
	while (++i < 1000)
	{
		name = create_name(dir, i);
		fd = open(name, O_CREAT | O_EXCL | O_RDWR, 0600);
		if (fd != -1)
		{
			node->heredoc = name;
			return (fd);
		}
		free(name);
		if (errno != EEXIST)
		{
			perror("Open error");
			return (-1);
		}
	}
	perror("Could not create heredoc file.\n");
	return (-1);
}

int	heredoc(char *s, t_tree *node, t_env **env)
{
	int		fd;
	int		len;

	if (node->heredoc)
		delete_heredoc(node);
	fd = create_tmp(node, env);
	if (fd == -1)
		return (-1);
	if (node->fd_in && node->fd_in != STDIN_FILENO)
		close(node->fd_in);
	node->fd_in = fd;
	len = read_heredoc(s, fd, node);
	node->fd_in = ft_lseek(fd, node->heredoc);
	if (node->fd_in == -1)
		return (perror("heredoc error"), -1);
	node->type = 'a';
	return (len + 2);
}
