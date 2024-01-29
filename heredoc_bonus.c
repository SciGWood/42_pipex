/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdetourn <gdetourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 22:22:45 by gwen              #+#    #+#             */
/*   Updated: 2024/01/29 13:34:24 by gdetourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdio.h>

int	ft_heredoc_parsing(int argc, char *argv[], t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < argc - 3)
	{
		pipex->cmd_args[i] = ft_split(argv[i + 3], ' ');
		i++;
	}
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write (fd, &s[i], 1);
		i++;
	}
}

int	ft_heredoc_init(int argc, char *argv[], t_pipex *pipex)
{
	char	*line;

	if (argc < 6)
	{
		ft_printf("pipex requires at least 5 arguments of type:\n");
		ft_printf("./pipex here_doc LIMITER cmd1 cmd2 (cmdx...) file2\n");
		exit(1);
	}
	line = NULL;
	pipex->in_fd = open("heredoc", O_CREAT | O_RDWR | O_TRUNC, 00777);
	while (1)
	{
		ft_printf("pipe heredoc> ");
		line = get_next_line(0);
		if (!line)
			return (1);
		if (ft_strlen(argv[2]) + 1 == ft_strlen(line)
			&& ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
		{
			free(line);
			return (0);
		}
		ft_putstr_fd(line, pipex->in_fd);
	}
	free(line);
	return (1);
}

int	ft_heredoc(int argc, char *argv[], char *envp[], t_pipex *pipex)
{
	int		i;

	ft_heredoc_init(argc, argv, pipex);
	close(pipex->in_fd);
	pipex->in_fd = open("heredoc", O_RDONLY);
	pipex->out_fd = open(argv[argc - 1], O_CREAT | O_RDWR, 0670);
	if (dup2(pipex->in_fd, STDIN_FILENO) == -1)
		return (-1);
	if (dup2(pipex->out_fd, STDOUT_FILENO) == -1)
		return (-1);
	ft_parsing(argc, argv, envp, pipex);
	i = 0;
	while (i < argc - 5)
	{
		ft_pipex(argc, argv, envp, pipex);
		i++;
	}
	parent_process(argc, argv, envp, pipex);
	ft_free(pipex);
	exit(1);
	return (0);
}

int	ft_check_args(int argc, char *argv[], char *envp[], t_pipex *pipex)
{
	if (argc < 5)
	{
		ft_printf("pipex requires at least 4 arguments of type:\n");
		ft_printf("./pipex file1 cmd1 cmd2 (cmdx...) file2\n");
		return (1);
	}
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
		ft_heredoc(argc, argv, envp, pipex);
	else if (access(argv[1], R_OK) != -1)
	{
		pipex->in_fd = open(argv[1], O_RDONLY);
		pipex->out_fd = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (dup2(pipex->in_fd, STDIN_FILENO) == -1)
			return (-1);
		if (dup2(pipex->out_fd, STDOUT_FILENO) == -1)
			return (-1);
	}
	else
	{
		ft_printf("No permission for openning this file\n");
		return (1);
	}
	return (0);
}
