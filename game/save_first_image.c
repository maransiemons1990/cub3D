/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_first_image.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/17 13:26:51 by Maran         #+#    #+#                 */
/*   Updated: 2020/05/11 13:21:35 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "bmp.h"

/*
** Bitmapfileheader, 14 bytes:
** Filetype         |2 bytes | "BM" or 0x4d42
** Filesize         |4 bytes | entire file size in bytes
** Reserved1        |2 bytes | reserved to be utilized by an image proc. app
** Reserved2        |2 bytes | reserved to be utilized by an image proc. app
** PixelDataOffset  |4 bytes | offset of actual pixel data in bytes
** Bitmapinfoheader, 40 bytes:
** HeaderSize       |4 bytes | size of the bitmapinfoheader in bytes
** ImageWidth       |4 bytes | width of the final image in pixels
** ImageHeight      |4 bytes | height of the final image in pixels
** Planes           |2 bytes | number of color planes of the target device
** BitsPerPixel     |2 bytes | number of bits (memory) a pixel takes (in pixel
**								data) to represent a color
** Compression      |4 bytes | 0 to represent no-compression
** ImageSize        |4 bytes | final size of the (compressed) image
** XpixelsPerMeter  |4 bytes | horizontal resolution of the target device
** YpixelsPerMeter  |4 bytes | verical resolution of the target device 
** TotalColors      |4 bytes | number of colors in the color pallet
** ImportantColors  |4 bytes | number of important colors
*/

static void     bmp_header(t_bitmap  *bmp, t_base *base)
{
    bmp->fileheader.filetype = 0x4d42;
    bmp->fileheader.filesize = base->read.render_y * 
        base->read.render_x * (base->mlx.bpp / 8) + 54;
    bmp->fileheader.pixeldataoffset = sizeof(t_bitmap);
    bmp->infoheader.headersize = sizeof(t_bmp_infoheader);
    bmp->infoheader.imagewidth = base->read.render_x;
    bmp->infoheader.imageheight = base->read.render_y;
    bmp->infoheader.planes = 1;
    bmp->infoheader.bitsperpixel = base->mlx.bpp;
    bmp->infoheader.compression = 0;
    bmp->infoheader.imagesize = bmp->fileheader.filesize - 54;
    bmp->infoheader.xpixelspermeter = 0;
    bmp->infoheader.ypixelspermeter = 0;
    bmp->infoheader.totalcolor = 0;
}

/*
** Memory allocation: for pixelbuffer.
** 		Pixelbuffer - Contains color values of each individual pixel.
** The coordinates of a BMP image start from the bottom-left corner.
** So we loop through y starting at the bottom of the image.
** Per y we loop through x and save the color of each individual pixel.
*/

static int      *pixel_data(t_base *base, t_mlx *mlx, uint32_t imagesize)
{
	int		*pixelbuffer;
	int		y;
	int		x;
	int		i;
	char	*dest;

	i = 0;
	y = base->read.render_y;
	pixelbuffer = (int *)malloc(imagesize);
	if (pixelbuffer == NULL)
		return (NULL);
	while (y > 0)
	{
		x = 0;
		while (x < base->read.render_x)
		{
			dest = mlx->addr + (y * mlx->line_length + x * (mlx->bpp / 8));
			pixelbuffer[i] = *(unsigned int*)dest;
			i++;
			x++;
		}
			y--;
	}
	return (pixelbuffer);
}

static void     error_bmp(t_base *base, t_bitmap *bmp, int *pxlbuf, int code)
{
	if (bmp)
		free(bmp);
	if (pxlbuf)
		free(pxlbuf);
	exit_game(base, 1, code);
}

/*
** Open file: O_WRONLY - writing only, O_CREAT - create is non existant
** ,S_IRUSR - Read rights owner, S_IWUSR -  write rights owner.
** Memory allocation: for both bitmap headers, fileheader and infoheader.
**		Bitmapfileheader - information about BMP file.
**		Bitmapinfoheader - information about BMP image.
** Initialise both BMP headers with values.
** Write: bmp headers to newly opened file.
** Pixelbuffer: Contains color values of each individual pixel.
** Write: pixelbuffer to file.
** Close: deletes the file descriptor.
** To check content of bmp file: xxd screenshot.bmp| vim -
*/

void            save_first_image_bmp(t_base *base)
{
	int			file;
	int			ret;
	int			*pixelbuffer;
	t_bitmap	*bmp;

	file = open("screenshot.bmp", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if (file == -1)
		exit_game(base, 1, 23);
	bmp = (t_bitmap *)calloc(1, sizeof(t_bitmap));
	if (bmp == NULL)
		exit_game(base, 1, 24);
	bmp_header(bmp, base);
	ret = write(file, bmp, sizeof(t_bitmap));
	if (ret == -1)
		error_bmp(base, bmp, NULL, 25);
	pixelbuffer = pixel_data(base, &base->mlx, bmp->infoheader.imagesize);
	if (pixelbuffer == NULL)
		error_bmp(base, bmp, NULL, 24);
	ret = write(file, pixelbuffer, bmp->infoheader.imagesize);
	if (ret == -1)
		error_bmp(base, bmp, pixelbuffer, 25);
	close(file);
	free(bmp);
	free(pixelbuffer);
}
