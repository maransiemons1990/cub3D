man mlx
https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html

### TO DO:
- Check return values van functies bijv. init
- Vraag hulp bij X11, " It therefore is no secret that this header is very useful for finding all the according events of MiniLibX"Moet ik head toevoegen ofzo?
	- Documentatie lezen over X11: "go read the documentation of each X11 function" 
	bijv https://tronche.com/gui/x/xlib/events/keyboard-pointer/keyboard-pointer.html
	http://www6.uniovi.es/cscene/CS8/CS8-04.html
	- wss iets van mask aanpassen in struct oid?


### COMPILEN
Voorlopig:
>$ make
>$ gcc -Wall -Wextra -Werror -I mlx -L mlx -lmlx -framework OpenGL -framework AppKit main.c

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
65280 lijkt toch groen --> misschien wordt toch niet omgedraaid. Maarja



--------------------------------------------
#
### EVENTS /MLX_lOOP
int		mlx_loop ( void *mlx_ptr );
int		mlx_key_hook 	(void *win_ptr, int (*funct_ptr)(), void *param );
int		mlx_mouse_hook (void *win_ptr, int (*funct_ptr)(), void *param );
int		mlx_expose_hook (void *win_ptr, int (*funct_ptr)(), void *param );
int		mlx_loop_hook (void *mlx_ptr, int (*funct_ptr)(), void *param );

Both X-Window and MacOSX graphical systems are bi-directionnal. 
On one hand, the program sends orders to the screen to display pixels, images, and so on.  			
On the other hand, it can get information from the keyboard and mouse associated to the screen. 	
To do so, the  program receives "events" from the keyboard or the mouse.

program --> screen
keyboard/mouse --**events**--> program

*Events are the foundation of writing interactive applications in MiniLibX.*

To  receive  events,  you  must  use mlx_loop (). This function never returns. It is an infinite loop that waits for an event, and then calls a user-defined function associated with this event. A single parameter is needed, the connection identifier mlx_ptr.

You can assign different functions to the three following events:
- A key is pressed
- The mouse button is pressed
- A part of the window should be re-drawn (this is called an "expose" event, and it is your program's job to handle it).

Each window can define a different function for the same event.

#
The three functions mlx_key_hook (), mlx_mouse_hook () and mlx_expose_hook () work exactly the same way:
funct_ptr is a pointer to the function you want to be called when an event occurs. This assignment is specific to the window defined by the win_ptr identifier.
The param adress will be passed to the function everytime it is called, and should be used to store the parameters it might need.

(void *win_ptr, 				int (*funct_ptr)(), 				void *param );


The  syntax  for  the  mlx_loop_hook () function is identical to the previous ones, but the given function will be called when **no** event occurs.
#

```
 When it catches an event, the MiniLibX calls the corresponding function with fixed parameters:

         expose_hook(void *param);
         key_hook(int keycode,void *param);
         mouse_hook(int button,int x,int y,void *param);
         loop_hook(void *param);

 These function names are arbitrary. They here are used to distinguish parameters according to the event. These functions are  NOT  part of the MiniLibX.
```

param  is  the  address  specified  in  the mlx_*_hook calls. This address is never used nor modified by the MiniLibX. 
On key and mouse events, additional information is passed: 
keycode tells you which key is pressed (X11 : look for the include file "keysymdef.h",  MacOS:  create  a small software and find out by yourself),( x , y ) are the coordinates of the mouse click in the window, and button tells you which mouse button was pressed.

#
All hooks in MiniLibX are nothing more than a function that gets called whenever a event is triggered.
#

#### X11 Events
X11 is the library that is used alongside of MiniLibX. It therefore is no secret that this header is very useful for finding all the according events of MiniLibX. There are a number of events to which you may describe.

02: KeyPress
03: KeyRelease
04: ButtonPress
05: ButtonRelease
etc.

#### X11 Masks
Each X11 event, also has a according mask. This way you can register to only one key when it triggers, or to all keys if you leave your mask to the default. Key masks therefore allow you to whitelist / blacklist events from your event subscriptions. The following masks are allowed:

https://harm-smits.github.io/42docs/libs/minilibx/events.html

#
##### X-WINDOW CONCEPT
X-Window is a network-oriented graphical system for Unix. It is based on two main parts:
1. On one side, your software wants to draw something on the screen and/or get keyboard & mouse entries.
2. On the other side, the X-Server manages the screen, keyboard and mouse (It is often refered to as a "display").

A network connection must be established between these two entities to send drawing orders (from the software to the X-Server), 
and keyboard/mouse events (from the X-Server to the software).

Nowadays, most of the time, both run on the same computer.
#

## Hooking into events (often intercepting?)

Keycodes:
https://eastmanreference.com/complete-list-of-applescript-key-codes

# Notes uit files
- Om een rode pixel te printen op window met bestaande trage functie:
mlx_pixel_put(mlx, mlx_win, 10, 10, 16711680);
- https://stackoverflow.com/c/42network/questions/531
- gcc -Wall -Wextra -Werror -I mlx -L mlx -lmlx -framework OpenGL -framework AppKit main.c
- keypress --> keypressfunction --> move --> delete --> move