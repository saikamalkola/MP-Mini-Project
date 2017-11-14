/*
  Temperature Sensor
  Moisture Sensor
  Humidity Sensor
  pH sensor
  Water Level sensor
  Motor Control
*/

#include "SPI.h"


#define temp_thresh 40
#define moist_thresh 40
#define water_thresh 3

uint8_t temp_sensor = P1_0;
uint8_t moist_sensor_1 = P1_4;
uint8_t moist_sensor_2 = P1_6;

uint8_t latch_pin = P2_0;
uint8_t clock_pin = P1_5;
uint8_t data_pin = P1_7;

uint8_t button = P1_3;

uint8_t last_data = 0, data = 0; //to control appliances

uint8_t flag = 0;

uint16_t temp_reading = 0;
uint16_t moist_reading_1 = 0;
uint16_t moist_reading_2 = 0;

uint16_t water_reading = 0;

unsigned long present_ms = 0, last_ms = 0, moist_ms = 0, update_time = 1000, moist_time = 5000;

boolean button_status = LOW, button_state = LOW, lastbutton_state = LOW;

void setup() {

  // Enabling sensor pins as Inputs
  pinMode(temp_sensor , INPUT);
  pinMode(moist_sensor_1, INPUT);
  pinMode(moist_sensor_2, INPUT);

  pinMode(latch_pin, OUTPUT); // we use this for SS pin
  SPI.begin(); // wake up the SPI bus.
  SPI.setBitOrder(LSBFIRST);

  // Enabling push button that controls motor as Output (Internal Pull-up)
  P1OUT |= BIT3;
  P1REN |= BIT3;

  //Starting Serial Comunication
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  present_ms = millis();
  read_sensor_data();
  calc_temp();
  calc_moist();
  if (Serial.available() > 0)
  {
    data = Serial.read();
  }
  pump_check();

  if (flag == 1)
  {
    data = 0x01;
    if (present_ms - moist_ms > moist_time)
    {
      flag = 0;
    }
  }

  fan_check();
  if (last_data != data)
  {
    control_appliances(data);
  }

  if (present_ms - last_ms > update_time)
  {
    last_ms = present_ms;
    send_data();
  }
  last_data = data;
}


void latch()
{
  digitalWrite(latch_pin, HIGH);
  digitalWrite(latch_pin, LOW);
}

void control_appliances(uint8_t value)
{
  SPI.transfer(value);
  latch();
}

void fan_check()
{
  if (temp_reading > temp_thresh)
  {
    data |= 0x02;
  }
  else
  {
    data &= ~(0x02);
  }
}
void pump_check()
{
  if (button_status == HIGH)
  {
    data |= 0x01;
  }
  else if (moist_reading_1 <= moist_thresh || moist_reading_2 <= moist_thresh)
  {
    flag = 1;
    data |= 0x01;
  }
  else
  {
    data &= ~(0x01);
  }
}

void calc_temp()
{
  // temp_reading /= 1024;
  // temp_reading *= 3300;
  // temp_reading /= 10; // temperature in celcius
}
void calc_moist()
{
  moist_reading_1 = map(moist_reading_1, 0, 1023, 100, 0);
  moist_reading_2 = map(moist_reading_2, 0, 1023, 100, 0);
}
void read_sensor_data()
{
  button_state = digitalRead(button);
  if (button_state == LOW && lastbutton_state == HIGH)
  {
    button_status = !button_status;
  }
  lastbutton_state = button_state;
  temp_reading = analogRead(temp_sensor);
  moist_reading_1 = analogRead(moist_sensor_1);
  moist_reading_2 = analogRead(moist_sensor_2);
  read_water_lev();
}

void read_water_lev()
{
  int i = 0;
  for (i = 0; i < 6; i++)
  {
    if (digitalRead(i + 5) == HIGH)
      break;
  }
  water_reading = i;
}
void send_data()
{
  Serial.print("#");
  Serial.print(temp_reading);
  Serial.print("#");
  Serial.print(moist_reading_1);
  Serial.print("#");
  Serial.print(moist_reading_2);
  Serial.print("#");
  Serial.print(water_reading);
  Serial.print("#");
  Serial.print(data);
  Serial.println("#");
}

