/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   savecwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborel <aborel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 21:46:31 by aborel            #+#    #+#             */
/*   Updated: 2025/09/09 12:25:36 by aborel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*copy_string(char *s, char *word, char *new_s, int l)
{
	int	i;
	int	j;
	int	len_value;
	int	len_key;

	len_value = ft_strlen(word);
	len_key = get_keylen(&s[l + 1]) + 1;
	i = -1;
	while (++i < l)
		new_s[i] = s[i];
	j = -1;
	i--;
	while (word[++j])
		new_s[++i] = word[j];
	while (s[++i + len_key - len_value])
		new_s[i] = s[i + len_key - len_value];
	new_s[i] = 0;
	return (new_s);
}

char	*create_name(char *name, int i)
{
	char	*tmp;
	char	*num;

	tmp = ft_strjoin(name, "/tmp_");
	num = ft_itoa(i);
	name = ft_strjoin(tmp, num);
	free(tmp);
	free(num);
	return (name);
}

void	savecwd(t_env **env)
{
	char	**arg;
	char	*wd;

	arg = (char **)malloc(3 * sizeof(char *));
	if (!arg)
		return ;
	arg[2] = 0;
	arg[0] = ft_strdup("export");
	wd = getcwd(NULL, 0);
	arg[1] = ft_strjoin("TMP=", wd);
	ft_export(arg, env);
	free(arg[1]);
	free(arg[0]);
	free(arg[2]);
	free(arg);
	free(wd);
}
