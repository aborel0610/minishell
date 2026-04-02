/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborel <aborel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:20:15 by aborel            #+#    #+#             */
/*   Updated: 2025/09/09 14:57:52 by aborel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

int	is_symbol(char c)
{
	if (c == '|')
		return (1);
	return (0);
}

int	is_whitespace(char c)
{
	if (c && ((c == ' ' || (c > 8 && c < 14)) || c == '\0'))
		return (1);
	return (0);
}

int	peek(char *s, char *search)
{
	int	i;
	int	len;
	int	white;

	if (!s || !search || !*s || !*search)
		return (0);
	i = 0;
	white = 0;
	len = ft_strlen(search);
	while (s[white] && is_whitespace(s[white]))
		white++;
	if ((int)ft_strlen(&s[white]) < len)
		return (0);
	while (i < len && s[i + white])
	{
		if (s[i + white] != search[i])
			return (0);
		i++;
	}
	if (i == len)
		return (1);
	return (0);
}

int	is_end(char c, int *quote)
{
	if (!c)
		return (1);
	if (is_symbol(c) && quote[0] < 0 && quote[1] < 0)
		return (1);
	return (0);
}

char	*add_quotes(char *s)
{
	char	*line;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(s);
	line = (char *)malloc((len + 3) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	line[0] = '"';
	j = 1;
	while (s[i])
	{
		line[j] = s[i];
		j++;
		i++;
	}
	line[j] = '"';
	line[j + 1] = 0;
	free(s);
	return (line);
}
