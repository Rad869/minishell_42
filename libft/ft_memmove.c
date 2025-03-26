/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:54:50 by rrabeari          #+#    #+#             */
/*   Updated: 2025/02/05 12:54:50 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*t;
	char	*c;
	size_t	i;

	c = (char *) src;
	t = (char *) dest;
	i = n;
	if (c < t)
		while (i--)
			t[i] = c[i];
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
