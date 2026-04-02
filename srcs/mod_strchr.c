/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_strchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tniambi- <tniambi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:44:17 by aborel            #+#    #+#             */
/*   Updated: 2025/09/09 14:18:13 by tniambi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	export_error(void)
{
	g_sig = 1;
	write(2, " not a valid identifier\n", 24);
	return ;
}

int	invalid_id(char c, int i)
{
	if (!ft_isalnum(c) && c != '_' && c != '=')
		return (0);
	if ((ft_isdigit(c) || c == '=') && i == 0)
		return (0);
	return (1);
}

char	*mod_strchr(const char *s, int c)
{
	int		i;
	char	pc;

	pc = (char) c;
	i = 0;
	while (s[i])
	{
		if (!invalid_id(s[i], i))
		{
			export_error();
			return (NULL);
		}
		if (s[i] == pc)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == pc)
		return ((char *) &s[i]);
	return (NULL);
}

void	setup_quote(int *quotes)
{
	quotes[0] = -1;
	quotes[1] = -1;
}

int	ft_iset(char s, char c, int *quotes)
{
	if ((s == c && quotes[0] < 0 && quotes[1] < 0) || s == '\0')
		return (1);
	else
		return (0);
}
