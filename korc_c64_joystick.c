// C64 Joystick read functions

#include "korc_c64_joystick.h"

#define JOY2_ENABLED

#ifdef JOY1_ENABLED

char _joy1State = 0xff;

void Joystick1Read()
{
    _joy1State = *(char *)0xdc01;
}

#endif


#ifdef JOY2_ENABLED

char _joy2State = 0x0f;

void Joystick2Read()
{
    _joy2State = *(char *)0xdc00;
}

#endif