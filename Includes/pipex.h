/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:03:44 by mmaila            #+#    #+#             */
/*   Updated: 2023/12/27 16:03:26 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_data
{
	char	*outpath;
	int		*pids;
	int		infd;
	int		outfd;
	int		id_count;
	int		outstatus;
	int		index;
}				t_data;

# define BUFFER_SIZE 10

char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strlen(const char *s);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcpy(char *s1, char *s2);
int		newline(char *buf);
char	*ft_strdup(const char *s1);
char	*ft_strncat(char *dest, const char *src, unsigned int nb);
char	*get_next_line(int fd);
void	ft_putstr_fd(char *s, int fd);
void	free_2d(char ***arr);
char	*get_path(char *cmd, char **env);
void	get_cmd(char ***cmd_line, char *cmd, char **env);
int		here_doc(char *lim, t_data *pipex);
void	ft_exit(int n);
void	exec_cmd(char *cmd, char **env);

#endif