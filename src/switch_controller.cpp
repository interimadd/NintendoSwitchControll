#include "switch_controller.h"

static const uint8_t _hidReportDescriptor[] PROGMEM = {
    0x05, 0x01,       //   USAGE_PAGE (Generic Desktop)
    0x09, 0x05,       //   USAGE (Game Pad)
    0xa1, 0x01,       //   COLLECTION (Application)
    0x15, 0x00,       //   LOGICAL_MINIMUM (0)
    0x25, 0x01,       //   LOGICAL_MAXIMUM (1)
    0x35, 0x00,       //   PHYSICAL_MINIMUM (0)
    0x45, 0x01,       //   PHYSICAL_MAXIMUM (1)
    0x75, 0x01,       //   REPORT_SIZE (1)
    0x95, 0x10,       //   REPORT_COUNT (16)
    0x05, 0x09,       //   USAGE_PAGE (Button)
    0x19, 0x01,       //   USAGE_MINIMUM (1)
    0x29, 0x10,       //   USAGE_MAXIMUM (16)
    0x81, 0x02,       //   INPUT (Data,Var,Abs)
    0x05, 0x01,       //   USAGE_PAGE (Generic Desktop)
    0x25, 0x07,       //   LOGICAL_MAXIMUM (7)
    0x46, 0x3b, 0x01, //   PHYSICAL_MAXIMUM (315)
    0x75, 0x04,       //   REPORT_SIZE (4)
    0x95, 0x01,       //   REPORT_COUNT (1)
    0x65, 0x14,       //   UNIT (20)
    0x09, 0x39,       //   USAGE (Hat Switch)
    0x81, 0x42,       //   INPUT (Data,Var,Abs)
    0x65, 0x00,       //   UNIT (0)
    0x95, 0x01,       //   REPORT_COUNT (1)
    0x81, 0x01,       //   INPUT (Cnst,Arr,Abs)
    0x26, 0xff, 0x00, //   LOGICAL_MAXIMUM (255)
    0x46, 0xff, 0x00, //   PHYSICAL_MAXIMUM (255)
    0x09, 0x30,       //   USAGE (X)
    0x09, 0x31,       //   USAGE (Y)
    0x09, 0x32,       //   USAGE (Z)
    0x09, 0x35,       //   USAGE (Rz)
    0x75, 0x08,       //   REPORT_SIZE (8)
    0x95, 0x04,       //   REPORT_COUNT (4)
    0x81, 0x02,       //   INPUT (Data,Var,Abs)
    0x06, 0x00, 0xff, //   USAGE_PAGE (Vendor Defined 65280)
    0x09, 0x20,       //   USAGE (32)
    0x95, 0x01,       //   REPORT_COUNT (1)
    0x81, 0x02,       //   INPUT (Data,Var,Abs)
    0x0a, 0x21, 0x26, //   USAGE (9761)
    0x95, 0x08,       //   REPORT_COUNT (8)
    0x91, 0x02,       //   OUTPUT (Data,Var,Abs)
    0xc0              // END_COLLECTION
};

CustomHID_::CustomHID_()
{
}

int CustomHID_::SendReport(const void *data, int len)
{
	auto ret = USB_Send(pluggedEndpoint | TRANSFER_RELEASE, data, len);
	return ret;
}

CustomHID_ &CustomHID()
{
	static CustomHID_ obj;
	return obj;
}

SwitchController_::SwitchController_()
{
    static HIDSubDescriptor node(_hidReportDescriptor, sizeof(_hidReportDescriptor));
    CustomHID().AppendDescriptor(&node);

    memset(&_joystickInputData, 0, sizeof(USB_JoystickReport_Input_t));
    setStickTiltRatio(0,0,0,0);
    releaseHatButton();
}

int SwitchController_::sendReport()
{
    CustomHID().SendReport(&_joystickInputData, sizeof(USB_JoystickReport_Input_t));
}

void SwitchController_::pressButton(Button button_num)
{
    _joystickInputData.Button |= (uint16_t)button_num;
    sendReport();
}

void SwitchController_::releaseButton(Button button_num)
{
    _joystickInputData.Button &= ((uint16_t)button_num ^ 0xffff);
    sendReport();
}

void SwitchController_::pressHatButton(Hat hat)
{
    _joystickInputData.Hat = (uint8_t)hat;
    sendReport();
}

void SwitchController_::releaseHatButton()
{
    _joystickInputData.Hat = (uint8_t)Hat::CENTER;
    sendReport();
}

void SwitchController_::setStickTiltRatio(int16_t lx_per, int16_t ly_per,
                                          int16_t rx_per, int16_t ry_per)
{
    _joystickInputData.LX = (uint8_t)(lx_per * 0xFF / 200 + 0x80);
    _joystickInputData.LY = (uint8_t)(ly_per * 0xFF / 200 + 0x80);
    _joystickInputData.RX = (uint8_t)(rx_per * 0xFF / 200 + 0x80);
    _joystickInputData.RY = (uint8_t)(ry_per * 0xFF / 200 + 0x80);
    sendReport();
}

SwitchController_ &SwitchController()
{
    static SwitchController_ obj;
    return obj;
}
