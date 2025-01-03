#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <ESPmDNS.h>
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>



// counters for move leg 1
int i1L1 = 0;
int i2L1 = 0;
int i3L1 = 0;
int i4L1 = 0;
int i5L1 = 0;
int i6L1 = 0;
// counters for move leg 1

bool gait1Status = false;
bool gait1ReverseStatus = false;



AsyncWebServer server(80);  //port for async server

WebSocketsServer websockets(81);  // port for web socket



void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Page Not found");
}




// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver board1 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver board2 = Adafruit_PWMServoDriver(0x41);
int maximumServo = 32;  //how many servos are connected

#define SERVOMIN 74   // 125  // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 513  // 575  // this is the 'maximum' pulse length count (out of 4096)

int servoNumber = 0;

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED:
      {
        IPAddress ip = websockets.remoteIP(num);
        Serial.printf("[%u] Connected from IP: %d.%d.%d.%d\n", num, ip[0], ip[1], ip[2], ip[3]);
        websockets.sendTXT(num, "Connected from server");
        break;
      }
    case WStype_TEXT:
      {
        Serial.printf("[%u] Received Text: %s\n", num, payload);
        String message = String((char *)(payload));

        if (message.equals("backward")) {
          Serial.println("backward");
          gait1Backward();
          delay(100);
          if (gait1ReverseStatus) {
            gait2Backward();
          }
          delay(500);
        }
        if (message.equals("sit")) {
          sit();
        }
        if (message.equals("stand")) {
          stand();
        }

        if (message.equals("forward")) {
          Serial.println("forward ");
          gait1();
          delay(100);
          if (gait1Status) {
            gait2();
          }
          delay(500);

          // DynamicJsonDocument doc(500);
          // DeserializationError error = deserializeJson(doc, message);

          // if (error) {
          //   Serial.print("JSON deserialization failed: ");
          //   Serial.println(error.c_str());
          //   return;
          // }

          // // Iterate over servo data received in JSON
          // for (int i = 0; i <= 31; i++) {           // loop through 18 servos (0 to 17)
          //   String servoKey = "servo" + String(i);  // create the key like "servo0", "servo1", etc.

          //   if (doc.containsKey(servoKey)) {
          //     int angle = doc[servoKey];  // get the angle from the JSON
          //     // Serial.printf("Servo %d -> Angle: %d\n", i, angle);  // debug print for each servo and its angle

          //     int pulse = angleToPulse(angle);  // convert angle to PWM pulse

          //     if (i <= 15) {
          //       board1.setPWM(i, 0, pulse);  // for servos 0 to 15 on board1
          //       delay(15);
          //     } else {
          //       Serial.print("board 2  : ");
          //       Serial.print(i - 16);
          //       Serial.print("angleg  : ");
          //       Serial.println(angle);

          //       board2.setPWM(i - 16, 0, pulse);  // for servos 16 and 17 on board2
          //       delay(15);
          //     }
          //   }
          // }


          break;
        }else{
          
        }
      }
    default:
      break;
  }
}



void setup() {

  Serial.begin(115200);
  Serial.println("32 channel Servo test!");

  // servo driver ;
  board1.begin();
  board2.begin();
  board1.setPWMFreq(50);  // Analog servos run at ~50 Hz updates
  board2.setPWMFreq(50);


  WiFi.softAP("ONESTEP", "");
  Serial.println("softap");
  Serial.println("");
  Serial.println(WiFi.softAPIP());


  // mdns
  if (MDNS.begin("ONESTEP")) {  //esp.local/
    Serial.println("MDNS responder started");
  }


  server.on("/", [](AsyncWebServerRequest *request) {
    String message = "hello world";
    request->send(200, "text/plain", message);
  });

  server.on("/page1", HTTP_GET, [](AsyncWebServerRequest *request) {
    String message = "Welcome to page1";
    board2.setPWM(0, 0, angleToPulse(90));
    request->send(200, "text/plain", message);
  });

  server.onNotFound(notFound);

  server.begin();
  websockets.begin();  //it will start web scoket
  websockets.onEvent(webSocketEvent);
}

void loop() {

  websockets.loop();
  if (Serial.available()) {

    String input = Serial.readStringUntil('\n');  // Read until newline character
    Serial.print("pulse : ");
    Serial.println(input);

    if (input.equals("sit")) {
      sit();  // Call the sit function
    } else if (input.equals("stand")) {
      // stand();  // Call the stand function
      moveLeg1();  // Moves Leg 1 with a speed of 15 ms delay per angle step
    } else if (input.equals("forward")) {
      // stand();  // Call the stand function
      // moveLeg1();  // Moves Leg 1 with a speed of 15 ms delay per angle step
      // moveLeg4();  // Moves Leg 1 with a speed of 15 ms delay per angle step
      // moveLeg5();  // Moves Leg 1 with a speed of 15 ms delay per angle step
      gait1();
      delay(100);
      if (gait1Status) {
        gait2();
      }
      delay(2500);

      // moveLeg2();
      // moveLeg3();
      // moveLeg6();
      // delay(2500);
    }

    // Convert the input string to an integer
    // int angle = input.toInt();  // Convert string to integer
    // Serial.println(angle);

    // board2.setPWM(0, 0, angleToPulse(angle));
    // board1.setPWM(0, 0, angleToPulse(angle));
  }
}


/*
 * angleToPulse(int ang)
 * gets angle in degree and returns the pulse width
 * also prints the value on seial monitor
 * written by Ahmad Nejrabi for Robojax, Robojax.com
 */
int angleToPulse(int ang) {
  int pulse = map(ang, 0, 180, SERVOMIN, SERVOMAX);  // map angle of 0 to 180 to Servo min and Servo max
  // Serial.print("Angle: ");
  // Serial.print(ang);
  // Serial.print(" pulse: ");
  // Serial.println(pulse);
  return pulse;
}




// Function to move hexapod to a sit position
void sit() {

  Serial.println("Siting a...");



  board1.setPWM(2, 0, angleToPulse(135));  // Leg 1 Coxa - move front
  board1.setPWM(13, 0, angleToPulse(45));  // Leg 2 Coxa - move back
  board1.setPWM(5, 0, angleToPulse(90));   // Leg 3 Coxa - move front
  board1.setPWM(10, 0, angleToPulse(90));  // Leg 4 Coxa - move front

  board2.setPWM(13, 0, angleToPulse(65));  //Leg 5  Coxa - move front
  board2.setPWM(2, 0, angleToPulse(155));  //Leg 6 Coxa - move back
  delay(50);


  board1.setPWM(1, 0, angleToPulse(180));  // Leg 1 Femur - move down
  board1.setPWM(14, 0, angleToPulse(0));   // Leg 2 Femur - move down
  board1.setPWM(4, 0, angleToPulse(180));  // Leg 3 Femur - move down
  board1.setPWM(11, 0, angleToPulse(0));   // Leg 4 Femur - down

  board2.setPWM(14, 0, angleToPulse(180));  //Leg 5  Femur - down
  board2.setPWM(1, 0, angleToPulse(5));     //Leg 6 Femur - move down
  delay(50);


  board1.setPWM(0, 0, angleToPulse(180));  // Leg 1 Tibia - neutral
  board1.setPWM(15, 0, angleToPulse(0));   // Leg 2 Tibia - neutral
  board1.setPWM(3, 0, angleToPulse(180));  // Leg 3 Tibia - neutral
  board1.setPWM(12, 0, angleToPulse(0));   // Leg 4 Tibia - neutral

  board2.setPWM(15, 0, angleToPulse(180));  //Leg 5  Tibia - neutral
  board2.setPWM(0, 0, angleToPulse(5));     //Leg 6 Tibia - neutral

  delay(500);  // Give time for the servos to move
}


// Function to move hexapod to a stand position
void stand() {

  Serial.println("Standing ...");
  board1.setPWM(2, 0, angleToPulse(135));  // Leg 1 Coxa - move front
  board1.setPWM(13, 0, angleToPulse(45));  // Leg 2 Coxa - move back
  board1.setPWM(5, 0, angleToPulse(90));   // Leg 3 Coxa - move front
  board1.setPWM(10, 0, angleToPulse(90));  // Leg 4 Coxa - move front

  board2.setPWM(13, 0, angleToPulse(65));  //Leg 5  Coxa - move front
  board2.setPWM(2, 0, angleToPulse(155));  //Leg 6 Coxa - move back
  delay(50);

  board1.setPWM(1, 0, angleToPulse(130));  // Leg 1 Femur - move down
  board1.setPWM(14, 0, angleToPulse(65));  // Leg 2 Femur - move down
  board1.setPWM(4, 0, angleToPulse(150));  // Leg 3 Femur - move down
  board1.setPWM(11, 0, angleToPulse(65));  // Leg 4 Femur - down

  board2.setPWM(14, 0, angleToPulse(150));  //Leg 5  Femur - down
  board2.setPWM(1, 0, angleToPulse(65));    //Leg 6 Femur - move down
  delay(50);

  board1.setPWM(0, 0, angleToPulse(180));  // Leg 1 Tibia - neutral
  board1.setPWM(15, 0, angleToPulse(0));   // Leg 2 Tibia - neutral

  board1.setPWM(3, 0, angleToPulse(180));  // Leg 3 Tibia - neutral
  board1.setPWM(12, 0, angleToPulse(0));   // Leg 4 Tibia - neutral

  board2.setPWM(15, 0, angleToPulse(180));  //Leg 5  Tibia - neutral
  board2.setPWM(0, 0, angleToPulse(5));     //Leg 6 Tibia - neutral


  delay(500);  // Give time for the servos to move
}


void moveLeg6() {
  Serial.println("Moving Leg 6 ...");

  // Swing phase - move leg through the air (initial to final position)
  // 1. Rise the leg (Swing Phase)

  board2.setPWM(0, 0, angleToPulse(20));  // Move tibia (servo 0)   160
  board2.setPWM(1, 0, angleToPulse(30));  // Move femur (servo 1) 160
  board2.setPWM(2, 0, angleToPulse(45));  // Move coxa (servo 2) 170

  delay(300);

  board2.setPWM(0, 0, angleToPulse(30));   // Move tibia (servo 0)   160
  board2.setPWM(1, 0, angleToPulse(45));   // Move femur (servo 1) 160
  board2.setPWM(2, 0, angleToPulse(165));  // Move coxa (servo 2) 170
  delay(300);
}



void moveLeg5() {
  Serial.println("Moving Leg 5...");

  // Swing phase - move leg through the air (initial to final position)
  // 1. Rise the leg (Swing Phase)

  board2.setPWM(15, 0, angleToPulse(170));  // Move tibia (servo 0)   160
  board2.setPWM(14, 0, angleToPulse(180));  // Move femur (servo 1) 160
  board2.setPWM(13, 0, angleToPulse(170));  // Move coxa (servo 2) 170

  delay(300);

  board1.setPWM(15, 0, angleToPulse(180));  // Move tibia (servo 0)   160
  board1.setPWM(14, 0, angleToPulse(150));  // Move femur (servo 1) 160
  board1.setPWM(13, 0, angleToPulse(65));   // Move coxa (servo 2) 170
  delay(300);
}




void moveLeg4() {
  Serial.println("Moving Leg 4...");

  // Swing phase - move leg through the air (initial to final position)
  // 1. Rise the leg (Swing Phase)

  board1.setPWM(12, 0, angleToPulse(30));  // Move tibia (servo 0)   160
  board1.setPWM(11, 0, angleToPulse(37));  // Move femur (servo 1) 160
  board1.setPWM(10, 0, angleToPulse(80));  // Move coxa (servo 2) 170

  delay(300);

  board1.setPWM(12, 0, angleToPulse(20));  // Move tibia (servo 0)   160
  board1.setPWM(11, 0, angleToPulse(52));  // Move femur (servo 1) 160
  board1.setPWM(10, 0, angleToPulse(90));  // Move coxa (servo 2) 170
  delay(300);
}




void moveLeg3() {
  Serial.println("Moving Leg 3...");

  // Swing phase - move leg through the air (initial to final position)
  // 1. Rise the leg (Swing Phase)

  board1.setPWM(3, 0, angleToPulse(150));  // Move tibia (servo 0)   160
  board1.setPWM(4, 0, angleToPulse(170));  // Move femur (servo 1) 160
  board1.setPWM(5, 0, angleToPulse(115));  // Move coxa (servo 2) 170

  delay(300);

  board1.setPWM(3, 0, angleToPulse(160));  // Move tibia (servo 0)   160
  board1.setPWM(4, 0, angleToPulse(140));  // Move femur (servo 1) 160
  board1.setPWM(5, 0, angleToPulse(90));   // Move coxa (servo 2) 170
  delay(300);
}



void moveLeg2() {
  Serial.println("Moving Leg 2...");

  // Swing phase - move leg through the air (initial to final position)
  // 1. Rise the leg (Swing Phase)

  board1.setPWM(15, 0, angleToPulse(20));  // Move tibia (servo 0)   160
  board1.setPWM(14, 0, angleToPulse(30));  // Move femur (servo 1) 160
  board1.setPWM(13, 0, angleToPulse(45));  // Move coxa (servo 2) 170

  delay(300);

  board1.setPWM(15, 0, angleToPulse(10));  // Move tibia (servo 0)   160
  board1.setPWM(14, 0, angleToPulse(45));  // Move femur (servo 1) 160
  board1.setPWM(13, 0, angleToPulse(60));  // Move coxa (servo 2) 170
  delay(300);
}



void moveLeg1() {
  Serial.println("Moving Leg 1...");

  // Swing phase - move leg through the air (initial to final position)
  // 1. Rise the leg (Swing Phase)

  board1.setPWM(0, 0, angleToPulse(170));  // Move tibia (servo 0)   160
  board1.setPWM(1, 0, angleToPulse(160));  // Move femur (servo 1) 160
  board1.setPWM(2, 0, angleToPulse(150));  // Move coxa (servo 2) 170

  delay(300);

  board1.setPWM(0, 0, angleToPulse(180));  // Move tibia (servo 0)   160
  board1.setPWM(1, 0, angleToPulse(130));  // Move femur (servo 1) 160
  board1.setPWM(2, 0, angleToPulse(135));  // Move coxa (servo 2) 170
  delay(300);
  // if (i1L1 <= 10) {
  //     Serial.print("Femur angle (rising): ");
  //     Serial.println(130 + i1L1 * 3);  // Log the angle for femur
  //     Serial.print("Coxa angle (rising): ");
  //     Serial.println(135 + i1L1 * 2);  // Log the angle for coxa



  //     i1L1++;
  // }

  // 2. Rotate the leg forward (Swing Phase - Tibia)
  // if (i2L1 <= 30) {
  //   Serial.print("Tibia angle (rotating forward): ");
  //   Serial.println(180 - i2L1);  // Log the angle for tibia

  //   board1.setPWM(0, 0, angleToPulse(180 - i2L1));  // Move tibia (servo 0)

  //   i2L1++;
  // }

  // 3. Lower the leg to touch the ground (Swing Phase)
  // if (i2L1 > 20 && i3L1 <= 10) {
  //   Serial.print("Coxa angle (lowering): ");
  //   Serial.println(40 + i3L1 * 2);  // Log the angle for coxa lowering

  //   Serial.print("Femur angle (lowering): ");
  //   Serial.println(60 + i3L1 * 3);  // Log the angle for femur lowering

  //   board1.setPWM(2, 0, angleToPulse(40 + i3L1 * 2));  // Lower the coxa (servo 2)
  //   board1.setPWM(1, 0, angleToPulse(60 + i3L1 * 3));  // Lower the femur (servo 1)

  //   i3L1++;
  // }

  // 4. Rotate back to the initial position (Stance Phase)
  // if (i2L1 >= 30) {
  //   Serial.print("Tibia angle (returning to stance): ");
  //   Serial.println(70 + i4L1);  // Log the angle for tibia returning to initial position

  //   board1.setPWM(0, 0, angleToPulse(70 + i4L1));  // Return tibia (servo 0) to starting position

  //   i4L1++;
  //   // Optional: Indicate that the leg is in stance phase
  //   // leg1Status = HIGH;  // Leg is now in stance phase
  // }

  // 5. Reset counters for next cycle
  if (i4L1 >= 30) {
    i1L1 = 0;
    i2L1 = 0;
    i3L1 = 0;
    i4L1 = 0;
  }

  delay(50);  // Control movement speed by adding delays
}


void gait2() {
  Serial.println("gait 2 ");
  // 2, 3, 6
  // Tibia
  board1.setPWM(15, 0, angleToPulse(20));  // Leg 2 Move tibia (servo 0)   160
  board1.setPWM(3, 0, angleToPulse(150));  // Leg 3 Move tibia (servo 0)   160
  board2.setPWM(0, 0, angleToPulse(20));   // Move tibia (servo 0)   160
  delay(50);

  // femur
  board1.setPWM(14, 0, angleToPulse(30));  // Leg 2 Move femur (servo 1) 160
  board1.setPWM(4, 0, angleToPulse(170));  // Leg 3 Move femur (servo 1) 160
  board2.setPWM(1, 0, angleToPulse(30));   // Move femur (servo 1) 160
  delay(50);

  // coxa
  board1.setPWM(13, 0, angleToPulse(45));  // Leg 2 Move coxa (servo 2) 170
  board1.setPWM(5, 0, angleToPulse(115));  // Leg 3 Move coxa (servo 2) 170
  board2.setPWM(2, 0, angleToPulse(150));  // Move coxa (servo 2) 170
  delay(100);


  // back to intial
  // Tibia
  board1.setPWM(15, 0, angleToPulse(10));  // Leg 2 Move tibia (servo 0)   160
  board1.setPWM(3, 0, angleToPulse(160));  // Leg 3 Move tibia (servo 0)   160
  board2.setPWM(0, 0, angleToPulse(30));   // Move tibia (servo 0)   160
  delay(50);

  // femur
  board1.setPWM(14, 0, angleToPulse(45));  // Leg 2 Move femur (servo 1) 160
  board1.setPWM(4, 0, angleToPulse(140));  // Leg 3 Move femur (servo 1) 160
  board2.setPWM(1, 0, angleToPulse(45));   // Move femur (servo 1) 160
  delay(50);

  // coxa
  board1.setPWM(13, 0, angleToPulse(60));  // Leg 2 Move coxa (servo 2) 170
  board1.setPWM(5, 0, angleToPulse(90));   // Leg 3 Move coxa (servo 2) 170
  board2.setPWM(2, 0, angleToPulse(165));  // Move coxa (servo 2) 170
  delay(50);

  gait1Status = false;
}


void gait1() {
  Serial.println("gait 1 ");
  // Tibia
  board1.setPWM(0, 0, angleToPulse(170));   // Leg1 Move tibia (servo 0)   160
  board1.setPWM(12, 0, angleToPulse(30));   // Leg4 Move tibia (servo 0)   160
  board2.setPWM(15, 0, angleToPulse(170));  // Leg 5 Move tibia (servo 0)   160
  delay(50);
  // femur
  board1.setPWM(1, 0, angleToPulse(160));   // Leg1 Move femur (servo 1) 160
  board1.setPWM(11, 0, angleToPulse(37));   // Leg4 Move femur (servo 1) 160
  board2.setPWM(14, 0, angleToPulse(180));  // Leg 5 Move femur (servo 1) 160
  delay(50);

  // //coxa
  board1.setPWM(2, 0, angleToPulse(150));   // Leg1 Move coxa (servo 2) 170
  board1.setPWM(10, 0, angleToPulse(80));   // Leg4 Move coxa (servo 2) 170
  board2.setPWM(13, 0, angleToPulse(120));  // Leg 5 Move coxa (servo 2) 170

  // back to intial
  delay(100);

  // Tibia
  board1.setPWM(0, 0, angleToPulse(180));   // Leg1  Move tibia (servo 0)   160
  board1.setPWM(12, 0, angleToPulse(20));   // Leg4 Move tibia (servo 0)   160
  board2.setPWM(15, 0, angleToPulse(180));  // Leg 5 Move tibia (servo 0)   160
  delay(50);


  // //femur
  board1.setPWM(1, 0, angleToPulse(130));   // Leg1  Move femur (servo 1) 160
  board1.setPWM(11, 0, angleToPulse(52));   // Leg4 Move femur (servo 1) 160
  board2.setPWM(14, 0, angleToPulse(150));  // Leg 5 Move femur (servo 1) 160
  delay(50);


  // //coxa
  board1.setPWM(2, 0, angleToPulse(135));  // Leg1  Move coxa (servo 2) 170
  board1.setPWM(10, 0, angleToPulse(90));  // Leg4 Move coxa (servo 2) 170
  board2.setPWM(13, 0, angleToPulse(65));  // Leg 5 Move coxa (servo 2) 170
  delay(50);

  gait1Status = true;
}











void gait1Backward() {
  // Reverse of gait1
  Serial.println("Reverse gait 1");

  // Tibia
  board1.setPWM(0, 0, angleToPulse(10));    // Leg1 Move tibia (servo 0) in reverse
  board1.setPWM(12, 0, angleToPulse(160));  // Leg4 Move tibia (servo 0) in reverse
  board2.setPWM(15, 0, angleToPulse(10));   // Leg5 Move tibia (servo 0) in reverse
  delay(50);

  // Femur
  board1.setPWM(1, 0, angleToPulse(50));    // Leg1 Move femur (servo 1) in reverse
  board1.setPWM(11, 0, angleToPulse(120));  // Leg4 Move femur (servo 1) in reverse
  board2.setPWM(14, 0, angleToPulse(30));   // Leg5 Move femur (servo 1) in reverse
  delay(50);

  // Coxa
  board1.setPWM(2, 0, angleToPulse(90));    // Leg1 Move coxa (servo 2) in reverse
  board1.setPWM(10, 0, angleToPulse(130));  // Leg4 Move coxa (servo 2) in reverse
  board2.setPWM(13, 0, angleToPulse(60));   // Leg5 Move coxa (servo 2) in reverse
  delay(100);

  // Return to initial position
  delay(50);

  gait1ReverseStatus = true;
}

void gait2Backward() {
  // Reverse of gait2
  Serial.println("Reverse gait 2");

  // Tibia
  board1.setPWM(15, 0, angleToPulse(160));  // Leg2 Move tibia (servo 0) in reverse
  board1.setPWM(3, 0, angleToPulse(20));    // Leg3 Move tibia (servo 0) in reverse
  board2.setPWM(0, 0, angleToPulse(160));   // Leg6 Move tibia (servo 0) in reverse
  delay(50);

  // Femur
  board1.setPWM(14, 0, angleToPulse(170));  // Leg2 Move femur (servo 1) in reverse
  board1.setPWM(4, 0, angleToPulse(30));    // Leg3 Move femur (servo 1) in reverse
  board2.setPWM(1, 0, angleToPulse(170));   // Leg6 Move femur (servo 1) in reverse
  delay(50);

  // Coxa
  board1.setPWM(13, 0, angleToPulse(115));  // Leg2 Move coxa (servo 2) in reverse
  board1.setPWM(5, 0, angleToPulse(45));    // Leg3 Move coxa (servo 2) in reverse
  board2.setPWM(2, 0, angleToPulse(150));   // Leg6 Move coxa (servo 2) in reverse
  delay(100);

  // Return to initial position
  delay(50);

  gait1ReverseStatus = false;
}
