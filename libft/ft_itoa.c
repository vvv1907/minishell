/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcolumbu <hcolumbu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:41:44 by hcolumbu          #+#    #+#             */
/*   Updated: 2021/10/25 10:22:04 by hcolumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_buf_len(int nb, char *s, int len)
{
	while (nb > 0)
	{
		s[len] = (char)(nb % 10);
		nb = nb / 10;
		len++;
	}
	return (len);
}

static char	*ft_buf_cpy(char *s2, char *s1, int size)
{
	int	j;

	j = 0;
	if (s1[0] == '-' || s1[0] == '0')
	{
		s2[j] = s1[0];
		j++;
		while (size > 0)
			s2[j++] = s1[size--] + '0';
	}
	else
	{
		while (size >= 0)
			s2[j++] = s1[size--] + '0';
	}
	s2[j] = '\0';
	return (s2);
}

char	*ft_itoa(int n)
{
	int		i;
	char	tmp[12];
	char	*result;

	i = 0;
	if (n < 0)
	{
		tmp[i++] = '-';
		if (n == -2147483648)
		{
			tmp[i++] = (char)8;
			n = 214748364;
		}
		else
			n = -n;
	}
	if (n == 0)
		tmp[i++] = '0';
	i = ft_buf_len(n, tmp, i);
	result = (char *)malloc(sizeof(char) * (i + 1));
	if (result == NULL)
		return (NULL);
	return (ft_buf_cpy(result, tmp, --i));
}
