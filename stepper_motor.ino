#include <Stepper.h>

// 50 steps = 180 degree
const int stepsPerRevolution = 40;

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void setup() {
  // set the speed at 40 rpm:
  myStepper.setSpeed(40);
  
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() { 
   clockwise_counterclockwide(); 
}

void clockwise_counterclockwide() {
  // step one revolution  in one direction:  
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  delay(500);

  // step one revolution in the other direction:
  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);
  delay(500);
}
