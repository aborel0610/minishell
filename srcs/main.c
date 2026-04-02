/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborel <aborel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 02:05:41 by tniambi-          #+#    #+#             */
/*   Updated: 2025/09/09 16:09:34 by aborel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include"../includes/minishell.h"

int		g_sig = 0;

static void	no_line(t_env *env)
{
	write(1, "exit\n", 5);
	free_env_list(env);
	rl_clear_history();
	exit(0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*env;

	(void) argc;
	(void) argv;
	line = NULL;
	env = create_env_list(envp);
	savecwd(&env);
	while (1)
	{
		reset_signals(1);
		line = readline("minishell > ");
		if (!line)
			no_line(env);
		if (line)
		{
			add_history(line);
			parse_execute(line, &env);
			free(line);
		}
	}
	rl_clear_history();
	free_env_list(env);
	return (g_sig);
}
