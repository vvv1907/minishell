/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcolumbu <hcolumbu@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 10:53:59 by hcolumbu          #+#    #+#             */
/*   Updated: 2022/06/05 11:40:38 by hcolumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_cmd(t_com *com, t_exec *exec)
{
	char	*tmp;
	char	*command;
	int		i;

	exec->cmd_full[0] = ft_strdup(com->name);
	i = 0;
	while (exec->path_cmd[i])
	{
		tmp = ft_strjoin(exec->path_cmd[i], "/");
		command = ft_strjoin(tmp, com->name);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

void	get_env(t_envp *env, t_exec *exec)
{
	t_envp	*envir;
	char	*tmp;
	int		i;

	envir = env;
	while (envir)
	{
		if (ft_strncmp("PATH", envir->key, 4) == 0)
			exec->path = envir->value;
		envir = envir->next;
	}
	exec->path_cmd = ft_split(exec->path, ':');
	i = envsize(env);
	exec->env = (char **)malloc (sizeof(char *) * (i + 2));
	i = 0;
	while (env)
	{
		tmp = ft_strjoin(env->key, "=");
		exec->env[i] = ft_strjoin(tmp, env->value);
		env = env->next;
		free(tmp);
		i++;
	}
}

void	check_extra_args(t_com *coms, t_exec *exec, int i, int j)
{
	while (coms && coms->delim != 1)
	{
		if (coms->arg)
		{
			while (coms->arg[j])
			{
				exec->cmd_full[i] = ft_strdup(coms->arg[j]);
				i++;
				j++;
			}
		}
		j = 0;
		coms = coms->next;
	}
}

void	find_args(t_com *com, t_exec *exec)
{
	int		i;
	int		j;
	t_com	*coms;

	coms = com;
	i = 1;
	j = 0;
	if (coms->delim == 1)
	{
		if (coms->arg)
		{
			while (coms->arg[j])
			{
				exec->cmd_full[i] = ft_strdup(coms->arg[j]);
				i++;
				j++;
			}
		}
		if (!coms->arg)
			exec->cmd_full[1] = (char *)malloc(sizeof(char *));
	}
	check_extra_args(coms, exec, i, j);
}

void	check_cmd(t_com *com, t_exec *exec)
{
	char	*com_name;
	t_com	*command;

	command = com;
	if (ft_strncmp(command->name, "/", 1) == 0)
	{
		exec->cmd_exec = command->name;
		com_name = ft_strrchr(command->name, '/');
		com_name++;
		exec->cmd_full[0] = ft_strdup(com_name);
	}
	else
	{
		exec->cmd_exec = make_cmd(command, exec);
		if (!exec->cmd_exec)
		{
			ft_putstr_fd("Myshell 🐚: ", 2);
			ft_putstr_fd(command->name, 2);
			ft_putendl_fd(": command not found", 2);
			g_exit_status = 127;
			free_pipe_struct(exec);
			exit(127);
		}
	}
}
