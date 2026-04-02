/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_cont.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborel <aborel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:28:06 by aborel            #+#    #+#             */
/*   Updated: 2025/09/09 12:06:57 by aborel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_keylen(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '?')
		return (1);
	while (s[i])
	{
		if (ft_isalnum(s[i]) || s[i] == '_')
			i++;
		else
			break ;
	}
	return (i);
}

int	is_quote(char c, int *quotes)
{
	if (c == '\'' && quotes[1] < 0)
	{
		quotes[0] *= -1;
		return (1);
	}
	if (c == '"' && quotes[0] < 0)
	{
		quotes[1] *= -1;
		return (1);
	}
	return (0);
}

char	*copy_wout_quotes(char *s, char *new_s)
{
	int	i;
	int	j;
	int	quotes[2];

	i = 0;
	j = 0;
	quotes[0] = -1;
	quotes[1] = -1;
	while (s[j])
	{
		if (!is_quote(s[j], quotes))
		{
			new_s[i] = s[j];
			i++;
		}
		j++;
	}
	new_s[i] = 0;
	return (new_s);
}

char	*remove_quotes(char *s)
{
	int		len;
	int		quotes[2];
	int		num_quotes;
	char	*new_s;

	len = 0;
	num_quotes = 0;
	quotes[0] = -1;
	quotes[1] = -1;
	while (s[len])
	{
		if (is_quote(s[len], quotes))
			num_quotes++;
		len++;
	}
	if (num_quotes == 0)
		return (s);
	new_s = (char *)malloc((len - num_quotes + 1) * sizeof(char));
	if (!new_s)
		return (NULL);
	new_s = copy_wout_quotes(s, new_s);
	free(s);
	return (new_s);
}

void	quotes(t_pipeline *pl)
{
	int	i;
	int	j;

	i = 0;
	while (i < pl->cmd_count)
	{
		j = 0;
		while (pl->commands[i].args && pl->commands[i].args[j])
		{
			pl->commands[i].args[j] = remove_quotes(pl->commands[i].args[j]);
			j++;
		}
		i++;
	}
}
