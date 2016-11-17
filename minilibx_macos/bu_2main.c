/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahunt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 05:31:48 by ahunt             #+#    #+#             */
/*   Updated: 2016/11/14 05:31:51 by ahunt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


void get_points(char *file)
{
	int fd;
	char str;
	char tmp;

	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &str) == 1)
	{
		reading = 1;
		while (reading)
		{
			if ((tmp = ft_strchr(str, ' ')) != NULL)
			{
				if (tmp[1] == ' ')
					tmp++;
				tmp[0] = '\0';
				points[j][i] = ft_atoi(str);
				free(str);
				str = ft_strdup(tmp + 1);
			}
			else
			{
				points[j][i] = ft_atoi(str);
				reading = 0;
			}
		}
	}
}

int main(int argc, char **argv)
{
	while (argc == 2)
	{
		get_points(argv[1]);
	}
	return (0);
}
