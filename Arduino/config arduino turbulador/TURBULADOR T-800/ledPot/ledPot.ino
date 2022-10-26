#include <SPI.h>

byte address = 0x00;
int CS= 10;

void setup()
{
  
Serial.begin(115200);
pinMode (CS, OUTPUT);
SPI.begin();
}

void loop()
{
for (int i = 0; i <= 128; i++)
{
digitalPotWrite(i);
delay(100);
Serial.println(i);
}
delay(500);
for (int i = 128; i >= 0; i--)
{
digitalPotWrite(i);
delay(100);
Serial.println(i);
}
}

int digitalPotWrite(int value)
{
digitalWrite(CS, LOW);
SPI.transfer(address);
SPI.transfer(value);
digitalWrite(CS, HIGH);
}
