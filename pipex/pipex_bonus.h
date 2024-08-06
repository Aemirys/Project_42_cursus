/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:55:26 by estosche          #+#    #+#             */
/*   Updated: 2024/03/14 14:12:03 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "./libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>

# define MAX_ARGS 100

enum e_bool
{
	FALSE,
	TRUE
};

typedef struct s_pipex
{
	int		here_doc;
	int		exit_status_last_command;
	int		parent_argc;
	char	**parent_argv;
	char	**parent_env;
	char	**path;
}			t_pipex;

//pipex_bonus
void	middle_commands(t_pipex *pipex, int command_index);
void	last_command(t_pipex *pipex);
void	first_command(t_pipex *pipex);
void	create_childs(t_pipex *pipex, int command_index);
// utils_bonus.c
int		init_pipex(t_pipex *pipex, int argc, char **argv, char **env);
void	get_path(t_pipex *pipex);
void	execute(t_pipex *pipex, char *command);
char	*find_executable(t_pipex *pipex, char *name);
int		get_exit_status(int exit_status);
// error_bonus.c
int		open_infile(t_pipex *pipex, int *tube_first_commad);
int		open_outfile(t_pipex *pipex);
int		here_doc(t_pipex *pipex, char *delimiter);
void	error(t_pipex *pipex, int exit_status, char *msg);
void	ft_free(char **name);
void	close_pipe(int pipes[2]);
//split_quote
char	**ft_split_quote(char *str);
int		is_whitespace(char c);
int		find_start_of_argument(char *str, int start_index);
int		find_end_of_argument(char *str, int start_index, char quote_char);
int		find_end_of_unquoted_argument(char *str, int start_index);
int		extract_argument(char *str, int start_index, char **arg);
void	trim_quotes_if_present(char **arg, int length);
void	free_allocated_memory(char **args, int arg_index);

#endif