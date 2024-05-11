#include <stdio.h>
#include <string.h>

#include <stdlib.h>
#include <conio.h>

//#define BORDER_DEBUG
#define JOY2_ENABLED

#include "c64_gfx.h"
#include "korc_c64_joystick.h"
#include "scoreordie_sprites.h"

//extern char _screenChar;
//extern char _screenCharColor;
extern char _joy2State;
extern char *_spriteColor;
extern const char _bitLUT[];

char _exit = 0;
char _exitGame = 0;
char _gameName[] = "SCORE OR DIE";
unsigned int _hiScore = 0;
unsigned int _score = 0;

signed int _enemyX = 511;
signed int _spriteX = 160;
char _enemyY = 229;
char _spriteY = 229;
char _spriteYPos = 229;

char _rollStage = 0;
char _rollSpeed = 0;

char _jumpActive = 0;
char _jumpStage = 0;
char _jumpOffset[] = { 0,1,3,5,6,8,9,11,12,13,15,16,17,18,18,19,20,20,20,20,20,20,20,20,19,18,18,17,16,15,13,12,11,9,8,6,5,3,1,0 };
char _printBuffer[6];

void Init()
{
    InitSprites();

    *(char *)0xd020 = GREEN;      // border
    *(char *)0xd021 = BLACK;    // screen background
    *(char *)0x286 = YELLOW;    // text 
    *(char *)2040 = 192;    // Player   (192 * 64 = 12288, of course 193 also)
    *(char *)2041 = 194;    // Enemy    (194 - 197)

    SPRITE_COLOR(0,YELLOW);
    SPRITE_COLOR(1,LIGHTRED);

    SetSpriteXY(0,100,229);
    SetSpriteXY(1,150,229);
}

void WaitForJoy(char keyboard)
{
    do
    {
        Joystick2Read();
        if(_joy2State != 0x0f) {
            if(JOY2_BUTTON) {
                do
                {
                    Joystick2Read();
                } while (JOY2_BUTTON);
                break;
            }; 
        }

        if(keyboard && kbhit()) {
            cgetc();
            _exitGame = 1;
            _exit = 1;
            break;
        }

    }while(1);
}

void IntroScreen()
{
    Cls();
    printf("%c\n\n\n\n\n", 19);
    PrintX(8, "HALF OF AMFF AKA AIRJURI\n\n");
    PrintX(16, "PRESENTS\n\n");
    PrintX(14, _gameName);

    WaitForJoy(0);
}

void MainMenu()
{
    Cls();
    printf("%c\n\n\n\n\n",19);
    PrintX(14, _gameName);
    printf("\n\n\n");
    PrintX(2, "GET 64000 POINTS TO BE C64 CHAMPION!\n\n");
    PrintX(12, "HINT: DO NOT DIE\n\n\n\n\n\n");
    PrintX(4, "JOYSTICK 2, PUSH BUTTON TO START\n\n");
    PrintX(5, ("HIGHEST SCORE OF SESSION: "));

    ltoa(_hiScore, _printBuffer, 10);
    printf("%c", (char)145);    // Up
    PrintX(31, _printBuffer);    

    WaitForJoy(1);
}

void AdvanceRoll()
{
    if(++_rollSpeed>3){
        _rollSpeed = 0;
        if(++_rollStage>3) _rollStage = 0;
        *(char *)2041 = 194 + _rollStage;
    }
}

void PrintScore()
{
    ltoa(_score, _printBuffer, 10);
    *(char *)0x00d6 = - 1;
    PrintX(7, _printBuffer);
}

void Jumpper()
{
    if(++_jumpStage>=sizeof(_jumpOffset))
    {
        _jumpActive = 0;
        _jumpStage = 0;
    }
}

void WaitVBL()
{
#ifdef BORDER_DEBUG
    *(char *)0xd020 = GREEN;    // border speed indicator
#endif

    while(((*(char *)(0xd011)) & 0b10000000) != 0b10000000);

#ifdef BORDER_DEBUG
    *(char *)0xd020 = LIGHTGREY;
#endif
        
    while(*(char *)(0xd012) < 50); // 251

#ifdef BORDER_DEBUG
    *(char *)0xd020 = RED;
#endif
}

void ScoreOrDie()
{
    if((_spriteX > _enemyX-8)
     &&(_spriteX < _enemyX+8))
     {
        if((_spriteY - _jumpOffset[_jumpStage]) < (229-15)) {
            _score += 5;
            PrintScore();
        }
        else _exitGame = 1;
     }

     if(_score>=64000UL) _exitGame = 1;
}

void GameLoop()
{
    signed char direction = 0;

    _spriteX = 160;
    _enemyX = 511;
    _score = 0;
    _exitGame = 0;
    _jumpStage = 0;
    _jumpActive = 0;

    Cls();
    printf("%cSCORE:",19);
    PrintScore();

    SPRITE_ON(0); // SpriteOn(0);
    SPRITE_ON(1); //SpriteOn(1);

    do
    {
        Joystick2Read();
        if(_joy2State != 0x0f)
        {
            if(!_jumpActive) {
                if(JOY2_LEFT) {
                    direction = -1;
                    _spriteX-=2;
                    if(_spriteX<2) _spriteX = 343;
                    *(char *)2040 = 193;
                }
                else if(JOY2_RIGHT) {
                    direction = 1;
                    _spriteX+=2;
                    if(_spriteX>343) _spriteX = 2;
                    *(char *)2040 = 192;
                }
                else {
                    direction = 0;
                }
            }
            else {
                if(direction > 0) {
                    _spriteX+=2;
                    if(_spriteX>343) _spriteX = 2;
                }
                else if (direction < 0) {
                    _spriteX-=2;
                    if(_spriteX<2) _spriteX = 343;
                }
            }

            if(JOY2_BUTTON || JOY2_UP) _jumpActive = 1;
        }

        if(_jumpActive == 1) Jumpper();

        _enemyX-=2;
        if(_enemyX<10) _enemyX = 330;

        SetSpriteXY(0, _spriteX, 229 - _jumpOffset[_jumpStage]);
        SetSpriteXY(1, _enemyX, 229);
        
        ScoreOrDie();

        AdvanceRoll();

        WaitVBL();
    }while(!_exitGame);

    PrintScore();

    WaitForJoy(0);

    SPRITE_OFF(0);
    SPRITE_OFF(1);
}

void GameOver()
{
    Cls();
    printf("%c\n\n\n\n\n\n\n\n", 19);
    PrintX(15, "GAME OVER\n\n");

    if(_score >= _hiScore) {
        _hiScore = _score;
        PrintX(4, "CONGRATULATIONS FOR HIGH SCORE\n\n");
        if(_hiScore<63000UL) {
            PrintX(10, "RANK: REGULAR CHAMP");
        }
        else {
            PrintX(10,"RANK: C64 CHAMPION 64000!");
        }

        printf("\n\n        NEW HIGH SCORE: %u", _hiScore);
    }
    else {
        PrintX(15, (14,14,"SAD TIMES"));
    }

    WaitForJoy(0);
}

int main()
{
    Init();
    IntroScreen();

    _exit = 0;
    do{
        MainMenu(); if(_exit) break;
        GameLoop();
        GameOver();
    }while(!_exit);

    return 0;
}