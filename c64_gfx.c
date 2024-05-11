#include <stdio.h>

#include "c64_gfx.h"

const char _bitLUT[] = { 1,2,4,8,16,32,64,128 };

//char _screenChar;
//char _screenCharColor;

char *_spriteColor = (char *)0xd027;

void Cls()
{
    /*
    _screenChar = ' '; 
    FillScreen();
    FillScreenColor();
    */
   printf("%c", 147);
}

/*
void FillScreen()
{
    __asm__("ldx #0");
    __asm__("lda %v", _screenChar);
    __asm__("FillScreen_Loop1:");
    __asm__("sta $0400,x");
    __asm__("sta $0500,x");
    __asm__("sta $0600,x");
    __asm__("sta $06e8,x");
    __asm__("dex");
    __asm__("bne FillScreen_Loop1");
}

void FillScreenColor()
{
    __asm__("ldx #0");
    __asm__("lda %v", _screenCharColor);
    __asm__("FillScreenColor_Loop1:");
    __asm__("sta $d800,x");
    __asm__("sta $d900,x");
    __asm__("sta $da00,x");
    __asm__("sta $dae8,x");
    __asm__("dex");
    __asm__("bne FillScreenColor_Loop1");
}
*/
// Sets position of sprite. Sprite number maximum is 7
// DO NOT go out of limits on that one!
// X- and Y-coordinates are "safe"
void SetSpriteXY(char sprite, int xPosition, char yPosition)
{
    char spriteOffset = sprite << 1;
    *(char *)(0xd000 + spriteOffset) = (char)xPosition;
    *(char *)(0xd001 + spriteOffset) = yPosition;

    *(char *)0xd010 = xPosition < 256
                    ? *(char *)0xd010 & ~_bitLUT[sprite]
                    : *(char *)0xd010 | _bitLUT[sprite];
}

void PrintX(char x, const char *text)
{
    *(char *)0x00d3 = x;
    puts(text);    
}