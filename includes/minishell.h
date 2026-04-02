/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborel <aborel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:07:54 by aborel            #+#    #+#             */
/*   Updated: 2025/09/09 16:03:12 by aborel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
///////////////////////////////// PARSING /////////////////////////////////////

extern int	g_sig;

typedef struct s_tree
{
	char			type;
	char			*arg;
	int				fd_in;
	int				fd_out;
	char			*input;
	char			*output;
	char			*heredoc;
	int				len_in;
	int				len_out;
	char			end;
	int				pipe;
	int				parsing_error;
	int				tot_pars_error;
	int				error;
	struct s_tree	*prev;
	struct s_tree	*next;
}	t_tree;

typedef struct s_len_cmd
{
	int	i;
	int	white;
	int	redir;
}	t_len_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

//shell struct
typedef struct s_shell
{
	t_env	*env;
	char	*current_dir;
	int		last_exit_status;
}				t_shell;

typedef struct s_command
{
	char	**args;
	char	*path;
	char	**pathnames;
	int		argc;
	int		input;
	int		output;
	int		cmd_count;
	t_env	**env;
}			t_command;

typedef struct s_pipeline
{
	t_command	*commands;
	int			cmd_count;
	t_tree		*root;
}				t_pipeline;
//PARSING LINE
t_tree		*create_node(t_tree *prev);
int			get_token(char *ps, t_tree *tree, t_env **env);
int			is_whitespace(char c);
int			is_symbol(char c);
int			is_end(char c, int *quote);
int			get_type(char *s, t_tree *tree);
int			peek(char *s, char *search);
char		*next_word(char *s);
int			skipword(char *line);
int			skipwhite(char *line);
int			end_of_arg(char *s, t_tree *tree);
t_tree		*redir_node(t_tree *node, char type);
t_tree		*make_tree(char *line, t_env **env);
int			build_cmd(t_tree *tree, char *s, int len, t_env **env);
t_len_cmd	lencmd(char *s, t_tree *tree, int len, t_env **env);
t_len_cmd	redir_len(t_len_cmd cmd, char *s, t_tree *tree, t_env **env);
char		*build_word(int len, int i, char *s);
char		*fill_cmd(t_tree *tree, char *s, int len);
int			skip_redir(char *s);
int			end_of_arg(char *s, t_tree *tree);
t_tree		*parse_pipe(char **ps);
int			runcmd(t_tree node);
t_tree		*parse_parentheses(char **ps);
int			calculate_actual_size(char *s, int len);
//IO
int			redirections(char *line, t_tree *node, t_env **env);
int			input(char *s, t_tree *node);
int			output(char *s, t_tree *node, int flag);
int			heredoc(char *s, t_tree *node, t_env **env);
int			read_heredoc(char *s, int fd, t_tree *node);
char		*create_name(char *name, int i);
void		delete_heredoc(t_tree *node);
int			read_heredoc(char *s, int fd, t_tree *node);
//SIGNAUX
void		reset_signals(int bool);
void		signals_child_mode(void);
void		handler_int(int signal);
void		signals_heredoc_mode(void);
void		handler_heredoc(int signal);
void		handler_child(int signal);
//EXPANSION
t_tree		*expand(t_tree *root, t_env **env);
void		check_quotes(char c, int *quotes);
char		**modified_split(const char *s, char c);
void		quotes(t_pipeline *pl);
char		*expanded_word(char *s, t_env **env);
char		*expanded_string(char *s, char *word, int l);
char		*expand_arg(char *s, t_env **env);
char		*remove_quotes(char *s);
int			get_keylen(char *s);
int			is_quote(char c, int *quotes);
int			len_next_word(char *s);
char		*add_quotes(char *s);
char		*copy_string(char *s, char *word, char *new_s, int l);
void		setup_quote(int *quotes);
int			ft_iset(char s, char c, int *quotes);
//CLEANUP
void		close_input(t_tree *node);
void		close_output(t_tree *node);
void		cleanup(t_tree *root, t_command *cmd);
void		error(int code, char *s, t_tree *node);
void		check_pars_errors(t_tree *root);
int			check_command_access(char *path, char *cmd_name);
int			is_directory(char *path);
//basic built-in
int			ft_env(char **args, char **env);
void		savecwd(t_env **env);
int			is_valid_number(char *str);
int			ft_exit(t_command *cmd, t_tree *root);
int			ft_echo(t_command *cmd);
int			ft_cd(char **args);
int			ft_pwd(void);
int			ft_export(char **argv, t_env **env);
int			execute_builtin(t_command *cmd, t_tree *root);
//built_in utils
int			is_builtin(char **argv);
int			is_basic_builtin(char *cmd);
int			is_advanced_builtin(char *cmd);
int			is_advanced_builtin(char *cmd);
void		setup_builtin_fds(t_command *cmd, int *saved_stdin,
				int *saved_stdout);
void		restore_builtin_fds(int saved_stdin, int saved_stdout);
//export_utils
char		*ft_strndup(char *s, int delim);
t_env		*find_var(t_env *env, char *key);
t_env		*update_existing(t_env *existing, char *value);
int			check_export(t_env *env);
t_env		*sort_env_list(t_env *env);
char		*mod_strchr(const char *s, int c);
//unset
int			is_valid_identifier(const char *s);
int			unset_env_var(const char *key, t_env **env);
int			ft_unset(char **args, t_env **env);
//create new env list
t_env		*new_env_node(const char *key, const char *value);
void		add_env_var(t_env **env, const char *key, const char *value);
int			print_env_list(t_env *env);
t_env		*create_env_list(char **env);
char		**env_to_array(t_env *env_list);
//execution
int			execute_temp(void);
int			parse_execute(char *line, t_env **env);
t_command	*init_commands(t_tree **root, t_env **env);
int			pre_exec_check(t_tree *root);
//simple command
int			check_builtin(char **argv, t_env *new_env, char *parsed);
int			execute_simple(char *cmd, t_tree *root, char **envp);
int			launch_builtin(t_command *cmd, t_tree *root);
char		*get_command(char *cmd, char **pathnames);
char		**get_pathnames(char **envp);
void		clean_cmd(t_command *cmd);
void		set_command_fds(t_command *cmd, t_tree *node);
int			count_args(char **args);
t_command	null_command(void);
t_command	*null_command_parse(void);
void		set_exit_status(int status);
void		handle_exit_command(t_command *cmd, t_tree *root);
void		setup_child_fds(t_pipeline *pipeline, int pipes[][2], int i);
//free functions
void		free_split(char **str);
void		free_env_list(t_env *env);
void		free_perror(char *str, char **cmd_arg, char **paths);
void		cleanup_heredocs(t_tree *root);
// multi pipes
char		*get_command_path(char *cmd, char **pathnames);
t_command	create_command(char **args, t_env **envp, t_tree *node);
int			create_pipes(int pipes[][2], int num_pipes);
void		close_pipe_child(int pipes[][2], int num_pipes, int cmd_index);
void		close_all_pipes(int pipes[][2], int num_pipes);
int			wait_for_children(pid_t *pids, int cmd_count);
void		execute_command(t_command *cmd, t_tree *root);
int			execute_single_command(t_command *cmd, t_tree *root);
void		change_fds(int input_fd, int output_fd);
int			fork_and_exec(t_pipeline *pipeline, int pipes[][2], pid_t *pids);
int			execute_pipeline(t_pipeline *pipeline, t_tree *root);
void		close_redirection_fds_parent(t_pipeline *pipeline);
void		redirect_fd(int fd, int target_fd);
int			get_output_fd(t_pipeline *pipeline, int pipes[][2], int i);
int			get_input_fd(t_pipeline *pipeline, int pipes[][2], int i);

#endif
