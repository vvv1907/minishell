/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcolumbu <hcolumbu@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 10:53:59 by hcolumbu          #+#    #+#             */
/*   Updated: 2022/06/05 11:40:38 by hcolumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_separator(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == '|' || c == '<' || c == '>')
		return (1);
	else
		return (0);
}

void	count_redirects(char *str, int *ind, int *num_words)
{
	int	i;
	int	words;

	i = *ind;
	words = *num_words;
	if (str[i] == '<')
	{
		if (str[i + 1] && str[i + 1] == '<')
			i++;
		words++;
		i++;
	}
	else if (str[i] == '>')
	{
		if (str[i + 1] && str[i + 1] == '>')
			i++;
		words++;
		i++;
	}
	*num_words = words;
	*ind = i;
}

void	count_rest(char *str, int *ind, int *num_words)
{
	int	i;
	int	count_one;
	int	count_double;

	count_one = 0;
	count_double = 0;
	i = *ind;
	while (str[i])
	{
		if (ft_separator(str[i]) && count_one % 2 == 0 && count_double % 2 == 0)
		{
			(*num_words)++;
			*ind = i;
			return ;
		}
		if (str[i] == '\'' && count_double % 2 == 0)
			count_one++;
		if (str[i] == '\"' && count_one % 2 == 0)
			count_double++;
		i++;
	}
	(*num_words)++;
	*ind = i;
}

int	count_words(char *str, int i, int words)
{
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i] == '|')
		{
			words++;
			i++;
		}
		else if (str[i] == '<' || str[i] == '>')
			count_redirects(str, &i, &words);
		else if (str[i + 1] && (!ft_strncmp(&str[i], "\'\'", 2)
				|| !ft_strncmp(&str[i], "\"\"", 2)))
			i += 2;
		else
			count_rest(str, &i, &words);
	}
	return (words);
}
