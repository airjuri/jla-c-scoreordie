#include <stdio.h>

#include "c64_gfx.h"
#include "korc_c64_joystick.h"

extern char _screenChar;
extern char _screenCharColor;

extern char _joy1State;
extern char _joy2State;

char _exit = 0;
char _gameName[] = "SCORE OR DIE";
int _hiScore = 0;

int _enemyX = 511;
char _enemyY = 229;
int _spriteX = 160;
char _spriteY = 229;

char _jumpActive = 0;
char _jumpStage = 0;
char _jumpOffset[] = { 0,1,3,5,6,8,9,11,12,13,15,16,17,18,18,19,20,20,20,20,20,20,20,20,19,18,18,17,16,15,13,12,11,9,8,6,5,3,1,0 };
/*
const jumpTime: byte = 40;
jumpOffset: array[jumpTime] of byte = (0,1,3,5,6,8,9,11,12,13,15,16,17,18,18,19,20,20,20,20,20,20,20,20,19,18,18,17,16,15,13,12,11,9,8,6,5,3,1,0);

*/


void Init()
{
 
    *(char *)0xd020 = RED;      // border
    *(char *)0xd021 = BLACK;    // screen background
    *(char *)0x286 = YELLOW;
    _screenCharColor = YELLOW;

    // Sprite pointers
    *(char *)2040 = 192;
    *(char *)2041 = 194;

    SetSpriteXY(0,100,229);
    SetSpriteXY(1,150,229);
    
    Cls();
}

void WaitForJoy()
{
    do
    {
        JoystickRead();
        if(_joy2State != 0x0f) {
            if(!(0x10 & _joy2State)) {
                do
                {
                    JoystickRead();
                } while (!(0x10 & _joy2State));
                break;
            }; 
        }

    }while(1);
}

void IntroScreen()
{
    Cls();
    printf("%c\n\n\n",19);
    //      0123456789012345678901234567890123456789
    printf("        HALF OF AMFF AKA AIRJURI\n\n");
    printf("                PRESENTS\n\n\n\n");
    printf("              %s", _gameName);

    WaitForJoy();
}

void MainMenu()
{
    Cls();
    printf("%c\n\n\n\n\n              %s\n\n\n\n",19, _gameName);
    printf("  GET 64000 POINTS TO BE C64 CHAMPION!\n\n");
    printf("            HINT: DO NOT DIE\n\n\n\n\n\n\n\n");
    printf("    JOYSTICK 2, PUSH BUTTON TO START\n\n");
    printf("     HIGHEST SCORE OF SESSION: %i", _hiScore);

    WaitForJoy();
}

char _rollStage = 0;
char _rollSpeed = 0;
char _spriteIdx = 0;

void AdvanceRoll()
{
    if(++_rollSpeed>3){
        _rollSpeed = 0;
        if(++_rollStage>3) _rollStage = 0;
        *(char *)2041 = 194 + _rollStage;
    }
}

void Jumpper()
{
    if(++_jumpStage>=sizeof(_jumpStage))
    {
        _jumpActive = 1;
        _jumpStage = 0;
    }
}

void WaitVBL()
{
//        *(char *)0xd020 = LIGHTRED;    // border speed indicator
        while(((*(char *)(0xd011)) & 0b10000000) != 0b10000000);
/*
        *(char *)0xd020 = GREEN;

        *(char *)0xd016 = _xControlRegisterState | xScroll;                  // Set X Scroll
        *(char *)0xd011 = _yControlRegisterState | yScroll[yScrollIndex++];  // Set X Scroll

        *(char *)0xd020 = DARKGREY;

        if(yScrollIndex >= sizeof(yScroll)) yScrollIndex = 0;
*/
        SetSpriteXY(1,_enemyX,_enemyY);
        
        while(*(char *)(0xd012) < 248);
}

void GameLoop()
{
    char exit = 0;

    _spriteX = 160;
    _enemyX = 511;

    Cls();
    SpriteOn(0);
    SpriteOn(1);

    do
    {

        Joystick2Read();
        if(_joy2State != 0x0f)
        {
            if(Joy2Button() == 0) _jumpActive = 1;
        }

        if(_jumpActive == 1) Jumpper();

        _enemyX-=2;
        if(_enemyX<10) _enemyX = 330;

        if(++_jumpStage>39) _jumpStage = 0;
        SetSpriteXY(0, _spriteX, 229 - _jumpOffset[_jumpStage]);
        SetSpriteXY(1, _enemyX, 229);
        AdvanceRoll();

        WaitVBL();
    }while(!exit);

    WaitForJoy();

    SpriteOff(0);
    SpriteOff(1);
}

void GameOver()
{
    Cls();
    printf("%c\n\n\n\n\n\n\n\n               GAME OVER", 19);

    WaitForJoy();
}

int main()
{
    Init();
    IntroScreen();

    _exit = 0;
    do{
        MainMenu();
        GameLoop();
        GameOver();
    }while(!_exit);

    return 0;
}