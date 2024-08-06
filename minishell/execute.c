/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:01:02 by estosche          #+#    #+#             */
/*   Updated: 2024/08/01 13:05:16 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_exit_code;

void	get_path(t_data *data)
{
	char	**path;
	char	**env;
	char	*path_var;
	int		i;

	i = -1;
	env = data->env;
	while (env[++i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		;
	if (!env[i])
		return ;
	path_var = ft_strdup(env[i] + 5);
	if (path_var == NULL)
	{
		perror("Error duplicating PATH environment variable");
		return ;
	}
	path = ft_split(env[i], ':');
	free(path_var);
	if (path == NULL)
	{
		perror("Error splitting PATH environment variable");
		return ;
	}
	data->path = path;
}

int	handle_environment_variables(t_data *data, t_cmd *command)
{
	int		token_index;
	char	*exit_code_str;

	token_index = 0;
	while (command->cmd_tokens[token_index] != NULL)
	{
		if (command->cmd_tokens[token_index][0] == '$')
		{
			if (ft_strncmp(command->cmd_tokens[token_index] + 1, "?", 1) == 0)
			{
				exit_code_str = ft_itoa(data->exit_code);
				print_error(exit_code_str);
				print_error(": command not found\n");
				exit(127);
			}
			return (token_index);
		}
		token_index++;
	}
	return (-1);
}

int	exc_cmd_from_env_var(t_data *data, char *env_var)
{
	char	*env_command;

	env_command = get_env_var(data, env_var);
	if (env_command)
	{
		execute_command_from_var(data, env_command);
		return (0);
	}
	else
	{
		print_error(env_var);
		print_error(": command not found\n");
		exit(127);
	}
	return (-1);
}

int	execute_command(t_data *data, t_cmd *command)
{
	int		env_var_i;
	char	*command_file;

	if (command == NULL || command->cmd_tokens == NULL \
	|| command->cmd_tokens[0] == NULL)
		return (write(2, "Error: Invalid command or tokens\n", 33), -1);
	env_var_i = handle_environment_variables(data, command);
	if (env_var_i != -1)
	{
		if (exc_cmd_from_env_var(data, command->cmd_tokens[env_var_i] + 1) == 0)
			return (0);
	}
	command_file = find_executable(data, command->cmd_tokens[0]);
	if (command_file == NULL)
	{
		print_error(command->cmd_tokens[0]);
		print_error(": command not found\n");
		free_builtins(data);
		exit(127);
	}
	else if (execve(command_file, command->cmd_tokens, data->env) == -1)
		exit((perror("execve failed in exec_cmd"), EXIT_FAILURE));
	return (0);
}

int	execute_command_from_var(t_data *data, char *command)
{
	pid_t	pid;
	int		status;
	char	*cmd_tokens[4];

	cmd_tokens[0] = "/bin/sh";
	cmd_tokens[1] = "-c";
	cmd_tokens[2] = command;
	cmd_tokens[3] = NULL;
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	else if (pid == 0)
	{
		if (execve("/bin/sh", cmd_tokens, data->env) == -1)
			exit((perror("execve"), EXIT_FAILURE));
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else
			return (-1);
	}
	return (0);
}
