#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <ESPmDNS.h>
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>

AsyncWebServer server(80);  // port for async server
WebSocketsServer websockets(81);  // port for web socket

Adafruit_PWMServoDriver board1 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver board2 = Adafruit_PWMServoDriver(0x41);

#define SERVOMIN 50  // minimum pulse length count (out of 4096)
#define SERVOMAX 330  // maximum pulse length count (out of 4096)

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Page Not Found");
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED: {
      IPAddress ip = websockets.remoteIP(num);
      Serial.printf("[%u] Connected from IP: %d.%d.%d.%d\n", num, ip[0], ip[1], ip[2], ip[3]);
      websockets.sendTXT(num, "Connected from server");
      break;
    }
    case WStype_TEXT: {
      Serial.printf("[%u] Received Text: %s\n", num, payload);
      String message = String((char *)(payload));

      DynamicJsonDocument doc(500);
      DeserializationError error = deserializeJson(doc, message);

      if (error) {
        Serial.print("JSON deserialization failed: ");
        Serial.println(error.c_str());
        return;
      }

      // Iterate over servo data received in JSON
      for (int i = 0; i <= 31; i++) {  // assuming 12 servos, adjust this based on your setup
        String servoKey = "servo" + String(i);
        if (doc.containsKey(servoKey)) {
          int angle = doc[servoKey];
          Serial.printf("Servo %d -> Angle: %d\n", i, angle);
          int pulse = angleToPulse(angle);
          if (i <= 16) {
            board1.setPWM(i - 1, 0, pulse);  // for board 1
          } else {
            board2.setPWM(i - 17, 0, pulse);  // for board 2
          }
        }
      }
      break;
    }
    default:
      break;
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Hexapod robot controller!");

  board1.begin();
  board2.begin();
  board1.setPWMFreq(60);  // Set frequency to 60 Hz
  board2.setPWMFreq(60);

  WiFi.softAP("ONESTEP", "");
  Serial.println("AP started, IP: " + WiFi.softAPIP().toString());

  MDNS.begin("ONESTEP");

  server.on("/", [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hello from Hexapod robot!");
  });

  server.onNotFound(notFound);

  server.begin();
  websockets.begin();
  websockets.onEvent(webSocketEvent);
}

void loop() {
  websockets.loop();
}

// Converts angle to pulse width
int angleToPulse(int ang) {
  return map(ang, 0, 180, SERVOMIN, SERVOMAX);
}
