#include <Wire.h>
#include <BH1750.h>

#include <Adafruit_GFX.h>     //INCLUSÃO DE BIBLIOTECA
#include <Adafruit_SSD1306.h> //INCLUSÃO DE BIBLIOTECA

// Sensor Luminosidade
bool BH1750Check = false;
BH1750 lightMeter;

// display
#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 64    // OLED display height, in pixels
#define OLED_RESET 4        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int delayTime = 2 * 1000;

void setup(){
  Serial.begin(9600);

  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin();
  // On esp8266 you can select SCL and SDA pins using Wire.begin(D4, D3);

  setupDisplay();

  BH1750Check = lightMeter.begin();
  //  lightMeter.SetAddress(0x5C);
  if (BH1750Check){
    Serial.println(F("BH1750 Test begin"));
  }
  else{
    Serial.println(F("BH1750 Initialization FAILED"));
    //flow trap
    while (true) {}
  }
}

void setupDisplay(){
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)){
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ; // Don't proceed, loop forever
  }
    //  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //INICIALIZA O DISPLAY COM ENDEREÇO I2C 0x3C

  display.display();
  delay(2000); // Pause for 2 seconds

  display.setTextColor(WHITE); // define text color
  display.setTextSize(1);      // define font size
  display.clearDisplay();      // clear display data
}

void writeDisplay(float lux){
  Serial.println("writeDisplay");
  display.clearDisplay();

  display.setTextColor(WHITE);
  display.setTextSize(1);

  display.setCursor(5, 20); // cursor position y,x
  display.print("LUX -> "); // print text

  display.setCursor(45, 20);

  display.print(lux);
  display.display(); // write the text
}

void loop(){
  float lux = getSensorValue();

  writeDisplay(lux);

  delay(delayTime);
}

float getSensorValue(){
  return lightMeter.readLightLevel();
}

// sensor log
void sensorLog(float lux){
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" (lx)");
}
