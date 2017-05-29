#include <SPI.h> // the SPI protocol is used to communicate with the RF module
#include "RF24.h" // This is the RF library

RF24 radio(9,10); // 9 = Chip Enable pin, 10 = Chip Select pin

enum Mode { // We pray to the compiler gods that this enum is implemented identically at the other end
  STOP,
  FORWARDS,
  REVERSE,
  LEFT,
  RIGHT  
};

void setup()
{
  Serial.begin(115200);
  radio.begin();
  radio.openWritingPipe(0xDEADBAB135); // We need an arbitraty 40-bit identifier :)
}

void loop()
{
  Mode mode;

  for (int i = 0; !Serial.available(); i++) { // Wait for serial data to become available, with 200ms timeout
    if (i > 200) {
      mode = STOP;
      radio.write(&mode, sizeof(mode));
      return;
    }
    delay(1);
  }

  switch(Serial.read()){
    case 'w':
      mode = FORWARDS;
      break;
    case 's':
      mode = REVERSE;
      break;
    case 'a':
      mode = LEFT;
      break;
    case 'd':
      mode = RIGHT;
      break;
    case 'x':
      mode = STOP;
      break;
    default:
      return;
  }
  
  radio.write(&mode, sizeof(mode));
}
