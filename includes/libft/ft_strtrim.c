/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tniambi- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 08:15:59 by tniambi-          #+#    #+#             */
/*   Updated: 2024/12/06 13:52:22 by tniambi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//CHAMGER JUSTE LE PREMIER CHAR ?

#include"libft.h"

static size_t	ft_ischarset(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;
	size_t	j;
	char	*new;

	j = 0;
	i = 0;
	len = 0;
	while (s1[len])
		len++;
	while (s1[i] && (ft_ischarset(s1[i], set) == 1))
		i++;
	while (ft_ischarset(s1[len - 1], set) == 1)
		len--;
	if (i > len)
		return (ft_strdup(""));
	new = malloc(sizeof(char) * (len - i) + 1);
	if (new == NULL)
		return (NULL);
	while (i < len)
		new[j++] = s1[i++];
	new[j] = '\0';
	return (new);
}
