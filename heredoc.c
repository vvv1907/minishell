/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcolumbu <hcolumbu@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:53:59 by hcolumbu          #+#    #+#             */
/*   Updated: 2022/06/07 11:40:38 by hcolumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(t_com *com)
{
	char	*line;
	int		fd[2];

	pipe(fd);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(com->file, line))
		{
			free(line);
			close(fd[1]);
			return (fd[0]);
		}
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
}
