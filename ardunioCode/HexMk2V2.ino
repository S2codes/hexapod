
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <ESPmDNS.h>
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>



// // Leg 1
#define LEG1_COXA_PIN_b2 13
#define LEG1_FEMUR_PIN_b2 14
#define LEG1_TIBIA_PIN_b2 15

// // Leg 4
#define LEG4_TIBIA_PIN_b1 12
#define LEG4_FEMUR_PIN_b1 11
#define LEG4_COXA_PIN_b1 10

// // Leg 5
#define LEG5_TIBIA_PIN_b2 9
#define LEG5_FEMUR_PIN_b2 8
#define LEG5_COXA_PIN_b2 7

// // Leg 2
#define LEG2_TIBIA_PIN_b1 1
#define LEG2_FEMUR_PIN_b1 14
#define LEG2_COXA_PIN_b1 13

// // Leg 3
#define LEG3_TIBIA_PIN_b2 12
#define LEG3_FEMUR_PIN_b2 11
#define LEG3_COXA_PIN_b2 10

// // Leg 6
#define LEG6_TIBIA_PIN_b1 9
#define LEG6_FEMUR_PIN_b1 8
#define LEG6_COXA_PIN_b1 7

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);


#define SERVOMIN 125
#define SERVOMAX 519


WebSocketsServer websockets(81);  // port for web socket


bool gait1Status = false;
bool gait2Status = false;

bool gait1ReverseStatus = false;
bool gait2ReverseStatus = false;

bool gait1LayStatus = false;
bool gait2LayStatus = false;

void webSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
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
        String message = String((char*)(payload));


        if (message.equals("sit")) {
          sit();
          delay(500);
        }
        if (message.equals("stand")) {
          stand();
          delay(500);
        }
        if (message.equals("forward")) {
          gait1();
          delay(200);
          if (gait1Status) {
            gait2();
          }
          delay(500);
        }
        if (message.equals("backward")) {
          gait1Reverse();
          delay(200);
          if (gait1ReverseStatus) {
            gait2Reverse();
          }
          delay(500);
        }

        if (message.equals("forwardlay")) {
          gait1Lay();
          delay(200);
          if (gait1LayStatus) {
            gait2Lay();
          }
          delay(500);
        }

        if (message.equals("moveleg1")) {
          moveLeg1();
          delay(500);
        }

        if (message.equals("moveleg2")) {
          moveLeg2();
          delay(500);
        }
        if (message.equals("moveleg3")) {
          moveLeg3();
          delay(500);
        }
        if (message.equals("moveleg4")) {
          moveLeg4();
          delay(500);
        }
        if (message.equals("moveleg5")) {
          moveLeg5();
          delay(500);
        }
        if (message.equals("moveleg6")) {
          moveLeg6();
          delay(500);
        }
        if (message.equals("moveFrontTwo")) {
          moveFrontTwo();
          delay(500);
        }
        if (message.equals("moveMiddleTwo")) {
          moveMiddleTwo();
          delay(500);
        }
        if (message.equals("moveLastTwo")) {
          moveLastTwo();
          delay(500);
        }
        if (message.equals("frontLegHook")) {
          frontLegHook();
          delay(500);
        }
        if (message.equals("expandMiddle")) {
          expandMiddle();
          delay(500);
        }
        if (message.equals("FrontLegHookandExpandMiddleLast")) {
          FrontLegHookandExpandMiddleLast();
          delay(500);
        }
        if (message.equals("moveMidleAndLastLegPairForward")) {
          moveMidleAndLastLegPairForward();
          delay(500);
        }
        if (message.equals("liftFrontTwo")) {
          liftFrontTwo();
          delay(500);
        }
        if (message.equals("middleLegsHook")) {
          middleLegsHook();
          delay(500);
        }
        if (message.equals("moveLastLegPairForward")) {
          moveLastLegPairForward();
          delay(500);
        }
        if (message.equals("lastLegsHook")) {
          lastLegsHook();
          delay(500);
        }
        if (message.equals("moveFrontForward")) {
          moveFrontForward();
          delay(500);
        }
        if (message.equals("moveFrontLay")) {
          moveFrontLay();
          delay(500);
        }
        if (message.equals("moveMiddleLay")) {
          moveMiddleLay();
          delay(500);
        }
        if (message.equals("rotateLeft")) {
          rotateLeft();
          delay(500);
        }
        // stand 
        if (message.equals("standLastTwo")) {
          standLastTwo();
          delay(500);
        }
        if (message.equals("standMiddleTwo")) {
          standMiddleTwo();
          delay(500);
        }
        if (message.equals("standFrontTwo")) {
          standFrontTwo();
          delay(500);
        }
        if (message.equals("moveMiddleAndLastLay")) {
          moveMiddleAndLastLay();
          delay(500);
        }
        if (message.equals("moveLastLay")) {
          moveLastLay();
          delay(500);
        }
        if (message.equals("moveFrontLegPairForward")) {
          moveFrontLegPairForward();
          delay(500);
        }
        if (message.equals("moveMiddleLegPairForward")) {
          moveMiddleLegPairForward();
          delay(500);
        }

        DynamicJsonDocument doc(500);
        DeserializationError error = deserializeJson(doc, message);

        if (error) {
          Serial.print("JSON deserialization failed: ");
          Serial.println(error.c_str());
          return;
        }

        // Iterate over servo data received in JSON
        for (int i = 0; i <= 31; i++) {           // loop through 18 servos (0 to 17)
          String servoKey = "servo" + String(i);  // create the key like "servo0", "servo1", etc.

          if (doc.containsKey(servoKey)) {
            int angle = doc[servoKey];  // get the angle from the JSON
            if (i <= 15) {
              servoWrite(1, i, angle);
              delay(200);
            } else {
              servoWrite(2, i - 16, angle);
              delay(200);
            }
          }
        }
      }
    default:
      break;
  }
}


void setup() {

  Serial.begin(115200);
  Serial.println("Hexapod MK2!");

  pwm.begin();
  pwm.setPWMFreq(50);

  pwm2.begin();
  pwm2.setPWMFreq(50);

  WiFi.softAP("ONESTEP", "");
  Serial.println("softap");
  Serial.println("");
  Serial.println(WiFi.softAPIP());

  websockets.begin();  //it will start web scoket
  websockets.onEvent(webSocketEvent);
}

void loop() {

  websockets.loop();

  if (Serial.available()) {

    String input = Serial.readStringUntil('\n');  // Read until newline character
    Serial.print("pulse : ");
    Serial.println(input);
  }
}


// check this  funcation
void servoWrite(int boardNumber, int pin, int angle) {
  if (boardNumber == 1) {
    int pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
    pwm.setPWM(pin, 0, pulse);
  } else {
    int pulse = map(angle, 180, 0, SERVOMIN, SERVOMAX);
    pwm2.setPWM(pin, 0, pulse);
  }
}



void sit() {

  stand();
  delay(500);

  int femurAngle = 90; // Initial angle
  // Gradually move femur servos to 50 degrees
  for (int angle = femurAngle; angle >= 50; angle -= 5) {
    servoWrite(1, LEG2_FEMUR_PIN_b1, angle);
    servoWrite(1, LEG4_FEMUR_PIN_b1, angle);
    servoWrite(1, LEG6_FEMUR_PIN_b1, angle);
    servoWrite(2, LEG1_FEMUR_PIN_b2, angle);
    servoWrite(2, LEG3_FEMUR_PIN_b2, angle);
    servoWrite(2, LEG5_FEMUR_PIN_b2, angle);
    delay(50);
  }

  delay(150);


  servoWrite(1, LEG2_FEMUR_PIN_b1, 50);
  servoWrite(1, LEG4_FEMUR_PIN_b1, 50);
  servoWrite(1, LEG6_FEMUR_PIN_b1, 50);
  servoWrite(2, LEG1_FEMUR_PIN_b2, 50);
  servoWrite(2, LEG3_FEMUR_PIN_b2, 50);
  servoWrite(2, LEG5_FEMUR_PIN_b2, 50);
  delay(150);
  servoWrite(1, LEG2_TIBIA_PIN_b1, 10);
  servoWrite(1, LEG4_TIBIA_PIN_b1, 10);
  servoWrite(1, LEG6_TIBIA_PIN_b1, 10);
  servoWrite(2, LEG1_TIBIA_PIN_b2, 10);
  servoWrite(2, LEG3_TIBIA_PIN_b2, 10);
  servoWrite(2, LEG5_TIBIA_PIN_b2, 10);

  delay(150);
  servoWrite(1, LEG2_COXA_PIN_b1, 90);
  servoWrite(1, LEG4_COXA_PIN_b1, 90);
  servoWrite(1, LEG6_COXA_PIN_b1, 90);
  servoWrite(2, LEG1_COXA_PIN_b2, 90);
  servoWrite(2, LEG3_COXA_PIN_b2, 90);
  servoWrite(2, LEG5_COXA_PIN_b2, 90);
  delay(200);


}

void stand() {
  servoWrite(1, LEG2_COXA_PIN_b1, 90);
  servoWrite(1, LEG4_COXA_PIN_b1, 90);
  servoWrite(1, LEG6_COXA_PIN_b1, 90);
  servoWrite(2, LEG1_COXA_PIN_b2, 90);
  servoWrite(2, LEG3_COXA_PIN_b2, 90);
  servoWrite(2, LEG5_COXA_PIN_b2, 90);
  delay(200);
  servoWrite(1, LEG2_FEMUR_PIN_b1, 90);
  servoWrite(1, LEG4_FEMUR_PIN_b1, 90);
  servoWrite(1, LEG6_FEMUR_PIN_b1, 90);
  servoWrite(2, LEG1_FEMUR_PIN_b2, 90);
  servoWrite(2, LEG3_FEMUR_PIN_b2, 90);
  servoWrite(2, LEG5_FEMUR_PIN_b2, 90);
  delay(150);
  servoWrite(1, LEG2_TIBIA_PIN_b1, 10);
  servoWrite(1, LEG4_TIBIA_PIN_b1, 10);
  servoWrite(1, LEG6_TIBIA_PIN_b1, 10);
  servoWrite(2, LEG1_TIBIA_PIN_b2, 10);
  servoWrite(2, LEG3_TIBIA_PIN_b2, 10);
  servoWrite(2, LEG5_TIBIA_PIN_b2, 10);

  delay(150);
}

// Function to move Leg 1
void moveLeg1() {
  // Swing Position
  servoWrite(2, LEG1_FEMUR_PIN_b2, 50);
  servoWrite(2, LEG1_TIBIA_PIN_b2, 10);
  servoWrite(2, LEG1_COXA_PIN_b2, 70);
  delay(500);

  // Stance Position
  servoWrite(2, LEG1_FEMUR_PIN_b2, 90);
  delay(500);
  servoWrite(2, LEG1_COXA_PIN_b2, 90);
  delay(500);
}

// Function to move Leg 2
void moveLeg2() {
  // Swing Position
  servoWrite(1, LEG2_FEMUR_PIN_b1, 50);
  servoWrite(1, LEG2_TIBIA_PIN_b1, 10);
  servoWrite(1, LEG2_COXA_PIN_b1, 70);
  delay(500);

  // Stance Position
  servoWrite(1, LEG2_FEMUR_PIN_b1, 90);
  delay(500);
  servoWrite(1, LEG2_COXA_PIN_b1, 90);
  delay(500);
}

// Function to move Leg 3
void moveLeg3() {
  // Swing Position
  servoWrite(2, LEG3_FEMUR_PIN_b2, 50);
  servoWrite(2, LEG3_TIBIA_PIN_b2, 10);
  servoWrite(2, LEG3_COXA_PIN_b2, 70);
  delay(500);

  // Stance Position
  servoWrite(2, LEG3_FEMUR_PIN_b2, 90);
  delay(500);
  servoWrite(2, LEG3_COXA_PIN_b2, 90);
  delay(500);
}

// Function to move Leg 4
void moveLeg4() {
  // Swing Position
  servoWrite(1, LEG4_FEMUR_PIN_b1, 50);
  servoWrite(1, LEG4_TIBIA_PIN_b1, 10);
  servoWrite(1, LEG4_COXA_PIN_b1, 70);
  delay(500);

  // Stance Position
  servoWrite(1, LEG4_FEMUR_PIN_b1, 90);
  delay(500);
  servoWrite(1, LEG4_COXA_PIN_b1, 90);
  delay(500);
}

// Function to move Leg 5
void moveLeg5() {
  // Swing Position
  servoWrite(2, LEG5_FEMUR_PIN_b2, 50);
  servoWrite(2, LEG5_TIBIA_PIN_b2, 10);
  servoWrite(2, LEG5_COXA_PIN_b2, 70);
  delay(500);

  // Stance Position
  servoWrite(2, LEG5_FEMUR_PIN_b2, 90);
  delay(500);
  servoWrite(2, LEG5_COXA_PIN_b2, 90);
  delay(500);
}

// Function to move Leg 6
void moveLeg6() {
  // Swing Position
  servoWrite(1, LEG6_FEMUR_PIN_b1, 50);
  servoWrite(1, LEG6_TIBIA_PIN_b1, 10);
  servoWrite(1, LEG6_COXA_PIN_b1, 70);
  delay(500);

  // Stance Position
  servoWrite(1, LEG6_FEMUR_PIN_b1, 90);
  delay(500);
  servoWrite(1, LEG6_COXA_PIN_b1, 90);
  delay(500);
}

void moveFrontTwo() {
  // Swing Position
  servoWrite(2, LEG1_FEMUR_PIN_b2, 50);
  servoWrite(1, LEG2_FEMUR_PIN_b1, 50);

  servoWrite(2, LEG1_TIBIA_PIN_b2, 10);
  servoWrite(1, LEG2_TIBIA_PIN_b1, 10);

  servoWrite(2, LEG1_COXA_PIN_b2, 70);
  servoWrite(1, LEG2_COXA_PIN_b1, 70);
  delay(800);

  // Stance Position
  servoWrite(2, LEG1_FEMUR_PIN_b2, 90);
  servoWrite(1, LEG2_FEMUR_PIN_b1, 90);
  delay(500);

  servoWrite(2, LEG1_COXA_PIN_b2, 90);
  servoWrite(1, LEG2_COXA_PIN_b1, 90);
  delay(500);
}


void moveMiddleTwo() {
  // Swing Position
  servoWrite(2, LEG3_FEMUR_PIN_b2, 50);
  servoWrite(1, LEG4_FEMUR_PIN_b1, 50);

  servoWrite(2, LEG3_TIBIA_PIN_b2, 10);
  servoWrite(1, LEG4_TIBIA_PIN_b1, 10);

  servoWrite(2, LEG3_COXA_PIN_b2, 70);
  servoWrite(1, LEG4_COXA_PIN_b1, 70);
  delay(800);

  // Stance Position
  servoWrite(2, LEG3_FEMUR_PIN_b2, 90);
  servoWrite(1, LEG4_FEMUR_PIN_b1, 90);
  delay(500);

  servoWrite(2, LEG3_COXA_PIN_b2, 90);
  servoWrite(1, LEG4_COXA_PIN_b1, 90);
  delay(500);
}


void moveLastTwo() {
  // Swing Position
  servoWrite(2, LEG5_FEMUR_PIN_b2, 50);
  servoWrite(1, LEG6_FEMUR_PIN_b1, 50);

  servoWrite(2, LEG5_TIBIA_PIN_b2, 10);
  servoWrite(1, LEG6_TIBIA_PIN_b1, 10);

  servoWrite(2, LEG5_COXA_PIN_b2, 70);
  servoWrite(1, LEG6_COXA_PIN_b1, 70);
  delay(800);

  // Stance Position
  servoWrite(2, LEG5_FEMUR_PIN_b2, 90);
  servoWrite(1, LEG6_FEMUR_PIN_b1, 90);
  delay(500);

  servoWrite(2, LEG5_COXA_PIN_b2, 90);
  servoWrite(1, LEG6_COXA_PIN_b1, 90);
  delay(500);
}

void frontLegHook() {
  Serial.println("frontLegHook");
  servoWrite(2, LEG1_COXA_PIN_b2, 90);
  servoWrite(1, LEG2_COXA_PIN_b1, 90);
  delay(500);
  servoWrite(2, LEG1_FEMUR_PIN_b2, 30);
  servoWrite(1, LEG2_FEMUR_PIN_b1, 30);
  delay(500);

  servoWrite(2, LEG1_TIBIA_PIN_b2, 120);
  servoWrite(1, LEG2_TIBIA_PIN_b1, 120);
  delay(800);

  servoWrite(2, LEG1_COXA_PIN_b2, 30);
  servoWrite(1, LEG2_COXA_PIN_b1, 30);
  delay(800);

  // Stance Position
  servoWrite(2, LEG1_TIBIA_PIN_b2, 40);
  servoWrite(1, LEG2_TIBIA_PIN_b1, 40);
  delay(500);
}



void expandMiddle() {
  // Swing Position
  servoWrite(2, LEG3_FEMUR_PIN_b2, 50);
  servoWrite(1, LEG4_FEMUR_PIN_b1, 50);

  servoWrite(2, LEG3_TIBIA_PIN_b2, 10);
  servoWrite(1, LEG4_TIBIA_PIN_b1, 10);

  servoWrite(2, LEG3_COXA_PIN_b2, 50);
  servoWrite(1, LEG4_COXA_PIN_b1, 50);
  delay(800);
  servoWrite(2, LEG3_FEMUR_PIN_b2, 90);
  servoWrite(1, LEG4_FEMUR_PIN_b1, 90);
  delay(300);

  // Stance Position
  // servoWrite(2, LEG3_FEMUR_PIN_b2, 90);
  // servoWrite(1, LEG4_FEMUR_PIN_b1, 90);
  // delay(500);

  // servoWrite(2, LEG3_COXA_PIN_b2, 90);
  // servoWrite(1, LEG4_COXA_PIN_b1, 90);
  // delay(500);



  //--------------------------------------------

  // Swing Position
  // servoWrite(2, LEG5_FEMUR_PIN_b2, 50);
  // servoWrite(1, LEG6_FEMUR_PIN_b1, 50);

  // servoWrite(2, LEG5_TIBIA_PIN_b2, 10);
  // servoWrite(1, LEG6_TIBIA_PIN_b1, 10);

  // servoWrite(2, LEG5_COXA_PIN_b2, 70);
  // servoWrite(1, LEG6_COXA_PIN_b1, 70);
  // delay(800);

  // // Stance Position
  // servoWrite(2, LEG5_FEMUR_PIN_b2, 90);
  // servoWrite(1, LEG6_FEMUR_PIN_b1, 90);
  // delay(500);

  // servoWrite(2, LEG5_COXA_PIN_b2, 90);
  // servoWrite(1, LEG6_COXA_PIN_b1, 90);
  // delay(500);
}


void moveMidleAndLastLegPairForward() {
  servoWrite(2, LEG3_FEMUR_PIN_b2, 170);
  servoWrite(1, LEG4_FEMUR_PIN_b1, 170);
  servoWrite(2, LEG5_FEMUR_PIN_b2, 170);
  servoWrite(1, LEG6_FEMUR_PIN_b1, 170);

  servoWrite(2, LEG3_TIBIA_PIN_b2, 90);
  servoWrite(1, LEG4_TIBIA_PIN_b1, 90);
  servoWrite(2, LEG5_TIBIA_PIN_b2, 90);
  servoWrite(1, LEG6_TIBIA_PIN_b1, 90);

  servoWrite(2, LEG3_COXA_PIN_b2, 70);
  servoWrite(1, LEG4_COXA_PIN_b1, 70);
  servoWrite(2, LEG5_COXA_PIN_b2, 120);
  servoWrite(1, LEG6_COXA_PIN_b1, 120);
  delay(2000);

  // leg 3 stance
  servoWrite(2, LEG3_FEMUR_PIN_b2, 40);
  servoWrite(2, LEG3_TIBIA_PIN_b2, 10);
  delay(1000);
  // leg 3 swing
  servoWrite(2, LEG3_FEMUR_PIN_b2, 170);
  servoWrite(2, LEG3_TIBIA_PIN_b2, 90);
  servoWrite(2, LEG3_COXA_PIN_b2, 50);
  delay(3500);

  // leg 4 stance
  servoWrite(1, LEG4_FEMUR_PIN_b1, 40);
  servoWrite(1, LEG4_TIBIA_PIN_b1, 10);
  delay(1000);
  // leg 4 swing
  servoWrite(1, LEG4_FEMUR_PIN_b1, 170);
  servoWrite(1, LEG4_TIBIA_PIN_b1, 90);
  servoWrite(1, LEG4_COXA_PIN_b1, 50);
  delay(3500);

  // leg 5 stance
  servoWrite(2, LEG5_FEMUR_PIN_b2, 40);
  servoWrite(2, LEG5_TIBIA_PIN_b2, 10);
  delay(1000);
  // leg 5 swing
  servoWrite(2, LEG5_FEMUR_PIN_b2, 170);
  servoWrite(2, LEG5_TIBIA_PIN_b2, 90);
  servoWrite(2, LEG5_COXA_PIN_b2, 50);
  delay(3500);

  // leg 6 stance
  servoWrite(1, LEG6_FEMUR_PIN_b1, 40);
  servoWrite(1, LEG6_TIBIA_PIN_b1, 10);
  delay(1000);
  // leg 6 swing
  servoWrite(1, LEG6_FEMUR_PIN_b1, 170);
  servoWrite(1, LEG6_TIBIA_PIN_b1, 90);
  servoWrite(1, LEG6_COXA_PIN_b1, 50);
  delay(3500);
}


void FrontLegHookandExpandMiddleLast() {

  stand();
  delay(800);
  servoWrite(2, LEG3_FEMUR_PIN_b2, 50);
  servoWrite(1, LEG4_FEMUR_PIN_b1, 50);

  servoWrite(2, LEG3_COXA_PIN_b2, 50);
  servoWrite(1, LEG4_COXA_PIN_b1, 50);
  delay(800);
  servoWrite(2, LEG3_FEMUR_PIN_b2, 90);
  servoWrite(1, LEG4_FEMUR_PIN_b1, 90);
  delay(800);

  servoWrite(2, LEG1_FEMUR_PIN_b2, 10);
  servoWrite(1, LEG2_FEMUR_PIN_b1, 10);
  delay(800);

  servoWrite(2, LEG1_TIBIA_PIN_b2, 120);
  servoWrite(1, LEG2_TIBIA_PIN_b1, 120);
  delay(800);


  servoWrite(2, LEG1_COXA_PIN_b2, 40);
  servoWrite(1, LEG2_COXA_PIN_b1, 40);
  delay(800);

  servoWrite(2, LEG1_TIBIA_PIN_b2, 30);
  servoWrite(1, LEG2_TIBIA_PIN_b1, 30);
  delay(800);

  // Movement ranges
  const int femurStart = 90, femurEnd = 170;
  const int tibiaStart = 10, tibiaEnd = 90;

  // Calculate total steps
  const int totalSteps = 100;  // Adjust this value to make the motion smoother or faster
  const float femurIncrement = float(femurEnd - femurStart) / totalSteps;
  const float tibiaIncrement = float(tibiaEnd - tibiaStart) / totalSteps;

  for (int step = 0; step <= totalSteps; step++) {
    int femurAngle = femurStart + step * femurIncrement;
    int tibiaAngle = tibiaStart + step * tibiaIncrement;

    servoWrite(2, LEG3_FEMUR_PIN_b2, femurAngle);
    servoWrite(1, LEG4_FEMUR_PIN_b1, femurAngle);
    servoWrite(2, LEG5_FEMUR_PIN_b2, femurAngle);
    servoWrite(1, LEG6_FEMUR_PIN_b1, femurAngle);

    servoWrite(2, LEG3_TIBIA_PIN_b2, tibiaAngle);
    servoWrite(1, LEG4_TIBIA_PIN_b1, tibiaAngle);
    servoWrite(2, LEG5_TIBIA_PIN_b2, tibiaAngle);
    servoWrite(1, LEG6_TIBIA_PIN_b1, tibiaAngle);
    delay(50);  // Delay to make the movement slow and smooth
  }

  delay(800);
}


void middleLegsHook() {

  servoWrite(2, LEG3_FEMUR_PIN_b2, 50);
  servoWrite(1, LEG4_FEMUR_PIN_b1, 50);

  servoWrite(2, LEG3_TIBIA_PIN_b2, 120);
  servoWrite(1, LEG4_TIBIA_PIN_b1, 120);
  delay(800);

  servoWrite(2, LEG3_COXA_PIN_b2, 40);
  servoWrite(1, LEG4_COXA_PIN_b1, 40);
  delay(800);

  servoWrite(2, LEG3_FEMUR_PIN_b2, 90);
  servoWrite(1, LEG4_FEMUR_PIN_b1, 90);
  delay(800);

  servoWrite(2, LEG3_TIBIA_PIN_b2, 50);
  servoWrite(1, LEG4_TIBIA_PIN_b1, 50);
  delay(800);
}

void moveMiddleLay() {
  servoWrite(2, LEG3_FEMUR_PIN_b2, 40);
  servoWrite(1, LEG4_FEMUR_PIN_b1, 50);

  servoWrite(2, LEG3_TIBIA_PIN_b2, 10);
  servoWrite(1, LEG4_TIBIA_PIN_b1, 10);
  delay(800);

  servoWrite(2, LEG3_COXA_PIN_b2, 50);
  servoWrite(1, LEG4_COXA_PIN_b1, 50);
  delay(800);

}

void moveFrontRow(){

  servoWrite(2, LEG1_FEMUR_PIN_b2, 40);
  servoWrite(1, LEG2_FEMUR_PIN_b1, 40);
  delay(800);

  servoWrite(2, LEG1_TIBIA_PIN_b2, 10);
  servoWrite(1, LEG2_TIBIA_PIN_b1, 10);
  delay(800);


  servoWrite(2, LEG1_COXA_PIN_b2, 40);
  servoWrite(1, LEG2_COXA_PIN_b1, 40);
  delay(800);


}


void moveFrontLegPairForward() {


  // leg 1 stance
  servoWrite(2, LEG1_FEMUR_PIN_b2, 40);
  servoWrite(2, LEG1_TIBIA_PIN_b2, 10);
  servoWrite(2, LEG1_COXA_PIN_b2, 70);
  delay(300);
  // leg 1 swing
  servoWrite(2, LEG1_FEMUR_PIN_b2, 170);
  servoWrite(2, LEG1_TIBIA_PIN_b2, 90);
  delay(500);

  // leg 2 stance
  servoWrite(1, LEG2_FEMUR_PIN_b1, 40);
  servoWrite(1, LEG2_TIBIA_PIN_b1, 10);
  servoWrite(1, LEG2_COXA_PIN_b1, 70);
  delay(500);
  // leg 2 swing
  servoWrite(1, LEG2_FEMUR_PIN_b1, 170);
  servoWrite(1, LEG2_TIBIA_PIN_b1, 90);
  delay(500);
  servoWrite(2, LEG1_COXA_PIN_b2, 100);
  servoWrite(1, LEG2_COXA_PIN_b1, 100);
  delay(500);
}

void moveMiddleLegPairForward() {

  // leg 3 stance
  servoWrite(2, LEG3_FEMUR_PIN_b2, 40);
  servoWrite(2, LEG3_TIBIA_PIN_b2, 10);
  servoWrite(2, LEG3_COXA_PIN_b2, 70);
  delay(300);
  // leg 3 swing
  servoWrite(2, LEG3_FEMUR_PIN_b2, 170);
  servoWrite(2, LEG3_TIBIA_PIN_b2, 90);
  delay(500);

  // leg 4 stance
  servoWrite(1, LEG4_FEMUR_PIN_b1, 40);
  servoWrite(1, LEG4_TIBIA_PIN_b1, 10);
  servoWrite(1, LEG4_COXA_PIN_b1, 70);
  delay(500);
  // leg 4 swing
  servoWrite(1, LEG4_FEMUR_PIN_b1, 170);
  servoWrite(1, LEG4_TIBIA_PIN_b1, 90);
  delay(500);
  servoWrite(2, LEG3_COXA_PIN_b2, 100);
  servoWrite(1, LEG4_COXA_PIN_b1, 100);
  delay(500);
}


void moveLastLegPairForward() {

  servoWrite(2, LEG5_FEMUR_PIN_b2, 170);
  servoWrite(1, LEG6_FEMUR_PIN_b1, 170);

  servoWrite(2, LEG5_TIBIA_PIN_b2, 90);
  servoWrite(1, LEG6_TIBIA_PIN_b1, 90);

  servoWrite(2, LEG5_COXA_PIN_b2, 120);
  servoWrite(1, LEG6_COXA_PIN_b1, 120);
  delay(2000);


  // leg 5 stance
  servoWrite(2, LEG5_FEMUR_PIN_b2, 40);
  servoWrite(2, LEG5_TIBIA_PIN_b2, 10);
  delay(1000);
  // leg 5 swing
  servoWrite(2, LEG5_FEMUR_PIN_b2, 170);
  servoWrite(2, LEG5_TIBIA_PIN_b2, 90);
  servoWrite(2, LEG5_COXA_PIN_b2, 50);
  delay(3500);

  // leg 6 stance
  servoWrite(1, LEG6_FEMUR_PIN_b1, 40);
  servoWrite(1, LEG6_TIBIA_PIN_b1, 10);
  delay(1000);
  // leg 6 swing
  servoWrite(1, LEG6_FEMUR_PIN_b1, 170);
  servoWrite(1, LEG6_TIBIA_PIN_b1, 90);
  servoWrite(1, LEG6_COXA_PIN_b1, 50);
  delay(3500);
}



void lastLegsHook() {

  servoWrite(2, LEG5_FEMUR_PIN_b2, 50);
  servoWrite(1, LEG6_FEMUR_PIN_b1, 50);

  servoWrite(2, LEG5_TIBIA_PIN_b2, 120);
  servoWrite(1, LEG6_TIBIA_PIN_b1, 120);
  delay(800);

  servoWrite(2, LEG5_COXA_PIN_b2, 25);
  servoWrite(1, LEG6_COXA_PIN_b1, 25);
  delay(800);

  servoWrite(2, LEG5_FEMUR_PIN_b2, 90);
  servoWrite(1, LEG6_FEMUR_PIN_b1, 90);
  delay(800);

  servoWrite(2, LEG5_TIBIA_PIN_b2, 20);
  servoWrite(1, LEG6_TIBIA_PIN_b1, 20);
  delay(800);
}

void liftFrontTwo() {

  servoWrite(2, LEG1_COXA_PIN_b2, 40);
  servoWrite(1, LEG2_COXA_PIN_b1, 40);

  servoWrite(2, LEG1_FEMUR_PIN_b2, 110);
  servoWrite(1, LEG2_FEMUR_PIN_b1, 110);
  delay(800);

  servoWrite(2, LEG1_TIBIA_PIN_b2, 10);
  servoWrite(1, LEG2_TIBIA_PIN_b1, 10);
  delay(800);
}

void moveFrontForward() {

  servoWrite(2, LEG1_COXA_PIN_b2, 40);
  servoWrite(1, LEG2_COXA_PIN_b1, 40);

  servoWrite(2, LEG1_FEMUR_PIN_b2, 90);
  servoWrite(1, LEG2_FEMUR_PIN_b1, 90);
  delay(800);

  servoWrite(2, LEG1_TIBIA_PIN_b2, 30);
  servoWrite(1, LEG2_TIBIA_PIN_b1, 30);
  delay(800);

  servoWrite(2, LEG1_TIBIA_PIN_b2, 10);
  servoWrite(1, LEG2_TIBIA_PIN_b1, 10);
  delay(800);

  servoWrite(2, LEG1_FEMUR_PIN_b2, 120);
  servoWrite(1, LEG2_FEMUR_PIN_b1, 120);
  delay(800);
}

// move lay 
void moveFrontLay() {

  servoWrite(2, LEG1_COXA_PIN_b2, 40);
  servoWrite(1, LEG2_COXA_PIN_b1, 40);
  delay(800);

  servoWrite(2, LEG1_FEMUR_PIN_b2, 90);
  servoWrite(1, LEG2_FEMUR_PIN_b1, 90);
  delay(800);

  servoWrite(2, LEG1_TIBIA_PIN_b2, 90);
  servoWrite(1, LEG2_TIBIA_PIN_b1, 90);
  delay(800);
}

// move down middleAndlast
void moveMiddleAndLastLay() {

  servoWrite(2, LEG3_FEMUR_PIN_b2, 30);
  servoWrite(1, LEG4_FEMUR_PIN_b1, 30);  //
  servoWrite(2, LEG5_FEMUR_PIN_b2, 30);  //
  servoWrite(1, LEG6_FEMUR_PIN_b1, 30);
  delay(500);

  servoWrite(2, LEG3_TIBIA_PIN_b2, 10);
  servoWrite(1, LEG4_TIBIA_PIN_b1, 10);  //
  servoWrite(2, LEG5_TIBIA_PIN_b2, 10);  //
  servoWrite(1, LEG6_TIBIA_PIN_b1, 10);

  delay(500);
  servoWrite(2, LEG3_COXA_PIN_b2, 60);
  servoWrite(1, LEG4_COXA_PIN_b1, 60);  //
  servoWrite(2, LEG5_COXA_PIN_b2, 60);  //
  servoWrite(1, LEG6_COXA_PIN_b1, 60);
  delay(500);
  //--------------------------------------------

  servoWrite(1, LEG4_FEMUR_PIN_b1, 65);  //
  servoWrite(2, LEG5_FEMUR_PIN_b2, 65);  //
  servoWrite(1, LEG6_FEMUR_PIN_b1, 65);
  servoWrite(2, LEG3_FEMUR_PIN_b2, 65);
  delay(500);

  servoWrite(2, LEG3_COXA_PIN_b2, 90);
  servoWrite(1, LEG4_COXA_PIN_b1, 90);  //
  servoWrite(2, LEG5_COXA_PIN_b2, 90);  //
  servoWrite(1, LEG6_COXA_PIN_b1, 90);
  delay(500);

}

void moveLastLay() {

  servoWrite(2, LEG5_FEMUR_PIN_b2, 30);  //
  servoWrite(1, LEG6_FEMUR_PIN_b1, 30);
  delay(500);

  servoWrite(2, LEG5_TIBIA_PIN_b2, 10);  //
  servoWrite(1, LEG6_TIBIA_PIN_b1, 10);

  delay(500);
  servoWrite(2, LEG5_COXA_PIN_b2, 60);  //
  servoWrite(1, LEG6_COXA_PIN_b1, 60);
  delay(500);
  //--------------------------------------------

  servoWrite(1, LEG5_FEMUR_PIN_b2, 65);
  servoWrite(2, LEG6_FEMUR_PIN_b1, 65);
  delay(500);

  servoWrite(2, LEG5_COXA_PIN_b2, 90);  //
  servoWrite(1, LEG6_COXA_PIN_b1, 90);
  delay(500);

}

// stand 
void standFrontTwo(){

  servoWrite(2, LEG1_COXA_PIN_b2, 40);
  servoWrite(1, LEG2_COXA_PIN_b1, 40);
  delay(500);

  servoWrite(2, LEG1_TIBIA_PIN_b2, 90);
  servoWrite(1, LEG2_TIBIA_PIN_b1, 90);
  delay(500);

  servoWrite(2, LEG1_FEMUR_PIN_b2, 170);
  servoWrite(1, LEG2_FEMUR_PIN_b1, 170);
  delay(500);
  servoWrite(2, LEG1_COXA_PIN_b2, 90);
  servoWrite(1, LEG2_COXA_PIN_b1, 90);
  delay(800);

}

void standMiddleTwo(){

  servoWrite(2, LEG3_COXA_PIN_b2, 70);
  servoWrite(1, LEG4_COXA_PIN_b1, 70);
  delay(500);
  
  servoWrite(2, LEG3_TIBIA_PIN_b2, 90);
  servoWrite(1, LEG4_TIBIA_PIN_b1, 90);
  delay(500);

  servoWrite(2, LEG3_FEMUR_PIN_b2, 170);
  servoWrite(1, LEG4_FEMUR_PIN_b1, 170);
  delay(500);
  
  servoWrite(2, LEG3_COXA_PIN_b2, 90);
  servoWrite(1, LEG4_COXA_PIN_b1, 90);
  delay(800);


}


void standLastTwo(){

  servoWrite(2, LEG5_COXA_PIN_b2, 40);
  delay(300);

  servoWrite(2, LEG5_TIBIA_PIN_b2, 90);
  delay(300);

  servoWrite(2, LEG5_FEMUR_PIN_b2, 170);
  delay(300);
  
  servoWrite(2, LEG5_COXA_PIN_b2, 90);
  delay(500);

  //-----------------------------
  servoWrite(1, LEG6_COXA_PIN_b1, 40);
  delay(300);

  servoWrite(1, LEG6_TIBIA_PIN_b1, 90);
  delay(300);

  servoWrite(1, LEG5_FEMUR_PIN_b2, 170);
  delay(300);
  
  servoWrite(1, LEG6_COXA_PIN_b1, 90);
  delay(800);

}

// stand 



void gait1() {
  servoWrite(2, LEG1_FEMUR_PIN_b2, 50);  //
  servoWrite(1, LEG4_FEMUR_PIN_b1, 50);  //
  servoWrite(2, LEG5_FEMUR_PIN_b2, 50);  //
  servoWrite(1, LEG2_FEMUR_PIN_b1, 90);
  servoWrite(1, LEG6_FEMUR_PIN_b1, 90);
  servoWrite(2, LEG3_FEMUR_PIN_b2, 90);
  delay(500);
  servoWrite(2, LEG1_TIBIA_PIN_b2, 10);  //
  servoWrite(1, LEG4_TIBIA_PIN_b1, 10);  //
  servoWrite(2, LEG5_TIBIA_PIN_b2, 10);  //
  servoWrite(1, LEG2_TIBIA_PIN_b1, 10);
  servoWrite(2, LEG3_TIBIA_PIN_b2, 10);
  servoWrite(1, LEG6_TIBIA_PIN_b1, 10);

  delay(500);
  servoWrite(2, LEG1_COXA_PIN_b2, 70);  //
  servoWrite(1, LEG4_COXA_PIN_b1, 70);  //
  servoWrite(2, LEG5_COXA_PIN_b2, 70);  //
  servoWrite(1, LEG2_COXA_PIN_b1, 90);
  servoWrite(1, LEG6_COXA_PIN_b1, 90);
  servoWrite(2, LEG3_COXA_PIN_b2, 90);
  delay(500);
  //--------------------------------------------
  servoWrite(2, LEG1_FEMUR_PIN_b2, 90);  //
  servoWrite(1, LEG4_FEMUR_PIN_b1, 90);  //
  servoWrite(2, LEG5_FEMUR_PIN_b2, 90);  //
  servoWrite(1, LEG2_FEMUR_PIN_b1, 90);
  servoWrite(1, LEG6_FEMUR_PIN_b1, 90);
  servoWrite(2, LEG3_FEMUR_PIN_b2, 90);
  delay(500);

  servoWrite(2, LEG1_COXA_PIN_b2, 90);  //
  servoWrite(1, LEG4_COXA_PIN_b1, 90);  //
  servoWrite(2, LEG5_COXA_PIN_b2, 90);  //
  servoWrite(1, LEG2_COXA_PIN_b1, 90);
  servoWrite(1, LEG6_COXA_PIN_b1, 90);
  servoWrite(2, LEG3_COXA_PIN_b2, 90);
  delay(500);
  gait1Status = true;
}

void gait2() {
  servoWrite(2, LEG1_FEMUR_PIN_b2, 90);
  servoWrite(1, LEG4_FEMUR_PIN_b1, 90);
  servoWrite(2, LEG5_FEMUR_PIN_b2, 90);
  servoWrite(1, LEG2_FEMUR_PIN_b1, 50);  //
  servoWrite(1, LEG6_FEMUR_PIN_b1, 50);  //
  servoWrite(2, LEG3_FEMUR_PIN_b2, 50);  //
  delay(500);
  servoWrite(2, LEG1_TIBIA_PIN_b2, 10);  //
  servoWrite(1, LEG4_TIBIA_PIN_b1, 10);  //
  servoWrite(2, LEG5_TIBIA_PIN_b2, 10);  //
  servoWrite(1, LEG2_TIBIA_PIN_b1, 10);
  servoWrite(2, LEG3_TIBIA_PIN_b2, 10);
  servoWrite(1, LEG6_TIBIA_PIN_b1, 10);

  delay(500);
  servoWrite(2, LEG1_COXA_PIN_b2, 90);  //
  servoWrite(1, LEG4_COXA_PIN_b1, 90);  //
  servoWrite(2, LEG5_COXA_PIN_b2, 90);  //
  servoWrite(1, LEG2_COXA_PIN_b1, 70);
  servoWrite(1, LEG6_COXA_PIN_b1, 70);
  servoWrite(2, LEG3_COXA_PIN_b2, 70);
  delay(500);
  //--------------------------------------------
  servoWrite(2, LEG1_FEMUR_PIN_b2, 90);  //
  servoWrite(1, LEG4_FEMUR_PIN_b1, 90);  //
  servoWrite(2, LEG5_FEMUR_PIN_b2, 90);  //
  servoWrite(1, LEG2_FEMUR_PIN_b1, 90);
  servoWrite(1, LEG6_FEMUR_PIN_b1, 90);
  servoWrite(2, LEG3_FEMUR_PIN_b2, 90);
  delay(500);

  servoWrite(2, LEG1_COXA_PIN_b2, 90);  //
  servoWrite(1, LEG4_COXA_PIN_b1, 90);  //
  servoWrite(2, LEG5_COXA_PIN_b2, 90);  //
  servoWrite(1, LEG2_COXA_PIN_b1, 90);
  servoWrite(1, LEG6_COXA_PIN_b1, 90);
  servoWrite(2, LEG3_COXA_PIN_b2, 90);
  delay(500);
  gait2Status = true;
}



// revese gait 

void gait1Reverse() {
  servoWrite(2, LEG1_FEMUR_PIN_b2, 50);  //
  servoWrite(1, LEG4_FEMUR_PIN_b1, 50);  //
  servoWrite(2, LEG5_FEMUR_PIN_b2, 50);  //
  servoWrite(1, LEG2_FEMUR_PIN_b1, 90);
  servoWrite(1, LEG6_FEMUR_PIN_b1, 90);
  servoWrite(2, LEG3_FEMUR_PIN_b2, 90);
  delay(500);
  servoWrite(2, LEG1_TIBIA_PIN_b2, 10);  //
  servoWrite(1, LEG4_TIBIA_PIN_b1, 10);  //
  servoWrite(2, LEG5_TIBIA_PIN_b2, 10);  //
  servoWrite(1, LEG2_TIBIA_PIN_b1, 10);
  servoWrite(2, LEG3_TIBIA_PIN_b2, 10);
  servoWrite(1, LEG6_TIBIA_PIN_b1, 10);

  delay(500);
  servoWrite(2, LEG1_COXA_PIN_b2, 110);  //
  servoWrite(1, LEG4_COXA_PIN_b1, 110);  //
  servoWrite(2, LEG5_COXA_PIN_b2, 110);  //
  servoWrite(1, LEG2_COXA_PIN_b1, 90);
  servoWrite(1, LEG6_COXA_PIN_b1, 90);
  servoWrite(2, LEG3_COXA_PIN_b2, 90);
  delay(500);
  //--------------------------------------------
  servoWrite(2, LEG1_FEMUR_PIN_b2, 90);  //
  servoWrite(1, LEG4_FEMUR_PIN_b1, 90);  //
  servoWrite(2, LEG5_FEMUR_PIN_b2, 90);  //
  servoWrite(1, LEG2_FEMUR_PIN_b1, 90);
  servoWrite(1, LEG6_FEMUR_PIN_b1, 90);
  servoWrite(2, LEG3_FEMUR_PIN_b2, 90);
  delay(500);

  servoWrite(2, LEG1_COXA_PIN_b2, 90);  //
  servoWrite(1, LEG4_COXA_PIN_b1, 90);  //
  servoWrite(2, LEG5_COXA_PIN_b2, 90);  //
  servoWrite(1, LEG2_COXA_PIN_b1, 90);
  servoWrite(1, LEG6_COXA_PIN_b1, 90);
  servoWrite(2, LEG3_COXA_PIN_b2, 90);
  delay(500);
  gait1ReverseStatus = true;
}

void gait2Reverse() {
  servoWrite(2, LEG1_FEMUR_PIN_b2, 90);
  servoWrite(1, LEG4_FEMUR_PIN_b1, 90);
  servoWrite(2, LEG5_FEMUR_PIN_b2, 90);
  servoWrite(1, LEG2_FEMUR_PIN_b1, 50);  //
  servoWrite(1, LEG6_FEMUR_PIN_b1, 50);  //
  servoWrite(2, LEG3_FEMUR_PIN_b2, 50);  //
  delay(500);
  servoWrite(2, LEG1_TIBIA_PIN_b2, 10);  //
  servoWrite(1, LEG4_TIBIA_PIN_b1, 10);  //
  servoWrite(2, LEG5_TIBIA_PIN_b2, 10);  //
  servoWrite(1, LEG2_TIBIA_PIN_b1, 10);
  servoWrite(2, LEG3_TIBIA_PIN_b2, 10);
  servoWrite(1, LEG6_TIBIA_PIN_b1, 10);

  delay(500);
  servoWrite(2, LEG1_COXA_PIN_b2, 90);  //
  servoWrite(1, LEG4_COXA_PIN_b1, 90);  //
  servoWrite(2, LEG5_COXA_PIN_b2, 90);  //
  servoWrite(1, LEG2_COXA_PIN_b1, 110);
  servoWrite(1, LEG6_COXA_PIN_b1, 110);
  servoWrite(2, LEG3_COXA_PIN_b2, 110);
  delay(500);
  //--------------------------------------------
  servoWrite(2, LEG1_FEMUR_PIN_b2, 90);  //
  servoWrite(1, LEG4_FEMUR_PIN_b1, 90);  //
  servoWrite(2, LEG5_FEMUR_PIN_b2, 90);  //
  servoWrite(1, LEG2_FEMUR_PIN_b1, 90);
  servoWrite(1, LEG6_FEMUR_PIN_b1, 90);
  servoWrite(2, LEG3_FEMUR_PIN_b2, 90);
  delay(500);

  servoWrite(2, LEG1_COXA_PIN_b2, 90);  //
  servoWrite(1, LEG4_COXA_PIN_b1, 90);  //
  servoWrite(2, LEG5_COXA_PIN_b2, 90);  //
  servoWrite(1, LEG2_COXA_PIN_b1, 90);
  servoWrite(1, LEG6_COXA_PIN_b1, 90);
  servoWrite(2, LEG3_COXA_PIN_b2, 90);
  delay(500);
  gait2ReverseStatus = true;
}

// lay 

void gait1Lay() {
  servoWrite(2, LEG1_FEMUR_PIN_b2, 10);  //
  servoWrite(1, LEG4_FEMUR_PIN_b1, 10);  //
  servoWrite(2, LEG5_FEMUR_PIN_b2, 10);  //
  servoWrite(1, LEG2_FEMUR_PIN_b1, 60);
  servoWrite(1, LEG6_FEMUR_PIN_b1, 60);
  servoWrite(2, LEG3_FEMUR_PIN_b2, 60);
  delay(500);
  servoWrite(2, LEG1_TIBIA_PIN_b2, 10);  //
  servoWrite(1, LEG4_TIBIA_PIN_b1, 10);  //
  servoWrite(2, LEG5_TIBIA_PIN_b2, 10);  //
  servoWrite(1, LEG2_TIBIA_PIN_b1, 10);
  servoWrite(2, LEG3_TIBIA_PIN_b2, 10);
  servoWrite(1, LEG6_TIBIA_PIN_b1, 10);

  delay(500);
  servoWrite(2, LEG1_COXA_PIN_b2, 70);  //
  servoWrite(1, LEG4_COXA_PIN_b1, 70);  //
  servoWrite(2, LEG5_COXA_PIN_b2, 70);  //
  servoWrite(1, LEG2_COXA_PIN_b1, 90);
  servoWrite(1, LEG6_COXA_PIN_b1, 90);
  servoWrite(2, LEG3_COXA_PIN_b2, 90);
  delay(500);
  //--------------------------------------------
  servoWrite(2, LEG1_FEMUR_PIN_b2, 60);  //
  servoWrite(1, LEG4_FEMUR_PIN_b1, 60);  //
  servoWrite(2, LEG5_FEMUR_PIN_b2, 60);  //
  servoWrite(1, LEG2_FEMUR_PIN_b1, 60);
  servoWrite(1, LEG6_FEMUR_PIN_b1, 60);
  servoWrite(2, LEG3_FEMUR_PIN_b2, 60);
  delay(500);

  servoWrite(2, LEG1_COXA_PIN_b2, 90);  //
  servoWrite(1, LEG4_COXA_PIN_b1, 90);  //
  servoWrite(2, LEG5_COXA_PIN_b2, 90);  //
  servoWrite(1, LEG2_COXA_PIN_b1, 90);
  servoWrite(1, LEG6_COXA_PIN_b1, 90);
  servoWrite(2, LEG3_COXA_PIN_b2, 90);
  delay(500);
  gait1LayStatus = true;
}

void gait2Lay() {
  servoWrite(2, LEG1_FEMUR_PIN_b2, 60);
  servoWrite(1, LEG4_FEMUR_PIN_b1, 60);
  servoWrite(2, LEG5_FEMUR_PIN_b2, 60);
  servoWrite(1, LEG2_FEMUR_PIN_b1, 10);  //
  servoWrite(1, LEG6_FEMUR_PIN_b1, 10);  //
  servoWrite(2, LEG3_FEMUR_PIN_b2, 10);  //
  delay(500);
  servoWrite(2, LEG1_TIBIA_PIN_b2, 10);  //
  servoWrite(1, LEG4_TIBIA_PIN_b1, 10);  //
  servoWrite(2, LEG5_TIBIA_PIN_b2, 10);  //
  servoWrite(1, LEG2_TIBIA_PIN_b1, 10);
  servoWrite(2, LEG3_TIBIA_PIN_b2, 10);
  servoWrite(1, LEG6_TIBIA_PIN_b1, 10);

  delay(500);
  servoWrite(2, LEG1_COXA_PIN_b2, 90);  //
  servoWrite(1, LEG4_COXA_PIN_b1, 90);  //
  servoWrite(2, LEG5_COXA_PIN_b2, 90);  //
  servoWrite(1, LEG2_COXA_PIN_b1, 70);
  servoWrite(1, LEG6_COXA_PIN_b1, 70);
  servoWrite(2, LEG3_COXA_PIN_b2, 70);
  delay(500);
  //--------------------------------------------
  servoWrite(2, LEG1_FEMUR_PIN_b2, 60);  //
  servoWrite(1, LEG4_FEMUR_PIN_b1, 60);  //
  servoWrite(2, LEG5_FEMUR_PIN_b2, 60);  //
  servoWrite(1, LEG2_FEMUR_PIN_b1, 60);
  servoWrite(1, LEG6_FEMUR_PIN_b1, 60);
  servoWrite(2, LEG3_FEMUR_PIN_b2, 60);
  delay(500);

  servoWrite(2, LEG1_COXA_PIN_b2, 90);  //
  servoWrite(1, LEG4_COXA_PIN_b1, 90);  //
  servoWrite(2, LEG5_COXA_PIN_b2, 90);  //
  servoWrite(1, LEG2_COXA_PIN_b1, 90);
  servoWrite(1, LEG6_COXA_PIN_b1, 90);
  servoWrite(2, LEG3_COXA_PIN_b2, 90);
  delay(500);
  gait2LayStatus = true;
}


void rotateLeft() {
  servoWrite(2, LEG1_FEMUR_PIN_b2, 50);  //
  servoWrite(1, LEG4_FEMUR_PIN_b1, 50);  //
  servoWrite(2, LEG5_FEMUR_PIN_b2, 50);  //
  servoWrite(1, LEG2_FEMUR_PIN_b1, 90);
  servoWrite(1, LEG6_FEMUR_PIN_b1, 90);
  servoWrite(2, LEG3_FEMUR_PIN_b2, 90);
  delay(500);
  servoWrite(2, LEG1_TIBIA_PIN_b2, 10);  //
  servoWrite(1, LEG4_TIBIA_PIN_b1, 10);  //
  servoWrite(2, LEG5_TIBIA_PIN_b2, 10);  //
  servoWrite(1, LEG2_TIBIA_PIN_b1, 10);
  servoWrite(2, LEG3_TIBIA_PIN_b2, 10);
  servoWrite(1, LEG6_TIBIA_PIN_b1, 10);

  delay(500);
  servoWrite(2, LEG1_COXA_PIN_b2, 70);  //
  servoWrite(1, LEG4_COXA_PIN_b1, 110);  //
  servoWrite(2, LEG5_COXA_PIN_b2, 70);  //
  servoWrite(1, LEG2_COXA_PIN_b1, 90);
  servoWrite(1, LEG6_COXA_PIN_b1, 90);
  servoWrite(2, LEG3_COXA_PIN_b2, 90);
  delay(500);
  //--------------------------------------------
  servoWrite(2, LEG1_FEMUR_PIN_b2, 90);  //
  servoWrite(1, LEG4_FEMUR_PIN_b1, 90);  //
  servoWrite(2, LEG5_FEMUR_PIN_b2, 90);  //
  servoWrite(1, LEG2_FEMUR_PIN_b1, 90);
  servoWrite(1, LEG6_FEMUR_PIN_b1, 90);
  servoWrite(2, LEG3_FEMUR_PIN_b2, 90);
  delay(500);

  servoWrite(2, LEG1_COXA_PIN_b2, 90);  //
  servoWrite(1, LEG4_COXA_PIN_b1, 90);  //
  servoWrite(2, LEG5_COXA_PIN_b2, 90);  //
  servoWrite(1, LEG2_COXA_PIN_b1, 90);
  servoWrite(1, LEG6_COXA_PIN_b1, 90);
  servoWrite(2, LEG3_COXA_PIN_b2, 90);
  delay(1500);

  servoWrite(2, LEG1_FEMUR_PIN_b2, 90);
  servoWrite(1, LEG4_FEMUR_PIN_b1, 90);
  servoWrite(2, LEG5_FEMUR_PIN_b2, 90);
  servoWrite(1, LEG2_FEMUR_PIN_b1, 50);  //
  servoWrite(1, LEG6_FEMUR_PIN_b1, 50);  //
  servoWrite(2, LEG3_FEMUR_PIN_b2, 50);  //
  delay(500);
  servoWrite(2, LEG1_TIBIA_PIN_b2, 10);  //
  servoWrite(1, LEG4_TIBIA_PIN_b1, 10);  //
  servoWrite(2, LEG5_TIBIA_PIN_b2, 10);  //
  servoWrite(1, LEG2_TIBIA_PIN_b1, 10);
  servoWrite(2, LEG3_TIBIA_PIN_b2, 10);
  servoWrite(1, LEG6_TIBIA_PIN_b1, 10);

  delay(500);
  servoWrite(2, LEG1_COXA_PIN_b2, 90);  //
  servoWrite(1, LEG4_COXA_PIN_b1, 90);  //
  servoWrite(2, LEG5_COXA_PIN_b2, 90);  //
  servoWrite(1, LEG2_COXA_PIN_b1, 110);
  servoWrite(1, LEG6_COXA_PIN_b1, 110);
  servoWrite(2, LEG3_COXA_PIN_b2, 70);
  delay(500);
  //--------------------------------------------
  servoWrite(2, LEG1_FEMUR_PIN_b2, 90);  //
  servoWrite(1, LEG4_FEMUR_PIN_b1, 90);  //
  servoWrite(2, LEG5_FEMUR_PIN_b2, 90);  //
  servoWrite(1, LEG2_FEMUR_PIN_b1, 90);
  servoWrite(1, LEG6_FEMUR_PIN_b1, 90);
  servoWrite(2, LEG3_FEMUR_PIN_b2, 90);
  delay(500);

  servoWrite(2, LEG1_COXA_PIN_b2, 90);  //
  servoWrite(1, LEG4_COXA_PIN_b1, 90);  //
  servoWrite(2, LEG5_COXA_PIN_b2, 90);  //
  servoWrite(1, LEG2_COXA_PIN_b1, 90);
  servoWrite(1, LEG6_COXA_PIN_b1, 90);
  servoWrite(2, LEG3_COXA_PIN_b2, 90);
  delay(800);


}










