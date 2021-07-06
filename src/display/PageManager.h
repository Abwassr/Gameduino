#pragma once

#include "Wire.h"
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "Utils.h"
#include "Canvas.h"
#include "Game.h"
class PageManager
{
public:
    int numberOfPages();
    void init();
    void goToPage(int page);
    void nextPage();
    void prevPage();
    void drawPageScreen();
    void showCanvas(CANVAS *canvas);
    Adafruit_ILI9341 getTFT();

private:
    int page = 0;
};
