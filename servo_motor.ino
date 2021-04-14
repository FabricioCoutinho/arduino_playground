#include <Servo.h>
#include <Wire.h>

// orange = data
// red = +
// brown = GND

// Servor Motor
Servo myservo; // create the servo object
int servoPin = 2; / pwm 2
int degree = 0; // initial degree
int degree_direction = 1; // 1 clockwise; -1 counterclockwise

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);

  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin();
  // On esp8266 you can select SCL and SDA pins using Wire.begin(D4, D3);
 
  myservo.attach(servoPin);
  myservo.write(degree); 
}

void loop() {
  delay(1000);
  degree += 15 * degree_direction;

  Serial.print("degree: ");
  Serial.println(degree);
  
  myservo.write(degree);

  // when the degree reach 180 turn to counterclockwise
  if (degree >= 180) {
    degree_direction = -1;
  }
  
  // when the degree reach 0 turn to clockwise
  if (degree <= 0) {
    degree_direction = 1;
  }
}
