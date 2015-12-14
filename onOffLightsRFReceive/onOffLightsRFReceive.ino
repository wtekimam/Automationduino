#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
/*
  This is the corresponding sketch to the 'basicSend' sketch.
  the nrf24l01 will listen for numbers 0-255, and light the red LED
  whenever a number in the sequence is missed.  Otherwise,
  it lights the green LED
*/
int msg[1];
RF24 radio(9, 10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int red = 3;
int green = 5;

int redOn = 0;
int greenOn = 0;

void setup(void) {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();

  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);

}

void loop(void) {
  if (radio.available())
  {
    bool done = false;

    while (!done) {
      done = radio.read(msg, 2);
      if (msg[0] == '1')
      {
        digitalWrite(green, HIGH);
      }
      else if (msg[0] == '2')
      {
        digitalWrite(green, LOW);
      }
      else if (msg[0] == '3')
      {
        digitalWrite(red, HIGH);
      }
      else if (msg[0] == '4')
      {
        digitalWrite(red, LOW);
      }
      else
      {
        digitalWrite(red, LOW);
        digitalWrite(green, LOW);
      }
      Serial.println(msg[0]);
    }
  }
  else
  {
    digitalWrite(red, LOW);
    digitalWrite(green, LOW);
  }
}
