#include <SPI.h>
#include <Servo.h>
#include "RF24.h"
Servo ESC;     // create servo object to control the ESC
Servo ESC1;
RF24 radio(7, 8); // (CE, CSN)
const byte address[6] = "1RF24"; // address / identifier
  int mr=90;
  int ml=90;
  int forward;
  int side;
struct Position{
  int joystickX;
  int joystickY;
};

void setup() {
  //Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1,address); // set the address for pipe 0
  radio.startListening(); // set as receiver
  

  ESC.attach(3,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  ESC1.attach(2,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  ESC.write(180); //forward
    ESC1.write(180); //forward
delay(2000);
  ESC.write(0);
    ESC1.write(0);
delay(2000);
  ESC.write(90);
    ESC1.write(90);
delay(2000);
}
void loop() {
      struct Position Position1;
  if(radio.available()){
    radio.read(&Position1, sizeof(Position1));
      //Serial.println(Position1.joystickX);
  }
  //forward = Position1.joystickX;
  side = map(Position1.joystickY, 0, 1024, -10, 10);
  forward = map(Position1.joystickX, 0, 1024, 75, 105);
  //mr = map(forward, 0, 1024, 75, 105);
  //ml = map(forward, 0, 1024, 75, 105);
  mr = forward - side;
  ml = forward + side;
  ESC.write(mr);
  ESC1.write(ml);
}
