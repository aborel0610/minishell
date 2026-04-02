/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tniambi- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:21:57 by tniambi-          #+#    #+#             */
/*   Updated: 2024/12/06 14:11:53 by tniambi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	ft_iset(char s, char c)
{
	if (s == c || s == '\0')
		return (1);
	else
		return (0);
}

static int	ft_count_word(const char *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (ft_iset(s[i], c) == 0 && ft_iset(s[i + 1], c) == 1)
			count++;
		i++;
	}
	return (count);
}

static char	*ft_copy(const char *s, char c)
{
	size_t	i;
	size_t	j;
	char	*dup;

	i = 0;
	j = 0;
	while (ft_iset(s[i], c) == 0)
		i++;
	dup = malloc(sizeof (char) * i + 1);
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (ft_iset(s[i], c) == 0)
	{
		dup[j] = s[i];
		i++;
		j++;
	}
	dup[j] = '\0';
	return (dup);
}

static char	**ft_filltab(char **tab, const char *s, char c)
{
	size_t	i;
	size_t	start;
	size_t	k;

	k = 0;
	i = 0;
	while (s[i])
	{
		start = i;
		while (ft_iset(s[i], c) == 0)
		{	
			if (ft_iset(s[i], c) == 0 && ft_iset(s[i + 1], c) == 1)
			{	
				tab[k] = ft_copy(&s[start], c);
				k++;
				break ;
			}
			i++;
		}
		i++;
	}
	tab[k] = NULL;
	return (tab);
}

char	**ft_split(const char *s, char c)
{
	char	**tab;

	tab = malloc(sizeof (char *) * (ft_count_word(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	tab = ft_filltab(tab, s, c);
	return (tab);
}
