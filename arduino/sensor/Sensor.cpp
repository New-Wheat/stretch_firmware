#include <Wire.h>
#include <DHT.h>
#include <Adafruit_SGP30.h>
#include "Sensor.h"

DHT dhtSensor(DHTPIN, DHTTYPE);
Adafruit_SGP30 sgpSensor;

Sensor wacc_sensor;

void setupSensor() {
  dhtSensor.begin();
  sgpSensor.begin();
}

/* return absolute humidity [mg/m^3] with approximation formula
* @param temperature [°C]
* @param humidity [%RH]
*/
uint32_t getAbsoluteHumidity(float temperature, float humidity) {
  // approximation formula from Sensirion SGP30 Driver Integration chapter 3.15
  const float absoluteHumidity = 216.7f * ((humidity / 100.0f) * 6.112f * exp((17.62f * temperature) / (243.12f + temperature)) / (273.15f + temperature)); // [g/m^3]
  const uint32_t absoluteHumidityScaled = static_cast<uint32_t>(1000.0f * absoluteHumidity); // [mg/m^3]
  return absoluteHumidityScaled;
}

void Sensor::timeCounter() {
  counter++;
  counter %= 2000;
  // Update sensors at 0.5HZ
  if (counter == 1) {
    state &= ~SENSOR_STANDBY;
    return;
  }
  state |= SENSOR_STANDBY;
}

#define DHT_DEBUG
#define I2C_DEBUG

void Sensor::getSensorState() {
  state = 0;
  timeCounter();
  if (state & SENSOR_STANDBY) {
    return;
  }

  float temperLocal = dhtSensor.readTemperature();
  float humidLocal = NAN;// dhtSensor.readHumidity();
  if (isnan(temperLocal)) {
    state |= SENSOR_TEMP_FAIL;
  } else {
    temper = temperLocal;
  }
  if (isnan(humidLocal)) {
    state |= SENSOR_HUMI_FAIL;
  } else {
    humid = humidLocal;
  }

  if (!((state & SENSOR_TEMP_FAIL) || (state & SENSOR_HUMI_FAIL))) {
    sgpSensor.setHumidity(getAbsoluteHumidity(temperLocal, humidLocal));
  }
  if (!sgpSensor.IAQmeasure()) {
    state |= SENSOR_IAQ_FAIL;
  } else {
    tvoc = sgpSensor.TVOC;
    eco2 = sgpSensor.eCO2;
  }
}

void Sensor::getSensorStatus(Sensor_Status &status) {
  // request sensor values and evaluate sensor states
  getSensorState();

  if (!(state & SENSOR_TEMP_FAIL)) {
    status.temperature = temper;
  }
  if (!(state & SENSOR_HUMI_FAIL)) {
    status.humidity = humid;
  }
  if (!(state & SENSOR_IAQ_FAIL)) {
    status.TVOC = tvoc;
    status.eCO2 = eco2;
  }
  status.state = state;
}

// If you have a baseline measurement from before you can assign it to start, to 'self-calibrate'
//sgp.setIAQBaseline(0x8E68, 0x8F41);  // Will vary for each sensor!
