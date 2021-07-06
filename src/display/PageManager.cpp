#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "Pins.h"
#include "PageManager.h"
#include "mainCanvas/MainCanvas.h"

CANVAS *lastDisplayed = nullptr;
long frame = 0;
long frameTime = 0;

//Adafruit_ILI9341 tft = Adafruit_ILI9341(10, 9, 13, 14, -1, 12);

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, -1, TFT_MISO);

Adafruit_ILI9341 PageManager::getTFT()
{
    return tft;
}

void PageManager::init()
{
    Serial.println("--- END OF TEST ---");
    tft.begin();
    delay(100);
    /*uint8_t x = tft.readcommand8(ILI9341_RDMODE);
    Serial.print("Display Power Mode: 0x");
    Serial.println(x, HEX);
    x = tft.readcommand8(ILI9341_RDMADCTL);
    x = tft.readcommand8(ILI9341_RDPIXFMT);
    Serial.print("Pixel Format: 0x");
    Serial.println(x, HEX);
    x = tft.readcommand8(ILI9341_RDIMGFMT);
    Serial.print("Image Format: 0x");
    Serial.println(x, HEX);
    x = tft.readcommand8(ILI9341_RDSELFDIAG);
    Serial.print("Self Diagnostic: 0x");
    Serial.println(x, HEX);*/
    tft.setRotation(3);
    tft.cp437();

    /*      // CODE FOR TROUBLESHOOTING ROTATION
    tft.fillScreen(ILI9341_BLACK);  
    tft.fillRect(10, 10, 10, 10, ILI9341_RED);
    tft.fillRect(50, 10, 10, 10, ILI9341_GREEN);
    tft.fillRect(50, 50, 10, 10, ILI9341_WHITE);
    tft.fillRect(10, 50, 10, 10, ILI9341_BLUE);
    */
    // Draw Boot
    tft.fillScreen(tft.color565(21, 21, 21));

    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(5);
    int *data2 = getBBoxOfText(tft, CONSOLE_NAME);
    tft.setCursor(data2[2] + 5, data2[3] + 1);
    tft.println(CONSOLE_NAME);

    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(5);
    tft.setCursor(data2[2], data2[3]);
    tft.println(CONSOLE_NAME);

    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(2);
    int *data = getBBoxOfText(tft, DEV_NAME);
    tft.setCursor(data[2] + 2, LCD_HEIGHT - 18);
    tft.println(DEV_NAME);

    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.setCursor(data[2], LCD_HEIGHT - 20);
    tft.println(DEV_NAME);
}

void PageManager::showCanvas(CANVAS *canvas)
{
    if (lastDisplayed != canvas)
    {
        frame = 0;
        lastDisplayed = canvas;
    }

    canvas->drawScreen(tft, frame);
    if (DEBUG)
    {
        tft.fillRect(0, LCD_HEIGHT - 10, LCD_WIDTH, 10, tft.color565(0, 0, 0));
        tft.setCursor(5, LCD_HEIGHT - 10);
        tft.setTextColor(tft.color565(255, 255, 255));
        tft.setTextSize(1);
        tft.print("Frame: ");
        tft.println(frame);
        tft.setCursor(100, LCD_HEIGHT - 10);
        long deltaTime = millis() - frameTime;
        tft.print("FrameTime: ");
        tft.print(deltaTime);
        tft.println("ms");
        tft.setCursor(210, LCD_HEIGHT - 10);
        tft.print("approx. FPS: ");
        tft.println((1000 / deltaTime));
        tft.fillRect(LCD_WIDTH - 10, LCD_HEIGHT - 10, 10, 10, tft.color565(255 * ((1000 / deltaTime) < 10), 255 * ((1000 / deltaTime) >= 10), 0));
        /* if (frame == 0)
        { // ONLY FOR STATIC CONTENT
            tft.fillRect(0, 0, LCD_WIDTH, 10, tft.color565(0, 0, 0));
            tft.setCursor(5, 0);
            // FD = First Draw
            tft.print("TFT: %dx%d, Version: %s, FD: %ldms@%ldfps", LCD_WIDTH, LCD_HEIGHT, VERSION, deltaTime, (1000 / deltaTime));
            tft.print("Version: ", LCD_WIDTH, LCD_HEIGHT, VERSION, deltaTime, (1000 / deltaTime));
        }*/
    }
    frame++;
    frameTime = millis();
}