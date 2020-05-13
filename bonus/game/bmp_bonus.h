/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 16:35:56 by Maran         #+#    #+#                 */
/*   Updated: 2020/05/13 13:15:52 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

# include <fcntl.h>

# pragma pack(push, 1)

/*
** Preprocessor statement: #Pragma pack
** Instructs the compiler to pack structure members with particular alignment.
** - We need to ensure that the compiler does not insert padding into the data.
** Each member of the struct should follow the previous one.
** - Push : Pushes the current packing alignment value on the internal compiler
** stack, and sets the current packing alignment value to n (-->1).
** - Pop: Removes the record from the top of the internal compiler stack.
**
** struct Test
** {
**    char AA;
**    int BB;
**    char CC;
** }
**
** Memory default:
** |   1   |   2   |   3   |   4   |
** | AA(1) | pad.................. |
** | BB(1) | BB(2) | BB(3) | BB(4) |
** | CC(1) | pad.................. |
** --> sizeof(test) = 4 * 3
**
** #pragma pack(1)
** |   1   |
** | AA(1) |
** | BB(1) |
** | BB(2) |
** | BB(3) |
** | BB(4) |
** | CC(1) |
** --> sizeof(test) = 1 * 6
*/

typedef struct			s_bmp_fileheader{
	uint16_t			filetype;
	uint32_t			filesize;
	uint16_t			reserved1;
	uint16_t			reserved2;
	uint32_t			pixeldataoffset;
}						t_bmp_fileheader;

typedef struct			s_bmp_infoheader{
	uint32_t			headersize;
	uint32_t			imagewidth;
	uint32_t			imageheight;
	uint16_t			planes;
	uint16_t			bitsperpixel;
	uint32_t			compression;
	uint32_t			imagesize;
	uint32_t			xpixelspermeter;
	uint32_t			ypixelspermeter;
	uint32_t			totalcolor;
	uint32_t			importantcolor;
}						t_bmp_infoheader;

typedef struct			s_bitmap{
	t_bmp_fileheader	fileheader;
	t_bmp_infoheader	infoheader;
}						t_bitmap;

# pragma pack(pop)
#endif
