/***************************************************
 This example reads Analog AC Current Sensor.
 
 Created 2016-3-10
 By berinie Chen <bernie.chen@dfrobot.com>
 
 GNU Lesser General Public License.
 See <http://www.gnu.org/licenses/> for details.
 All above must be included in any redistribution
 ****************************************************/

/***********Notice and Troubleshooting***************
 1.Connection and Diagram can be found here  http://wiki.dfrobot.com.cn/index.php?title=%EF%BC%88SKU:SEN0211%EF%BC%89%E6%A8%A1%E6%8B%9F%E9%87%8F%E4%BA%A4%E6%B5%81%E7%94%B5%E6%B5%81%E4%BC%A0%E6%84%9F%E5%99%A8#.E6.A0.B7.E4.BE.8B.E4.BB.A3.E7.A0.81
 2.This code is tested on Arduino Uno.
 ****************************************************/

float Vref = 0;
const int ACPin = A2;         //set arduino signal read pin
#define ACTectionRange 20;    //set Non-invasive AC Current Sensor tection range (20A,30A,50A,100A)
void setup() 
{
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  Vref = readVref();        //Read reference voltage
}

void loop() 
{
  float ACCurrentValue = readACCurrentValue(); //read AC Current Value
  Serial.println(ACCurrentValue);
  digitalWrite(13, HIGH);
  delay(50);
  digitalWrite(13, LOW);
  delay(50);
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
  
  return ACCurrtntValue/1000;
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
