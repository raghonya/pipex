/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memFuncs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:30:32 by raghonya          #+#    #+#             */
/*   Updated: 2023/01/16 16:16:34 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	unsigned char	*s11;
	unsigned char	*s22;

	if (!s1 && !s2)
		return (NULL);
	s11 = (unsigned char *)s1;
	s22 = (unsigned char *)s2;
	if (s22 < s11)
	{
		s11 += n;
		s22 += n;
		while (n--)
			*--s11 = *--s22;
	}
	else
		while (n--)
			*s11++ = *s22++;
	return (s1);
}
