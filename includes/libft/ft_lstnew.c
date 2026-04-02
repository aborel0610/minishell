/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tniambi- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:08:08 by tniambi-          #+#    #+#             */
/*   Updated: 2025/02/26 11:05:41 by tniambi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
/*
#include <stdio.h>

int	main(void)
{
	t_list	*elem1;
	t_list	*elem2;
	t_list	*elem3;

	elem1 = ft_lstnew("salut");
	elem2 = ft_lstnew("ca");
	elem3 = ft_lstnew("va");

	elem1->next = elem2;
	elem2->next = elem3;

	while(elem1->next != NULL)
	{
		printf("%s ", (char *)elem1->content);
		elem1 = elem1->next;
	}
	return (0);
}*/
