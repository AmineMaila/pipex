/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:21:14 by mmaila            #+#    #+#             */
/*   Updated: 2023/12/27 16:08:08 by mmaila           ###   ########.fr       */
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
		return (free_2d(&path), NULL);
	i = 0;
	while (path[i] && access(tmp, F_OK | X_OK))
	{
		free(tmp);
		tmp = ft_strjoin(path[i++], cmd);
	}
	free_2d(&path);
	return (tmp);
}

void	get_cmd(char ***cmd_line, char *cmd, char **env)
{
	char	*tmp;

	if (*cmd_line)
		free_2d(cmd_line);
	*cmd_line = ft_split(cmd, ' ');
	if (!*cmd_line)
		ft_exit(1);
	tmp = ft_strjoin("/", (*cmd_line)[0]);
	if (!tmp)
	{
		free_2d(cmd_line);
		ft_exit(1);
	}
	free((*cmd_line)[0]);
	(*cmd_line)[0] = get_path(tmp, env);
	free(tmp);
	if (!(*cmd_line)[0])
		ft_exit(1);
}

void	exec_cmd(char *cmd, char **env)
{
	char	**cmd_line;

	cmd_line = NULL;
	get_cmd(&cmd_line, cmd, env);
	if (execve(cmd_line[0], cmd_line, NULL) == -1)
	{
		free_2d(&cmd_line);
		ft_exit(3);
	}
}
