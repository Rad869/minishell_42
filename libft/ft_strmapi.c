/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:56:37 by rrabeari          #+#    #+#             */
/*   Updated: 2025/02/05 12:56:38 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*value;
	size_t			len;
	unsigned int	i;

	len = ft_strlen((char *) s);
	i = 0;
	value = (char *) malloc(sizeof(char) * (len + 1));
	if (value == NULL)
		return (NULL);
	while (s[i])
	{
		value[i] = f(i, s[i]);
		i++;
	}
	value[i] = '\0';
	return (value);
}
