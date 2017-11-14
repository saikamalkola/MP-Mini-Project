#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "kamal";       //my WiFi or Hotspot name
const char* password = "kamalkamal";//my WiFi Password

HTTPClient http;

String username = "saikamalkola";
String kwh[8];

String server = "http://192.168.43.222";
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
    for(int i = 0; i < 8; i++)
  {
    kwh[i] = msg.substring(limits[i], limits[i+1] - 1);
    Serial.println(kwh[i]);
  }
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
    String url = "/MiniProject/get_energy_data.php/?username=";
    url += username;
    url += "&data=";
    for (int i = 0; i < 7; i++)
    { url += kwh[i];
      url += "_";
    }
    url += kwh[7];
    
    String request = server + url;
    http.begin(request);
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

