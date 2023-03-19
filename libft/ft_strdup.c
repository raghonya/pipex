/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:22:57 by raghonya          #+#    #+#             */
/*   Updated: 2023/01/16 16:23:03 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*dup;

	i = 0;
	dup = malloc((sizeof(char) * ft_strlen(s)) + 1);
	if (!dup)
		return (NULL);
	while (i < ft_strlen(s))
	{
		*(dup + i) = *(s + i);
		i++;
	}
	*(dup + i) = 0;
	return (dup);
}
