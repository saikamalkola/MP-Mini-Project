 #define N 1024

uint8_t sense_pin = P1_3;

float voltage = 0;
long offset = 511;
float division = 66*3.54/5;
float rms_current = 0;
float current = 0;

float temp = 0;

void setup() {
  // put your setup code here, to run once:
pinMode(sense_pin, INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly: 
  for(int i = 0; i < N; i++)
  {
  voltage = analogRead(sense_pin);
  calc_current();
  temp = voltage;
  current += temp;
  rms_current += temp * temp;
  }

  rms_current = sqrt(rms_current / N);
  current = current / N;

  Serial.print("RMS Current: ");
  Serial.print(rms_current);
  Serial.print("  Current: ");
  Serial.println(current);
  

}

void calc_current()
{
  voltage = (voltage - offset);
  voltage = voltage * 3.3 / 1023;
  voltage = voltage * 1000 / division;
}

