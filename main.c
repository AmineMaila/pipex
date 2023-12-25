/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 17:35:35 by mmaila            #+#    #+#             */
/*   Updated: 2023/12/25 18:43:28 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/pipex.h"

void	free_2d(char ***arr)
{
	int	i;

	i = 0;
	while ((*arr)[i])
		free((*arr)[i++]);
	free(*arr);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	**path;
	char	*tmp;

	i = 0;
	while (ft_strncmp("PATH", env[i], 4))
		i++;
	path = ft_split(env[i] + 5, ':');
	if (!path)
		return (NULL);
	i = 0;
	tmp = ft_strjoin(path[i], cmd);
	if (!tmp)
	{
		free_2d(&path);
		return (NULL);
	}
	i = 0;
	while(path[i] && access(tmp, F_OK | X_OK))
	{
		free(tmp);
		tmp = ft_strjoin(path[i++], cmd);
	}
	free_2d(&path);
	return (tmp);
}

int	get_cmd(char ***cmd_line, char *cmd, char **env)
{
	char	*tmp;

	if(*cmd_line)
		free_2d(cmd_line);
	*cmd_line = ft_split(cmd, ' ');
	if (!*cmd_line)
		return (-1);
	tmp = ft_strjoin("/", (*cmd_line)[0]);
	if (!tmp)
	{
		free_2d(cmd_line);
		return (-1);
	}
	free((*cmd_line)[0]);
	(*cmd_line)[0] = get_path(tmp, env);
	if (!(*cmd_line)[0])
		return (-1);
	free(tmp);
	return (0);
}

void	ft_exit(int n)
{
	if (n == 1)
		perror("Error");
	exit(n);
}

void	exec_cmd(char *cmd, char **env)
{
	char	**cmd_line;

	cmd_line = NULL;
	get_cmd(&cmd_line, cmd, env);
	execve(cmd_line[0], cmd_line, NULL);
}

int	main(int argc, char **argv, char **env)
{
	int	infd;
	int outfd;
	int pids[20];
	int i;
	int j;
	
	if (argc < 5)
		exit(1);
	infd = open(argv[1], O_RDONLY);
	j = 2;
	i = 0;
	while (j < argc - 1)
	{
		int fd[2];

		pipe(fd);
		if (j == argc - 2)
		{
			outfd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC , 0777);
			close(fd[1]);
		}
		else
			outfd = fd[1];
		fprintf(stderr, "|%d| ", infd);
		pids[i] = fork();
		if (pids[i] == 0)
		{
			close(fd[0]);
			dup2(infd, 0);
			close (infd);
			dup2(outfd, 1);
			close(outfd);
			exec_cmd(argv[j], env);
		}
		close(infd);
		infd = fd[0];
		close(outfd);
		i++;
		j++;
	}
	
	j = 0;
	while (j < i)
		waitpid(pids[j++], 0, 0);
	//printf("%d\n", infd);
	// dup2(infd, 0);
	// close(infd);
	// outfd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC , 0777);
	// if (outfd == -1)
	// 	ft_exit(1);
	// dup2(outfd, 1);
	// close(outfd);
	// exec_cmd(argv[argc - 2], env);
}