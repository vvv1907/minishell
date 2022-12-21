/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcolumbu <hcolumbu@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 10:53:59 by hcolumbu          #+#    #+#             */
/*   Updated: 2022/06/05 11:40:38 by hcolumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	std_out_close(int save_stdout)
{
	close(0);
	dup2(save_stdout, 0);
	close(save_stdout);
}

void	pipe_close(t_com *com, int fd0, int fd1)
{
	if (com->next)
	{
		dup2(fd0, 0);
		close(fd0);
		close(fd1);
	}
}

void	free_pipe_struct(t_exec *exec)
{
	if (exec->path_cmd)
		free_array(exec->path_cmd);
	if (exec->cmd_full)
		free_array(exec->cmd_full);
	if (exec->env)
		free_array(exec->env);
}
