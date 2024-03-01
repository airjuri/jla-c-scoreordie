#include "c64_gfx.h"

char _screenChar;
char _screenCharColor;

void Cls()
{
    _screenChar = ' '; 
    FillScreen();
    FillScreenColor();
}

// TODO these 2 functions to their own source file
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

void Scroll1Left()
{
    __asm__("clc");
    __asm__("ldx #4");
    __asm__("ldy #0");
    __asm__("LineCopyLoop:");
    __asm__("lda $0429,y"); __asm__("sta $0428,y");
    __asm__("lda $042a,y"); __asm__("sta $0429,y");
    __asm__("lda $042b,y"); __asm__("sta $042a,y");
    __asm__("lda $042c,y"); __asm__("sta $042b,y");
    __asm__("lda $042d,y"); __asm__("sta $042c,y");
    __asm__("lda $042e,y"); __asm__("sta $042d,y");
    __asm__("lda $042f,y"); __asm__("sta $042e,y");
    __asm__("lda $0430,y"); __asm__("sta $042f,y");
    __asm__("lda $0431,y"); __asm__("sta $0430,y");
    __asm__("lda $0432,y"); __asm__("sta $0431,y");
    __asm__("tya");
    __asm__("adc #10");
    __asm__("tay");
    __asm__("dex");
    __asm__("bne LineCopyLoop");
}

