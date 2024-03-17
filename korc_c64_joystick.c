// C64 Joystick read functions

#include "korc_c64_joystick.h"

#define JOYSTICK2_ENABLED

#ifdef JOYSTICK1_ENABLED
char _joy1State = 0xff;

void Joystick1Read()
{
    _joy1State = *(char *)0xdc01;
}

char Joy1Up()
{
    return 0x01 & _joy1State;
}

char Joy1Down()
{
    return 0x02 & _joy1State;
}

char Joy1Right()
{
    return 0x08 & _joy1State;
}

char Joy1Left()
{
    return 0x04 & _joy1State;
}

char Joy1Button()
{
    return 0x10 & _joy1State;
}
#endif

#ifdef JOYSTICK2_ENABLED

char _joy2State = 0x0f;

void Joystick2Read()
{
    _joy2State = *(char *)0xdc00;
}

char Joy2Up()
{
    return 0x01 & _joy2State;
}

char Joy2Down()
{
    return 0x02 & _joy2State;
}

char Joy2Right()
{
    return 0x08 & _joy2State;
}

char Joy2Left()
{
    return 0x04 & _joy2State;
}

char Joy2Button()
{
    return 0x10 & _joy2State;
}
#endif