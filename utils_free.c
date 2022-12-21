/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcolumbu <hcolumbu@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 10:53:59 by hcolumbu          #+#    #+#             */
/*   Updated: 2022/06/05 11:40:38 by hcolumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envp_list(t_envp *envp_list)
{
	if (!envp_list)
		return ;
	while (envp_list)
	{
		if (envp_list->key)
			free(envp_list->key);
		if (envp_list->value)
			free(envp_list->value);
		envp_list = envp_list->next;
	}
	free(envp_list);
	envp_list = NULL;
}

void	free_com_list(t_com *com)
{
	t_com	*tmp;

	if (com)
	{
		while (com)
		{
			tmp = com->next;
			if (com->name)
				free(com->name);
			if (com->arg)
				free_array(com->arg);
			if (com->file)
				free(com->file);
			com = tmp;
		}
		if (com)
			free(com);
	}
}

void	ft_free_com_list(t_com **com)
{
	t_com	*tmp;

	if (*com)
	{
		while (*com)
		{
			tmp = (*com)->next;
			if ((*com)->name)
				free((*com)->name);
			if ((*com)->arg)
				free_array((*com)->arg);
			if ((*com)->file)
				free((*com)->file);
			if (*com)
				free(*com);
			(*com) = tmp;
		}
		if ((*com))
			free((*com));
	}
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		if (arr[i])
		{
			while (arr[i])
			{
				free(arr[i]);
				i++;
			}
		}
		free(arr);
	}
}

void	ft_free(char *str)
{
	if (str)
		free(str);
}
