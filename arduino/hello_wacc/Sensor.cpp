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
  // Update sensors at 0.5HZ
  uint32_t now = millis();
  if (now - lastReadTime > 2000) {
    state &= ~SENSOR_STANDBY;
    lastReadTime = now;
    return;
  }
  state |= SENSOR_STANDBY;
}

/*
 * request sensor values and evaluate sensor states
 */
void Sensor::pollSensorStatus() {
  state = 0;
  timeCounter();
  if (state & SENSOR_STANDBY) {
    return;
  }

  float temperLocal = dhtSensor.readTemperature();
  float humidLocal = dhtSensor.readHumidity();
  if (isnan(temperLocal) || isnan(humidLocal)) {
    state |= SENSOR_DHT_FAIL;
  } else {
    temper = temperLocal;
    humid = humidLocal;
  }

  if (!(state & SENSOR_DHT_FAIL)) {
    sgpSensor.setHumidity(getAbsoluteHumidity(temperLocal, humidLocal));
  }
  if (!sgpSensor.IAQmeasure()) {
    state |= SENSOR_SGP_FAIL;
  } else {
    tvoc = sgpSensor.TVOC;
    eco2 = sgpSensor.eCO2;
  }
}

void Sensor::updateSensorStatus(Sensor_Status &status) const {
  if (!(state & SENSOR_DHT_FAIL)) {
    status.temperature = temper;
    status.humidity = humid;
  }
  if (!(state & SENSOR_SGP_FAIL)) {
    status.TVOC = tvoc;
    status.eCO2 = eco2;
  }
  status.state = state;
}

// If you have a baseline measurement from before you can assign it to start, to 'self-calibrate'
//sgp.setIAQBaseline(0x8E68, 0x8F41);  // Will vary for each sensor!
