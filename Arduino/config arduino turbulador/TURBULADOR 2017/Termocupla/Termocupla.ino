
#include <Ports.h>
#include <RF12.h>

Port tplug(1);
Port tplug2(2);
Port tplug3(3);
Port tplug4(4);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  Serial.println("\n[termo_demo]");
  Serial.println("t1      t2     t3     t4");
  /*  tplug.mode(OUTPUT);
    tplug.digiWrite(1);
    tplug2.digiWrite(1);
    delay(1000);
    tplug.digiWrite(0);
    tplug2.digiWrite(0);
  */
}

void loop() {
  // put your main code here, to run repeatedly:
  int t = tplug.anaRead();
  int t2 = tplug2.anaRead();
  int t3 = tplug3.anaRead();
  int t4 = tplug4.anaRead();
  Serial.print(map(t, 0, 1023, 0, 600)); //10 mv/C
  Serial.print("     ");
   Serial.print(map(t2, 0, 1023, 0, 600)); //10 mv/C
  Serial.print("     ");
   Serial.print(map(t3, 0, 1023, 0, 600)); //10 mv/C
  Serial.print("     ");
  Serial.println(map(t4, 0, 1023, 0, 600)); //10 mv/C
  delay(500);
}
