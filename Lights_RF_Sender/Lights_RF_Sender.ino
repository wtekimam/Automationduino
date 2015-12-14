#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
char msg[1];

//Opening the radio pins
RF24 radio(9, 10);

//opening the pipe for the connection between arduinos
const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup(void)
{
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);

  Serial.println("Turn on?");
}

void loop(void)
{
  if (Serial.available() > 0)
  {
    msg[0] = Serial.read();
    Serial.println(msg[0]);
  }

  radio.write(msg, 1);
 // delay(10000);
}
