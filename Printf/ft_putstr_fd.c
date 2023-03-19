/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:39:06 by raghonya          #+#    #+#             */
/*   Updated: 2023/01/16 14:39:07 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	printf_putstr_fd(char *s, int fd, unsigned int *count)
{
	if (s == NULL)
	{
		write (fd, "(null)", 6);
		*count += 6;
		return ;
	}
	write (fd, s, printf_strlen (s));
	*count += printf_strlen (s);
}
