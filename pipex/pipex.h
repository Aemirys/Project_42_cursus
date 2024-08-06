/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:26:16 by estosche          #+#    #+#             */
/*   Updated: 2024/03/13 16:55:29 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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

typedef struct s_pipex
{
	int		pipe[2];
	pid_t	first_child;
	pid_t	second_child;
	char	**parent_argv;
	char	**parent_env;
	char	**argv_childs;
	char	**path;
}				t_pipex;

//utils
void	init_pipex(t_pipex *pipex, int argc, char **argv, char **env);
void	open_pipe(t_pipex *pipex);
void	close_pipe(t_pipex *pipex);
void	get_path(t_pipex *pipex);
int		get_exit_status(int exit_status);
//error
void	error(t_pipex *pipex, int exit_status, char *msg);
void	ft_free(char **name);
//pipex
void	execute(t_pipex *pipex, char *command);
char	*find_executable(t_pipex *pipex);
void	first_child(t_pipex *pipex, char *command);
void	second_child(t_pipex *pipex, char *command);
int		main(int argc, char **argv, char **env);
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