/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborel <aborel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:33:21 by tniambi-          #+#    #+#             */
/*   Updated: 2026/04/02 14:54:31 by aborel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	ft_createstr(long n)
{
	int		i;
	long	num;

	i = 0;
	num = n;
	if (n == 0)
		i++;
	if (n < 0)
	{
		num = -num;
		i++;
	}
	while (num > 0)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	num;
	int		i;
	char	*str;

	num = n;
	i = ft_createstr(num);
	str = malloc (sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	str[i] = '\0';
	if (num < 0)
		num = -num;
	while (i > 0)
	{
		str[--i] = num % 10 + 48;
		num = num / 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
