//Thibault De Schaepmeester 6IT
#include <SPI.h>
#include <Wire.h> 
#include <Adafruit_GFX.h>
#include <U8g2lib.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>     // https://github.com/tzapu/WiFiManager

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

const char* ssid = "ingegno"; //Geef hier wifi in
const char* password = "ingegnofablab"; //Geef hier ww in

WiFiClient client;
ESP8266WebServer server(80);
String Argument_Name, Clients_Response;
String input; //string die geprint wordt (max 20 characters per lijn)
int groote_vierkant = 30;  // mag veranderd worden


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid,password);

  WiFiManager wifiManager;

  wifiManager.setTimeout(180);
  //fetches ssid and password and tries to connect, if connections succeeds it starts an access point with the name called "ESP8266_AP" and waits in a blocking loop for configuration
  if(!wifiManager.autoConnect("ESP8266_AP")) {
    Serial.println("failed to connect and timeout occurred");
    delay(3000);
    ESP.reset(); //reset and try again
    delay(5000);
  }
  // In dit stadium heeft de WiFi-manager met succes een verbinding met een netwerk tot stand gebracht, of anders probeert hij het over 180 seconden opnieuw
  //----------------------------------------------------------------------------------------------------------------------
  server.begin(); // Start the webserver  
  server.on("/", HandleClientROOT); // Hier zeg je wat de server moet doen als hij aan staat
  server.on("/CIRKEL", HTTP_POST, HandleClientCIRC); // Hier zeg je wat de server moet doen als hij aan staat
  server.on("/VIERKANT", HTTP_POST, HandleClientVIERK); // Hier zeg je wat de server moet doen als hij aan staat

  //Hier start je het scherm op en doe je alles weg dat nog in buffer zou kunnen zitten.
  //----------------------------------------------------------------------------------------------------------------------
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.clearDisplay();

  opstarten();  //Eerste dat geprint wordt bij opstarten
}

void HandleClientROOT() //de webpagina aanmaken
{
  if (server.args() > 0 ) { // Arguments were received
    for ( uint8_t i = 0; i < server.args(); i++ ) {
      Argument_Name = server.argName(i);
      if (server.argName(i) == "user_input") {
        input = server.arg(i);
        Clients_Response = server.arg(i);
        
      }
    }
  }

  writeText();
      Serial.println( "TEKST DOEN ");
  makeSite();
}
  
void HandleClientVIERK() //de webpagina aanmaken
{
  // toon vierkant
      Serial.println( "VIERKANT DOEN ");
  vierkant();
  makeSite();
}
void HandleClientCIRC() //de webpagina aanmaken
{
  // toon cirkel
      Serial.println( "CIRKEL DOEN ");
  makeSite();
}

void makeSite() //de webpagina aanmaken
{
  String IPaddress = WiFi.localIP().toString();
  String webpage;
    //hier wordt de webserver zelf gemaakt
    webpage =  "<html>";
    webpage += "<head><title>Ingegno Watch</title>";  //naam van tabblad
    webpage += "<style>";
    webpage += "body { background-color: #FFFFFF; font-family: Arial, Helvetica, Sans-Serif; Color: black; display: inline-block; margin: 0px auto; text-align: center;}";
    webpage += "</style>";
    webpage += "</head>";
    
    //hier ga je alles toevoegen aan webserver pagina
    webpage += "<body>";
    webpage += "<center>";
    webpage += "<form action='http://"+IPaddress+"' method='POST'>";  //gegevens in adresbalk
    webpage += "<h1>Ingegno Watch</h1><br>";  //titel
    webpage += "Geef iets in om te printen (20 tekens max) of kies een figuur<br>";  //text op nieuwe lijn, <br> kan worden gezien als een end line
     webpage += "<input type='text' name='user_input'><br><br><button class=\"button\" value=\"0\">Enter</button><br><br>";  //textbox en Enter toets aanmaken
    webpage += "</form>";
    webpage += "<form action=\"/CIRKEL\" method='POST'>";
    webpage += "<button class=\"button\" value=\"1\">Cirkel</button>&nbsp;";  //Cirkel butten aanmaken met witruimte (= &nbsp;) voor de volgende button
    webpage += "</form>";
    webpage += "<form action=\"/VIERKANT\" method='POST'>";
    webpage += "<button class=\"button\" value=\"2\">Vierkant</button>";  //Vierkant butten aanmaken 
    webpage += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}"; //text opmaken + centeren
    webpage += "</form>";
    webpage += "</body>";
    webpage += "</html>";

  server.send(200, "text/html", webpage); // Send a response to the client asking for input
  
}

void loop() {

  server.handleClient();
}

void opstarten() {           //Eerste dat geprint wordt bij opstarten

  String IP = WiFi.localIP().toString();
  int lengte = 70 - (3*IP.length());
  
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);  // gekozen font
  u8g2.drawStr(30,15,"Ingegno watch");  
  u8g2.drawStr(10,35,"Gelieve iets te geven"); 
  u8g2.drawStr(25,45,"om te printen via");
  u8g2.drawStr(lengte,60,IP.c_str());
  u8g2.sendBuffer();          // transfer internal memory to the display 
  
}

void writeText() {           //Schrijven van text naar oled
  
  int lengte = 64 - (3*input.length()); // lengte wordt gebruikt om x-waarde te bepalen om te centreren (helft scherm - 3 pixels per letter)
  if(input != ""){
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB08_tr);  // gekozen font
    u8g2.drawStr(lengte,35,input.c_str());  // string naar internal memory schrijven
    u8g2.sendBuffer();          // transfer internal memory to the display 
  }  
}

void vierkant() {           //Eerste dat geprint wordt bij opstarten

  int lengte = 64 - groote_vierkant; // lengte wordt gebruikt om x-waarde te bepalen om te centreren
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);  // gekozen font
  for(int y = 0; y < groote_vierkant; y++)
  {
    for(int x = 0; x < groote_vierkant; x++)
    {
        u8g2.drawStr(lengte+x,lengte/2+y,".");
    }
  } 
  u8g2.sendBuffer();          // transfer internal memory to the display 
  
}
