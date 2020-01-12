#include <HID.h>

#pragma once

enum Button : uint16_t
{
	Y = 0x0001,
	B = 0x0002,
	A = 0x0004,
	X = 0x0008,
	L = 0x0010,
	R = 0x0020,
	ZL = 0x0040,
	ZR = 0x0080,
	MINUS = 0x0100,
	PLUS = 0x0200,
	LCLICK = 0x0400,
	RCLICK = 0x0800,
	HOME = 0x1000,
	CAPTURE = 0x2000
};

enum Hat : uint8_t
{
	UP = 0x00,
    UP_RIGHT = 0x01,
	RIGHT = 0x02,
    RIGHT_DOWN = 0x03,
	DOWN = 0x04,
    DOWN_LEFT = 0x05,
	LEFT = 0x06,
    LEFT_UP = 0x07,
	CENTER = 0x08
};

typedef struct
{
	uint16_t Button;
	uint8_t Hat;
	uint8_t LX;
	uint8_t LY;
	uint8_t RX;
	uint8_t RY;
	uint8_t VendorSpec;
} USB_JoystickReport_Input_t;

class CustomHID_ : public HID_
{
public:
  CustomHID_();
  int SendReport(const void *data, int len);
};

class SwitchController_
{
    private:
        USB_JoystickReport_Input_t _joystickInputData;
    public:
        SwitchController_();
        int sendReport();
        void pressButton(Button button_num);
        void releaseButton(Button button_num);
        void pressHatButton(Hat hat);
        void releaseHatButton();
        void setStickTiltRatio(int16_t lx_per, int16_t ly_per,
                               int16_t rx_per, int16_t ry_per);
};

CustomHID_ &CustomHID();
SwitchController_ &SwitchController();

