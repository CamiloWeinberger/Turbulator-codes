# Turbulator-codes

## Arduino folder for MARK1.9

Specifications
```
Arduino Mega2630
Fans: San Ace 120W: 9WV1248P1J001
```

It must be considered that the Arduino frequency was adjusted for 25kHz, by the code:
``` c++
TCCR3A = 0X00; //pin2,3,5 (3,5 turb)
TCCR3B = 0X12;
ICR3 = 40;
```
This means that the PWM work for values of [0-40].
#
## Arduino folder for T-800
Same specifications for Mark1.9, but includes libraries of

``` c++
//sensor temp y humedad
#include <dht11.h>
dht11 DHT;
#define DHT11_PIN 4

//termocuplas
#include <Ports.h>
#include <RF12.h>

//potenciometro y Current sensor
#include <SPI.h>
```

Also, is connected and controlled by serial port as 57600 bauds/sec.

The airflow depens of the Turbulator size, so this value is not include in the code.
#
This code includes an automatical switch for the fans and the potentiomenter. And includes a delay to turn-off the systen and keep safe the turbulator.
``` c++
int relayvent = 40;
int relaypot = 41;
if (map(t1 - t3, 0, 1023, 0, 6000) >= 100) {
    digitalWrite(relaypot, HIGH);
    digitalWrite(variac, LOW);
    Serial.println("APAGANDO SISTEMA,Esperando que se enfríen las resistencias.");
    delay(1000);
}
else {
    digitalWrite(relayvent, HIGH);
    digitalWrite(verde, LOW);
    dif = 0;
    dat = 0;
    pot = 0;
}
```
Also, it is protected to switch on the fun before the power supply.

``` c++
    if (dif == 0) {
      digitalWrite(relaypot, HIGH);
      digitalWrite(variac, LOW);
      if (pot - switchvent >= 1) {
        Serial.println("NO MEDIDA, PRIMERO ENCENDER VENTILADORES");
        dat = 0;
        pot = 0;
      }
      digitalWrite(relayvent, HIGH);
      delay(20);
    }
```

## Matlab controller

Only fors for T-800 turbulador by serial-port. 
```
Do not use the Arduino library in matlab!!!
```
This code doesn't include the arduino library on Matlab because only read and send comunication by the serial port. The arduino has their own configuration.

