#ifndef __SENSOR_H__
#define __SENSOR_H__

// #include "Common.h"

#define DHTPIN 14     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11 sensor

#define SENSOR_TEMP_FAIL (1L)
#define SENSOR_HUMI_FAIL (1L << 1)
#define SENSOR_IAQ_FAIL (1L << 2)
#define SENSOR_STANDBY (1L << 3)


struct __attribute__ ((packed)) Sensor_Status{
  float temperature;
  float humidity;
  uint16_t TVOC;
  uint16_t eCO2;
  uint8_t state;
};

class Sensor{
  private:
    float temper;   // °C
    float humid; // %
    uint16_t tvoc;  // ppb
    uint16_t eco2;  // ppm
    uint8_t state;
    uint16_t counter;
    void timeCounter();
    void getSensorState();

  public:
    Sensor(): temper(100), humid(50), tvoc(10), eco2(20), state(0), counter(0) {}
    void getSensorStatus(Sensor_Status&);
};

extern Sensor wacc_sensor;
extern void setupSensor();

#endif
