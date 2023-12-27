/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:17:42 by mmaila            #+#    #+#             */
/*   Updated: 2023/12/27 14:45:34 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/pipex.h"

void	is_lim(char **lim, int fd)
{
	char	*tmp;

	while (1)
	{
		tmp = get_next_line(0);
		if (!tmp)
			ft_exit(1);
		if (!ft_strcmp(*lim, tmp))
		{
			free(tmp);
			free(*lim);
			close(fd);
			exit(0);
		}
		ft_putstr_fd(tmp, fd);
		free(tmp);
	}
}

int	here_doc(char *lim, t_data *pipex)
{
	int		fd[2];

	pipe(fd);
	pipex->pids[pipex->id_count] = fork();
	if (!pipex->pids[pipex->id_count])
	{
		close(fd[0]);
		lim = ft_strjoin(lim, "\n");
		if (!lim)
			ft_exit(1);
		is_lim(&lim, fd[1]);
	}
	return (close(fd[1]), fd[0]);
}
