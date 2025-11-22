  /*
  -------------------------------------------------------------
  Hello Robot - Hello Wacc

  All materials released under the GNU General Public License v3.0 (GNU GPLv3).
  https://www.gnu.org/licenses/gpl-3.0.html      

  Copyright (c) 2020 by Hello Robot Inc. 
  --------------------------------------------------------------
*/

#include <Arduino.h>
#include "Common.h"
#include "Transport.h"
#include "Wacc.h"
#include "Accel.h"
#include "Sensor.h"

void setup()        // This code runs once at startup
{
  setupBoardVariants();
  setupAccel();
  setupSensor();
  SerialUSB.begin(2000000);
  setupWacc();
  setupTransport();

  delay(20);        // Delay for a bit for better stability
  wacc_sensor.pollSensorStatus();
}

void loop()
{
  stepWaccRPC();
  wacc_sensor.pollSensorStatus();
}