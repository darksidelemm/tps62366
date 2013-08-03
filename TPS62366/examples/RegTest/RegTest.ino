/*
  TPS62366 Library Example Program
  Copyright (c) 2013 Mark Jessop.  All right reserved.
  
  This program sets enables the regulator, and switches the output voltage 
  between 2 defined values. It also checks the junction temperature bit
  to check it is not >120 degrees C.

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

#include <Wire.h>
#include <TPS62366.h>

#define ENABLE_PIN   5
#define VSELECT_PIN  4

#define VOLTAGE1    1000
#define VOLTAGE2    500
#define DELAY_TIME  2000

TPS62366 vreg(ENABLE_PIN, VSELECT_PIN);

void setup(){
  Serial.begin(9600);
  Serial.println("Starting up.");
  vreg.setVoltage(VOLTAGE1);
  vreg.enable(1);
}

void loop(){
    vreg.setVoltage(VOLTAGE1);
    Serial.print("Output Voltage(mV): ");
    Serial.println(VOLTAGE1);
    if(vreg.readTjEW()) Serial.println("Tj over 120 degrees!");
    
    delay(DELAY_TIME);
    
    vreg.setVoltage(VOLTAGE2);
    Serial.print("Output Voltage(mV): ");
    Serial.println(VOLTAGE2);
    if(vreg.readTjEW()) Serial.println("Tj over 120 degrees!");
    
    delay(DELAY_TIME);
}