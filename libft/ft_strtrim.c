/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcolumbu <hcolumbu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:41:44 by hcolumbu          #+#    #+#             */
/*   Updated: 2021/10/25 10:22:04 by hcolumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_match(char const s1, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (s1 == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	ft_start(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (ft_match(s1[i], set))
			i++;
		else
			break ;
	}
	return (i);
}

static int	ft_end(char const *s1, char const *set)
{
	int	len;

	len = ft_strlen(s1);
	while (len > 0)
	{
		if (ft_match(s1[len - 1], set))
			len--;
		else
			break ;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		len;
	char	*newstr;
	int		j;

	if (!s1)
		return (NULL);
	i = ft_start(s1, set);
	len = ft_end(s1, set);
	if (i > len)
		i = 0;
	newstr = (char *)malloc(len - i + 1);
	if (!newstr)
		return (NULL);
	j = 0;
	while (i < len)
	{
		newstr[j] = s1[i];
		i++;
		j++;
	}
	newstr[j] = '\0';
	return (newstr);
}
