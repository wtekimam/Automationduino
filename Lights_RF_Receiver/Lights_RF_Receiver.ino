#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

int msg[1];
RF24 radio(9, 10);

const uint64_t pipe = 0xE8E8F0F0E1LL;


int red = 3;
int green = 5;

void setup(void)
{
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

    // I don't know what the while is for
    while (!done)
    {
      done = radio.read(msg, 2);
      // 1 is for turning light 1 on and 2 is for off
      // 3 is for turning light 3 on and 4 is for off
      // any other number is for turning everything off
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
