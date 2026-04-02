/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tniambi- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:31:41 by tniambi-          #+#    #+#             */
/*   Updated: 2025/02/26 11:32:10 by tniambi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst)
	{
		if (*lst)
			new->next = *lst;
		*lst = new;
	}
}
/*
#include <stdio.h>
int	main(void)
{
	t_list	*list;
	t_list	*elem1;
	t_list	*elem2;
	t_list	*elem3;
	t_list	*test;

	list = ft_lstnew("Hey !");
	elem1 = ft_lstnew(" salut");
	elem2 = ft_lstnew(" ca");
	elem3 = ft_lstnew(" va");
	test = ft_lstnew("prout");
	list->next = elem1;
	elem1->next = elem2;
	elem2->next = elem3;
	
	ft_lstadd_front(&list, test);

	while (list != NULL)
	{
		printf("%s", (char *)list->content);
		list = list->next;
	}
	return (0);
}*/
