/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:55:41 by rrabeari          #+#    #+#             */
/*   Updated: 2025/02/05 12:55:43 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int i)
{
	unsigned int	k;
	char			c;

	c = (char) i;
	k = 0;
	while (s[k])
	{
		if (s[k] == c)
			return ((char *)&s[k]);
		k++;
	}
	if (c == '\0')
		return ((char *)&s[k]);
	return (NULL);
}
