/*
  Temperature Sensor
  Moisture Sensor
  Humidity Sensor
  pH sensor
  Water Level sensor
  Motor Control
*/
#define temp_thresh 40
#define humid_thresh 400
#define moist_T1 40
#define moist_T2 95
#define water_thresh 400
uint8_t temp_sensor = P1_0;
uint8_t moist_sensor = P1_4;
uint8_t humid_sensor = P1_5;
uint8_t ph_sensor = P1_6;
uint8_t water_level = P1_7;
uint8_t button = P1_3;
uint8_t fan = P2_0;
uint8_t spray = P2_1;
uint8_t pump = P2_2;
uint8_t pump_res = P2_3;

uint16_t temp_reading = 0;
uint16_t moist_reading = 0;
uint16_t humid_reading = 0;
uint16_t ph_reading = 0;
uint16_t water_reading = 0;

unsigned long present_ms = 0, last_ms = 0, update_time = 1000;

boolean button_status = LOW, button_state = LOW, lastbutton_state = LOW;

void setup() {

  // Enabling sensor pins as Inputs
  pinMode(temp_sensor , INPUT);
  pinMode(moist_sensor, INPUT);
  pinMode(humid_sensor, INPUT);
  pinMode(ph_sensor, INPUT);
  pinMode(water_level, INPUT);

  pinMode(fan, OUTPUT);
  pinMode(spray, OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode(pump_res, OUTPUT);

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
  if(Serial.available() > 0)
  {
    button_status = Serial.read();
  }
  if(button_status == 1)
  {
    digitalWrite(pump_res,HIGH);
  }
  else
  {
    digitalWrite(pump_res,LOW);
  }
  if(water_level <= water_thresh)
  {
    digitalWrite(pump_res,HIGH);
  }
  else
  {
    digitalWrite(pump_res,LOW);
  }
  if(moist_reading <= moist_T1)
  {
    digitalWrite(pump,HIGH);
  }
  if(moist_reading >= moist_T2)
  {
    digitalWrite(fan,LOW);
  }
  if(temp_reading > temp_thresh)
  {
    digitalWrite(fan,HIGH);
  }
  else
  {
    digitalWrite(fan,LOW);
  }
  if(humid_reading > humid_thresh)
  {
    digitalWrite(spray,HIGH);
  }
  else
  {
    digitalWrite(spray,LOW);
  }
  if (present_ms - last_ms > update_time)
  {
    last_ms = present_ms;
    send_data();
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
  moist_reading = map(moist_reading, 0, 1023, 0, 100);
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
  moist_reading = analogRead(moist_sensor);
  humid_reading = analogRead(humid_sensor);
  ph_reading = analogRead(ph_sensor);
  water_reading = analogRead(water_level);
}

void send_data()
{
  Serial.print("#");
  Serial.print(temp_reading);
  Serial.print("#");
  Serial.print(moist_reading);
  Serial.print("#");
  Serial.print(humid_reading);
  Serial.print("#");
  Serial.print(ph_reading);
  Serial.print("#");
  Serial.print(water_reading);
  Serial.println("#");
}

