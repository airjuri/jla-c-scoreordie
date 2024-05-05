// C64 Joystick functions

#ifndef _KORC_C64_JOYSTICK_
#define _KORC_C64_JOYSTICK_

#define JOY2_UP (!(0x01 & _joy2State))
#define JOY2_DOWN (!(0x02 & _joy2State))
#define JOY2_RIGHT (!(0x08 & _joy2State))
#define JOY2_LEFT (!(0x04 & _joy2State))
#define JOY2_BUTTON (!(0x10 & _joy2State))

#define JOY1_UP (!(0x01 & _joy1State))
#define JOY1_DOWN (!(0x02 & _joy1State))
#define JOY1_RIGHT (!(0x08 & _joy1State))
#define JOY1_LEFT (!(0x04 & _joy1State))
#define JOY1_BUTTON (!(0x10 & _joy1State))

#ifdef JOY2_ENABLED
void Joystick2Read();
#endif

#endif