/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tniambi- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 01:09:04 by tniambi-          #+#    #+#             */
/*   Updated: 2024/12/06 15:09:51 by tniambi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	pc;

	pc = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == pc)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == pc)
		return ((char *) &s[i]);
	return (NULL);
}
