/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdetourn <gdetourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:30:06 by gdetourn          #+#    #+#             */
/*   Updated: 2024/01/25 11:19:39 by gdetourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <strings.h>

typedef struct s_pipex
{
	int		in_fd;
	int		out_fd;
	char	**cmd_paths;
	char	***cmd_args;
	char	*path;
	int		cmd_count;
	int		*end;
}				t_pipex;

/*ft_printf_pi*/
void	ft_putnbr_base(long int nbr, char *base, int *ret);
void	ft_putnbr_b_un(unsigned int nbr, char *base, int *ret);
void	ft_pnbr_p(unsigned long nbr, char *base, int *ret);
int		ft_check_type(va_list args, const char *format, int *ret);
int		ft_printf(const char *format, ...);

char	**ft_split(char const *s, char c);

/*ft_str.c*/
void	ft_putchar(char c, int *ret);
size_t	ft_strlen(const char *s);
void	ft_putstr(char *s, int *ret);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);

/*ft_strjoin.c*/
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlcat(char *dst, char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strdup(char	*src);
char	*ft_strjoin(char const *s1, char const *s2);

/*get_next_line.c*/
char	*ft_next_line(char *stash);
char	*ft_get_line(char *stash);
char	*ft_strjoin_and_free(char *s1, char *s2);
char	*ft_read_text(int fd, char *stash);
char	*get_next_line(int fd);

/*heredoc.c*/
int		ft_heredoc_parsing(int argc, char *argv[], t_pipex *pipex);
void	ft_putstr_fd(char *s, int fd);
int		ft_heredoc_init(int argc, char *argv[], t_pipex *pipex);
int		ft_heredoc(int argc, char *argv[], char *envp[], t_pipex *pipex);
int		ft_check_args(int argc, char *argv[], char *envp[], t_pipex *pipex);

/*init.c*/
void	ft_free_tab(char **tab);
void	ft_free(t_pipex *pipex);
char	*ft_full_path(char *path, char *cmd);
char	*ft_find_exec(char *cmd_paths[], char *cmd);
int		ft_parsing(int argc, char *argv[], char *envp[], t_pipex *pipex);

/*pipex.c*/
int		ft_execute(int argc, char *argv[], t_pipex *pipex, char *envp[]);
int		parent_process(int argc, char *argv[], char *envp[], t_pipex *pipex);
int		child_process(int argc, char *argv[], char *envp[], t_pipex *pipex);
int		ft_pipex(int argc, char *argv[], char *envp[], t_pipex *pipex);

#endif