/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:07:05 by gdetourn          #+#    #+#             */
/*   Updated: 2024/01/23 09:58:30 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free(t_pipex *pipex)
{
	ft_free_tab(pipex->cmd1_args);
	ft_free_tab(pipex->cmd2_args);
	ft_free_tab(pipex->cmd_paths);
	free(pipex->exec1);
	free(pipex->exec2);
	close(pipex->in_fd);
	close(pipex->out_fd);
}

char	*ft_full_path(char *path, char *cmd)
{
	char	*full_path;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!full_path)
		return (NULL);
	return (full_path);
}

char	*ft_find_exec(char *cmd_paths[], char *cmd)
{
	char	*path;
	int		i;

	i = 0;
	while (cmd_paths[i])
	{
		path = ft_full_path(cmd_paths[i], cmd);
		if (!path)
			return (NULL);
		if (!access(path, 1))
			return (path);
		i++;
		free(path);
	}
	ft_printf("Error\ncmd_path not found\n");
	return (NULL);
}

int	ft_parsing(char *argv[], char *envp[], t_pipex *pipex)
{
	int		i;

	i = 0;
	if (!envp)
		return (1);
	while (envp[i])
	{
		if (ft_strlen(envp[i]) > 4 && ft_strncmp(envp[i], "PATH", 4) == 0)
			pipex->cmd_paths = ft_split(&envp[i][5], ':');
		i++;
	}
	pipex->cmd1_args = ft_split(argv[2], ' ');
	pipex->cmd2_args = ft_split(argv[3], ' ');
	pipex->exec1 = ft_find_exec(pipex->cmd_paths, pipex->cmd1_args[0]);
	pipex->exec2 = ft_find_exec(pipex->cmd_paths, pipex->cmd2_args[0]);
	if (!pipex->exec1 || !pipex->exec2 || !pipex->cmd1_args
		|| !pipex->cmd2_args)
		return (1);
	return (0);
}
