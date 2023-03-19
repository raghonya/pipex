/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:20:46 by raghonya          #+#    #+#             */
/*   Updated: 2023/01/16 16:20:59 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *s1, const char *s2, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	q;

	i = 0;
	k = ft_strlen(s1);
	j = ft_strlen(s2);
	q = k;
	if (size <= k)
		return (size + j);
	while (s2[i] && k + 1 < size)
		s1[k++] = s2[i++];
	s1[k] = 0;
	return (q + j);
}
