#include <SoftwareSerial.h>
SoftwareSerial serial(2, 3); //RX | TX

void setup() {
  pinMode(9, OUTPUT);
  serial.begin(9600);
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  if (serial.available())
  {
    char caracter = serial.read();
    Serial.println(caracter);
    switch (caracter) {
      case ' ':
        noTone(9);
        break;
      case 'a':
        tone(9, 261.63);
        break;
      case 's':
        tone(9, 293.66);
        break;
      case 'd':
        tone(9, 329.63);
        break;
      case 'f':
        tone(9, 349.23);
        break;
      case 'g':
        tone(9, 392);
        break;
      case 'h':
        tone(9, 440);
        break;
      case 'j':
        tone(9, 493.88);
        break;
      case 'k':
        tone(9, 523.25);
        break;
      case 'l':
        tone(9, 587.33);
        break;
      case 'ñ':
        tone(9, 493.88);
        break;
      case 'w':
        tone(9, 277.10);
        break;
      case 'e':
        tone(9, 311.13);
        break;
      case 't':
        tone(9, 369.99);
        break;
      case 'y':
        tone(9, 415.3);
        break;
      case 'u':
        tone(9, 466.16);
        break;
      case 'o':
        tone(9, 493.88);
        break;

    }
  }
  // put your main code here, to run repeatedly:

}
