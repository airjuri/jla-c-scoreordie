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

void Init()
{
 
    *(char *)0xd020 = RED;      // border
    *(char *)0xd021 = BLACK;    // screen background
    *(char *)0x286 = YELLOW;
    _screenCharColor = YELLOW;
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




void GameLoop()
{

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