/*********************************************************************
  This is an example for our Monochrome OLEDs based on SH110X drivers
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define i2c_Address 0x3c // Initialize with the I2C addr 0x3C
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   // Reset pin

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Function prototypes
void showEyeAnimation();
void displayMessages();

void setup() {
  Serial.begin(9600);
  delay(250); // Wait for the OLED to power up
  display.begin(i2c_Address, true); // Initialize display

  display.clearDisplay();

  // Show initial messages
  displayMessages();

  // Start eye animation
  showEyeAnimation();
}

void loop() {
  // No need to do anything here; animation runs in showEyeAnimation()
}

void displayMessages() {
  display.setTextSize(2); // Increased font size for better visibility
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 1);
  display.println("Waking up ..."); // Funny message
  display.display();
  delay(2000);
  
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Good day"); // Greeting message
  display.setCursor(0, 16); // Move cursor down for the second line
  display.println("Boss"); // Greeting message
  display.display();
  delay(2000);
  
  display.clearDisplay();
  display.println("ONESTEP"); // Final message before animation
  display.display();
  delay(2000);
  
  display.clearDisplay();
}

void showEyeAnimation() {
  while (true) { // Loop forever for the animation
    // Draw eyes open
    display.clearDisplay();
    drawEyes(true); // Draw open eyes
    display.display();
    delay(2000); // Increased delay before closing eyes (1 second)

    // Draw eyes closed
    display.clearDisplay();
    drawEyes(false); // Draw closed eyes
    display.display();
    delay(1000); // Increased delay while eyes are closed (1.5 seconds)
  }
}

void drawEyes(bool open) {
  int eyeY = 30; // Increased Y position of the eyes for more space
  int leftEyeX = 36; // X position of the left eye
  int rightEyeX = 94; // X position of the right eye
  int eyeRadius = 15; // Increased radius of the eyes
  
  // Draw left eye
  if (open) {
    display.fillCircle(leftEyeX, eyeY, eyeRadius, SH110X_WHITE); // Open eye
  } else {
    display.fillCircle(leftEyeX, eyeY, eyeRadius, SH110X_BLACK); // Closed eye
  }
  
  // Draw right eye
  if (open) {
    display.fillCircle(rightEyeX, eyeY, eyeRadius, SH110X_WHITE); // Open eye
  } else {
    display.fillCircle(rightEyeX, eyeY, eyeRadius, SH110X_BLACK); // Closed eye
  }
}
