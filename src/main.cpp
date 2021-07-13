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

PageManager pm = PageManager();
CANVAS *currentlyDisplayed = nullptr;

// ! HEY FALLS DER ESP JETZT NICHT FUNKTIONIERT,
// ! CHECK DIE "Pins.h", falls das Problem weiterhin besteht, Pins direkt in "PageManager.h" eintragen!

void setup()
{
  Serial.begin(9600); // Initialisiert die Serielle Kommunikation
  delay(1000);
  pm.init();                          // Initialisiert den Bildschirm
  Serial.println("TFT initialized!"); // Gibt im Seriellen Monitor
  Serial.println(HALF_LCD_HEIGHT);
  Serial.println(HALF_LCD_WIDTH);
  //currentlyDisplayed = new MAIN_CANVAS();
  currentlyDisplayed = new PACMAN_CANVAS();
  delay(2000);
}

void loop()
{

  long start = millis();
  //GET JOYSTICK POSITION
  /*int y = analogRead(JOY_X)-512-9;
  int x = analogRead(JOY_Y)-512+5;
  Serial.print("JOY X: ");
  Serial.print(x);
  Serial.print(" JOY Y: ");
  Serial.println(y);
  if(abs(x)>50 || abs(y)>50)
 currentlyDisplayed->handleJoyStick(x,y);*/
  pm.showCanvas(currentlyDisplayed);
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