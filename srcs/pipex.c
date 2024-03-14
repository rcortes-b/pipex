/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:55:59 by rcortes-          #+#    #+#             */
/*   Updated: 2024/03/10 18:55:59 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	do_infile(t_data *data, char **arguments)
{
	data->infile = open(arguments[1], O_RDONLY);
	if (data->infile == -1)
	{
		perror("pipex.c Line 20");
		if (pipe(data->fd) == -1)
			do_error(data->path, "pipex.c Line 22: Pipe Error:", -3);
		close(data->fd[WRITE_END]);
		dup2(data->fd[READ_END], STDIN_FILENO);
		close(data->fd[READ_END]);
	}
	else
	{
		dup2(data->infile, STDIN_FILENO);
		close(data->infile);
	}
}

static void	do_commands(t_data *data, char *argument)
{
	t_temp	utils;

	if (pipe(data->fd) == -1)
		do_error(data->path, "pipex.c Line 39: Pipe Error:", -3);
	utils.pid = fork();
	if (utils.pid == -1)
		do_error(data->path, "pipex.c Line 42: Fork Error:", -4);
	else if (utils.pid == 0)
	{
		close(data->fd[READ_END]);
		dup2(data->fd[WRITE_END], STDOUT_FILENO);
		close(data->fd[WRITE_END]);
		utils.cmd = ft_split(argument, ' ');
		if (!utils.cmd)
			do_error(data->path, "pipex.c Line 50: Malloc Error.", -5);
		utils.cmd_path = check_path(data->path, utils.cmd[0]);
		if (execve(utils.cmd_path, utils.cmd, NULL) == -1)
			do_error(data->path, "pipex.c Line 53: Exec Error:", -6);
	}
	else
		parent_commands(utils.pid, data->fd);
}

static void	do_outfile(t_data *data, char **arguments, int argc)
{
	t_temp	utils;

	utils.pid = fork();
	if (utils.pid == -1)
		do_error(data->path, "pipex.c Line 65: Fork Error:", -4);
	if (utils.pid == 0)
	{
		if (data->is_heredoc == 0)
			data->outfile = open(arguments[argc - 1], O_CREAT | O_RDWR
					| O_TRUNC, 0644);
		else
			data->outfile = open(arguments[argc - 1], O_CREAT | O_RDWR
					| O_APPEND, 0644);
		if (data->outfile == -1)
		{
			perror("pipex.c Line 76");
			return ;
		}
		dup2(data->outfile, STDOUT_FILENO);
		close(data->outfile);
		utils.cmd = ft_split(arguments[argc - 2], ' ');
		utils.cmd_path = check_path(data->path, utils.cmd[0]);
		execve(utils.cmd_path, utils.cmd, NULL);
	}
}

static void	pipex(t_data *data, char **arguments, int argc)
{
	int	pid_counter;
	int	wait_counter;

	pid_counter = 1;
	wait_counter = -1;
	if (ft_strncmp(arguments[1], "here_doc", 8) == 0)
	{
		do_here_doc(data, arguments);
		data->is_heredoc = 1;
		pid_counter++;
		wait_counter++;
	}
	else
	{
		do_infile(data, arguments);
		if (data->infile == -1)
			pid_counter++;
	}
	while (++pid_counter < argc - 2)
		do_commands(data, arguments[pid_counter]);
	do_outfile(data, arguments, argc);
	while (++wait_counter < argc - 3)
		waitpid(-1, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc < 5)
	{
		ft_putstr_fd("Invalid number of arguments: ", 2);
		ft_putstr_fd("./pipex <file1> <cmd> <cmd2> <...> <file2>\n", 1);
		exit(EXIT_FAILURE);
	}
	data.is_heredoc = 0;
	data.path = parse_path(envp);
	pipex(&data, argv, argc);
	do_error(data.path, NULL, 0);
	return (0);
}
