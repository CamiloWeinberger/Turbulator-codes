int enablePin = 11;

int in1Pin = 10;
int in2Pin = 9;
int switchPin = 7;
int potPin = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  int velocidad = analogRead(potPin) / 4;
  boolean direccion = digitalRead(switchPin);
  Motor(velocidad, direccion);
}
void Motor(int velocidad, boolean direccion)
{
  analogWrite(enablePin, velocidad);
  digitalWrite(in1Pin, ! direccion);
  digitalWrite(in2Pin, direccion);

}

