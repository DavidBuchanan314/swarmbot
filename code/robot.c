#include <SPI.h> // the SPI protocol is used to communicate with the RF module
#include "RF24.h" // This is the RF library

// declare the pins used for the motor controller
#define L1 3
#define L2 4
#define R1 5
#define R2 6

RF24 radio(9,10); // 9 = Chip Enable pin, 10 = Chip Select pin

enum Mode {
  STOP,
  FORWARDS,
  REVERSE,
  LEFT,
  RIGHT  
};

void setup()
{
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);

  radio.begin();
  radio.openReadingPipe(1, 0xDEADBAB135); // We need an arbitraty 40-bit identifier :)
  radio.startListening();
}

void stop()
{
  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
}

void forwards()
{
  digitalWrite(L1, HIGH);
  digitalWrite(L2, LOW);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
}

void reverse()
{
  digitalWrite(L1, LOW);
  digitalWrite(L2, HIGH);
  digitalWrite(R1, LOW);
  digitalWrite(R2, HIGH);
  
}

void turn(Mode direction)
{
  switch(direction) {
    case LEFT:
      digitalWrite(L1, LOW);
      digitalWrite(L2, HIGH);
      digitalWrite(R1, HIGH);
      digitalWrite(R2, LOW);
      break;
    case RIGHT:
      digitalWrite(L1, HIGH);
      digitalWrite(L2, LOW);
      digitalWrite(R1, LOW);
      digitalWrite(R2, HIGH);
      break;
    default:
      // This should never happen. If I could log an error, I would.
      break;
  }
}

void loop()
{
  Mode mode;
  
  while (radio.available()) {
    radio.read(&mode, sizeof(mode));
    
    switch(mode) {
      case STOP:
        stop();
        break;
      case FORWARDS:
        forwards();
        break;
      case REVERSE:
        reverse();
        break;
      case LEFT:
      case RIGHT:
        turn(mode);
        break;
      default:
        // This should also never happen :(
        break;
    }
  }
}
