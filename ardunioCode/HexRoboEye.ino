#include "U8glib.h"

U8GLIB_SH1106_128X64 oled(U8G_I2C_OPT_NONE);  // Initialize OLED display

// Updated Eye positions and dimensions
const int centerX = 64;   // Center X of the spider's face
const int centerY = 32;   // Center Y of the spider's face
const int largeEyeRadius = 14;  // Larger radius for central eyes
const int smallEyeRadius = 8;   // Larger radius for small eyes
const int eyeSpacing = 22;      // Increased spacing between eyes

void drawSpiderEyesOpen() {
  // Draw central large eyes (open)
  oled.drawDisc(centerX - eyeSpacing, centerY, largeEyeRadius);  // Left large eye
  oled.drawDisc(centerX + eyeSpacing, centerY, largeEyeRadius);  // Right large eye

  // Draw smaller surrounding eyes (open)
  oled.drawDisc(centerX - 2 * eyeSpacing, centerY - eyeSpacing, smallEyeRadius);  // Top-left small eye
  oled.drawDisc(centerX + 2 * eyeSpacing, centerY - eyeSpacing, smallEyeRadius);  // Top-right small eye
  oled.drawDisc(centerX - 2 * eyeSpacing, centerY + eyeSpacing, smallEyeRadius);  // Bottom-left small eye
  oled.drawDisc(centerX + 2 * eyeSpacing, centerY + eyeSpacing, smallEyeRadius);  // Bottom-right small eye
}

void drawSpiderEyesClosed() {
  // Draw lines to represent closed eyes (bigger lines for larger eyes)
  oled.drawLine(centerX - eyeSpacing - largeEyeRadius, centerY, centerX - eyeSpacing + largeEyeRadius, centerY);  // Left large eye closed
  oled.drawLine(centerX + eyeSpacing - largeEyeRadius, centerY, centerX + eyeSpacing + largeEyeRadius, centerY);  // Right large eye closed

  // Smaller eyes closed (lines)
  oled.drawLine(centerX - 2 * eyeSpacing - smallEyeRadius, centerY - eyeSpacing, centerX - 2 * eyeSpacing + smallEyeRadius, centerY - eyeSpacing);  // Top-left small eye closed
  oled.drawLine(centerX + 2 * eyeSpacing - smallEyeRadius, centerY - eyeSpacing, centerX + 2 * eyeSpacing + smallEyeRadius, centerY - eyeSpacing);  // Top-right small eye closed
  oled.drawLine(centerX - 2 * eyeSpacing - smallEyeRadius, centerY + eyeSpacing, centerX - 2 * eyeSpacing + smallEyeRadius, centerY + eyeSpacing);  // Bottom-left small eye closed
  oled.drawLine(centerX + 2 * eyeSpacing - smallEyeRadius, centerY + eyeSpacing, centerX + 2 * eyeSpacing + smallEyeRadius, centerY + eyeSpacing);  // Bottom-right small eye closed
}

void showWakeUpMessage() {
  oled.firstPage();
  do {
    oled.setFont(u8g_font_unifont);  // Use a readable font
    oled.drawStr(10, 20, "I... am...");  // First part of the message
    oled.drawStr(10, 40, "waking up...");  // Funny robot "wake-up" message
  } while(oled.nextPage());
  delay(2500);  // Hold the message for 2 seconds
  
  oled.firstPage();
  do {
    oled.setFont(u8g_font_unifont);  // Use the same font
    oled.drawStr(10, 30, "Good day Boss!");  // Show "Good day Boss"
  } while(oled.nextPage());
  delay(2000);  // Hold the message for 2 seconds

  oled.firstPage();
  do {
    oled.setFont(u8g_font_unifont);  // Use the same font
    oled.drawStr(30, 40, "ONESTEP");  // Show "Onestep!"
  } while(oled.nextPage());
  delay(2000);  // Hold the message for 2 seconds
}

void setup(void) {
  // Initialize OLED display and show the wake-up sequence
  showWakeUpMessage();

  // Now start with the spider eyes open after messages
  oled.firstPage();
  do {
    drawSpiderEyesOpen();  // Start with spider eyes open
  } while(oled.nextPage());
  delay(1000);
}

void loop(void) {
  // Animation loop: spider eyes open and closed
  oled.firstPage();
  do {
    drawSpiderEyesClosed();  // Spider eyes closed
  } while(oled.nextPage());
  delay(1000);

  oled.firstPage();
  do {
    drawSpiderEyesOpen();    // Spider eyes open
  } while(oled.nextPage());
  delay(1000);
}
