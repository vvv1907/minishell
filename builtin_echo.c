/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcolumbu <hcolumbu@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 10:53:59 by hcolumbu          #+#    #+#             */
/*   Updated: 2022/06/03 11:40:38 by hcolumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_to_string_from_array(char **array, int i)
{
	char	*tmp;

	while (array[i])
	{
		if (!ft_strcmp(array[i], "$?"))
		{
			tmp = ft_itoa(g_exit_status);
			ft_putstr_fd(tmp, 1);
			ft_free(tmp);
		}
		else
			ft_putstr_fd(array[i], 1);
		if (array[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
}

int	builtin_echo(t_com *com)
{
	int	i;

	i = 0;
	while (com)
	{
		if (!com->arg)
		{
			ft_putchar_fd('\n', 1);
		}
		else if (!ft_strcmp(com->arg[i], "-n"))
		{
			while (!ft_strcmp(com->arg[i], "-n"))
				i++;
			print_to_string_from_array(com->arg, i);
		}
		else
		{
			print_to_string_from_array(com->arg, i);
			ft_putchar_fd('\n', 1);
		}
		com = com->next;
	}
	return (0);
}
