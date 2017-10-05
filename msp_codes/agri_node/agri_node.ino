/*
  Temperature Sensor
  Moisture Sensor
  Humidity Sensor
  pH sensor
  Water Level sensor
  Motor Control
*/
uint8_t temp_sensor = P1_0;
uint8_t moist_sensor = P1_4;
uint8_t humid_sensor = P1_5;
uint8_t ph_sensor = P1_6;s
uint8_t water_level = P1_7;

uint16_t temp_reading = 0;
uint16_t moist_reading = 0;
uint16_t humid_reading = 0;
uint16_t ph_reading = 0;
uint16_t water_reading = 0;

boolean button_state = LOW, lastbutton_state = LOW;

void setup() {

  // Enabling sensor pins as Inputs
  pinMode(temp_sensor , INPUT);
  pinMode(moist_sensor, INPUT);
  pinMode(humid_sensor, INPUT);
  pinMode(ph_sensor, INPUT);
  pinMode(water_level, INPUT);

  // Enabling push button that controls motor as Output (Internal Pull-up)
  P1OUT |= BIT3;
  P1REN |= BIT3;

  //Starting Serial Comunication
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  read_sensor_data();
  delay(1);
  calc_temp();
  calc_moist();
}
void calc_temp()
{
  temp_reading /= 1024;
  temp_reading *= 3300;
  temp_reading /= 10; // temperature in celcius
}
void calc_moist()
{
  moist_reading = map(moist_reading,0,1023,0,100);
}
void read_sensor_data()
{
  temp_reading = analogRead(temp_sensor);
  moist_reading = analogRead(moist_sensor);
  humid_reading = analogRead(humid_sensor);
  ph_reading = analogRead(ph_sensor);
  water_reading = analogRead(water_level);
  Serial.print("temp: ");
  Serial.print(temp_reading);
  Serial.print(" moist: ");
  Serial.print(moist_reading);
  Serial.print(" humid: ");
  Serial.print(humid_reading);
  Serial.print(" ph: ");
  Serial.print(ph_reading);
  Serial.print(" water lev: ");
  Serial.println(water_reading);
}

