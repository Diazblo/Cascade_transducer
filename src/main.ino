#include"Arduino.h"
#include"serial_debug.h"
#include"server_handler.h"


void setup() {
  delay(2000);
  Serial.begin(115200);

  initConf();
  initWiFi();
  initServer();
  // xTaskCreatePinnedToCore( serverHandler, "serverHandler", 10000, NULL, 0, NULL, 1);

}

void loop() {
  serverHandler();
  Serial.println("Hello");
  delay(700);
}
