/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:32:39 by raghonya          #+#    #+#             */
/*   Updated: 2023/01/16 17:13:07 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_calloc(size_t size, size_t byte)
{
	size_t	i;
	void	*arr;

	i = 0;
	if (size == SIZE_MAX || byte == SIZE_MAX)
		return (NULL);
	arr = malloc(size * byte);
	if (!arr)
		return (NULL);
	while (i < size * byte)
	{
		((char *)arr)[i] = 0;
		i++;
	}
	return (arr);
}
