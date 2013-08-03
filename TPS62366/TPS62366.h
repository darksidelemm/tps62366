/*
  TPS62366.h - Texas Instruments TPS62366x Control Library
  Copyright (c) 2013 Mark Jessop.  All right reserved.

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  For a full copy of the GNU General Public License, 
  see <http://www.gnu.org/licenses/>.
*/

#ifndef __TPS62366_H__
#define __TPS62366_H__

#include <Arduino.h>
#include <Wire.h>

// TPS62366 I2C Address
#define TPS62366_ADDR   0x60

// Registers
#define SET0_ADDR       0x00    // Voltage Control Register 0
#define SET1_ADDR       0x01    // Voltage Control Register 1
#define CTRL_ADDR       0x04    // EN/VSEL Pin Control Register
#define TEMP_ADDR       0x05    // Temperature Shutdown Register
#define RMPCTRL_ADDR    0x06    // Ramp Control Register
#define CHIP_ID0        0x08    // Chip ID Register 0
#define CHIP_ID1        0x09    // Chip ID Register 1

// Voltage Control Masks
#define SET_MODE        0x80    // Operation Mode Bit (1 = Forced PWM, 0 = PFM/PWM)
#define SET_OV          0x7F    // Output Voltage mask(0x00 = 500mV, 0x7F = 1770mV)

// IO Control Register Masks
#define CTRL_PD_EN      0x80    // EN internal pull down
#define CTRL_PD_VSEL    0x40    // VSEL internal pull down

// Temp Register Masks
#define TEMP_DIS_TS     0x04    // Temperature shutdown disable bit (1 = disable, 0 = enabled)
#define TEMP_TJEW       0x02    // Junction Temperature early warning bit (0 = <120, 1 = >120)
#define TEMP_TJTS       0x01    // Junction Temperature Shutdown bit (1 = triggered)

// Ramp Control Masks
#define RMP_SET         0xE0    // Ramp Timing. (0 = 32mV/us, 7=0.25mV/us)
#define RMP_EN_DISC     0x04    // Activate output capacitor discharge at shutdown.
#define RMP_PFM         0x02    // PFM mode ramp behaviour. See datasheet.

// ID register Masks
#define ID_VENDOR       0xF0    // Vendor ID (0b1001)
#define ID_PART         0x0C    // Part Number ID (00=A, 01=B)
#define ID_REV          0x03    // Chip Revision

// Limits
#define TPS_VOLTAGE_MAX     1770
#define TPS_VOLTAGE_MIN     500

class TPS62366
{
	public:
	  TPS62366(int enable_pin, int vselect_pin);
      uint8_t readID();
      int readOPMode(int reg);
      void setVoltage(int reg, int millivolts);
      void setVoltage(int reg, int millivolts, int opmode);
      void setVoltage(int millivolts);
      void enable(int enableoutput);
      void setVSEL(int vselstate);
      int readTjEW();
      int readTjTS();
      void resetTjTS();
      

	protected:
	  void write(int address, int byte);
	  uint8_t read(int address);

	private:
	  int EN_PIN;
	  int VSEL_PIN;
};


#endif