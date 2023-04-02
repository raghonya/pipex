/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:03:43 by raghonya          #+#    #+#             */
/*   Updated: 2023/01/29 20:03:45 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	c %= 256;
	while (1)
	{
		if (s[i] == c)
			return (1);
		if (s[i] == 0)
			return (0);
		i++;
	}
}

static char	*ft_substr(char const *s, unsigned int start)
{
	size_t	i;
	size_t	len;
	char	*str;

	i = 0;
	len = 0;
	if (!s)
		return (NULL);
	if (!ft_strchr(s, '\n'))
		len = gnl_strlen(s);
	else
	{
		while (s[len] != '\n')
			len++;
		len++;
	}
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len)
		str[i++] = s[start++];
	str[len] = 0;
	return (str);
}

static char	*read_func(int fd, char *line)
{
	char	buf[BUFFER_SIZE + 1];
	char	*tmp;
	int		read_size;

	while (1)
	{
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size < 0)
		{
			free (line);
			return (NULL);
		}
		buf[read_size] = 0;
		if (!line)
			tmp = gnl_strdup (buf);
		else
		{
			tmp = gnl_strjoin(line, buf);
			free(line);
		}
		line = tmp;
		if (ft_strchr(line, '\n') || read_size == 0)
			break ;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*ret;
	char		*tmp;

	if (fd < 0)
		return (NULL);
	line = read_func(fd, line);
	if (!line)
		return (NULL);
	ret = ft_substr(line, 0);
	tmp = gnl_strdup(line + (gnl_strlen(ret)));
	free(line);
	line = gnl_strdup(tmp);
	free(tmp);
	if (!ft_strchr(ret, '\n'))
	{
		free(line);
		line = NULL;
		if (*ret != 0)
			return (ret);
		free(ret);
		return (line);
	}
	return (ret);
}

// int main()
// {
// 	char *s;
// 	int fd = open("43_with_nl", O_RDONLY);
// 	s = get_next_line(fd);
// 	printf ("%s", s);
// 	free(s);
// 	close(fd);
// 	s = get_next_line(fd);
// 	printf ("%s", s);
// 	free(s);
	// s = get_next_line(fd);
	// printf ("%s", s);
	// free(s);
	// s = get_next_line(fd);
	// printf ("%s", s);
	// free(s);
	// s = get_next_line(fd);
	// printf ("%s", s);
	// free(s);
	// s = get_next_line(fd);
	// printf ("%s", s);
	// free(s);
	// s = get_next_line(fd);
	// printf ("%s", s);
	// free(s);
	// s = get_next_line(fd);
	// printf ("%s", s);
	// free(s);
	// s = get_next_line(fd);
	// printf ("%s", s);
	// free(s);
	// printf ("\n");
	// system("leaks a.out");
	// s = get_next_line(fd);
	// printf ("4. '%s'", s);
	// free(s);
	// s = get_next_line(fd);
	// printf ("5. '%s'", s);
	// free(s);
	// s = get_next_line(fd);
	// printf ("6. '%s'", s);
	// free(s);
	// s = get_next_line(fd);
	// printf ("7. '%s'", s);
	// free(s);
	// s = get_next_line(fd);
	// printf ("8. '%s'\n", s);
	// free(s);
	// s = get_next_line(fd);
	// ft_printf ("%s\n", s);
	// s = get_next_line(fd);
	// s = get_next_line(fd);
	// if (s == NULL)
	// 	write (1, "(null)\n", 7);
	// else
	// 	ft_printf ("%s\n", s);
	// s = get_next_line(fd);
	// ft_printf ("%s\n", s);
	// s = get_next_line(fd);
	// ft_printf ("%s\n", s);
	// s = get_next_line(fd);
	// ft_printf ("%s\n", s);
	// s = get_next_line(fd);
	// ft_printf ("%s\n", s);
	// s = get_next_line(fd);
	// ft_printf ("%s\n", s);
	// s = get_next_line(fd);
	// ft_printf ("%s\n", s);
	// if (s == NULL)
	// 	write (1, "(null)\n", 7);
	// else
	// 	ft_printf ("%s\n", s);
	// s = get_next_line(fd);
	// if (s == NULL)
	// 	write (1, "(null)\n", 7);
	// else
	// 	ft_printf ("%s\n", s);
	// s = get_next_line(fd);
	// if (s == NULL)
	// 	write (1, "(null)\n", 7);
	// else
	// 	ft_printf ("%s\n", s);
	// s = get_next_line(fd);
	// if (s == NULL)
	// 	write (1, "(null)\n", 7);
	// else
	// 	ft_printf ("%s\n", s);
	// s = get_next_line(fd);
	// if (s == NULL)
	// 	write (1, "(null)\n", 7);
	// else
	// 	ft_printf ("%s\n", s);
	// s = get_next_line(fd);
	// if (s == NULL)
	// 	write (1, "(null)\n", 7);
	// else
	// 	ft_printf ("%s\n", s);
	// s = get_next_line(fd);
	// if (s == NULL)
	// 	write (1, "(null)\n", 7);
	// else
	// 	ft_printf ("%s\n", s);
	// s = get_next_line(fd);
	// if (s == NULL)
	// 	write (1, "(null)\n", 7);
	// else
	// 	ft_printf ("%s\n", s);
	// ft_printf ("%s\n", s);
	// s = get_next_line(fd);
	// ft_printf ("%s\n", s);
	// s = get_next_line(fd);
	// ft_printf ("%s\n", s);
	// s = get_next_line(fd);
	// ft_printf ("%s\n", s);
	// s = get_next_line(fd);
	// ft_printf ("%s\n", s);
	// // s = get_next_line(fd);
	// ft_printf ("%s\n", s);
	// free(s);
	// printf ("%s\n", get_next_line(fd));
	// printf ("%s\n", get_next_line(fd));
	// printf ("%s\n", get_next_line(fd));
	// printf ("%s\n", get_next_line(fd));
// }