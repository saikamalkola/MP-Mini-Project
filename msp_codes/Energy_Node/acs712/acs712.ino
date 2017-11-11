uint8_t sense_pin = P1_3;

long voltage = 0;
long offset = 511;
float division = 66*3.54/5;
float current = 0;
void setup() {
  // put your setup code here, to run once:
pinMode(sense_pin, INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly: 

  for(int i = 0; i < 1024; i++)
  {
  voltage += analogRead(sense_pin);
  }
  voltage = voltage / 1024;
  current = (voltage - offset);
  current = current * 3.3 / 1023;
  current = current * 1000 / division;
  Serial.print("Current: ");
  Serial.println(current);
}
