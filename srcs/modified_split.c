/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modified_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborel <aborel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:03:46 by aborel            #+#    #+#             */
/*   Updated: 2025/09/17 18:06:34 by aborel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	mod_count_word(const char *s, char c)
{
	int	i;
	int	count;
	int	quotes[2];
	int	in_word;

	i = 0;
	count = 0;
	in_word = 0;
	setup_quote(quotes);
	while (s[i])
	{
		is_quote(s[i], quotes);
		if (ft_iset(s[i], c, quotes) == 0)
		{
			if (!in_word)
			{
				in_word = 1;
				count++;
			}
		}
		else
			in_word = 0;
		i++;
	}
	return (count);
}

static char	*mod_copy(const char *s, char c, int *end_pos)
{
	size_t	i;
	size_t	j;
	int		quotes[2];
	char	*dup;

	i = 0;
	setup_quote(quotes);
	while (s[i] && ft_iset(s[i], c, quotes) == 0)
		is_quote(s[i++], quotes);
	*end_pos = i;
	dup = malloc(sizeof(char) * (i + 1));
	if (!dup)
		return (NULL);
	j = 0;
	i = 0;
	setup_quote(quotes);
	while (s[i] && ft_iset(s[i], c, quotes) == 0)
	{
		is_quote(s[i], quotes);
		dup[j++] = s[i++];
	}
	dup[j] = '\0';
	return (dup);
}

static char	**mod_filltab(char **tab, const char *s, char c)
{
	size_t	i;
	size_t	k;
	int		quotes[2];
	int		end_pos;

	i = 0;
	k = 0;
	while (s[i])
	{
		setup_quote(quotes);
		while (s[i] && ft_iset(s[i], c, quotes) == 1)
			is_quote(s[i++], quotes);
		if (s[i])
		{
			tab[k] = mod_copy(&s[i], c, &end_pos);
			if (!tab[k])
				return (NULL);
			k++;
			i += end_pos;
		}
	}
	tab[k] = NULL;
	return (tab);
}

char	**modified_split(const char *s, char c)
{
	char	**tab;
	int		words;

	if (!s)
		return (NULL);
	words = mod_count_word(s, c);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	if (!mod_filltab(tab, s, c))
		return (NULL);
	return (tab);
}
