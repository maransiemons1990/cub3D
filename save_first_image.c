/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_first_image.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/17 13:26:51 by Maran         #+#    #+#                 */
/*   Updated: 2020/04/21 18:29:27 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
xxd screenshot.bmp| vim -
Sources:
https://engineering.purdue.edu/ece264/17au/hw/HW15
https://stackoverflow.com/questions/11004868/creating-a-bmp-file-bitmap-in-c
https://itnext.io/bits-to-bitmaps-a-simple-walkthrough-of-bmp-image-format-765dc6857393
*/

#include "cub3d.h"
#include "bmp.h"

void            bmp_header(t_bitmap  *bmp, t_base *base)
{
  bmp->fileheader.filetype = 0x4d42;
  bmp->fileheader.filesize = base->read.render_y * base->read.render_x * (base->mlx.bits_per_pixel / 8) + 54;
  bmp->fileheader.pixeldataoffset = sizeof(t_bitmap);

  bmp->infoheader.headersize = sizeof(t_bmp_infoheader);
  bmp->infoheader.imagewidth = base->read.render_x;
  bmp->infoheader.imageheight = base->read.render_y;
  bmp->infoheader.planes = 1;
  bmp->infoheader.bitsperpixel = base->mlx.bits_per_pixel;
  bmp->infoheader.compression = 0;
  bmp->infoheader.imagesize = bmp->fileheader.filesize - 54;
  bmp->infoheader.xpixelspermeter = 0;
  bmp->infoheader.ypixelspermeter = 0;
  bmp->infoheader.totalcolor = 0;

}

void		save_first_image(t_base *base)
{
    int         file;
    int         ret;
    t_bitmap    *bmp;
    uint8_t     *pixelbuffer;

    file = open("screenshot.bmp", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (file == -1)
         printf("FAIL TO OPEN FILE\n");
  
    
    bmp = (t_bitmap *)calloc(1, sizeof(t_bitmap));
    bmp_header(bmp, base);
    pixelbuffer = (uint8_t*)malloc(bmp->fileheader.filesize);
   
	
	ret = write(file, bmp, sizeof(t_bitmap));
    if (ret == -1)
         printf("FAIL TO WRITE\n");
    
    ft_memset(pixelbuffer, 0XFF, bmp->infoheader.imagesize);
    ret = write(file, pixelbuffer, bmp->infoheader.imagesize);
    if (ret == -1)
         printf("FAIL TO WRITE\n");
    
	close(file);
    free(bmp);
    free(pixelbuffer);
}

