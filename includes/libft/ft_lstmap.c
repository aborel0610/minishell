/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tniambi- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:38:16 by tniambi-          #+#    #+#             */
/*   Updated: 2025/02/26 12:35:23 by tniambi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void*))
{
	t_list	*new;
	t_list	*tmp;
	t_list	*current;

	new = NULL;
	tmp = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst != NULL)
	{
		current = ft_lstnew(f(lst->content));
		if (!current)
		{
			ft_lstclear(&current, del);
			return (NULL);
		}
		if (new == NULL)
			new = current;
		else
			tmp->next = current;
		tmp = current;
		lst = lst->next;
	}
	return (new);
}
