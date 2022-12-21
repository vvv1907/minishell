/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcolumbu <hcolumbu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:41:44 by hcolumbu          #+#    #+#             */
/*   Updated: 2021/10/25 10:22:04 by hcolumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c && s[i])
		{
			while (s[i] != c && s[i])
				i++;
			words++;
		}
		else if (s[i] == c && s[i])
		{
			while (s[i] == c && s[i])
				i++;
		}
	}
	return (words);
}

static int	ft_count_symb(char const *s, int i, char c)
{
	size_t	size;

	size = 0;
	while (s[i] != c && s[i] != '\0')
	{
		size++;
		i++;
	}	
	return (size);
}

static void	ft_emptymall(char **result, int j)
{
	while (j >= 0)
	{
		free(result[j]);
		j--;
	}
	free(result);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	i;
	int				j;
	char			**result;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	result = (char **)malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (s[i] && j < ft_count_words(s, c))
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			result[j] = ft_substr(s, i, ft_count_symb(s, i, c));
			if (!result[j++])
				ft_emptymall(result, j);
			i = i + ft_count_symb(s, i, c);
		}
	}
	result[j] = NULL;
	return (result);
}
