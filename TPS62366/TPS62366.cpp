/*
  TPS62366.cpp - Texas Instruments TPS62366x Control Library
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

#include <Arduino.h> 
#include "TPS62366.h"

TPS62366::TPS62366(int enable_pin, int vselect_pin)
{
    EN_PIN = enable_pin;
    VSEL_PIN = vselect_pin;
    // Set the mode for the enable pin, and set it low.
    pinMode(EN_PIN, OUTPUT);
    digitalWrite(EN_PIN, LOW);
    // And the same for the VSEL pin
    pinMode(VSEL_PIN, OUTPUT);
    digitalWrite(VSEL_PIN, LOW);
    
    Wire.begin();
}

uint8_t TPS62366::readID()
{
    return read(CHIP_ID0);
}

void TPS62366::enable(int enableoutput){
    digitalWrite(EN_PIN, enableoutput);
}

void TPS62366::setVSEL(int vselstate){
    digitalWrite(VSEL_PIN, vselstate);
}

void TPS62366::setVoltage(int reg, int millivolts){
    if(millivolts>TPS_VOLTAGE_MAX || millivolts<TPS_VOLTAGE_MIN){
        return;
    }else{
        millivolts = ((millivolts - 500)/10) & SET_OV; // Scale output to go into register, and bitmask.
    }
    
    if(readOPMode(reg)){
        if(reg){
            write(SET1_ADDR, SET_MODE|millivolts);
        }else{
            write(SET0_ADDR, SET_MODE|millivolts);
        }
    }else{
        if(reg){
            write(SET1_ADDR, millivolts);
        }else{
            write(SET0_ADDR, millivolts);
        }
    }
}

void TPS62366::setVoltage(int reg, int millivolts, int opmode){
    if(millivolts>TPS_VOLTAGE_MAX || millivolts<TPS_VOLTAGE_MIN){
        return;
    }else{
        millivolts = ((millivolts - 500)/10) & SET_OV; // Scale output to go into register, and bitmask.
    }
    
    if(opmode){
        if(reg){
            write(SET1_ADDR, SET_MODE|millivolts);
        }else{
            write(SET0_ADDR, SET_MODE|millivolts);
        }
    }else{
        if(reg){
            write(SET1_ADDR, millivolts);
        }else{
            write(SET0_ADDR, millivolts);
        }
    }
}

void TPS62366::setVoltage(int millivolts){
    setVoltage(0, millivolts);
    setVoltage(1, millivolts);
}

int TPS62366::readOPMode(int reg){
    // Read in the entire SET register.
    uint8_t set_reg_data;
    if(reg){
        set_reg_data = read(SET1_ADDR);
    }else{
        set_reg_data = read(SET0_ADDR);
    }
    
    // Return 1 if the MODE bit is set (if forced PWM is on).
    return (set_reg_data & SET_MODE)>0;
}

int TPS62366::readTjEW(){
    uint8_t temp_reg_data = read(TEMP_ADDR);
    return (temp_reg_data & TEMP_TJEW) > 0;
}

int TPS62366::readTjTS(){
    uint8_t temp_reg_data = read(TEMP_ADDR);
    return (temp_reg_data & TEMP_TJTS) > 0;
}

void TPS62366::resetTjTS(){
    write(TEMP_ADDR, 0x00);
}

void TPS62366::write(int address, int data)
{
  Wire.beginTransmission(TPS62366_ADDR);
  Wire.write(address);
  Wire.write(data);
  Wire.endTransmission();
}

uint8_t TPS62366::read(int address)
{
  Wire.beginTransmission(TPS62366_ADDR);
  Wire.write(address);
  Wire.endTransmission();
  
  Wire.beginTransmission(TPS62366_ADDR);
  Wire.requestFrom(TPS62366_ADDR, 1, true);

  uint8_t read_data = Wire.read();
  Wire.endTransmission();

  return read_data;
}