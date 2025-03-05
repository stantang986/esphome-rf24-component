#include "rf24_sensor.h"

RF24Sensor::RF24Sensor(uint8_t ce_pin, uint8_t csn_pin) 
  : PollingComponent(1000), radio(ce_pin, csn_pin) {
  // 每秒轮询一次
}

void RF24Sensor::setup() {
  if (!radio.begin()) {
    ESP_LOGE("RF24", "Radio hardware not responding!");
    return;
  }
  radio.setPALevel(RF24_PA_LOW);       // 设置功率级别
  radio.setDataRate(RF24_1MBPS);       // 设置数据速率
  radio.openReadingPipe(1, 0xE8E8F0F0E1LL);  // 设置读取管道地址
  radio.startListening();              // 开始监听
}

void RF24Sensor::update() {
  if (radio.available()) {
    char data[32] = {0};
    radio.read(&data, sizeof(data));
    String hex_data = String(data, HEX);  // 将数据转换为 HEX 格式
    id(remote_signal).publish_state(hex_data.c_str());
  }
}
