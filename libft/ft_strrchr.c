/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:17:24 by raghonya          #+#    #+#             */
/*   Updated: 2023/01/16 16:23:17 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	c %= 256;
	i = ft_strlen(s);
	if (!s)
		return (NULL);
	while (1)
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		if (i == 0)
			return (NULL);
		i--;
	}
}
