
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define HTTP_REST_PORT 80

ESP8266WebServer http_rest_server(HTTP_REST_PORT);

// Network SSID
const char* ssid = "HGnett";
const char* password = "kimsogge";

void config_rest_server_routing() {
  http_rest_server.on("/", HTTP_GET, []() {
      http_rest_server.send(200, "text/html",
          "Welcome to the ESP8266 REST Web Server");
  });
  http_rest_server.on("/pong", HTTP_GET, []() {
      pongEnabled = true;
      http_rest_server.send(200, "text/html",
          "Pong enabled");
  });
  http_rest_server.on("/snake", HTTP_GET, []() {
      snakeEnabled = true;
      http_rest_server.send(200, "text/html",
          "Snake enabled");
  });
  http_rest_server.on("/left", HTTP_GET, []() {
      if (pongEnabled) {
        pressLeftPong();
      } else if (snakeEnabled) {
        pressLeftSnake();
      }
      http_rest_server.send(200, "text/html",
          "Pressed left");
  });
  http_rest_server.on("/right", HTTP_GET, []() {
      if (pongEnabled) {
        pressRightPong();
      } else if (snakeEnabled) {
        pressRightSnake();
      }
      http_rest_server.send(200, "text/html",
          "Pressed right");
  });
  //http_rest_server.on("/leds", HTTP_GET, get_leds);
  //http_rest_server.on("/leds", HTTP_POST, post_put_leds);
  //http_rest_server.on("/leds", HTTP_PUT, post_put_leds);
}
 
void setupWifi() {
  // Connect WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.hostname("ledbookshelf");
  WiFi.begin(ssid, password);
  int waitCount = 0;
  while (WiFi.status() != WL_CONNECTED) {
    waitCount++;
    delay(500);
    drawSquareNr(waitCount%25, 255, 0, 0);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Print the IP address
  Serial.print("IP address: ");
  Serial.print(WiFi.localIP());
  config_rest_server_routing();
  http_rest_server.begin();
  Serial.println("HTTP REST Server Started");
}

void handleServer() {
  http_rest_server.handleClient();
}
