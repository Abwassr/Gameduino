#include "main.h"
#include <Arduino.h>
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "Pins.h"
#include "display/PageManager.h"
#include "display/mainCanvas/MainCanvas.h"
#include "Utils.h"
#include "display/pacman/PacManCanvas.h"
#include "Esp.h"

PageManager pm = PageManager();
CANVAS *currentlyDisplayed = nullptr;

// ! HEY FALLS DER ESP JETZT NICHT FUNKTIONIERT,
// ! CHECK DIE "Pins.h", falls das Problem weiterhin besteht, Pins direkt in "PageManager.h" eintragen!

void setup()
{
  Wire.begin();
  Serial.begin(9600); // Initialisiert die Serielle Kommunikation
  Serial.print("ESP.getBootMode(); ");
  Serial.println(ESP.getBootMode());
  Serial.print("ESP.getSdkVersion(); ");
  Serial.println(ESP.getSdkVersion());
  Serial.print("ESP.getBootVersion(); ");
  Serial.println(ESP.getBootVersion());
  Serial.print("ESP.getChipId(); ");
  Serial.println(ESP.getChipId());
  Serial.print("ESP.getFlashChipSize(); ");
  Serial.println(ESP.getFlashChipSize());
  Serial.print("ESP.getFlashChipRealSize(); ");
  Serial.println(ESP.getFlashChipRealSize());
  Serial.print("ESP.getFlashChipSizeByChipId(); ");
  Serial.println(ESP.getFlashChipSizeByChipId());
  Serial.print("ESP.getFlashChipId(); ");
  Serial.println(ESP.getFlashChipId());
  Serial.print("ESP.getFreeHeap(); ");
  Serial.println(ESP.getFreeHeap());
  delay(1000);
  pm.init();                          // Initialisiert den Bildschirm
  Serial.println("TFT initialized!"); // Gibt im Seriellen Monitor

  Serial.println(HALF_LCD_HEIGHT);
  Serial.println(HALF_LCD_WIDTH);
  //currentlyDisplayed = new MAIN_CANVAS();
  currentlyDisplayed = new PACMAN_CANVAS();

  delay(2000);
}

double recursiveAngle(double angle)
{
  if (angle < -180)
  {
    return recursiveAngle(angle + 360);
  }
  if (angle > 180)
  {
    return recursiveAngle(angle - 360);
  }
  return angle;
}

void loop()
{
  long start = millis();
  Wire.requestFrom(8, 16); //! MAYBE 17
  String joyStr = "";
  while (Wire.available())
  {                       // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
    joyStr.concat(c);
  }
  joyStr.replace("_", "");
  String joy_y_str = joyStr.substring(0, joyStr.indexOf(":"));
  String joy_x_str = joyStr.substring(joyStr.indexOf(":") + 1, joyStr.length());
  double joy_x = atof(joy_y_str.c_str());
  double joy_y = atof(joy_x_str.c_str());
  double angle = recursiveAngle((atan2(joy_x, (joy_y == 0 ? 0.01 : joy_y)) * 180 / PI) - 90);
  bool strongEnougth = abs(joy_x) > 200 || abs(joy_y) > 200;
  if (VERBOSE)
  {
    String message = "";
    message.concat("[");
    message.concat(strongEnougth ? "X" : " ");
    message.concat("] \t");
    message.concat(joy_y);
    message.concat(" : ");
    message.concat(joy_x);
    message.concat(" ? ");
    message.concat(angle);
    message.concat("°");
    Serial.println(message.c_str());
  }

  //* Only memory leak in main.cpp
  // ! HEAP LEAK WITH PAC_MAN(): 48-64hpc WITH MAIN_CANVAS(): 16hpc
  //// FIX in PageManager: LEAK WITH PAC_MAN(): EXCEPTION  WITH MAIN_CANVAS(): 0hpc

  pm.showCanvas(currentlyDisplayed);
  if (strongEnougth)
    currentlyDisplayed->handleJoyStick(joy_x, joy_y, angle);
  while (millis() - start < (1000 / FPS))
    ;
}

PageManager getPageManager()
{
  return pm;
}
void setCurrentlyDisplayedCanvas(CANVAS *canvas)
{
  currentlyDisplayed = canvas;
}
CANVAS *getCurrentlyDisplayedCanvas()
{
  return currentlyDisplayed;
}