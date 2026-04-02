/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tniambi- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 02:33:17 by tniambi-          #+#    #+#             */
/*   Updated: 2024/12/06 15:12:53 by tniambi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t					i;
	unsigned const char		*ps;
	unsigned char			pc;

	pc = (unsigned char) c;
	ps = s;
	i = 0;
	while (i < n)
	{
		if (ps[i] == pc)
			return ((void *) &ps[i]);
		i++;
	}
	return (NULL);
}
