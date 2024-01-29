/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:07:05 by gdetourn          #+#    #+#             */
/*   Updated: 2024/01/24 21:44:03 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	int	i;

	i = 0;
	while (pipex->cmd_args)
	{
		ft_free_tab(pipex->cmd_args[i]);
		i++;
	}
	ft_free_tab(pipex->cmd_paths);
	free(pipex->path);
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

int	ft_parsing(int argc, char *argv[], char *envp[], t_pipex *pipex)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strlen(envp[i]) > 4 && ft_strncmp(envp[i], "PATH", 4) == 0)
			pipex->cmd_paths = ft_split(&envp[i][5], ':');
		i++;
	}
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		pipex->cmd_args = ft_calloc(argc - 3, sizeof(char *));
		ft_heredoc_parsing(argc, argv, pipex);
		return (0);
	}
	pipex->cmd_args = ft_calloc(argc - 2, sizeof(char *));
	if (!pipex->cmd_args)
		return (1);
	i = 0;
	while (i < argc - 3)
	{
		pipex->cmd_args[i] = ft_split(argv[i + 2], ' ');
		i++;
	}
	return (0);
}
