/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcolumbu <hcolumbu@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 10:53:59 by hcolumbu          #+#    #+#             */
/*   Updated: 2022/06/05 11:40:38 by hcolumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_env_declare(t_envp *envp_list)
{
	if (!envp_list)
		return (1);
	while (envp_list)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(envp_list->key, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(envp_list->value, 1);
		ft_putendl_fd("\"", 1);
		envp_list = envp_list->next;
	}
	return (0);
}

int	var_position_in_envp(t_envp *envp_list, char *str)
{
	int	i;

	i = 0;
	if (!envp_list || !str)
		return (-1);
	while (envp_list)
	{
		if (!ft_strcmp(envp_list->key, str))
			return (i);
		i++;
		envp_list = envp_list->next;
	}
	return (-1);
}

int	put_value_to_envp(t_envp *envp_list, char *key, char *new_value)
{
	int	pos;
	int	i;

	if (!envp_list || !key)
		return (1);
	pos = var_position_in_envp(envp_list, key);
	if (pos == -1)
		return (1);
	i = 0;
	while (i < pos)
	{
		envp_list = envp_list->next;
		i++;
	}
	envp_list->value = new_value;
	return (0);
}

char	*get_value_from_envp(t_envp *envp_list, char *str)
{
	int	pos;
	int	i;

	if (!envp_list || !str)
		return (NULL);
	pos = var_position_in_envp(envp_list, str);
	if (pos == -1)
		return (NULL);
	i = 0;
	while (i < pos)
	{
		envp_list = envp_list->next;
		i++;
	}
	return (ft_strdup(envp_list->value));
}

void	add_var_to_envp_list(t_envp **envp_list, char **array, char *str)
{
	t_envp	*tmp;

	tmp = *envp_list;
	if (!array[1])
		return ;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, array[0]))
		{
			if (ft_strchr(array[1], '+'))
			{
				free(tmp->value);
				tmp->value = ft_strjoin(tmp->value, array[2]);
			}
			else
			{
				free(tmp->value);
				tmp->value = ft_strdup(array[2]);
			}
			return ;
		}
		tmp = tmp->next;
	}
	envp_add_front(envp_list, envp_new(str));
}
