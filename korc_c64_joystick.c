// C64 Joystick read functions

char _joy1State = 0xff;
char _joy2State = 0x0f;

void JoystickRead()
{
    _joy1State = *(char *)0xdc01;
    _joy2State = *(char *)0xdc00;
}

/*
void Joy1Read()
{
    joy1State = *(char *)0xdc01;
}

void Joy2Read()
{
    joy2State = *(char *)0xdc00;
}
*/

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