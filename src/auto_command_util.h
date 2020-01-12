#include "switch_controller.h"

#pragma once

void pushButton(Button button, int delay_after_pushing_msec, int loop_num=1);
void pushHatButton(Hat button, int delay_after_pushing_msec, int loop_num=1);
void pushHatButtonContinuous(Hat button, int pushing_time_msec);
void tiltJoystick(int lx_per, int ly_per, int rx_per, int ry_per, int tilt_time_msec);
