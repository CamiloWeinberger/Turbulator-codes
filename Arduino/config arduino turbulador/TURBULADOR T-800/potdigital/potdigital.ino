//NO MODIFICAR POR NADA!!!!!

/*MCO4131 conectores (revisar SPI en la página!!!!!)
   1 10 (uno) y 53 (mega2560)
   2 13 (uno) y 52 (mega2560)
   3 11 (uno) y 51 (mega2560)
   4 GND
   5 5V
   6 OUTPUT
   7 GND
   8 5V
*/

#include <SPI.h>

byte address = 0x00;
int CS = 53;
int dat = 0;

void setup()
{
  pinMode (CS, OUTPUT);
  SPI.begin();
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available() > 0) {
    //Delay para favorecer la lectura de caracteres
    delay(20);
    //Se crea una variable que servirá como buffer
    String bufferString = "";
    /*
       Se le indica a Arduino que mientras haya datos
       disponibles para ser leídos en el puerto serie
       se mantenga concatenando los caracteres en la
       variable bufferString
    */
    while (Serial.available() > 0) {
      bufferString += (char)Serial.read();
    }
    //Se transforma el buffer a un número entero
    int dat = bufferString.toInt();
    digitalPotWrite(dat);
    Serial.println(dat);
    delay(100);
  }
}
int digitalPotWrite(int value)
{
  digitalWrite(CS, LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(CS, HIGH);
}
