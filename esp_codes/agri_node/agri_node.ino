#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "kamal";       //my WiFi or Hotspot name
const char* password = "kamalkamal";//my WiFi Password

HTTPClient http;

String username = "saikamalkola";
String temperature = "10";
String moisture = "70";
String humidity = "100";
String water_level = "500";
String ph = "500";

String server = "http://10.100.9.141";
int port = 80;
String response;

String msg = "";

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  //connecting to WiFi or Hotspot
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  if (Serial.available() > 0)
  {
    msg = Serial.readStringUntil('\n');
    parse_msg();
    req_server();
  }
}

void parse_msg()
{
  int l = msg.length(), k = 0;
  int limits[200];
  for (int i = 0; i < l; i++)
  {
    if (msg[i] == '#')
    {
      limits[k] = i + 1;
      k++;
    }
  }
  Serial.println(msg);
  temperature = msg.substring(limits[0], limits[1] - 1);
  moisture = msg.substring(limits[1], limits[2] - 1);
  humidity = msg.substring(limits[2], limits[3] - 1);
  ph = msg.substring(limits[3], limits[4] - 1);
  water_level = msg.substring(limits[4], limits[5] - 1);
}

void parse_response()
{
  Serial.println(response);
  if (response == "0")
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
}
void req_server()
{

  if (WiFi.status() == WL_CONNECTED)
  {
    String url = "/MiniProject/get_agri_data.php/?username=";
    url += username;
    url += "&data=";
    url += temperature;
    url += "_";
    url += moisture;
    url += "_";
    url += humidity;
    url += "_";
    url += water_level;
    url += "_";
    url += ph;

    
    String request = server + url;
    http.begin(request);
    //http.begin("http://10.50.37.170/MiniProject/esp_test.php"); //HTTP
    int response_code = http.GET();
    Serial.println(request);
    if (response_code == HTTP_CODE_OK ) {
        response = http.getString();
        parse_response();
    }
    else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(response_code).c_str());
    }
    http.end();
  }
  delay(1000);
}

