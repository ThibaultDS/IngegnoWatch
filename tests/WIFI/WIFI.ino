#include <ESP8266WiFi.h>

const char* ssid = "ingegno";
const char* password = "ingegnofablab";

WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Verbonden met: ");
  Serial.println(ssid);

  WiFi.begin(ssid,password);

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Wifi verbonden");

  server.begin();
  Serial.println("Server geïniteerd");

  Serial.println("Binnenkomen via een web navigator met IP: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  WiFiClient client = server.available();
  if(client)
  {
    Serial.println("Nieuwe client");
  }

  while(!client.available()&&client.connected())
  {
    delay(1);
  }

//  String linea1 = client.readStringUntil('r');
//  Serial.println(linea1);
//
//  if (linea1.indexOf("LED=ON")>0)
//  {
//    digitalWrite(2,HIGH);
//  }
//
//  if (linea1.indexOf("LED=OFF")>0)
//  {
//    digitalWrite(2,LOW);
//  }

    client.flush();

//    Serial.println("Gevraagd adres...");
//    Serial.println("HTTP/1.1 200 OK");
//    Serial.println("Content-Type: text/html");
//    Serial.println("Connection: close");

}
