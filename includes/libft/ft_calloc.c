/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tniambi- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:34:24 by tniambi-          #+#    #+#             */
/*   Updated: 2024/12/06 15:08:02 by tniambi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	bufsize;
	void	*ptr;

	bufsize = nmemb * size;
	ptr = malloc(bufsize);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, bufsize);
	return (ptr);
}
