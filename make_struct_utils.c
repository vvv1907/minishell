/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_struct_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcolumbu <hcolumbu@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 10:53:59 by hcolumbu          #+#    #+#             */
/*   Updated: 2022/06/05 11:40:38 by hcolumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_copy_arr(char **arr_in, char **arr_out)
{
	int	i;

	i = 0;
	while (arr_out[i])
		i++;
	arr_in = malloc(sizeof(char *) * i + 1);
	arr_in[i] = NULL;
	i = -1;
	while (arr_out[++i])
		arr_in[i] = ft_substr(arr_out[i], 0, ft_strlen(arr_out[i]));
}

int	ft_n_words(char **arr, int i)
{
	int	n;

	n = 0;
	while (arr[i] && !ft_isdelim(arr[i++]))
		n++;
	return (n);
}

void	ft_empty_arr(char ***tmp, char *str)
{
	*tmp = (char **)malloc(sizeof(char *) * 2);
	(*tmp)[0] = ft_substr(str, 0, ft_strlen(str));
	ft_free(str);
	(*tmp)[1] = NULL;
}

void	add_first_str_in_arr(char ***arr, char *str)
{
	char	**tmp;
	int		i;

	i = 0;
	if (*arr)
	{
		while ((*arr)[i])
			i++;
		tmp = malloc(sizeof(char *) * (i + 2));
		tmp[i + 1] = NULL;
		tmp[0] = ft_substr(str, 0, ft_strlen(str));
		ft_free(str);
		i = 0;
		while ((*arr)[i])
		{
			tmp[i + 1] = ft_substr((*arr)[i], 0, ft_strlen((*arr)[i]));
			ft_free((*arr)[i]);
			i++;
		}
	}
	else
		ft_empty_arr(&tmp, str);
	free(*arr);
	*arr = tmp;
}

void	ft_one_name(t_com **com)
{
	t_com	*tmp;
	int		first_name;

	tmp = *com;
	first_name = 1;
	while ((*com))
	{
		if (first_name && (*com)->name != NULL)
			first_name = 0;
		else
		{
			add_first_str_in_arr(&(*com)->arg, (*com)->name);
			(*com)->name = NULL;
		}
		if ((*com)->delim == 1)
			first_name = 1;
		(*com) = (*com)->next;
	}
	*com = tmp;
}
