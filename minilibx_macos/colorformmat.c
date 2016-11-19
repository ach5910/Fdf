#include "libft.h"

int main(int argc, char **argv)
{
	int fd;
	char *str;
	char **rgb;
	char *tmp;
	int i = 0;
	int r;
	int g;
	int b;
	int c;

	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &str))
	{
		c = 0;
		if (i >= 64 && i < 192 && i % 2 == 0)
		{
			tmp = ft_strchr(str, ' ');
			tmp[0] = '\0';	
			r = ft_atoi(str);
			str = tmp + 1;
			tmp = ft_strchr(str, ' ');
			tmp[0] = '\0';
			g = ft_atoi(str);
			str = tmp + 1;
			b = ft_atoi(str);
			c += r<< 16;
			c += g<< 8;
			c += b;
			ft_printf("%#x, ", c);
			//ft_printf("0x%x%x%x -%d %d %d, ", r, g, b, r, g, b);
		}
		i++;
	}
	return (0);
}