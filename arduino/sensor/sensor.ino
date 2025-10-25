  /*
  -------------------------------------------------------------
  Hello Robot - Hello Wacc

  All materials released under the GNU General Public License v3.0 (GNU GPLv3).
  https://www.gnu.org/licenses/gpl-3.0.html      

  Copyright (c) 2020 by Hello Robot Inc. 
  --------------------------------------------------------------
*/

#include <Arduino.h>
#include "Sensor.h"

Sensor_Status sensor;

void setup()        // This code runs once at startup
{
  SerialUSB.begin(2000000);
  setupSensor();
}

void loop()
{
  wacc_sensor.getSensorStatus(sensor);
  if(!(sensor.state & SENSOR_STANDBY)) {
    SerialUSB.println(sensor.temperature);
    SerialUSB.println(sensor.humidity);
    SerialUSB.println(sensor.TVOC);
    SerialUSB.println(sensor.eCO2);
  }
  delay(1);
}
