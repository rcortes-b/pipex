/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:53:20 by rcortes-          #+#    #+#             */
/*   Updated: 2024/03/09 17:53:21 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

//ft_putstr_fd(s, 2);

void	do_error(char **array, char const *s, int error_code)
{
	int			i;

	i = -1;
	if (*array)
	{
		while (array[++i])
			free(array[i]);
	}
	if (array)
		free(array);
	if (!s)
		return ;
	if (error_code != -7)
		perror(s);
	else
		ft_putstr_fd(s, 2);
	exit(error_code);
}

static char	**append_bar(char **split)
{
	char	**path;
	int		j;

	j = 0;
	while (split[j])
		j++;
	path = malloc(sizeof(char *) * (j + 1));
	if (!path)
		do_error(split, "utils.c Line 48: Malloc Error", -2);
	j = -1;
	while (split[++j])
	{
		path[j] = ft_strjoin(split[j], "/");
		if (!path[j])
		{
			do_error(path, NULL, 0);
			do_error(split, "utils.c Line 56: Malloc Error", -2);
		}
		free(split[j]);
	}
	free(split);
	path[j] = NULL;
	return (path);
}

char	**parse_path(char **envp)
{
	char	**path;
	int		j;
	int		i;

	j = -1;
	i = 0;
	path = NULL;
	while (envp[++j])
	{
		if (ft_strncmp("PATH", envp[j], 4) == 0)
		{
			while (envp[j][i] != '/')
				i++;
			path = ft_split(&envp[j][i], ':');
			if (!path)
			{
				ft_putendl_fd("utils.c Line 83: Malloc Error", 2);
				exit(EXIT_FAILURE);
			}
			path = append_bar(path);
			break ;
		}
	}
	return (path);
}

char	*check_path(char **path, char *cmd)
{
	int		i;
	int		fd;
	char	*cmd_path;

	i = 0;
	while (path[i])
	{
		cmd_path = ft_strjoin(path[i], cmd);
		if (!cmd_path)
			do_error(path, "utils.c Line 104: Malloc Error", -2);
		fd = open(cmd_path, O_RDONLY);
		if (fd > -1)
			return (close(fd), cmd_path);
		i++;
		free(cmd_path);
	}
	do_error(path, "utils.c Line 111: Command not found\n", -7);
	return (NULL);
}

void	parent_commands(pid_t pid, int fd[2])
{
	waitpid(pid, NULL, 0);
	close(fd[WRITE_END]);
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
}
