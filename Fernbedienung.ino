#include <SPI.h>
#include <RF24.h>

const byte PinJoystickX = 0;
const byte PinJoystickY = 1;

struct Position{
int joystickX;
int joystickY;
};


RF24 radio(9, 10); // (CE, CSN)
const byte address[6] = "1RF24"; // address / identifier

void setup() {

radio.begin();
  radio.openWritingPipe(address); // set the address
  radio.stopListening(); // set as transmitter
  radio.setPALevel(RF24_PA_MAX);
}

void loop() {
  struct Position Position1;
  Position1.joystickX = analogRead(PinJoystickX);
  Position1.joystickY = analogRead(PinJoystickY);

  radio.write(&Position1, sizeof(Position1));
  delay(50);

}
