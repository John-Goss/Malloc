#include <malloc.h>

int	main(void)
{
	char *str;
	
	str = (char*)malloc(8);
	for (int i = 0; i < 8; ++i)
	{
		str[i] = 42;
	}
	dump_zone(TINY);
	free(str);
	dump_zone(TINY);
	str = calloc(1, 8);
	dump_zone(TINY);
	return (0);
}
