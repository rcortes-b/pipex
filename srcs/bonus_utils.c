/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:03:12 by rcortes-          #+#    #+#             */
/*   Updated: 2024/03/13 21:03:18 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	do_here_doc(t_data *data, char **arguments)
{
	char	*line;
	int		fd[2];

	if (pipe(fd) == -1)
		do_error(data->path, "here_doc.c Line: 21: Pipe Error:", -3);
	ft_putstr_fd("pipe heredoc> ", 1);
	line = NULL;
	while (1)
	{
		if (line)
			ft_putstr_fd("pipe heredoc> ", 1);
		line = get_next_line(0);
		if (!line)
			continue ;
		if (ft_strncmp(line, arguments[2], ft_strlen(line)) == 0)
			break ;
		write(fd[WRITE_END], line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(fd[WRITE_END]);
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
}
