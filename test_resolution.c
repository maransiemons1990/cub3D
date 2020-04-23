
// cpp -v
//gcc -framework CoreGraphics test_resolution.c 

// https://stackoverflow.com/questions/4170459/mac-adding-coregraphics-framework-for-cg-use-in-a-c-header
// https://stackoverflow.com/questions/4921817/get-screen-resolution-programmatically-in-os-x
// https://stackoverflow.com/questions/1780133/linking-against-apple-frameworks-with-gcc
// https://developer.apple.com/library/archive/documentation/MacOSX/Conceptual/BPFrameworks/Tasks/IncludingFrameworks.html

#include <CoreGraphics/CGDirectDisplay.h>
#include <stdio.h>

int main()
{
    int mainDisplayId = CGMainDisplayID();
    int width = CGDisplayPixelsWide(mainDisplayId);
    int height = CGDisplayPixelsHigh(mainDisplayId);

    printf("%d %d\n", width, height);
}