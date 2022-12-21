/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcolumbu <hcolumbu@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 10:53:59 by hcolumbu          #+#    #+#             */
/*   Updated: 2022/06/05 11:40:38 by hcolumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdelim(char *s)
{
	if (!ft_strncmp(s, "|", 1) || !ft_strncmp(s, "<", 1) || \
		!ft_strncmp(s, ">", 1) || !ft_strncmp(s, "<<", 2) || \
		!ft_strncmp(s, ">>", 2))
		return (1);
	else
		return (0);
}

int	delimetr(char *s)
{
	if (s[0] == '|')
		return (1);
	if (s[0] == '<' && s[1] == '\0')
		return (2);
	if (s[0] == '>' && s[1] == '\0')
		return (3);
	if (s[0] == '<' && s[1] == '<')
		return (4);
	if (s[0] == '>' && s[1] == '>')
		return (5);
	return (0);
}

void	dollar_redirect(char *str, int *num)
{
	int	i;

	i = *num + 2;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '$')
	{
		i++;
		while (str[i] && ft_isalnum(str[i + 2]))
			i++;
	}
	*num = i;
}

void	make_struct1(char **arr, int *ind, t_com **new_com)
{
	int	i;

	i = *ind;
	if (ft_isdelim(arr[i]) && arr[i][0] != '|')
	{
		*new_com = com_new1(NULL, NULL, delimetr(arr[i]), arr[i + 1]);
		i += 2;
	}
	else if (ft_isdelim(arr[i]) && arr[i][0] == '|')
	{
		*new_com = com_new1(0, 0, 1, 0);
		i++;
	}
	else
		i = make_new_com(i, arr, new_com);
	*ind = i;
}
