/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:58:37 by mmaila            #+#    #+#             */
/*   Updated: 2023/12/24 17:32:39 by mmaila           ###   ########.fr       */
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

void	fork_cmd(char *cmd, char **env)
{
	int		fd[2];
	int		pid;

	pipe(fd);
	pid = fork();
	if (pid != 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		wait(0);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		exec_cmd(cmd, env);
	}
}

void	here_doc(char *lim)
{
	int		fd[2];
	int		pid;
	char	*tmp;
	
	pipe(fd);
	pid = fork();
	if (pid)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		wait(0);
	}
	else
	{
		close(fd[0]);
		lim = ft_strjoin(lim, "\n");
		while(1)
		{
			tmp = get_next_line(0);
			if (!tmp)
				ft_exit(1);
			if (!ft_strcmp(lim, tmp))
			{
				free(tmp);
				free(lim);
				exit(0);
			}
			ft_putstr_fd(tmp, fd[1]);
			free(tmp);
		}	
	}
}

int	main(int argc, char *argv[], char **env) // ./a.out txt "cat" "wc -l" outc
{
	int	i;
	int	infile;
	int	outfile;

	if (argc < 5)
		ft_exit(1);
	if (!ft_strcmp(argv[1], "here_doc"))
	{
		if (argc < 6)
			ft_exit(1);
		here_doc(argv[2]);
		i = 3;
	}
	else
	{
		infile = open(argv[1], O_RDONLY);
		if (infile == -1)
			ft_exit(1);
		dup2(infile, 0);
		close(infile);
		i = 2;
	}
	while (i < argc - 2)
	{
		fork_cmd(argv[i], env);
		i++;
	}
	outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC , 0777);
	if (outfile == -1)
		ft_exit(1);
	dup2(outfile, 1);
	close(outfile);
	exec_cmd(argv[argc - 2], env);
}


/*int		fd[2];
	int		id;
	int		outfd;
	int		infd;
	char	**cmd_line;

	(void)argc;
	if (argc != 5)
		ft_exit(0);
	cmd_line = NULL;
	get_cmd(&cmd_line, argv[2], env);
	pipe(fd);
	id = fork();
	if (id != 0)
		wait(0);
	if (id == 0)
	{
		infd = open(argv[1], O_RDONLY);
		dup2(infd, 0);
		dup2(fd[1], 1);
		close(fd[1]);
		close(infd);
		close(fd[0]);
		execve(cmd_line[0], cmd_line, NULL);
	}
	get_cmd(&cmd_line, argv[3], env);
	id = fork();
	if (id == 0)
	{
		outfd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(fd[0], 0);
		close(fd[0]);
		dup2(outfd, 1);
		close(outfd);
		close(fd[1]);
		execve(cmd_line[0], cmd_line, NULL);
	}
	//close(infd);
	close(fd[0]);
	close(fd[1]);*/