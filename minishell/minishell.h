/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:37:49 by estosche          #+#    #+#             */
/*   Updated: 2024/08/01 13:05:15 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <string.h>
# include <ncurses.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <limits.h>
# include <fcntl.h>
# include <stdbool.h>
# include <errno.h>

# define MAX_PATH_LENGTH 1024
# define MAX_ARGS 64
# define ANSI_COLOR_CYAN    "\x1b[36m"
# define ANSI_COLOR_RESET   "\x1b[0m"
# define SIZE_PARSER 1000

typedef struct s_token
{
	char			*value;
	struct s_token	*next;
	int				connected;
	int				end;
	int				start;
}				t_token;

typedef struct s_pid
{
	pid_t			pid;
	struct s_pid	*next;
}				t_pid;

typedef struct s_cmd
{
	t_token			**tokens;
	struct s_cmd	*next;
	void			*content;
	char			**cmd_tokens;
}				t_cmd;

typedef struct s_redir
{
	char				**list;
	struct s_redir		*next;
}			t_redir;

typedef struct s_heredoc
{
	char	*tmpfile;
	int		fd;
	int		*line_num;
}			t_heredoc;

typedef struct s_data
{
	int				i;
	int				j;
	char			q_c;
	int				quote_pos;
	bool			double_quote;
	int				len;
	t_redir			**redir_out;
	bool			redir;
	bool			shit;
	bool			o_quote;
	bool			q_open;
	bool			append;
	bool			in;
	bool			pipes;
	bool			here_doc;
	bool			quote_open;
	bool			s_quote;
	bool			d_quotes;
	bool			dollar;
	char			quote;
	int				command_index;
	int				*pos_in;
	int				*pos_out;
	int				*pos_h;
	char			**redir_h;
	char			**redir_in;
	int				in_fd;
	char			*prompt;
	int				pipe[2];
	t_pid			*pids;
	char			**env;
	char			*cwd;
	char			**path;
	char			**args;
	char			*input_line;
	char			*home_dir;
	int				exit_code;
	t_token			*tokens;
	int				end;
	int				start;
	int				token_count;
	int				count;
	int				pipe_in;
	int				num_cmds;
	t_cmd			*commands;
	char			*new_value;
	int				check_quote;
	pid_t			child_running;
}					t_data;

typedef struct s_args
{
	t_data	*data;
	char	**line;
	char	prev_char;
	int		start;
	int		end;
	t_token	**prev_token;
}			t_args;

typedef struct s_env
{
	t_data	*data;
	char	*arg_copy;
	char	*key;
	char	*new_value;
	int		j;
}				t_env;

typedef struct s_key
{
	t_data	*data;
	char	*arg_copy;
	char	*key;
	char	*value;
	int		index;
}			t_key;

typedef struct s_h_read
{
	char	buffer[BUFFER_SIZE];
	char	*line;
	char	*temp;
	ssize_t	bytes_read;
	size_t	total_length;
}			t_h_read;

//main
void	handle_exit(t_data *data);
int		handle_line(t_data *data, const char *prompt);
void	handle_input(t_data *data);
void	process_input(t_data *data);

//lexer 1
void	handle_variables(char **line, t_data *data);
void	handle_quotes(t_data *data, char **line, char *i_quote);
void	advance_line(t_data *data, char **line, char i_quotes);
void	handle_quotes_and_advance(t_data *data, char **line, char *i_quotes);
void	handle_regular_tokens(char **line, t_data *data);

//lexer 2
t_token	*create_token(char *value, int start, int end, int connected);
void	handle_token_creation(t_args *args);
void	skip_spaces(char **line);
int		lexer(t_data *data);

//Parser
bool	initialize_positions(t_data *data);
bool	initialize_redir_out(t_data *data);
char	*expand(t_data *data, char *var_name_start);
t_cmd	*create_link_command(void);
t_cmd	*parser(t_data *data);

//Parser 1
bool	is_quote(char c);
char	**add_array(char **array, char *str);
void	process_quotes(t_data *data, char **value, char *i_quotes, int *quote);
int		check_quote(t_data *data, t_token *token);
void	handle_redir_and_pipes(t_data *data, t_token **token, t_cmd **current);

//Parser_2
void	handle_single_redir(t_data *data, t_token **token, int command_count);
void	handle_pipe(t_data *data, t_token **token, t_cmd **current, int *count);
void	handle_command(t_data *data, t_token **token, t_cmd **current);
void	quotes(char *value, t_data *data, char *new_value);
void	special_case(char *val, char **new_val, char ***tok_arr, t_data *data);

//Parser_3
void	process_expanded_value(char *val, char **new_val, t_data *data);
void	dollar_sign(char *val, char **new_val, char ***tok_array, t_data *data);
void	question_mark(char *val, char **new_val, char ***tok_arr, t_data *data);
void	space_in_quotes(char *val, char **n_val, char ***tok_arr, t_data *data);

//Parser_4
void	init_parser(t_data *data);
void	handle_open_quote(char *new_value, t_data *data);
void	process_value(char *val, char **new_val, char ***tok_arr, t_data *data);
char	**remove_quotes(t_token *token, t_data *data);

//Parser_5
void	copy_characters(char *val, char **new_val, t_data *d);
void	handle_quotes_parser(char *val, char **new_val, t_data *d);
void	default_case(char *val, char **new_val, t_data *d);

//Execute Builtins
bool	is_builtin(char **cmd_tokens);
void	execute_builtin_1(t_data *data, char **cmd_tokens);
void	execute_builtin_2(t_data *data, char **cmd_tokens);
void	execute_builtin(t_data *data, char **cmd_tokens);

//execute
void	get_path(t_data *data);
int		handle_environment_variables(t_data *data, t_cmd *command);
int		exc_cmd_from_env_var(t_data *data, char *env_var);
int		execute_command(t_data *data, t_cmd *command);
int		execute_command_from_var(t_data *data, char *command);

//execute_1
t_pid	*get_pid_node(t_data *data, int command_index);
void	create_childs(t_data *data, t_cmd *command, int command_index);
void	wait_for_children(t_data *data);
int		open_infile_1(t_data *data, t_cmd *command);

//execute_2
int		open_infile(t_data *data, t_cmd *command);
int		open_outfile(t_data *data);
int		print_file_error_1(char *file);
void	print_file_error_2(char *file);
int		error_out(char *file);

//execute_3
void	cleanup_and_reset(t_data *data);
void	exc_cmd(t_data *data);
char	*find_executable(t_data *data, char *name);
void	close_here_doc(t_data *data);

//execute_first_1
void	exec_or_exit_builtin_first(t_data *data, t_cmd *command);
void	handle_input_redir(t_data *data, t_cmd *command, int command_index);
void	handle_redir_exe_first(t_data *data, t_cmd *command, int command_index);
void	prepare_command(t_data *data, t_cmd *command, int command_index);
void	close_and_free(t_data *data);

//execute_first_2
void	handle_redir_exe_first_2(t_data *data, t_cmd *command, int cmd_index);
int		handle_here_doc(t_data *data, t_cmd *command);
void	first_command(t_data *data, t_cmd *command, int command_index);
void	close_parent(t_data *data);
void	close_open(t_data *data);

//execute_middle
void	exec_or_exit_builtin_middle(t_data *data, t_cmd *command);
void	handle_redir_exe_mid(t_data *data, t_cmd *command, int command_index);
void	prepare_command_middle(t_data *data, t_cmd *command, int command_index);
void	middle_commands(t_data *data, t_cmd *command, int command_index);

//execute_last
void	exec_or_exit_builtin_last(t_data *data, t_cmd *command);
void	handle_redir_exe_last(t_data *data, t_cmd *command, int command_index);
void	prepare_command_last(t_data *data, t_cmd *command, int command_index);
void	last_command(t_data *data, t_cmd *command, int command_index);

//execute_utils
void	check_file_status(t_cmd *command);
void	handle_file_error(t_cmd *command);
void	check_command_type(t_cmd *command);
int		check_here_doc_sigint(t_data *data);

//execute_single_1
int		wait_for_child(t_data *data, pid_t pid);
void	execute_external_command(t_data *data, t_cmd *command);
void	handle_here_doc_and_execute(t_data *data, t_cmd *command, int in_fd);
int		check_if_command_is_directory(t_data *data, t_cmd *command);
int		check_file_status_single(const char *file_path, t_data *data);

//execute_single_2
void	handle_access_error(const char *file_path, t_data *data);
int		handle_redir_out_and_builtin(t_data *data, t_cmd *command);
void	handle_redirections_and_exec(t_data *data, t_cmd *command, int in_fd);
int		check_access_and_status(char *cmd_token, t_data *data);
int		handle_directory_error(char *cmd_token, t_data *data);

//execute_single_3
int		handle_command_and_check_path(t_data *data, t_cmd *command);
int		exc_single_command(t_data *data, t_cmd *command);

//heredoc_1
int		reopen_tmpfile(char *tmpfile);
int		handle_missing_line(t_data *data, int line_num, int i);
int		check_delimiter_and_write(t_data *data, int fd, char *line, int i);
char	*read_line_heredoc(int fd);
char	*read_line_and_check_exit(int fd, int *line_num);

//heredoc_2
int		process_heredoc_inner_loop(t_data *data, t_heredoc *info, int i);
int		process_here_doc(t_data *data, char *tmpfile, int fd);
int		open_tmpfile(char *tmpfile);
int		here_doc(t_data *data, t_cmd *command);

//history
void	print_history(void);
void	handle_history(void);

//signals
void	sigint_handler(int signum);
void	sigint_nl_handler(int signum);
void	quit_handler(int signum);
void	handle_signals(void);

//signals_heredoc
void	heredoc_sigint_handler(int signum);
void	handle_signals_heredoc(void);

//utils
int		count_commands(t_cmd *cmd_list);
void	count_pid(t_data *data);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
//void	*ft_realloc_parser(void *ptr, size_t size);
void	*ft_realloc_parser(void *ptr, size_t old_size, size_t new_size);
void	*ft_realloc_2args(void *ptr, size_t new_size);

//Utils 2
char	*handle_special_chars(char *new_line, char *line, int *i, int *j);
char	*add_spaces_special_chars(char *line);
bool	is_space(char c);
bool	is_special_char(const char *token);

//error
void	error(t_data *data, int exit_status, char *msg);
void	cd_error(char *cmd, char *error, int d);
int		handle_error(t_data *data, char *arg_copy);

//split_quote
void	trim_quotes_if_present(char **arg, int length);
void	free_allocated_memory(char **args, int num_args);
int		find_next_non_whitespace(char *str, int start_index);
char	**ft_split_quote(char *str);
int		is_whitespace(char c);
int		find_start_of_argument(char *str, int start_index);
int		find_end_of_argument(char *str, int start_index, char quote_char);
int		find_end_of_unquoted_argument(char *str, int start_index);
int		extract_argument(char *str, int start_index, char **arg);

//Builtins
void	print_error(const char *message);
void	list_env_variables(t_data *data);
void	handle_env_args(t_data *data, char **args);
void	builtin_env(t_data *data, char **args);
char	*builtin_pwd(char **args);

//Builtin cd
int		check_path_validity(t_data *data, char *path);
int		change_directory(t_data *data, char *path);
int		builtin_cd(t_data *data, char *path);

//Builtin echo
void	print_dollar_args(t_data *data, char **args, int *start_i);
void	print_echo_args(t_data *data, char **args, int start_i, bool no_nl);
int		builtin_echo(t_data *data, char **args);

//Builtin Unset
void	free_env_var(t_data *data, char *arg);
char	**copy_env(t_data *data);
void	check_path(t_data *data, char *arg);
int		check_unset_options(t_data *data, char **args);
void	builtin_unset(t_data *data, char **args);

//Builtin Export 1
void	split_string(char *str, char **key, char **value);
void	sort_env(char **env);
void	print_export(t_data *data);
int		update_env(t_env *env);
int		handle_env_null(t_env *env, char *value);

//Builtin Export 2
int		is_matching_key(char *env_entry, char *key);
int		process_existing_key(t_key *ikey);
int		handle_plus_equal(t_data *data, char *arg_copy, char *key, char *value);
int		update_env_with_value(t_key *ikey);
int		update_env_without_value(t_key *ikey);

//Builtin Export 3
int		process_matching_key(t_key *ikey);
int		handle_non_matching_key(t_key *ikey);
int		handle_equal(t_data *data, char *key, char *value, char *arg);
int		process_plus_equal(t_data *data, char *arg_copy, char *plus_sign);
int		is_valid_identifier(char *str);

//Builtin Export 4
int		handle_invalid_identifier(t_data *data, char *key, char *arg_copy);
int		validate_arg_copy(t_data *data, char *arg_copy);
int		process_arg(t_data *data, char *arg);
int		check_export_options(t_data *data, char **args);
int		builtin_export(t_data *data, char **args);

//Builtin Exit
int		ft_isnum(const char *str);
void	free_data_and_exit(t_data *data, int exit_code);
void	handle_exit_args(t_data *data, char **args);
void	builtin_exit(t_data *data, char **args);

//free
void	free_cmd_list(t_cmd *cmd_list);
void	free_tokens(t_token *tokens);
void	free_tokens_lexer(t_token **tokens);
void	free_pids(t_data *data);
void	ft_free(void *ptr);

//free_1
void	free_builtins(t_data *data);
void	free_path(t_data *data);
void	free_prompt(t_data *data);
void	free_all(t_data *data);

//free_2
void	free_redir_h(t_data *data);
void	free_redir_in(t_data *data);
void	free_child(t_data *data);
void	free_redir(t_data *data);
void	free_redir_2(t_data *data);

//free_3
void	free_env(t_data *data);
void	free_redir_4(t_redir *redir);
void	free_cleaned_value(char **cleaned_value);
void	free_redir_out_list(t_data *data);

//env
int		init_env(t_data *data, char **envp, int i);
void	update_shlvl(t_data *data);
void	decrement_shlvl(t_data *data);
char	*get_env_var(t_data *data, char *var_name);

//redir_1
bool	is_redirect(char *arg);
t_redir	*create_redir(char *redir_out);
void	add_redir_out(t_data *data, char *redir_out, int command_count);
void	handle_redir_input(t_data *data, t_token **token, int command_count);
void	handle_heredoc_redir(t_data *data, t_token **token, int command_count);

//redir_2
void	append_open(t_data *data, t_token **tok, char *redir_tok);
void	handle_redir_output(t_data *data, t_token **token, int command_count);
void	handle_redirection(t_data *data, t_token **token, int command_count);
int		get_array_length(char **array);
int		single_redir(t_data *data, t_cmd *command);

//redir_3
int		redir_out(t_data *data, t_cmd *command);
int		single_redir_1(t_data *data, t_cmd *command);

//prompt
void	prompt(t_data *data);

//Init
int		init_data(t_data *data, char **envp);

#endif