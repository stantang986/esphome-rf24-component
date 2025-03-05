#pragma once
#include "esphome.h"
#include <RF24.h>

class RF24Sensor : public PollingComponent {
 public:
  RF24Sensor(uint8_t ce_pin, uint8_t csn_pin);
  void setup() override;
  void update() override;

 private:
  RF24 radio;
};
