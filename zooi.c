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