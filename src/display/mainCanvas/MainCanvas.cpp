#include <Arduino.h>
#include "MainCanvas.h"
#include "../pacman/PacManCanvas.h"
#include "../tetris/TetrisCanvas.h"
#include "main.h"

// Number of pages of the Main Menu
#define NUM_OF_PAGES 2

MAIN_MENU_ENTRY *pages[] = {new PACMAN_MENU_ENTRY(), new TETRIS_MENU_ENTRY()};
bool forceUpdate = false;
MAIN_CANVAS *instance = new MAIN_CANVAS();

MAIN_CANVAS *getMainCanvasInstance()
{
    return instance;
}

void MAIN_CANVAS::drawScreen(Adafruit_ILI9341 tft, long frame)
{
    if (frame == 0 || forceUpdate)
        pages[page]->drawPage(tft, frame);
    if (forceUpdate)
        forceUpdate = false;
}
void MAIN_CANVAS::onSelect()
{
    pages[page]->onSelect();
}

void MAIN_CANVAS::handleJoyStick(int x, int y, double angle)
{
    if (x > 0)
    {
        this->page++;
        if (this->page >= NUM_OF_PAGES)
            this->page = NUM_OF_PAGES - 1;
    }
    if (x < 0)
    {
        this->page--;
        if (this->page < 0)
            this->page = 0;
    }
    Serial.print("Page: ");
    Serial.println(this->page);
    forceUpdate = true;
}
void MAIN_CANVAS::handleBTN1()
{
    this->onSelect();
}
void MAIN_CANVAS::handleBTN2()
{
}
