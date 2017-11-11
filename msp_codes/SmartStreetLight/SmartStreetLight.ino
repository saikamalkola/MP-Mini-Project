/*
  4 IR Sensors
  2 LDR Sensors
  4 Street Lights
*/
#define THRESHOLD 500

#define DAY_THRESH 300

uint8_t data = 0;

uint8_t bitmsk = 1;

uint8_t pins[6] = {P1_0, P1_3, P1_4, P1_5, P1_6, P1_7};
uint8_t led[4] = {P2_0, P2_1, P2_2, P2_3};

unsigned int ldr1 = 0, ldr2 = 0;

void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i < 6; i++)
  {
    pinMode(pins[i], INPUT);
  }
  for(int i = 0; i < 4; i++)
  {
    pinMode(led[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  data = 0;
  read_sensors();
  bitmsk = 1;
  for(int i = 0; i < 4; i++)
  {
    if((data & bitmsk) && ldr1 < DAY_THRESH && ldr2 < DAY_THRESH)
    {
      digitalWrite(led[i], HIGH);
      delay(300);
    }
    else
    {
      digitalWrite(led[i], LOW);
    }
    bitmsk = bitmsk << 1;
  }
}


void read_sensors()
{
  int temp = 0, temp_amb = 0;
  for(int i = 0; i < 4; i++)
  {
    data = data << 1;
    temp = analogRead(pins[i]);
    delay(1);
    if( temp  < THRESHOLD )
    {
      data |= 0;
    }
    else
    {
      data |= 1;
    }
  }
  Serial.print(data, BIN);
  ldr1 = analogRead(pins[4]);
  delay(1);
  ldr2 = analogRead(pins[5]);
  delay(1);
  Serial.print(" ");
  Serial.print(ldr1);
  Serial.print(" ");
  Serial.println(ldr2);
  
}

