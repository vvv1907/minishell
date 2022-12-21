/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcolumbu <hcolumbu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:41:44 by hcolumbu          #+#    #+#             */
/*   Updated: 2021/10/25 10:22:04 by hcolumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *source, size_t n)
{
	unsigned int	i;
	char			*result;
	char			*original;

	if (!dest && !source)
		return (NULL);
	i = 0;
	result = (char *)dest;
	original = (char *)source;
	if (dest < source)
	{
		while (i < n)
		{
			result[i] = original[i];
			i++;
		}
	}
	else
	{
		while (n-- > 0)
			result[n] = original[n];
	}
	return (result);
}
