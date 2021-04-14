#include <Wire.h>
#include <BH1750.h>

// SCL = D21
// SDA = D20

bool BH1750Check = false;
BH1750 lightMeter;


void setup() {

  Serial.begin(9600);

  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin();
  // On esp8266 you can select SCL and SDA pins using Wire.begin(D4, D3);

  BH1750Check = lightMeter.begin();
  if (BH1750Check) {
    Serial.println(F("BH1750 Test begin"));
  }
  else {
    Serial.println(F("BH1750 Initialization FAILED"));
    while (true) //flow trap
    {}
  }

}


void loop() {

  if (BH1750Check) {
    float lux = lightMeter.readLightLevel();
    Serial.print("Light: ");
    Serial.print(lux);
    Serial.println(" lx");
  }
  delay(1000);

}
