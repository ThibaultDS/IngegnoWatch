#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>     // https://github.com/tzapu/WiFiManager

WiFiClient client;
ESP8266WebServer server(80); // Start server on port 80 (default for a web-browser, change to your requirements, e.g. 8080 if your Router uses port 80
                             // To access server from the outsid of a WiFi network e.g. ESP8266WebServer server(8266); and then add a rule on your Router that forwards a
                             // connection request to http://your_network_ip_address:8266 to port 8266 and view your ESP server from anywhere.
                             // Example http://g6ejd.uk.to:8266 will be directed to http://192.168.0.40:8266 or whatever IP address your router gives to this server

String Argument_Name, Clients_Response;

void setup() {
  Serial.begin(115200);
  //WiFiManager intialisation. Once completed there is no need to repeat the process on the current board
  WiFiManager wifiManager;
  // New OOB ESP8266 has no Wi-Fi credentials so will connect and not need the next command to be uncommented and compiled in, a used one with incorrect credentials will
  // so restart the ESP8266 and connect your PC to the wireless access point called 'ESP8266_AP' or whatever you call it below in ""
  // wifiManager.resetSettings(); // Command to be included if needed, then connect to http://192.168.4.1/ and follow instructions to make the WiFi connection
  // Set a timeout until configuration is turned off, useful to retry or go to sleep in n-seconds
  wifiManager.setTimeout(180);
  //fetches ssid and password and tries to connect, if connections succeeds it starts an access point with the name called "ESP8266_AP" and waits in a blocking loop for configuration
  if(!wifiManager.autoConnect("ESP8266_AP")) {
    Serial.println("failed to connect and timeout occurred");
    delay(3000);
    ESP.reset(); //reset and try again
    delay(5000);
  }
  // At this stage the WiFi manager will have successfully connected to a network, or if not will try again in 180-seconds
  //----------------------------------------------------------------------------------------------------------------------
  Serial.println("WiFi connected..");
  server.begin(); Serial.println("Webserver started..."); // Start the webserver
  Serial.print("Use this URL to connect: http://");// Print the IP address
  // NOTE: You must use the IP address assigned to YOUR Board when printed/displayed here on your serial port
  // If your IP address is http://10.0.1.10/ then that's the address you must use, not the one I used !
  Serial.print(WiFi.localIP());Serial.println("/");
  
  // Next define what the server should do when a client connects
  server.on("/", HandleClient); // The client connected with no arguments e.g. http:192.160.0.40/
  server.on("/result", ShowClientResponse);
}

void HandleClient() {
  String webpage;
  webpage =  "<html>";
   webpage += "<head><title>ESP8266 Input Example</title>";
    webpage += "<style>";
     webpage += "body { background-color: #E6E6FA; font-family: Arial, Helvetica, Sans-Serif; Color: blue;}";
    webpage += "</style>";
   webpage += "</head>";
   webpage += "<body>";
     String IPaddress = WiFi.localIP().toString();
     webpage += "<form action='http://"+IPaddress+"' method='POST'>";
     webpage += "Please enter your details:<input type='text' name='user_input'>&nbsp;<input type='submit' value='Enter'>";
    webpage += "</form>";
   webpage += "</body>";
  webpage += "</html>";
  server.send(200, "text/html", webpage); // Send a response to the client asking for input
  if (server.args() > 0 ) { // Arguments were received
    for ( uint8_t i = 0; i < server.args(); i++ ) {
      Serial.print(server.argName(i)); // Display the argument
      Argument_Name = server.argName(i);
      if (server.argName(i) == "user_input") {
        Serial.print(" Input received was: ");
        Serial.println(server.arg(i));
        Clients_Response = server.arg(i);
        // e.g. range_maximum = server.arg(i).toInt();   // use string.toInt()   if you wanted to convert the input to an integer number
        // e.g. range_maximum = server.arg(i).toFloat(); // use string.toFloat() if you wanted to convert the input to a floating point number
      }
    }
  }
}

void ShowClientResponse() {
  String webpage;
  webpage =  "<html>";
   webpage += "<head><title>ESP8266 Input Example</title>";
    webpage += "<style>";
     webpage += "body { background-color: #E6E6FA; font-family: Arial, Helvetica, Sans-Serif; Color: blue;}";
    webpage += "</style>";
   webpage += "</head>";
   webpage += "<body>";
    webpage += "<h1><br>ESP8266 Server - This was what the client sent</h1>";
    webpage += "<p>Response received was: " + Clients_Response + "</p>";
   webpage += "</body>";
  webpage += "</html>";
  server.send(200, "text/html", webpage); // Send a response to the client asking for input
}

void loop() {
  server.handleClient();
}
