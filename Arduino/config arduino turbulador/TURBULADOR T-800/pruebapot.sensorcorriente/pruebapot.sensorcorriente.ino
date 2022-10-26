/*MCO4131 conectores (revisar SPI en la página!!!!!)
   1 10 (uno) y 53 (mega2560) CS
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
int prueba = 3;
float Vref = 0;
const int ACPin = A8;         //set arduino signal read pin
#define ACTectionRange 30;    //set Non-invasive AC Current Sensor tection range (20A,30A,50A,100A)

void setup()
{
  Serial.begin(115200);
  pinMode(prueba, OUTPUT);
  Vref = readVref();        //Read reference voltage
  pinMode (CS, OUTPUT);
  SPI.begin();
}

void loop()
{
  for (int j = 0; j <= 128; j++)
  {
    digitalPotWrite(j);
    float ACCurrentValue = readACCurrentValue(); //read AC Current Value
    Serial.print("    lecture:  ");
    Serial.println(ACCurrentValue);
    delay(1);

  }

  for (int j = 128; j >= 0; j--)
  {
    digitalPotWrite(j);
    float ACCurrentValue = readACCurrentValue(); //read AC Current Value
    Serial.print("    lecture:  ");
    Serial.println(ACCurrentValue);
    delay(1);
  }


}

int digitalPotWrite(int value)
{
  digitalWrite(CS, LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(CS, HIGH);
}

float readACCurrentValue()
{
  float ACCurrtntValue = 0;
  unsigned int peakVoltage = 0;
  unsigned int voltageVirtualValue = 0;  //Vrms
  for (int i = 0; i < 5; i++)
  {
    peakVoltage += analogRead(ACPin);   //read peak voltage
    delay(1);
  }
  peakVoltage = peakVoltage / 5;
  voltageVirtualValue = peakVoltage * 0.707;    //change the peak voltage to the Virtual Value of voltage

  /*The circuit is amplified by 2 times, so it is divided by 2.*/
  voltageVirtualValue = (voltageVirtualValue * Vref / 1024) / 2;

  ACCurrtntValue = voltageVirtualValue * ACTectionRange;

  return ACCurrtntValue / 1000;
}



/*Read reference voltage*/
long readVref()
{
  long result;
#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328__) || defined (__AVR_ATmega328P__)
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#elif defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__AVR_AT90USB1286__)
  ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  ADCSRB &= ~_BV(MUX5);   // Without this the function always returns -1 on the ATmega2560 http://openenergymonitor.org/emon/node/2253#comment-11432
#elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
  ADMUX = _BV(MUX5) | _BV(MUX0);
#elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
  ADMUX = _BV(MUX3) | _BV(MUX2);
#endif
#if defined(__AVR__)
  delay(2);                                        // Wait for Vref to settle
  ADCSRA |= _BV(ADSC);                             // Convert
  while (bit_is_set(ADCSRA, ADSC));
  result = ADCL;
  result |= ADCH << 8;
  result = 1126400L / result;  //1100mV*1024 ADC steps http://openenergymonitor.org/emon/node/1186
  return result;
#elif defined(__arm__)
  return (3300);                                  //Arduino Due
#else
  return (3300);                                  //Guess that other un-supported architectures will be running a 3.3V!
#endif
}
