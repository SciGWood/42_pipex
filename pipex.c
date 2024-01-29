/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdetourn <gdetourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:29:14 by gdetourn          #+#    #+#             */
/*   Updated: 2024/01/25 11:28:38 by gdetourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* while (path)
	access(path, R_OK)W_OK, X_OK) //function to verify if cmd exists or not. */
int	parent_process(char *envp[], t_pipex *pipex)
{
	if (dup2(pipex->out_fd, STDOUT_FILENO) == -1)
		return (-1);
	if (pipex->exec2)
		execve(pipex->exec2, pipex->cmd2_args, envp);
	return (0);
}

int	child_process(char *envp[], t_pipex *pipex, int *end)
{
	if (dup2(pipex->in_fd, STDIN_FILENO) == -1)
		return (-1);
	close(end[0]);
	dup2(end[1], STDOUT_FILENO);
	if (pipex->exec1)
		execve(pipex->exec1, pipex->cmd1_args, envp);
	close(end[1]);
	return (0);
}

int	ft_pipex(char *envp[], t_pipex *pipex)
{
	int		end[2];
	pid_t	id;

	if (pipe(end) == -1)
		return (ft_printf("Error with pipe\n"), 1);
	id = fork();
	if (id == -1)
	{
		close(end[0]);
		close(end[1]);
		ft_free(pipex);
	}
	if (id == 0)
		child_process(envp, pipex, end);
	else
	{
		close(end[1]);
		dup2(end[0], STDIN_FILENO);
		parent_process(envp, pipex);
		close(end[0]);
	}
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc != 5)
	{
		ft_printf("pipex requires 4 arguments of type:\n");
		ft_printf("./pipex file1 cmd1 cmd2 file2\n");
		return (1);
	}
	if (access(argv[1], R_OK) != -1)
	{
		pipex.in_fd = open(argv[1], O_RDONLY);
		pipex.out_fd = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	else
	{
		ft_printf("No permission for openning this file\n");
		return (1);
	}
	ft_parsing(argv, envp, &pipex);
	ft_pipex(envp, &pipex);
	ft_free(&pipex);
	return (0);
}

/* 
ft_init_pipex();
ft_check_args();
I have a function ft_check_args which simply opens all files needed and
handles here_doc as well as /dev/urandom. You should be able to get away
with a custom get_next_line to complete them.
ft_parse_cmds();
ft_parse_args();
while (cmds)
	ft_exec();
ft_cleanup(); */