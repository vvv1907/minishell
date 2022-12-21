/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcolumbu <hcolumbu@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 10:53:59 by hcolumbu          #+#    #+#             */
/*   Updated: 2022/06/05 11:40:38 by hcolumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_full_com(t_com *com, t_exec *exec)
{
	t_com	*full_com;
	t_com	*com_name;
	int		com_num;

	com_num = 1;
	full_com = com;
	com_name = com;
	while (full_com && full_com->delim != 1 && com_num++)
		full_com = full_com->next;
	exec->cmd_full = (char **)malloc(sizeof(char *) * (com_num * 10));
	if (!exec->cmd_full)
		return ;
	if (com_name->delim == 0 || com_name->delim == 1)
		check_cmd(com_name, exec);
	while (com_name && com_name->delim != 1)
	{
		if (com_name->name)
		{
			check_cmd(com_name, exec);
			break ;
		}
		com_name = com_name->next;
	}
	find_args(com, exec);
}

void	execve_handler(t_com *com, t_exec *exec, t_envp *envp_list)
{
	int	exit_status;
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		get_env(envp_list, exec);
		make_full_com(com, exec);
		execve(exec->cmd_exec, exec->cmd_full, exec->env);
		ft_putstr_fd("Myshell 🐚: ", 2);
		perror(exec->cmd_full[0]);
		g_exit_status = 127;
		free_pipe_struct(exec);
		exit(127);
	}
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
}

void	executor(t_com *com, t_envp **envp_list, t_exec *exec)
{
	if (!ft_strcmp(com->name, "echo") || !ft_strcmp(com->name, "ECHO"))
		g_exit_status = builtin_echo(com);
	else if (!ft_strcmp(com->name, "env") || !ft_strcmp(com->name, "ENV"))
		g_exit_status = builtin_env(*envp_list);
	else if (!ft_strcmp(com->name, "pwd") || !ft_strcmp(com->name, "PWD"))
		g_exit_status = builtin_pwd(*envp_list);
	else if (!ft_strcmp(com->name, "cd"))
		g_exit_status = builtin_cd(com, *envp_list);
	else if (!ft_strcmp(com->name, "export"))
		g_exit_status = builtin_export(com, envp_list);
	else if (!ft_strcmp(com->name, "unset"))
		g_exit_status = builtin_unset(com, envp_list);
	else if (!ft_strcmp(com->name, "exit"))
		builtin_exit(com, *envp_list);
	else
		execve_handler(com, exec, *envp_list);
}

void	execute(t_com *com, t_envp **env)
{
	t_exec	exec;

	exec.pipe_num = count_pipes(com);
	if (com->delim != 0)
		pipe_handler(com, env, &exec);
	else
		executor(com, env, &exec);
}
