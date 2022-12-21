/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcolumbu <hcolumbu@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 10:53:59 by hcolumbu          #+#    #+#             */
/*   Updated: 2022/06/05 11:40:38 by hcolumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	arguments_handler(char **array, t_com *com, t_envp *envp_list)
{
	int	i;

	i = 0;
	if (array[0][i] == '+' || array[0][i] == '-')
		i++;
	while (array[0][++i])
	{
		if (array[0][i] < '0' || array[0][i] > '9')
		{
			ft_putendl_fd("Myshell 🐚: exit: numeric argument required", 2);
			free_com_list(com);
			free_envp_list(envp_list);
			exit(255);
		}
	}
	if (array[1])
		ft_putendl_fd("exit \nMyshell 🐚: exit: too many arguments", 2);
	else
	{
		i = ft_atoi(array[0]);
		ft_putendl_fd("exit", 1);
		free_com_list(com);
		free_envp_list(envp_list);
		exit(i);
	}
}

void	builtin_exit(t_com *com, t_envp *envp_list)
{
	int	i;

	i = 0;
	if (!com->arg)
	{
		ft_putendl_fd("exit", 1);
		free_com_list(com);
		free_envp_list(envp_list);
		exit(0);
	}
	else
		arguments_handler(com->arg, com, envp_list);
}
