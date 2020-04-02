// Check of map alleen bestaat uit 0, 1, 2, N,S,E or W
// Alle zijkanten 1
// No empty lines!
// Map als laatst
// Spaces are a valid part of the map, and is up to you to handle --> empty space?
// ook tabs vooraan de regel?
	// printf("--TWOD[%d][%d] = [%c]--counter = [%d]\n", y, x, TWOD[y][x], *counter);

	// printf("----------------------------------------------------------------------------GO RIGHT----\n");
	// printf("1. y[%d], x[%d] = [%c]\n", y, x, TWOD[y][x]);
	// printf("y_start = [%d], y_end= [%d], x= [%d], strlen = [%d]\n", base->read.y_start, base->read.y_end, x, ((int)ft_strlen(TWOD[y])));
    // printf("----------------------------------------------------------------------------GO DOWN----\n");
	// printf("TWOD = [%c], pos = [%c]\n", TWOD[y][x], base->read.pos);
	// printf("Hier\n");
//    printf("----------------------------------------------------------------------------GO LEFT----\n");

//1 		NIET DEFINITIEF
// spatie en andere tekens DEFINITIET

		//printf("----------------------------------BAM OF MAP--TWOD[%d][%d] = [%c]--\n", y, x, TWOD[y][x]);
		//printf("---------------------------------------------------------------------BAM MUUR--TWOD[%d][%d] = [%c]--\n", y, x, TWOD[y][x]);

	// if (x < 0 || x > ((int)ft_strlen(TWOD[y])))
	// {
	// 	printf("--error 13--[%d][%d]----\n", y, x);
	// 	printf("**Y_START [%d], Y_END [%d], X_strlen [%d]= \n", base->read.y_start, base->read.y_end, (int)ft_strlen(TWOD[y]));
	// 	return (base->read.error = 13);
	// }

	// Check of alle identifiers gevuld!
// TWOD[21][29]


// void			fill_up(t_base *base)
// {
// 	int i;
// 	int x;
// 	int y_start2;
// 	int strlen;
	
// 	i = 0;
// 	x = 0;
// 	y_start2 = base->read.y_start;
// 	while (y_start2 <= base->read.y_end)
// 	{
// 		//printf("y_str in[%d] = [%s]\n", y_start2, TWOD[y_start2]);
// 		while (TWOD[y_start2][x] == ' ')
// 		{
// 			//printf("**y[%d]**\n", y_start2);
// 			TWOD[y_start2][x] = '-';
// 			x++;
// 		}
// 		strlen = ft_strlen(TWOD[y_start2]);
// 		printf("strlen [%d] = [%d]\n", y_start2, strlen);
// 		if (strlen < base->read.big_strlen)
// 		{
// 			//printf("KLEINER strlen [%d] = [%d]\n", y_start2, strlen);
// 			//while (i < (base->read.big_strlen - strlen))
// 			//{
// 					TWOD[y_start2][strlen + i] = '-';
// 					i++;
// 					TWOD[y_start2][strlen + i] = '-';
// 					i++;
// 					TWOD[y_start2][strlen + i] = '-';
// 					i++;
// 			//}
// 		// 	while ((strlen + i) < base->read.big_strlen) // 17 + 1 // 23
// 		// 	{
// 		// 		TWOD[y_start2][strlen + i] = '-';
// 		// 		//printf("**[%d][%d]\n", y_start2, (strlen + i));
// 		// 		i++;
// 		// 	}
// 		// 	TWOD[y_start2][base->read.big_strlen] = '\0';
// 		}
// 		// //printf("y_str uit = [%s]\n", TWOD[y_start2]);
// 		x = 0;
// 		i = 0;
// 		strlen = 0;
// 		y_start2++;
// 	}
// }

//Eerste rij 1
//eerste index 1 laatste index 1
// ondersre rij 1

// check of eerste regel uit spaties en 1 // save eerste 1
	// opvolgende regels beginnen met 1
		// 0, 1, 2, N,S,E or W



	while (dif > -1) //s1> s2
	{
		if (s1[strlen1 - dif] != '1')
		{
			printf("---s2[%d] != 1\n", strlen2);
			return (1);
		}
		dif--;
	}
	while (dif < 1)
	{
		if (s2[strlen2 + dif] != '1')
		{
			printf("---s2[%d] != 1\n", strlen2);
			return (1);
		}
		dif++;; //-1	
	}


	while (dif > count) // diff > i
	{
		if (s1[strlen1] != '1') //strlen - dif - i
			return (1);
		count++;
		strlen1--;
	}
	count = 1;
	while (dif < count)
	{
		if (s2[strlen2] != '1')
			return (1);
		count--;
		strlen2--;
	}



	----

	y_start2 = *y;
	y_start3= *y;
	//printf("BIGGEST: [%d]\n", base->read.big_strlen);
	
	//----------------------------------------------

	printf("------------------BEFORE--------------------------\n");
	while(base->read.array[y_start2])
	{
		printf("[%i][%s]\n", y_start2, base->read.array[y_start2]);
		y_start2++;
	}
	printf("--------------------------------------------------\n");



	//fill_up(base);

	
	//
	// printf("-----------------AFTER---------------------------\n");
	// while(base->read.array[y_start3])
	// {
	// 	printf("[%i][%s]\n", y_start3, base->read.array[y_start3]);
	// 	y_start3++;
	// }
	
	//printf("**TWOD[%d][%d] = [%c]**\n", base->read.y_pos, base->read.x_pos, TWOD[base->read.y_pos][base->read.x_pos]);
	//flood_fill(base, base->read.y_pos, base->read.x_pos);
	//printf("ERROR SIGN = [%d]\n", base->read.error); 
	//fill_up(base);

	
	//
	// printf("-----------------AFTER---------------------------\n");
	// while(base->read.array[y_start3])
	// {
	// 	printf("[%i][%s]\n", y_start3, base->read.array[y_start3]);
	// 	y_start3++;
	// }
	
	//printf("**TWOD[%d][%d] = [%c]**\n", base->read.y_pos, base->read.x_pos, TWOD[base->read.y_pos][base->read.x_pos]);
	//flood_fill(base, base->read.y_pos, base->read.x_pos);
	//printf("ERROR SIGN = [%d]\n", base->read.error); 

int				flood_fill(t_base *base, int y, int x)
{
	if (TWOD[y][x] == '+' || TWOD[y][x] == '1' || TWOD[y][x] == '2')
		return (0);
	if (TWOD[y][x]== '\0' || y <= base->read.y_start || y >= base->read.y_back)
	{
		printf("--error 12--[%d][%d]----\n", y, x);
		return (base->read.error = 12);	
	}
	if (TWOD[y][x] == ' ')
	{
		printf("--error 10--[%d][%d]----\n", y, x);
		return (base->read.error = 10);
	}
    if (TWOD[y][x]!= '0' && TWOD[y][x] != base->read.pos)
	{
		printf("--error 11--[%d][%d]----\n", y, x);
		return (base->read.error = 11);
	}
    TWOD[y][x] = '+';
	//printf("---YES--TWOD[%d][%d] = [%c]--\n", y, x, TWOD[y][x]);
    flood_fill(base, y - 1, x);
    flood_fill(base, y, x + 1);
    flood_fill(base, y + 1, x);
    flood_fill(base, y, x - 1);
    return (0);
}

int	padding(int y, t_base *base)
{
	int i;
	
	while(TWOD[y])
	{
		i = 0;
		while (TWOD[y][i])
		{
			//if (TWOD[y][i] == ' ')
			//	TWOD[y][i] = '0';
			if (TWOD[y][i] != '0' && TWOD[y][i] != '1' && TWOD[y][i] != '2' && TWOD[y][i] != 'N' && TWOD[y][i] != 'S' && TWOD[y][i] != 'E' && TWOD[y][i] !='W' && TWOD[y][i] !=' ')
				return (base->read.error = 99);
			if (TWOD[y][i] == 'N' || TWOD[y][i] == 'S' || TWOD[y][i] == 'E' || TWOD[y][i] =='W')
			{
				if (base->read.pos != -1)
					return (base->read.error = 999);
				base->read.pos = TWOD[y][i];
				base->read.x_pos = i;
				base->read.y_pos = y;
			}
			i++;
			if (i > base->read.big_strlen)
				base->read.big_strlen = i;
		}
		y++;
	}
	return (0);
}


TWOD[y][i] != 'N' && TWOD[y][i] != 'S' && TWOD[y][i] != 'E' &&
		TWOD[y][i] != 'W'




//gcc -Wall -Wextra -Werror -I mlx readmap.c gnl_cub3d.c gnl_cub3d_utils.c libft/ft_split.c libft/ft_substr.c




Testen + leaks:
1. Te weinig en te veel argumenten
2. File die niet bestaat.
3. Bestaande file maar geen .cub
4.  getcubfile:
	line = NULL;
	new = NULL; --> lijkt 1 leak, maar kan niet echt testen.
	new->read.array == NULL --> heel veel leaks. Maar kan niet echt testen want is geen NULL.
5. Foutief teken in file 
6. Foutief teken in R line
7. R getal 0
8. Niet bestaand path
9. ./ weghalen
10. Extra komma's in F line
11. getal groter dan 255
12. Map fouten
13. Missing elements
14. Missing map
15. Missing start pos

16. ENTER IN MAP KAN IK NIET SOLVEN?



To do:
1. arrray initialiseren nodig?
2. define buffersize?



-----------------------------------------------
// void		texture(t_base *base)
// {
// 	//FILE	*fd;
// 	int fd;
// 	int ret;
// 	//unsigned int *texture[3];
// 	base->game.texWidth = 64;
// 	base->game.texHeight = 64;
// 	int			*tex_n;
// 	char buf[3345];
// 	int	buff[1];
// 	int iter;
// 	int iter2;
// 	int iter3;

// 	//while (i < 4)
// 	//texture[0] = 
		

// 	fd = open("path_to_the_north_texture/colorstone.png", O_RDONLY);
// 	if (fd == -1)
// 		printf("ERROR\n");
// 	//ret = read(fd, buf, 3344);
// 	//printf("ret = %d\n", ret);
// 	tex_n = (int *)malloc(sizeof(int) * (64 * 64 + 1));
// 	iter3 = 64*64;
// 	tex_n[iter3] = 0;

// 	iter = 0;
// 	while (iter < 64)
// 	{
// 		iter2 = 0;
// 		while (iter2 < 64)
// 		{
// 			read(fd, buff, 1);
// 			tex_n[iter3--] = buff[0];
// 		}
// 		iter++;
// 	}	
// 	//new
// 	//buffer[base->read.y_pos][base->read.x_pos];
//}


// void		texture(t_base *base)
// {
// 	int x;
// 	int y;
// 	base->game.texWidth = 64;
// 	base->game.texHeight = 64;
// 	unsigned int *texture[3][base->game.texWidth * base->game.texHeight];
	
// 	x = 0;
// 	y = 0;
	
// 	while (y < base->game.texHeight)
// 	{
// 		while (x < base->game.texWidth)
// 		{
// 			int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
//     		//int xcolor = x * 256 / texWidth;
//     		int ycolor = y * 256 / texHeight;
//     		int xycolor = y * 128 / texHeight + x * 128 / texWidth;
//     		texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); //flat red texture with black cross
//     		texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
//     		texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
//     		texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
//     		texture[4][texWidth * y + x] = 256 * xorcolor; //xor green
//     		texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
//     		texture[6][texWidth * y + x] = 65536 * ycolor; //red gradient
//     		texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
// 			x++;
// 		}
// 		y++;
// 	}
    
// void	loop_tex64_64(t_base *base, FILE *img, int *tex)
// {
// 	int	buff[1];

// 	while (base->game.iter++ < base->game.texh)
// 	{
// 		base->game.iter2 = 0;
// 		while (base->game.iter2++ < base->game.texw)
// 		{
// 			fread(buff, 3, 1, img);
// 			tex[base->game.iter3--] = buff[0];
// 		}
// 	}
// }

// void	texture(t_base *base)
// {
// 	unsigned char	header[54];
// 	FILE			*img;
// 	base->game.texWidth = 64;
//  	base->game.texHeight = 64;

// 	base->game.iter = 0;
// 	img = fopen("bmp/greystone.bmp", "r");
// 	fread(header, sizeof(unsigned char), 54, img);
// 	fseek(img, header[10], SEEK_SET);
// 	base->game.texw = header[18];
// 	base->game.texh = header[22];
// 	base->game.tex_grey = (int *)malloc(sizeof(int) * (base->game.texw * base->game.texh + 1));
// 	base->game.iter3 = base->game.texw * base->game.texh;
// 	base->game.tex_grey[base->game.iter3--] = 0;
// 	loop_tex64_64(base, img, base->game.tex_grey);
// }

void	texture(t_base *base)
{
	//FILE			*img;
	int				fd;
	int				buf[1];
	int				y;
	int				x;

	y = 0;
	x = 0;
	base->game.texWidth = 64;
 	base->game.texHeight = 64;
	base->game.texres = base->game.texWidth * base->game.texHeight;
	//img = fopen("bmp/greystone.bmp", "r");
	fd = open("bmp/greystone.bmp", O_RDONLY);
	base->game.tex_grey = (int *)malloc(sizeof(int) * (base->game.texres + 1));
	// base->game.iter3 = base->game.texw * base->game.texh;
	base->game.tex_grey[base->game.texres] = 0;
	//loop_tex64_64(base, img, base->game.tex_grey);

	base->game.texres--;
	// while (y < base->game.texHeight)
	// {
	// 	x = 0;
	// 	while (x < base->game.texWidth)
	// 	{
	// 		fread(buf, 3, 1, img); // leest 1 element, grootte van 3 bytes(RGB)
	// 		base->game.tex_grey[base->game.texres] = buf[0];
	// 		x++;
	// 		base->game.texres--;
	// 	}
	// 	y++;
	// }
	while (y < base->game.texHeight)
	{
		x = 0;
		while (x < base->game.texWidth)
		{
			read(fd, buf, 3); // leest 1 element, grootte van 3 bytes(RGB)
			base->game.tex_grey[base->game.texres] = buf[0];
			x++;
			base->game.texres--;
		}
		y++;
	}
	printf("grey: %d\n", base->game.tex_grey[0]);
	printf("grey: %d\n", base->game.tex_grey[4095]);
	printf("grey: %d\n", base->game.tex_grey[4096]);
}

-------------



void		texture(t_base *base)
{
	// int		current_color;
	// char    *dst;
	// int		x;
	// int		y;
	
	// x = 0;
	base->tex.texWidth = 64;
	base->tex.texHeight = 64;
	base->tex.png_img = mlx_png_file_to_image(base->mlx.mlx, "./path_to_the_north_texture/colorstone.png", &base->tex.texWidth, &base->tex.texHeight);
	base->tex.png_addr = mlx_get_data_addr(base->tex.png_img, &base->tex.png_bits_per_pixel, &base->tex.png_line_length, &base->tex.png_endian);
	// while (x < base->tex.texWidth)
	// {
	// 	y = 0;
	// 	while (y < base->tex.texHeight)
	// 	{
	// 		dst = base->tex.png_addr + (y * base->tex.png_line_length + x * (base->tex.png_bits_per_pixel / 8));
	// 		//printf("Komt hier?\n");
	// 		current_color = *(unsigned int*)dst;
	// 		printf("current color[%d][%d] = [%d]\n", y , x, current_color);
	// 		y++;
	// 	}
	// 	x++;
	// }
}
