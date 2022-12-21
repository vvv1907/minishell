/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcolumbu <hcolumbu@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 10:53:59 by hcolumbu          #+#    #+#             */
/*   Updated: 2022/06/04 11:40:38 by hcolumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export_error(char *str)
{
	if (str)
	{
		ft_putstr_fd("Myshell 🐚: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("': not a valid identifier", 2);
	}
}

static char	**array_from_string(char *str, char **array)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str);
	while (str[i] != '=' && str[i] != '+')
		i++;
	if (str[i] == '+' && str[i + 1] != '=')
	{
		print_export_error(str);
		return (NULL);
	}
	array[0] = ft_substr(str, 0, i);
	if (str[i] == '+')
	{
		array[1] = ft_strdup("+=");
		i++;
	}
	else if (str[i] == '=')
		array[1] = ft_strdup("=");
	array[2] = ft_substr(str, i + 1, len - i - 1);
	array[3] = NULL;
	return (array);
}

static char	**split_for_export(char *str)
{
	char	**var;

	var = malloc(sizeof(char *) * 4);
	if (!var)
		return (NULL);
	if (ft_strchr(str, '='))
		var = array_from_string(str, var);
	else
	{
		var[0] = ft_strdup(str);
		var[1] = NULL;
		var[2] = NULL;
		var[3] = NULL;
	}
	return (var);
}

static int	check_arg_of_export(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '_')
		return (1);
	if (ft_isalpha(str[0]))
		return (1);
	return (0);
}

int	builtin_export(t_com *com, t_envp **envp_list)
{
	int		i;
	char	**array;

	i = -1;
	if (!envp_list || !com)
		return (1);
	if (!com->arg)
		return (print_env_declare(*envp_list));
	while (com->arg[++i])
	{
		if (check_arg_of_export(com->arg[i]))
		{
			array = split_for_export(com->arg[i]);
			if (!array)
				return (1);
			add_var_to_envp_list(envp_list, array, com->arg[i]);
			free_array(array);
		}
		else
		{
			print_export_error(com->arg[i]);
			return (1);
		}
	}
	return (0);
}
