man mlx
https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html

### TO DO:
- Check return values van functies bijv. init



### DESCRIPTION
MiniLibX  is  an  easy way to create graphical software, without any X-Window/Cocoa programming knowledge. It provides simple window creation, a drawing tool, image and basic events management.

### MLX_INIT (STEP 1)
First of all, you need to initialize the connection between your  software  and  the display.  Once this connection is established, you'll be able to use other MiniLibX functions to send the graphical orders, like "I  want  to draw a yellow pixel in this window" or "did the user hit a key?".

The **mlx_init function** will create this connection.  No  parameters  are needed,  ant it will return a void * identifier, used for further calls to the library routines.


### MLX_NEW_WINDOW - Managing windows
void *mlx_new_window ( void *mlx_ptr, int size_x, int size_y, char *title );

The mlx_new_window  ()  function creates a new window on the screen, using the size_x and size_y parameters to determine its size, and title as the text that should be displayed in the window's title bar. The mlx_ptr parameter is the connection identifier  returned  by mlx_init  ().

mlx_new_window () returns a void * window identifier that can be used by other MiniLibX calls.

### MLX_NEW_IMAGE - Manipulating images
void *mlx_new_image ( void *mlx_ptr, int width, int height);

mlx_new_image () creates a new image in memory. It returns a void * identifier needed to manipulate this image later. It only needs the size of the image to be created, using the width and height parameters, and the mlx_ptr connection identifier returned by mlx_init ().

The user can draw inside the image (see below), and can dump the image inside a specified window at any  time  to  display  it  on  the screen. This is done using **mlx_put_image_to_window ()**. Three identifiers are needed here, for the connection to the display, the window to use, and the image (respectively mlx_ptr , win_ptr and img_ptr ). The ( x , y ) coordinates define where the image should be  placed in the window.

### MLX_GET_DATA_ADDR
char *mlx_get_data_addr (void *img_ptr, int *bits_per_pixel, int *size_line, int *endian );

returns information about the created image, allowing a user to modify it later. The img_ptr parameter specifies the image to use. 
The three next parameters should be the addresses of three different valid integers:

- **bits_per_pixel**: will  be  filled with  the number of bits needed to represent a pixel color (also called the depth of the image).  
- **size_line**: is the number of bytes used to store one line of the image in memory.  This information is needed to move from one line to another in the image.  
- **endian**: tells  you wether the pixel color in the image needs to be stored in little endian ( endian == 0), or big endian ( endian == 1).

mlx_get_data_addr returns a char * address that represents the begining of the memory area where the image is stored. From this adress:
- the first bits_per_pixel bits represent the color of the first pixel in the first line of the image.
- The second group of bits_per_pixel bits represent the second pixel of the first line, and so on.
Add size_line to the adress to get the begining of the second line. You can reach any pixels of the image that way.

>We must understand that the bytes are not aligned, this means that the line_length (size_line) differs from the actual window width. We therefore should ALWAYS calculate the memory offset using the line length  set by mlx_get_data_addr.

```
We can calculate it very easily by using the following formula:
int     offset = (y * line_length + x * (bits_per_pixel / 8));
```


/*
    ** After creating an image, we can call `mlx_get_data_addr`, we pass
    ** `bits_per_pixel`, `line_length`, and `endian` by reference. These will
    ** then be set accordingly for the *current* data address.
*/


# COLOR MANAGEMENT
https://www.shodor.org/stella2java/rgbint.html
The  color parameter has an integer type. 

The displayed color needs to be encoded in this integer, following a defined scheme. All displayable colors can be split in 3 basic colors: red, green and blue. Three associated values, in the 0-255 range, represent how much of each color is mixed up to create the original color. Theses three values must be set inside the integer to display the right color. The three least significant bytes of this integer are filled as shown in the picture below:

               | 0 | R | G | B |   color integer
               +---+---+---+---+

While filling the integer, make sure you avoid endian problems. Remember that the "blue" byte should always be  the  least  significant one.


We shift bits to use an TRGB format. We initialize it as follows: **0xTTRRGGBB**

T Transparency;
R Red color;
G Green color;
B Blue color.

Red: 0x00FF0000; ARGB(0,255,0,0)
Green: 0x0000FF00;
Blue: 0x000000FF;

0000 0000 - 1111 1111
Since each byte contains 2^8 values, and rgb values range from 0 to 255, we can perfeclty fit a integer (as an int is 4 bytes (32 bits)).

> As the pixels are basically ints, these usually are 4 bytes, however, this can differ if we are dealing with a small endian (which means we most likely are on a remote display and only have 8 bit colors).

### Bitshifting
https://stackoverflow.com/questions/7358533/how-to-pack-argb-to-one-integer-uniquely

0101 1010	= 90
90 >> 1				; shift to the right by 1
0010 1101	= 45 	; shift to the right by 1 is same as /2

90 << 1				; shifting to the left by 1
1011 0100	= 180	; shifting to the left by 1 is same as *2


Because ints are stored from right to left, we need to bitshift each value the according amount of bits backwards. 


----
Each value in your color map is 8 bits long. So in order for the resulting number to be unique, it must string them all together, for a total of 8 *4 =32 bits.

```
TTTTTTTT
RRRRRRRR
GGGGGGGG
BBBBBBBB
```
```
TTTTTTTTRRRRRRRRGGGGGGGGBBBBBBBB
```
This means you have to add the following together:
> Because ints are stored from right to left, we need to bitshift each value the according amount of bits backwards. 
```
						TTTTTTTT
        		RRRRRRRR00000000
        GGGGGGGG0000000000000000
BBBBBBBB000000000000000000000000
--------------------------------
BBBBBBBBGGGGGGGGRRRRRRRRTTTTTTTT
```
We accomplish this by bit-shifting to the left. Taking B and shifting 24 bits to the left will produce BBBBBBBB followed by 24 0 bits, just like we want. Following that logic, you will want to do:

```
sum = b << 24 + g << 16 + r << 8 + t 
```
**BGRT**
RED: 
0000 0000 | 0000 0000 | 1111 1111 | 0000 0000 	= 65280

GREEN:
0000 0000 | 1111 1111 | 0000 0000 | 0000 0000 	= 16711680

etc.

---
Lijkt niet te kloppen:
65280 lijkt toch groen