/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:38:42 by raghonya          #+#    #+#             */
/*   Updated: 2023/01/26 14:38:46 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>

int		ft_printf(const char *s, ...);
int		check_perc(int i, const char *s, va_list *a, unsigned int *count);
void	printf_putnbr_fd(int n, int fd, unsigned int *count);
void	printf_putchar_fd(char c, int fd);
void	printf_putstr_fd(char *s, int fd, unsigned int *count);
void	putuint(unsigned int n, unsigned int *count);
void	putlowhex(unsigned int n, unsigned int *count);
void	putuphex(unsigned int n, unsigned int *count);
void	checkptr(uintptr_t n, unsigned int *count);
size_t	printf_strlen(const char *s);

#endif
