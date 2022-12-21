/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcolumbu <hcolumbu@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 10:53:59 by hcolumbu          #+#    #+#             */
/*   Updated: 2022/06/05 11:40:38 by hcolumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_envp *envp_list)
{
	char	*pwd;

	if (!envp_list)
		return (1);
	pwd = get_value_from_envp(envp_list, "PWD");
	if (!pwd)
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
		{
			if (chdir("..") == -1)
			{
				perror("Myshell 🐚: pwd: ");
				return (1);
			}
			pwd = getcwd(NULL, 0);
		}
	}
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (0);
}
