/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:55:30 by rcortes-          #+#    #+#             */
/*   Updated: 2024/03/17 14:24:04 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>

# define READ_END 0
# define WRITE_END 1

typedef struct s_data
{
	int		infile;
	int		outfile;
	int		fd[2];
	int		is_heredoc;
	char	**path;
}	t_data;

typedef struct temp_data
{
	char	**cmd;
	char	*cmd_path;
	pid_t	pid;
}	t_temp;

//Function to parse the pathing
char	**parse_path(char **envp);

//Function to check the correct path of command
char	*check_path(char **path, char *cmd);

//Function to throw error
void	do_error(char **array, char const *s, int error_num);

//HERE_DOC
void	do_here_doc(t_data *data, char **arguments);

//Aux for Norminette
void	parent_commands(int fd[2]);

#endif
