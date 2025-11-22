#ifndef __SENSOR_H__
#define __SENSOR_H__

#include "Common.h"

#define DHTPIN D1
#define DHTTYPE DHT11

#define SENSOR_DHT_FAIL (1L)
#define SENSOR_SGP_FAIL (1L << 1)
#define SENSOR_STANDBY (1L << 2)

class Sensor{
  private:
    float temper;   // °C
    float humid; // %
    uint16_t tvoc;  // ppb
    uint16_t eco2;  // ppm
    uint8_t state;
    uint32_t lastReadTime;
    void timeCounter();

  public:
    Sensor(): temper(0), humid(0), tvoc(0), eco2(0), state(0), lastReadTime(0) {}
    inline uint8_t getState() const { return state; }
    void pollSensorStatus();
    void updateSensorStatus(Sensor_Status&) const;
};

extern Sensor wacc_sensor;
extern void setupSensor();

#endif
