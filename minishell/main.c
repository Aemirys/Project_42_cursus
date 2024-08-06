/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:06:29 by estosche          #+#    #+#             */
/*   Updated: 2024/08/01 13:05:14 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_exit_code;

void	handle_exit(t_data *data)
{
	ft_printf("exit\n");
	free_env(data);
	free_all(data);
	free_redir(data);
	exit(0);
}

int	handle_line(t_data *data, const char *prompt)
{
	char	*line;
	char	*process_line;

	line = readline(prompt);
	if (g_exit_code != 0)
	{
		data->exit_code = g_exit_code;
		g_exit_code = 0;
	}
	signal(SIGQUIT, quit_handler);
	signal(SIGINT, sigint_handler);
	if (line == NULL)
		handle_exit(data);
	if (line[0] != '\0')
		add_history(line);
	process_line = add_spaces_special_chars(line);
	data->input_line = ft_strdup(process_line);
	if (data->input_line == NULL)
	{
		perror("Error storing input line");
		return (free(data->input_line), -1);
	}
	free(line);
	free(process_line);
	return (0);
}

void	handle_input(t_data *data)
{
	if (handle_line(data, data->prompt) == -1)
	{
		write(2, "Error handling command line\n", 28);
		exit(EXIT_FAILURE);
	}
}

void	process_input(t_data *data)
{
	lexer(data);
	free(data->input_line);
	exc_cmd(data);
	free_cmd_list(data->commands);
	data->commands = NULL;
	free_tokens(data->tokens);
	data->tokens = NULL;
	free_prompt(data);
	if (g_exit_code != 0)
	{
		data->exit_code = g_exit_code;
		g_exit_code = 0;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data		data;

	(void)argv;
	if (init_data(&data, envp) == -1)
	{
		write(2, "Error initializing data\n", 24);
		exit(EXIT_FAILURE);
	}
	if (argc != 1)
		return (printf("Too many arguments\n"), 1);
	while (1)
	{
		handle_signals();
		prompt(&data);
		handle_input(&data);
		if (data.input_line[0] == '\0')
		{
			free(data.input_line);
			free(data.prompt);
			continue ;
		}
		process_input(&data);
	}
	decrement_shlvl(&data);
	return (0);
}
