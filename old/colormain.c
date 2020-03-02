#include <stdio.h>
// https://stackoverflow.com/questions/7358533/how-to-pack-argb-to-one-integer-uniquely

int		create_trgb(int t, int r, int g, int b)
{
	return(b << 24 | g << 16 | r << 8 | t);
}

int		get_t(int trgb)
{
	return (trgb & 0xFF);
}

int		get_r(int trgb)
{
	return (trgb & 0xFF00);
}

int		get_g(int trgb)
{
	return (trgb & 0xFF0000);
}

int		get_b(int trgb)
{
	return (trgb & 0xFF000000);
}

int		main(void)
{
	printf("[%d]\n", create_trgb(0, 0, 0, 255));
	printf("[%d]\n", get_t(-16777216));
	printf("[%d]\n", get_r(-16777216));
	printf("[%d]\n", get_g(-16777216));
	printf("[%d]\n", get_b(-16777216));
	return (0);
}