// C64 Joystick functions

#ifndef _KORC_C64_JOYSTICK_
#define _KORC_C64_JOYSTICK_

#ifdef JOYSTICK2_ENABLED
void Joystick2Read();
char Joy2Up();
char Joy2Down();
char Joy2Right();
char Joy2Left();
char Joy2Button();
#endif

#ifdef JOYSTICK1_ENABLED
void Joystick1Read();
char Joy1Up();
char Joy1Down();
char Joy1Right();
char Joy1Left();
char Joy1Button();
#endif

#endif