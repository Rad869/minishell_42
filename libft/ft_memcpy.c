/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:54:43 by rrabeari          #+#    #+#             */
/*   Updated: 2025/02/05 12:54:44 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*t;
	char	*c;

	i = 0;
	c = (char *) src;
	t = (char *) dest;
	if (n != 0 && c != t)
	{
		while (i < n)
		{
			t[i] = c[i];
			i++;
		}
	}
	return (dest);
}
