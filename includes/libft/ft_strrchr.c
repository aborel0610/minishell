/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tniambi- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 01:44:30 by tniambi-          #+#    #+#             */
/*   Updated: 2024/12/06 15:11:58 by tniambi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	pc;
	char	*tmp;

	tmp = NULL;
	pc = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == pc)
			tmp = (char *) &s[i];
		i++;
	}
	if (s[i] == pc)
		tmp = (char *) &s[i];
	return (tmp);
}
