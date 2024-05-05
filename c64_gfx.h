#ifndef _C64_GFX_H_
#define _C64_GFX_H_

#define BLACK 0
#define WHITE 1
#define RED 2
#define CYAN 3
#define PURPLE 4
#define GREEN 5
#define BLUE 6
#define YELLOW 7
#define ORANGE 8
#define BROWN 9
#define LIGHTRED 10
#define DARKGREY 11
#define GREY 12
#define LIGHTGREEN 13
#define LIGHTBLUE 14
#define LIGHTGREY 15

void FillScreen();
void FillScreenColor();
void Scroll1Left();
void Cls();

#define SPRITE_ON(sprite_no) (*(char *)0xd015 |= _bitLUT[sprite_no])
#define SPRITE_OFF(sprite_no) (*(char *)0xd015 &= ~_bitLUT[sprite_no])
#define SPRITE_BEHIND_GFX(sprite_no) (*(char *)0xd01b |= _bitLUT[sprite_no])
#define SPRITE_FRONT_GFX(sprite_no) (*(char *)0xd01b &= ~_bitLUT[sprite_no])
#define SPRITE_COLOR(sprite_no,color) (_spriteColor[sprite_no] = color)

// Sets position of sprite. Sprite number maximum is 7
// DO NOT go out of limits on that one!
// X- and Y-coordinates are "safe"
void SetSpriteXY(char sprite, int xPosition, char yPosition);

#endif