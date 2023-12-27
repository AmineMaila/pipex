/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 17:35:35 by mmaila            #+#    #+#             */
/*   Updated: 2023/12/27 16:08:27 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/pipex.h"

void	get_outfd(t_data *pipex, int fd)
{
	if (pipex->outstatus == 1)
	{
		pipex->outfd = open(pipex->outpath, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (pipex->outfd == -1)
			ft_exit(1);
		close(fd);
	}
	else
		pipex->outfd = fd;
}

void	birth(t_data *pipex, char **env, char *cmd)
{
	int	fd[2];

	pipe(fd);
	get_outfd(pipex, fd[1]);
	pipex->pids[pipex->id_count] = fork();
	if (pipex->pids[pipex->id_count] == 0)
	{
		close(fd[0]);
		if (dup2(pipex->infd, 0) == -1)
			ft_exit(3);
		close (pipex->infd);
		if (dup2(pipex->outfd, 1) == -1)
			ft_exit(3);
		close(pipex->outfd);
		exec_cmd(cmd, env);
	}
	pipex->id_count++;
	close(pipex->infd);
	pipex->infd = fd[0];
	close(pipex->outfd);
}

void	spawn_children(t_data *pipex, char **env, char **argv, int argc)
{
	while (pipex->index < argc - 1)
	{
		if (pipex->index == argc - 2)
			pipex->outstatus = 1;
		birth(pipex, env, argv[pipex->index++]);
	}
	close(pipex->infd);
	pipex->index = 0;
	while (pipex->index < pipex->id_count)
		waitpid(pipex->pids[pipex->index++], 0, 0);
}

void	pipex_init(t_data *pipex, char *out, int argc)
{
	pipex->id_count = 0;
	pipex->outstatus = 0;
	pipex->outpath = out;
	pipex->pids = malloc((argc - 3) * sizeof(int));
}

int	main(int argc, char **argv, char **env)
{
	t_data	pipex;

	if (argc < 5)
		exit(1);
	pipex_init(&pipex, argv[argc - 1], argc);
	pipex.index = 2;
	if (!ft_strcmp(argv[1], "here_doc"))
	{
		if (argc < 6)
			ft_exit(1);
		pipex.infd = here_doc(argv[2], &pipex);
		pipex.index = 3;
	}
	else
		pipex.infd = open(argv[1], O_RDONLY);
	if (pipex.infd == -1)
		ft_exit(1);
	spawn_children(&pipex, env, argv, argc);
}
