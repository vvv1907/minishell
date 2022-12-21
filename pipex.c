/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcolumbu <hcolumbu@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 10:53:59 by hcolumbu          #+#    #+#             */
/*   Updated: 2022/06/05 11:40:38 by hcolumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_proc(t_com *com, t_envp **env, t_exec *exec, int *pipefd)
{
	if ((com->next || com->delim == 1) && com->delim != 4)
	{
		close(1);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		close(pipefd[0]);
	}
	redirect_handler(com, pipefd);
	executor(com, env, exec);
	exit(g_exit_status);
}

void	pipex(t_com *com, t_envp **env, t_exec *exec)
{
	int	pid;
	int	pipefd[2];
	int	exit_status;

	if (com->delim != 0)
		pipe(pipefd);
	pid = fork();
	if (pid == 0)
		child_proc(com, env, exec, pipefd);
	wait(&exit_status);
	if (WIFSIGNALED(exit_status))
	{
		if (WTERMSIG(exit_status) != 13)
			g_exit_status = 128 + WTERMSIG(exit_status);
		if (WTERMSIG(exit_status) == SIGQUIT)
			ft_putendl_fd("Quit", 2);
	}
	else
		g_exit_status = WEXITSTATUS(exit_status);
	close (0);
	pipe_close(com, pipefd[0], pipefd[1]);
}

void	pipe_handler(t_com *com, t_envp **env, t_exec *exec)
{
	int		save_stdout;
	int		i;
	t_com	*tmp;

	save_stdout = dup(0);
	tmp = com;
	i = 0;
	while (tmp && i <= exec->pipe_num)
	{
		pipex(tmp, env, exec);
		if ((exec->pipe_num) > 0)
		{
			if (tmp->delim && tmp->delim != 1)
			{
				while (tmp->delim && tmp->delim != 1 && tmp->next)
					tmp = tmp->next;
				if (tmp->delim == 1 && !tmp->name)
					tmp = tmp->next;
			}
			else
				tmp = tmp->next;
		}
		i++;
	}
	std_out_close(save_stdout);
}
