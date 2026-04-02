/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborel <aborel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:42:16 by aborel            #+#    #+#             */
/*   Updated: 2025/09/09 15:53:30 by aborel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

char	*fill_cmd(t_tree *tree, char *s, int len)
{
	int	i;
	int	j;
	int	quote[2];

	i = 0;
	j = 0;
	quote[0] = -1;
	quote[1] = -1;
	while (i < len)
	{
		is_quote(s[i], quote);
		if ((s[i] == '<' || s[i] == '>') && (quote[0] < 0 && quote[1] < 0))
			i += skip_redir(&s[i]);
		else
		{
			tree->arg[j] = s[i];
			if (is_whitespace(s[i]))
				i += skipwhite(&s[i]);
			else
				i++;
			j++;
		}
	}
	tree->arg[j] = '\0';
	return (tree->arg);
}

int	build_cmd(t_tree *tree, char *s, int len, t_env **env)
{
	t_len_cmd	cmd;
	int			size;

	cmd = lencmd(s, tree, len, env);
	size = calculate_actual_size(s, len);
	tree->arg = (char *)malloc((size + 1) * sizeof(char));
	if (!tree->arg)
		return (0);
	tree->arg = fill_cmd(tree, s, len);
	return (cmd.i);
}

/**
 * @brief Get the token type, fill out arg, input, output
 * 
 * @param s : the start of the token
 * @param tree : the node to fill out
 * @return int : the number of chars of the line dealt with
 */
int	get_token(char *s, t_tree *tree, t_env **env)
{
	int	i;
	int	j;
	int	quote[2];

	quote[0] = -1;
	quote[1] = -1;
	i = skipwhite(s);
	if ((tree->heredoc || tree->input || tree->output) && is_symbol(s[i]))
	{
		tree->type = 'a';
		return (i);
	}
	j = i;
	j += get_type(&s[i], tree);
	while (s[j])
	{
		is_quote(s[j], quote);
		if (is_end(s[j], quote))
			break ;
		j++;
	}
	if (tree->type == 'a')
		build_cmd(tree, &s[i], j - i, env);
	return (j);
}

t_tree	*create_node(t_tree *prev)
{
	t_tree	*node;

	node = (t_tree *)ft_calloc(sizeof(t_tree), 1);
	if (!node)
		return (NULL);
	node->prev = prev;
	return (node);
}

/**
 * @brief creates linked list of tokens
 * 
 * @param line read
 * @return head of list
 */
t_tree	*make_tree(char *line, t_env **env)
{
	t_tree	*node;
	t_tree	*root;
	int		i;

	root = create_node(0);
	node = root;
	i = 0;
	while (line[i])
	{
		i += redirections(&line[i], node, env);
		if (line[i])
			i += get_token(&line[i], node, env);
		i += redirections(&line[i], node, env);
		if (node->type == '\'' || node->type == '"' || is_symbol(node->type))
			i++;
		i += skipwhite(&line[i]);
		if (line[i])
			node->next = create_node(node);
		node = node->next;
	}
	check_pars_errors(root);
	return (root);
}

// int	main(int argc, char **argv)
// {
// 	(void) argc;
// 	t_tree	*root;
// 	t_tree	*node;
// 	char	*line;

// 	signal(SIGINT, handler_int);
// 		line = readline("");
// 		if (line)
// 			add_history(line);
// 		root = make_tree(line);
// 		node = root;
// 		while (node)
// 		{
// 			printf("NEW TOKEN\nType: %c\nArg: %s\nInput: %s\nOutput: %s\n\n", 
// 				root->type, root->arg, root->input, root->output);
// 			node = node->next;
// 		}
// 		free(line);
// 		cleanup(root);
// }
