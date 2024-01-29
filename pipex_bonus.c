/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:29:14 by gdetourn          #+#    #+#             */
/*   Updated: 2024/01/25 11:04:42 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

//gérer ' ' dans le split.

int	ft_execute(int argc, char *argv[], t_pipex *pipex, char *envp[])
{
	int		i;
	int		j;

	i = pipex->cmd_count;
	j = 0;
	j = argc - 3;
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
		j = argc - 4;
	if (i < j)
	{
		pipex->path = ft_find_exec(pipex->cmd_paths, pipex->cmd_args[i][0]);
		if (!pipex->path)
			return (1);
		else
			execve(pipex->path, pipex->cmd_args[i], envp);
	}
	return (0);
}

int	parent_process(int argc, char *argv[], char *envp[], t_pipex *pipex)
{
	pipex->cmd_count++;
	ft_execute(argc, argv, pipex, envp);
	return (0);
}

int	child_process(int argc, char *argv[], char *envp[], t_pipex *pipex)
{
	close(pipex->end[0]);
	dup2(pipex->end[1], STDOUT_FILENO);
	ft_execute(argc, argv, pipex, envp);
	close(pipex->end[1]);
	return (0);
}

int	ft_pipex(int argc, char *argv[], char *envp[], t_pipex *pipex)
{
	int		end[2];
	pid_t	id;

	if (pipe(end) == -1)
		return (ft_printf("Error with pipe\n"), 1);
	pipex->cmd_count++;
	pipex->end = end;
	id = fork();
	if (id == -1)
	{
		close(end[0]);
		close(end[1]);
		ft_free(pipex);
	}
	if (id == 0)
		child_process(argc, argv, envp, pipex);
	else
	{
		close(end[1]);
		dup2(end[0], STDIN_FILENO);
		close(end[0]);
	}
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	int		i;

	pipex.cmd_count = -1;
	if (ft_check_args(argc, argv, envp, &pipex) != 0)
		return (1);
	ft_parsing(argc, argv, envp, &pipex);
	i = 0;
	while (i < argc - 4)
	{
		ft_pipex(argc, argv, envp, &pipex);
		i++;
	}
	parent_process(argc, argv, envp, &pipex);
	ft_free(&pipex);
	return (0);
}
